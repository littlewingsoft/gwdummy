// ChatClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ChatClientDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChatClientDlg ��ȭ ����
extern map<WORD,CHAR_DATA> g_UserMap;

unsigned __stdcall ThreadProc(void *lp)
{
	CChatClientDlg* pMain = (CChatClientDlg*)lp;

	char szlog[64]; memset(szlog, 0x00, sizeof(szlog));
	char buf[1024]; memset(buf, 0x00, sizeof(buf));

	while(true)
	{
		if(pMain->m_bStatus == 0x00) {
			Sleep(100);
			continue;
		}
		while( !pMain->m_ASocket.IsDataArrived())
		{
			Sleep(100);
			continue;
		}

		memset(buf, 0x00, sizeof(buf));
		int n = pMain->m_ASocket.RecvData( buf, sizeof( buf ) );
		if ( n == SOCKET_ERROR ) 
		{
			int err = GetLastError();
			if(err != ERROR_IO_PENDING) {
				pMain->m_ASocket.CloseSocket();
				pMain->m_bStatus = 0x00;
				pMain->m_ChatList.AddString("closed to server.");
				Sleep(100);
				continue;
			}
		}
		else
		{
			pMain->m_ASocket.ReceivedData(buf, n);

			bool retval = false;
			char tempbuff[_PACKET_MTU] = {0,};
			DWORD dwGetLen = 0;
			do {
				memset(tempbuff, 0x00, sizeof(tempbuff));
				retval = pMain->m_ASocket.PullOutCore(tempbuff, dwGetLen);
				if(retval) {
					// Packet Dispatch...
					PACKET_BASE* pPacket = (PACKET_BASE*)tempbuff;
					pMain->Process(pPacket);
				}
			} while(retval);
		}
	}

	return 1;
}


CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
	, m_strChat(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bStatus = 0x00;
	m_wSid = -1;
	memset(m_szUserID, 0x00, sizeof(m_szUserID));
	memset(m_szPwd, 0x00, sizeof(m_szPwd));
}

CChatClientDlg::~CChatClientDlg()
{
	if(!m_UserArray.IsEmpty()) 
		m_UserArray.DeleteAllData();
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHATLIST, m_ChatList);
	DDX_Control(pDX, IDC_USERLIST, m_UserList);
	DDX_Text(pDX, IDC_CHATEDIT, m_strChat);
	DDX_Control(pDX, IDC_CHATEDIT, m_ChatEdit);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_UPDATEDATA, OnUpdateData)
	ON_MESSAGE(WM_USERCLOSE, OnUserClose)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()




BOOL CChatClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	UINT	WorkerID = 0;
	m_hThread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, ThreadProc, (LPVOID)this, 0, &WorkerID));
	
	TCHAR szPath[_MAX_PATH] = {0,};
	TCHAR Buf[_MAX_PATH] = {0, };
	TCHAR szIniPath[_MAX_PATH] = {0,};
	TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	::GetModuleFileName(AfxGetApp()->m_hInstance, Buf, _MAX_PATH);
	_splitpath(Buf,drive,dir,fname,ext);
	_tcscpy(szPath, drive);
	_tcscat(szPath, dir);		
//	sprintf(szIniPath, _T("%s%s"), szPath, _T("server.ini"));

	//GetPrivateProfileString("SERVER", "IP", "127.0.0.1", m_szServerIP, MAX_IP_SIZE, szIniPath);
	//m_nPort = GetPrivateProfileInt( "SERVER" , "PORT" , RELAY_PORT, szIniPath);
		// Lua �� �ʱ�ȭ �Ѵ�.
		// LuaTinker �� �̿��ؼ� �Լ��� ����Ѵ�.
	luaGlue::setting();

	int port = lua_tinker::get<int>( luaGlue::g_hLua, "PORT" );
	char* ip = lua_tinker::get<char*>( luaGlue::g_hLua, "IP" );
	m_ASocket.ConnectSocket( ip, port );

	Sleep(100);

	int count = 0;
	while( !m_ASocket.IsConnected() ) {
		Sleep(100);
		count++;
		if( count > 10) {
			AfxMessageBox("connot connect to server!!");
			PostQuitMessage(0);
			return FALSE;
		}
	}

	m_bStatus = 0x01;

	sprintf_s( m_szUserID,_MAX_USER_ID_SIZE,"%s",lua_tinker::get<char*>( luaGlue::g_hLua,"ID") );
	sprintf_s( m_szPwd,_MAX_USER_ID_SIZE,"%s",lua_tinker::get<char*>( luaGlue::g_hLua,"PASS") );


	LS_PKT_LOGIN pkt_login;
	pkt_login.MPID = _LS_PKT_LOGIN;
	pkt_login.Len = sizeof(LS_PKT_LOGIN);
	pkt_login.FROM = _FROM_CLIENT;
	strcpy(pkt_login.szUserID, m_szUserID);
	strcpy(pkt_login.szPwd, m_szPwd);

	if(m_ASocket.SendData(&pkt_login, pkt_login.Len)==false) {
		AfxMessageBox("Login fail.");
	}

	this->SetWindowText( theApp.m_lpCmdLine );

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CChatClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatClientDlg::RefreshUserList()
{
	int cnt = m_UserList.GetCount();
	for( int n=cnt ; n>=0 ; n-- )
		m_UserList.DeleteString(n);

	map<WORD,CHAR_DATA>::iterator it = g_UserMap.begin();
	while( it != g_UserMap.end() )
	{
		const CHAR_DATA& kData = (*it).second;

		char dst[64]={0,};
		int retLength = WideCharToMultiByte(CP_ACP, 0, 
		kData.szCharName, _MAX_CHAR_ID_SIZE, dst, 64, 0,0);

		stringstream ss;
		ss<<dst<<"("<<(WORD)(*it).first<<")";
		m_UserList.AddString( ss.str().c_str() );
		it++;
	}
}



BOOL CChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == LB_ADDSTRING )
	{
		HWND pkret ;
		GetDlgItem( IDC_CHATLIST, &pkret );
		if( pMsg->hwnd == pkret )
		{
		int a=0;
		}
	}

	if( pMsg->message == WM_KEYDOWN ) {
		if( pMsg->wParam == VK_ESCAPE )
			return TRUE;
		if(pMsg->wParam == VK_RETURN ) {
			UpdateData(TRUE);
			if(m_strChat.GetLength()) {
				if( m_strChat =="/cls" )
				{
					m_ChatList.ResetContent();
					return TRUE;
				}

				

				m_ChatEdit.SetSel(0, -1, TRUE);
			    m_ChatEdit.Clear();
				
			}

			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

LONG CChatClientDlg::OnUpdateData(UINT wParam, LONG lParam)
{
	int nCount = m_ChatList.GetCount();
	m_ChatList.SetCurSel(nCount-1);

	UpdateData(FALSE);

	return 0L;
}

LONG CChatClientDlg::OnUserClose(UINT wParam, LONG lParam)
{
	PostQuitMessage(0);

	return 0L;
}
void CChatClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if( nIDEvent == 1024 )
	{
		GS_PKT_ALIVE	send;
		send.Len = sizeof(GS_PKT_ALIVE);
		send.FROM = _FROM_CLIENT;
		m_ASocket.SendData(&send, send.Len);		
		}
	else

	if( luaGlue::timerID == nIDEvent )
	{
		lua_tinker::call<void >(luaGlue::g_hLua,"OnTimer" );
	}


	CDialog::OnTimer(nIDEvent);
}

void CChatClientDlg::OnBnClickedButton1()
{
	luaGlue::setting();
}
