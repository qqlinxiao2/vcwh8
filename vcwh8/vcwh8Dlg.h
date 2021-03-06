#include "CExportParam.h"
// vcwh8Dlg.h: 头文件
//

#pragma once


// Cvcwh8Dlg 对话框
class Cvcwh8Dlg : public CDialogEx
{
// 构造
public:
	Cvcwh8Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VCWH8_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CExportParam *pDlg;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnList();
	bool IsCoveredByOtherWindow(HWND hWnd);
	void SetParams(HWND hwnd,CString str);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_param_list;
};
