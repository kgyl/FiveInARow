#pragma once
#include "resource.h"
#include "afxdialogex.h"
#include "UserManager.h"

class CRankDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDialog)

public:
	CRankDialog(UserManager* mgr, CWnd* pParent = nullptr);
	virtual ~CRankDialog();

	enum { IDD = IDD_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

private:
	UserManager* m_userManager;
	CListCtrl m_listCtrl;
};
