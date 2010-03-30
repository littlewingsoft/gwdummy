// ChatClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChatClientDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChatClientDlg 대화 상자
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

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
		// Lua 를 초기화 한다.
		// LuaTinker 를 이용해서 함수를 등록한다.
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

	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
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
