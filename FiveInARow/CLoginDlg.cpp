// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FiveInARow.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(UserManager* mgr, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Login_DIALOG, pParent), m_userManager(mgr)
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_username);
	DDX_Text(pDX, IDC_EDIT_PASS, m_password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Login, &CLoginDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_Register, &CLoginDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

void CLoginDlg::OnBnClickedButtonLogin()
{
	UpdateData(TRUE);
	if (m_username.IsEmpty() || m_password.IsEmpty()) {
		AfxMessageBox(_T("请输入用户名和密码！"));
		return;
	}
	if (m_userManager->LoginUser(m_username, m_password, m_loggedInUser)) {
		AfxMessageBox(_T("登录成功！"));
		EndDialog(IDOK);
	}
	else {
		AfxMessageBox(_T("用户名或密码错误！"));
	}
}

void CLoginDlg::OnBnClickedButtonRegister()
{
	UpdateData(TRUE);
	if (m_username.IsEmpty() || m_password.IsEmpty()) {
		AfxMessageBox(_T("请输入用户名和密码！"));
		return;
	}
	if (m_userManager->RegisterUser(m_username, m_password)) {
		AfxMessageBox(_T("注册成功！请点击登录按钮进入游戏"));
	}
	else {
		AfxMessageBox(_T("用户名已存在，请更换用户名"));
	}
}
