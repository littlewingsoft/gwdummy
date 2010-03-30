// ChatClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#define WM_USERCLOSE	(WM_USER+500)
#define WM_UPDATEDATA	(WM_USER+501)

struct _USER_INFO 
{
	WORD	wSid;
	TCHAR	szUserID[_MAX_USER_ID_SIZE];
	_USER_INFO() {
		memset(this, 0x00, sizeof(_USER_INFO));
	}
};

typedef CSTLMap	<WORD, _USER_INFO>	CUserArray;

// CChatClientDlg 대화 상자
class CChatClientDlg : public CDialog
{
// 생성
public:
	CChatClientDlg(CWnd* pParent = NULL);	// 표준 생성자
	virtual ~CChatClientDlg();

// 대화 상자 데이터
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원

	void RefreshUserList();
// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LONG OnUpdateData(UINT wParam, LONG lParam);
	afx_msg LONG OnUserClose(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
public:
	void Process(PACKET_BASE* pPacket);

	TCHAR	m_szUserID[_MAX_USER_ID_SIZE];
	TCHAR	m_szPwd[_MAX_USER_ID_SIZE];

	CAsynSocket		m_ASocket;
	HANDLE			m_hThread;
	BYTE			m_bStatus;
	WORD			m_wSid;

	TCHAR			m_szServerIP[_MAX_IP_SIZE];
	UINT			m_nPort;
	CListBox m_ChatList;
	CListBox m_UserList;

	CUserArray	m_UserArray;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_strChat;
	string m_szSession;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	CEdit m_ChatEdit;
};
