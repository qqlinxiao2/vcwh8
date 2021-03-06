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
	HWND hWnd = NULL;
	HWND hWnd2 = NULL;
	if (::IsWindow(hWnd) == FALSE)
		hWnd = ::FindWindowEx(NULL, NULL, TEXT("#32770"), TEXT("模型回测报告"));
	hWnd = ::GetDlgItem(hWnd, 1517);
	hWnd = ::GetDlgItem(hWnd, 0);
	hWnd2 = ::GetDlgItem(hWnd, 4068);
	hWnd = ::GetDlgItem(hWnd, 1483);

	int count, i ,j;
	TCHAR item[512] = { 0 }, subitem[512] = { 0 };

	LVITEM lvi, *_lvi;
	TCHAR *_item, *_subitem;
	DWORD pid;
	HANDLE process;
	count = (int)::SendMessage(hWnd, LVM_GETITEMCOUNT, 0, 0);

	GetWindowThreadProcessId(hWnd, &pid);
	process = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ |
		PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, FALSE, pid);

	_lvi = (LVITEM*)VirtualAllocEx(process, NULL, sizeof(LVITEM),
		MEM_COMMIT, PAGE_READWRITE);
	_item = (TCHAR*)VirtualAllocEx(process, NULL, 512, MEM_COMMIT,
		PAGE_READWRITE);
	_subitem = (TCHAR*)VirtualAllocEx(process, NULL, 512, MEM_COMMIT,
		PAGE_READWRITE);

	lvi.cchTextMax = 512;

	for (i = 0; i<count; i++) {
		lvi.iSubItem = 0;
		lvi.pszText = _item;
		WriteProcessMemory(process, _lvi, &lvi, sizeof(LVITEM), NULL);
		::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);

		lvi.iSubItem = 1;
		lvi.pszText = _subitem;
		
		WriteProcessMemory(process, _lvi, &lvi, sizeof(LVITEM), NULL);
		::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);

		ReadProcessMemory(process, _item, item, 512, NULL);
		ReadProcessMemory(process, _subitem, subitem, 512, NULL);
		//
		CString item1;
		item1.Format(TEXT("%s"),item);
		CString item2;
		item2.Format(TEXT("%s"), subitem);
		if (item1 == TEXT("交易合约")) {
			CString countText;
			countText.Format(TEXT("%d"),nCount + 1);
			pDlg->m_param_list.InsertItem(nCount, countText, 0);
			pDlg->m_param_list.SetItemText(nCount, 1, item2);
		}
		if (item1 == TEXT("K线周期")) {
			pDlg->m_param_list.SetItemText(nCount, 2, item2);
		}
		if (item1 == TEXT("模型")) {
			pDlg->m_param_list.SetItemText(nCount, 3, item2);
		}
	}

	CString params;
	for (j = 0; j < 6; j++) {
		lvi.iSubItem = 4;
		lvi.pszText = _item;
		WriteProcessMemory(process, _lvi, &lvi, sizeof(LVITEM), NULL);
		::SendMessage(hWnd2, LVM_GETITEMTEXT, (WPARAM)j, (LPARAM)_lvi);
		ReadProcessMemory(process, _item, item, 512, NULL);
		if (j == 0) {
			params.Append(item);
		}
		else {
			params.Append(TEXT(","));
			params.Append(item);
		}
	}
	pDlg->m_param_list.SetItemText(nCount, 4, params);

	VirtualFreeEx(process, _lvi, 0, MEM_RELEASE);
	VirtualFreeEx(process, _item, 0, MEM_RELEASE);
	VirtualFreeEx(process, _subitem, 0, MEM_RELEASE);
	CloseHandle(process);
}
