#pragma once
#include "afxdialogex.h"
#include "UserManager.h"


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CString m_username, m_password;
	UserManager* m_userManager;
	UserInfo m_loggedInUser;

	CLoginDlg(UserManager* mgr, CWnd* pParent = nullptr);
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Login_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonRegister();
};
