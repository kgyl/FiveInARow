#include "stdafx.h"
#include "CRankDialog.h"
#include "afxdialogex.h"
#include<algorithm>
#include<string>
IMPLEMENT_DYNAMIC(CRankDialog, CDialogEx)

CRankDialog::CRankDialog(UserManager* mgr, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RANK_DIALOG, pParent), m_userManager(mgr)
{
}

CRankDialog::~CRankDialog() {}

void CRankDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RANK, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CRankDialog, CDialogEx)
END_MESSAGE_MAP()

BOOL CRankDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置列标题
	m_listCtrl.InsertColumn(0, _T("用户名"), LVCFMT_LEFT, 120);
	m_listCtrl.InsertColumn(1, _T("胜场"), LVCFMT_CENTER, 60);
	m_listCtrl.InsertColumn(2, _T("败场"), LVCFMT_CENTER, 60);
	m_listCtrl.InsertColumn(3, _T("胜率"), LVCFMT_CENTER, 80);

	// 排序用户列表
	std::vector<UserInfo> users = m_userManager->GetAllUsers();
	std::sort(users.begin(), users.end(), [](const UserInfo& a, const UserInfo& b) {
		int totalA = a.wins + a.losses;
		int totalB = b.wins + b.losses;
		double rateA = totalA ? (double)a.wins / totalA : 0;
		double rateB = totalB ? (double)b.wins / totalB : 0;
		return rateA > rateB;
		});

	// 插入数据
	int index = 0;
	for (auto& user : users)
	{
		CString strRate;
		int total = user.wins + user.losses;
		if (total == 0) strRate = _T("0.00");
		else strRate.Format(_T("%.2f"), (double)user.wins * 100 / total);

		m_listCtrl.InsertItem(index, user.username);
		m_listCtrl.SetItemText(index, 1, CString(std::to_string(user.wins).c_str()));
		m_listCtrl.SetItemText(index, 2, CString(std::to_string(user.losses).c_str()));
		m_listCtrl.SetItemText(index, 3, strRate + _T("%"));
		index++;
	}
	return TRUE;
}
