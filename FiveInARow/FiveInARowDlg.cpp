#include "stdafx.h"
#include "FiveInARow.h"
#include "FiveInARowDlg.h"
#include "afxdialogex.h"
#include "bmpScreen.h"
#include <Windows.h>
#include <mmsystem.h>			  //播放音乐头文件
#pragma comment(lib, "winmm.lib") // 播放音乐库文件
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum
	{
		IDD = IDD_ABOUTBOX
	};
	afx_msg void OnPaint();

protected:
	virtual void DoDataExchange(CDataExchange *pDX); //
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void CAboutDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CBitmap bmp;
    bmp.LoadBitmap(IDB_BITMAP_ABOUT);

    BITMAP bm;
    bmp.GetObject(sizeof(BITMAP), &bm);

    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
    CBitmap* pOldBitmap = memDC.SelectObject(&bmp);

    // 居中绘制图片
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - bm.bmWidth) / 2;
    int y = (rect.Height() - bm.bmHeight) / 2;

    dc.BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);

    memDC.SelectObject(pOldBitmap);
}


CFiveInARowDlg::CFiveInARowDlg(CWnd *pParent /*=NULL*/)
	: CDialogEx(CFiveInARowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CFiveInARowDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CFiveInARowDlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_LBUTTONUP()
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON1, &CFiveInARowDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CFiveInARowDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CFiveInARowDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &CFiveInARowDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CFiveInARowDlg::OnBnClickedButton5)
END_MESSAGE_MAP()
BOOL CFiveInARowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu *pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetWindowPos(NULL, 0, 0, 1024, 768, SWP_NOZORDER | SWP_NOMOVE);
	m_FontTimer.CreatePointFont(250, "Segoe UI Semibold", NULL);
	m_FontOver.CreatePointFont(666, "微软雅黑", NULL);
	m_bState = false;

	return TRUE;
}
void CFiveInARowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
void CFiveInARowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CBitmap bmp;
		BITMAP bm;
		bmp.LoadBitmap(IDB_BITMAP_BK);
		bmp.GetObject(sizeof(BITMAP), &bm);
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		CBitmap *pOldBitmap = MemDC.SelectObject(&bmp);
		dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOldBitmap);
		m_Manager.Show(&dc);
		CDialogEx::OnPaint();
	}
}
HCURSOR CFiveInARowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFiveInARowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (NewGame(point.x, point.y))
		return;
	if (About(point.x, point.y))
		return;
	if (!m_bState)
	{
		AfxMessageBox("请选择【开始】按钮开始新的游戏，按【ESC】键退出游戏");
		return;
	}
	int r = m_Manager.Add(point.x, point.y);
	if (r == 0)
	{
		CClientDC dc(this);
		m_Manager.Show(&dc);
		if (m_Manager.GameOver())
		{
			KillTimer(1);
			CString csTemp;
			if (m_Manager.GetWinner() == WHITE)
				csTemp.Format("白子胜");
			else
				csTemp.Format("黑子胜");
			m_bState = false;
			CClientDC dc(this);
			CFont *pOldFont = dc.SelectObject(&m_FontOver);
			int OLdBkMode = dc.GetBkMode();
			COLORREF OldColor, NewColor1 = RGB(60, 60, 60), NewColor2 = RGB(250, 50, 50);
			dc.SetBkMode(TRANSPARENT);
			OldColor = dc.SetTextColor(NewColor1);
			dc.TextOut(334, 54, csTemp);
			dc.SetTextColor(NewColor2);
			dc.TextOut(330, 50, csTemp);

			dc.SetTextColor(OldColor);
			dc.SetBkMode(OLdBkMode);
			dc.SelectObject(pOldFont);
		}
	}
	if (r == 1)
		AfxMessageBox("请在棋盘交叉点落子");
	else if (r == 2)
		AfxMessageBox("不可以重复落子");
	CDialogEx::OnLButtonUp(nFlags, point);
}
bool CFiveInARowDlg::NewGame(int x, int y)
{
	int x0 = 35, y0 = 150, x1 = 200, y1 = 185;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1))
	{
		m_Manager.NewGame();
		Invalidate();
		m_iTime = 0;
		SetTimer(1, 1000, NULL);
		m_bState = true;
		return true;
	}
	return false;
}

bool CFiveInARowDlg::About(int x, int y)
{
	int x0 = 35, y0 = 70, x1 = 200, y1 = 95;
	if ((x >= x0 && x <= x1) && (y >= y0 && y <= y1))
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return true;
	}
	return false;
}

void CFiveInARowDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		CClientDC dc(this);
		CFont *pOldFont;
		pOldFont = dc.SelectObject(&m_FontTimer);
		m_iTime++;
		CString csTemp;
		csTemp.Format("%04d ", m_iTime);
		int OldBkMode = dc.GetBkMode();
		COLORREF OldColor, NewColor = RGB(150, 50, 50);
		OldColor = dc.SetTextColor(NewColor);
		dc.TextOut(725, 20, csTemp);
		dc.SetTextColor(OldColor);
		dc.SelectObject(pOldFont);
		break;
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CFiveInARowDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetResourceHandle(), SND_ASYNC | SND_RESOURCE | SND_NODEFAULT);
}

void CFiveInARowDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
}

void CFiveInARowDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Manager.m_nChess--;											  // 让最大落子数减1
	m_Manager.m_Color = (m_Manager.m_Color == WHITE ? BLACK : WHITE); // 改变当前即将落子的颜色
	Invalidate();													  // 刷新当前界面 调用onpaint重绘
	UpdateWindow();													  // 消息提前
}

void CFiveInARowDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = AfxMessageBox("要退出程序吗？单击“确定”按钮退出，单击“取消”按钮继续运行！", MB_OKCANCEL | MB_ICONQUESTION);
	if (iRet == IDOK)

		CDialogEx::SendMessage(WM_CLOSE);
}

void CFiveInARowDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// 创建 BmpScreen 类对象
	bmpScreen screen;
	// 调用 screenShot 函数进行截图，并保存到文件中。截图的大小是 1000x800 像素，位置是屏幕左上角的（0, 0）处
	screen.screenShot(1000, 800, 0, 0, "screenshot.bmp");
}
