// CExportParam.cpp: 实现文件
//

#include "stdafx.h"
#include "vcwh8.h"
#include "CExportParam.h"
#include "afxdialogex.h"
#include "vcwh8Dlg.h"

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
	ON_BN_CLICKED(IDC_BUTTON1, &CExportParam::OnBnClickedButton1)
END_MESSAGE_MAP()


// CExportParam 消息处理程序


void CExportParam::OnBnClickedButton1()
{
	Cvcwh8Dlg *pDlg = (Cvcwh8Dlg*)AfxGetMainWnd();
	int nCount = pDlg->m_param_list.GetItemCount();//获取列表中数据项个数
	CString strText;
	strText.Format(TEXT("第%d行，第1列"), nCount + 1);//要插入的数据
	pDlg->m_param_list.InsertItem(nCount, strText, 0);            //插入行
	strText.Format(TEXT("第%d行，第2列"), nCount + 1);//要插入的数据...
	pDlg->m_param_list.SetItemText(nCount, 1, strText); 
	strText.Format(TEXT("第%d行，第3列"), nCount + 1);//要插入的数据
	pDlg->m_param_list.SetItemText(nCount, 2, strText); 
}
