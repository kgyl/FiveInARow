// LoginBox.cpp: 实现文件
//

#include "pch.h"
#include "FiveInARow.h"
#include "afxdialogex.h"
#include "LoginBox.h"


// LoginBox 对话框

IMPLEMENT_DYNAMIC(LoginBox, CDialogEx)

LoginBox::LoginBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Login_DIALOG, pParent)
{

}

LoginBox::~LoginBox()
{
}

void LoginBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginBox, CDialogEx)
END_MESSAGE_MAP()


// LoginBox 消息处理程序
