// CExportParam.cpp: 实现文件
//

#include "stdafx.h"
#include "vcwh8.h"
#include "CExportParam.h"
#include "afxdialogex.h"


// CExportParam 对话框

IMPLEMENT_DYNAMIC(CExportParam, CDialogEx)

CExportParam::CExportParam(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EXPORT, pParent)
{

}

CExportParam::~CExportParam()
{
}

void CExportParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExportParam, CDialogEx)
END_MESSAGE_MAP()


// CExportParam 消息处理程序
