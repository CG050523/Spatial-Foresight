// AboutDlg.cpp: 实现文件
//

#include "pch.h"
#include "spatial_foresight.h"
#include "afxdialogex.h"
#include "AboutDlg.h"


// AboutDlg 对话框

IMPLEMENT_DYNAMIC(AboutDlg, CDialogEx)

AboutDlg::AboutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void AboutDlg::setText()
{
	
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialogEx)
END_MESSAGE_MAP()


// AboutDlg 消息处理程序
