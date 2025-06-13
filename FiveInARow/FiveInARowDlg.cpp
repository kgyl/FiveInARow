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

// 关于对话框背景绘制
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
ON_BN_CLICKED(IDC_BUTTON_NewGame, &CFiveInARowDlg::OnBnClickedButtonNewgame)
ON_BN_CLICKED(IDC_BUTTON_Introduction, &CFiveInARowDlg::OnBnClickedButtonIntroduction)
ON_BN_CLICKED(IDC_BUTTON_ChooseBG, &CFiveInARowDlg::OnBnClickedButtonChoosebg)
ON_BN_CLICKED(IDC_BUTTON_PlayMusic, &CFiveInARowDlg::OnBnClickedButtonPlaymusic)
ON_BN_CLICKED(IDC_BUTTON_StopMusic, &CFiveInARowDlg::OnBnClickedButtonStopmusic)
ON_BN_CLICKED(IDC_BUTTON_Withdraw, &CFiveInARowDlg::OnBnClickedButtonWithdraw)
ON_BN_CLICKED(IDC_BUTTON_Quit, &CFiveInARowDlg::OnBnClickedButtonQuit)
ON_BN_CLICKED(IDC_BUTTON_Screenshot, &CFiveInARowDlg::OnBnClickedButtonScreenshot)
ON_MESSAGE(MM_MCINOTIFY, &CFiveInARowDlg::OnMciNotify)
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
	m_iTime = 0;

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
        CRect rect;
        GetClientRect(&rect);
        
        if (m_hasCustomBk && m_bkImage.IsNull() == FALSE)
        {
            m_bkImage.StretchBlt(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), SRCCOPY);
        }
        else
        {
			// 默认背景图（从资源或路径加载）
			CImage defaultBk;
			HRESULT hr = defaultBk.Load(_T("res\\IMG_202506095120_1024x768.jpg"));  // 或直接资源 ID

			if (SUCCEEDED(hr))
			{
				defaultBk.StretchBlt(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			}
			else
			{
				AfxMessageBox(_T("默认背景图像加载失败！"));
			}
        }

		// 2. 绘制棋盘线（网格）
		double d = CChess::m_d;
		int dx = CChess::m_dx + d * 0.5;
		int dy = CChess::m_dy + d * 0.5;
		int gridSize = 15;

		CPen pen(PS_SOLID, 3, RGB(0, 0, 0)); // 黑色实线
		CPen* pOldPen = dc.SelectObject(&pen);

		// 横线
		for (int i = 0; i < gridSize; ++i)
		{
			int y = dy + i * d;
			dc.MoveTo(dx, y);
			dc.LineTo(dx + (gridSize - 1) * d, y);
		}

		// 竖线
		for (int j = 0; j < gridSize; ++j)
		{
			int x = dx + j * d;
			dc.MoveTo(x, dy);
			dc.LineTo(x, dy + (gridSize - 1) * d);
		}

		dc.SelectObject(pOldPen);
		pen.DeleteObject();

        m_Manager.Show(&dc);


		// 4. 添加时钟绘制（补充）
		CFont* pOldFont = dc.SelectObject(&m_FontTimer);
		CString csTemp;
		csTemp.Format("%04d", m_iTime);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(150, 50, 50));
		dc.TextOut(725, 20, csTemp);
		dc.SelectObject(pOldFont);

        CDialogEx::OnPaint();
    }
}
HCURSOR CFiveInARowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFiveInARowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bState)
	{
		AfxMessageBox("请选择【开始】按钮开始新的游戏，按【ESC】键退出游戏");
		return;
	}
	int r = m_Manager.Add(point.x, point.y);
	if (r == 0)
	{
		sndPlaySound(MAKEINTRESOURCE(IDR_WAVE2), SND_ASYNC | SND_RESOURCE);
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


void CFiveInARowDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case 1:
		{
			// 触发只更新时钟区域
			m_iTime++;
			CRect timeRect(725, 20, 800, 60); // 根据时钟文本宽度调整
			InvalidateRect(&timeRect, TRUE);  // TRUE 表示重绘前清除背景
			UpdateWindow();                   // 立即触发 OnPaint 重绘
			break;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CFiveInARowDlg::OnMciNotify(WPARAM wParam, LPARAM lParam)
{
	// 只在播放完成时（MCI_NOTIFY_SUCCESSFUL）自动 replay
	if (wParam == MCI_NOTIFY_SUCCESSFUL)
	{
		playMusic();
	}
	return 0;
}

void CFiveInARowDlg::playMusic() {
	TCHAR exePath[MAX_PATH]{ 0 };
	GetModuleFileName(nullptr, exePath, MAX_PATH);
	CString folder = CString(exePath);
	folder = folder.Left(folder.ReverseFind('\\'));

	// 拼接成 res\background_music.wav 的完整路径
	CString bgmPath;
	bgmPath.Format(_T("%s\\res\\background_music.wav"), folder);

	// Debug 输出：检查拼接结果
	//AfxMessageBox(bgmPath);

	// 若文件不存在，提醒
	if (!PathFileExists(bgmPath))
	{
		AfxMessageBox(_T("背景音乐文件不存在！"));
		return;
	}

	// 关闭旧 alias
	mciSendString(_T("close BGM"), nullptr, 0, nullptr);

	// 打开并循环播放
	CString cmd;
	cmd.Format(_T("open \"%s\" type waveaudio alias BGM"), bgmPath);
	//AfxMessageBox(cmd);
	if (mciSendString(cmd, nullptr, 0, nullptr) == 0)
	{
		mciSendString(_T("play BGM notify"), nullptr, 0, m_hWnd);
	}
	else
	{
		AfxMessageBox(_T("背景音乐打开失败！"));
	}
}

void CFiveInARowDlg::OnBnClickedButtonPlaymusic()
{
	playMusic();
}

void CFiveInARowDlg::OnBnClickedButtonStopmusic()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendString(_T("stop BGM"), nullptr, 0, nullptr);
	mciSendString(_T("close BGM"), nullptr, 0, nullptr);
}

void CFiveInARowDlg::OnBnClickedButtonWithdraw()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Manager.m_nChess--;											  // 让最大落子数减1
	m_Manager.m_Color = (m_Manager.m_Color == WHITE ? BLACK : WHITE); // 改变当前即将落子的颜色
	Invalidate();													  // 刷新当前界面 调用onpaint重绘
	UpdateWindow();													  // 消息提前
}

void CFiveInARowDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = AfxMessageBox("要退出程序吗？单击“确定”按钮退出，单击“取消”按钮继续运行！", MB_OKCANCEL | MB_ICONQUESTION);
	if (iRet == IDOK)

		CDialogEx::SendMessage(WM_CLOSE);
}

void CFiveInARowDlg::OnBnClickedButtonScreenshot()
{
	// TODO: 在此添加控件通知处理程序代码
	// 创建 BmpScreen 类对象
	bmpScreen screen;
	// 调用 screenShot 函数进行截图，并保存到文件中。截图的大小是 1000x800 像素，位置是屏幕左上角的（0, 0）处
	screen.screenShot(1000, 800, 0, 0, "screenshot.bmp");
}

// 更换图片
void CFiveInARowDlg::OnBnClickedButtonChoosebg()
{
	CFileDialog dlg(TRUE, _T("图片文件"), NULL, OFN_FILEMUSTEXIST, _T("图片文件 (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png||"));
    if (dlg.DoModal() == IDOK)
    {
        CString path = dlg.GetPathName();

        // 如果之前有图像，释放
        if (!m_bkImage.IsNull())
            m_bkImage.Destroy();

        if (m_bkImage.Load(path) == S_OK)
        {
            m_hasCustomBk = true;
            Invalidate(); // 触发重绘
        }
        else
        {
            AfxMessageBox(_T("加载背景图像失败。"));
        }
    }
}


void CFiveInARowDlg::OnBnClickedButtonNewgame()
{
	m_Manager.NewGame();
	Invalidate();
	m_iTime = 0;
	SetTimer(1, 1000, NULL);
	m_bState = true;
}

void CFiveInARowDlg::OnBnClickedButtonIntroduction()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
