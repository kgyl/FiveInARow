#pragma once
#include"CChessManager.h"
#include <atlimage.h>
class CFiveInARowDlg : public CDialogEx
{
	CChessManager m_Manager;        
	CFont m_FontTimer;
	CFont m_FontOver;
	int m_iTime;
	bool m_bState;
	CImage m_bkImage;       // ����ͼ��
	bool m_hasCustomBk = false; // �Ƿ��Ѽ��ر���
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonNewgame();
	afx_msg void OnBnClickedButtonIntroduction();
	afx_msg void OnBnClickedButtonChoosebg();
	afx_msg void OnBnClickedButtonPlaymusic();
	afx_msg void OnBnClickedButtonStopmusic();
	afx_msg void OnBnClickedButtonWithdraw();
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonScreenshot();
};