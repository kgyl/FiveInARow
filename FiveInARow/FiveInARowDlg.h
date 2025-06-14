#pragma once
#include"CChessManager.h"
#include "AIPlayer.h"	//引入AI
#include "UserManager.h" //引入用户管理
#include "UserInfo.h"   //引入用户信息
#include <atlimage.h>
class CFiveInARowDlg : public CDialogEx
{
	CChessManager m_Manager;        
	CFont m_FontTimer;
	CFont m_FontOver;
	int m_iTime;
	int m_iTimeBlack = 0;
	int m_iTimeWhite = 0;
	bool m_bState;
	CImage m_bkImage;       // 背景图像
	bool m_hasCustomBk = false; // 是否已加载背景
	bool AIflag = false;	//是否启用AI
	AIPlayer ai;
	UserManager m_userManager;
	bool m_loggedIn = false;     // 是否已登录（建议添加）
	UserInfo m_currentUser;
public:
	CFiveInARowDlg(CWnd* pParent = NULL);	
	enum { IDD = IDD_FIVEINAROW_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	
protected:
	HICON m_hIcon;
    virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//bool NewGame(int x,int y);
	void playMusic();
	void HandleGameOver();
	void AIPlay();
	afx_msg LRESULT OnMciNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonNewgame();
	afx_msg void OnBnClickedButtonIntroduction();
	afx_msg void OnBnClickedButtonChoosebg();
	afx_msg void OnBnClickedButtonPlaymusic();
	afx_msg void OnBnClickedButtonStopmusic();
	afx_msg void OnBnClickedButtonWithdraw();
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonScreenshot();
	afx_msg void OnBnClickedButtonSavegame();
	afx_msg void OnBnClickedButtonLoadgame();
	afx_msg void OnBnClickedButtonStartai();
	afx_msg void OnBnClickedButtonCloseai();
	afx_msg void OnBnClickedButtonRank();
	afx_msg void OnBnClickedButtonUser();
};