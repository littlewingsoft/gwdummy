// LoginDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ChatClient.h"
#include "LoginDlg.h"
#include ".\logindlg.h"


// CLoginDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_szID(_T(""))
	, m_szPwd(_T(""))
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID_EDIT, m_szID);
	DDX_Text(pDX, IDC_PWD_EDIT, m_szPwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg �޽��� ó�����Դϴ�.

void CLoginDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	OnOK();
}
