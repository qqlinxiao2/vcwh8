
// vcwh8Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "vcwh8.h"
#include "vcwh8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cvcwh8Dlg 对话框



Cvcwh8Dlg::Cvcwh8Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VCWH8_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cvcwh8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PARAM, m_param_list);
}

BEGIN_MESSAGE_MAP(Cvcwh8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &Cvcwh8Dlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_LIST, &Cvcwh8Dlg::OnBnClickedBtnList)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cvcwh8Dlg 消息处理程序

BOOL Cvcwh8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	pDlg = new CExportParam();
	pDlg->Create(IDD_DIALOG_EXPORT, this);
	pDlg->ShowWindow(SW_HIDE);
	this->SetTimer(1, 1, NULL);
	//初始化列表
	//初始化列表
	m_param_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);    //报表样式
	m_param_list.InsertColumn(0, TEXT("序号"), LVCFMT_CENTER, 50);//增加一列，左对齐，120px
	m_param_list.InsertColumn(1, TEXT("交易合约"), LVCFMT_CENTER, 60);//增加一列，左对齐，120px
	m_param_list.InsertColumn(2, TEXT("K线周期"), LVCFMT_CENTER, 60);//增加一列，左对齐，120px
	m_param_list.InsertColumn(3, TEXT("模型"), LVCFMT_CENTER, 130);//增加一列，左对齐，120px
	m_param_list.InsertColumn(4, TEXT("参数组"), LVCFMT_CENTER, 150);//增加一列，左对齐，120px

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cvcwh8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cvcwh8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cvcwh8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cvcwh8Dlg::OnBnClickedBtnLoad()
{
	HWND hwnd = HWND(0x1F04A6);		//systreeview32的hwnd

	CStringArray strArr;
	CString text;
	const int bufferLength = 4000;
	DWORD processId = NULL;
	LPTVITEM item = (LPTVITEM)new BYTE[bufferLength];

	GetWindowThreadProcessId(hwnd, &processId);
	HANDLE process = ::OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, false, processId);
	PVOID buffer = VirtualAllocEx(process, NULL, bufferLength, MEM_COMMIT, PAGE_READWRITE);
	item->mask = TVIF_TEXT;
	item->cchTextMax = 512;
	item->pszText = LPTSTR((PBYTE)buffer + sizeof(TVITEM));//(LPSTR)VirtualAllocEx(process, NULL, 512, MEM_COMMIT, PAGE_READWRITE);
	item->hItem = (HTREEITEM)::SendMessage(hwnd, TVM_GETNEXTITEM, TVGN_ROOT, 0);
	while (item->hItem)
	{
		::SendMessage(hwnd, TVM_SELECTITEM, TVGN_CARET, (long)item->hItem);
		WriteProcessMemory(process, buffer, item, sizeof(TVITEM), NULL);
		::SendMessage(hwnd, TVM_GETITEM, 0, (LPARAM)buffer);
		ReadProcessMemory(process, buffer, item, bufferLength, NULL);
		text = (LPTSTR)((PBYTE)item + sizeof(TVITEM));
		AfxMessageBox(text);
		if (-1 != text.Find(TEXT("bbb")))
		{	
			::SendMessage(hwnd, TVM_EXPAND, TVE_EXPAND, (long)item->hItem);
			::SendMessage(hwnd, TVM_SELECTITEM, TVGN_CARET, (long)item->hItem);
			//break;
		}
		item->hItem = (HTREEITEM)::SendMessage(hwnd, TVM_GETNEXTITEM, TVGN_NEXT, (long)item->hItem);
	}

	VirtualFreeEx(process, item, 0, MEM_RELEASE);
	CloseHandle(process);
}


void Cvcwh8Dlg::OnBnClickedBtnList()
{
	HWND hwnd = NULL;
	int count, i;
	TCHAR item[512] = { 0 }, subitem[512] = { 0 };

	LVITEM lvi, *_lvi;
	TCHAR *_item, *_subitem;
	DWORD pid;
	HANDLE process;

	hwnd = HWND(0xC0632);
	count = (int)::SendMessage(hwnd, LVM_GETITEMCOUNT, 0, 0);

	GetWindowThreadProcessId(hwnd, &pid);
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
		::SendMessage(hwnd, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);

		lvi.iSubItem = 1;
		lvi.pszText = _subitem;
		//测试 改变第二列的值
		TCHAR* str1 = TEXT("hehe");
		WriteProcessMemory(process, _subitem, str1, 512, NULL);
		WriteProcessMemory(process, _lvi, &lvi, sizeof(LVITEM), NULL);
		::SendMessage(hwnd, LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);

		ReadProcessMemory(process, _item, item, 512, NULL);
		ReadProcessMemory(process, _subitem, subitem, 512, NULL);

		//CString str;
		//str.Format(TEXT("%s - %s\n"), item, subitem);
		//AfxMessageBox(str);
	}

	VirtualFreeEx(process, _lvi, 0, MEM_RELEASE);
	VirtualFreeEx(process, _item, 0, MEM_RELEASE);
	VirtualFreeEx(process, _subitem, 0, MEM_RELEASE);
}

bool Cvcwh8Dlg::IsCoveredByOtherWindow(HWND hWnd)
{
	RECT rcTarget;
	bool r = ::GetWindowRect(hWnd, &rcTarget);
	if (r == FALSE) {
		return true;
	}

	bool isChild = (WS_CHILD == (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD));

	if (::GetDesktopWindow() == hWnd)
		hWnd = ::GetWindow(::GetTopWindow(hWnd), GW_HWNDLAST);

	do {
		HWND hCurWnd = hWnd;

		while (NULL != (hWnd = ::GetNextWindow(hWnd, GW_HWNDPREV))) {
			if (::IsWindowVisible(hWnd)) {
				RECT rcWnd;
				::GetWindowRect(hWnd, &rcWnd);

				if (!((rcWnd.right < rcTarget.left) || (rcWnd.left > rcTarget.right) ||
					(rcWnd.bottom < rcTarget.top) || (rcWnd.top > rcTarget.bottom))) {
					return true;
				}
			}
		}

		if (isChild) {
			hWnd = ::GetParent(hCurWnd);
			isChild = hWnd ? (WS_CHILD == (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD)) : false;
		}
		else
			break;
	} while (true);

	return false;
}

void Cvcwh8Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HWND hWnd = NULL;
	if(::IsWindow(hWnd) == FALSE)
		hWnd = ::FindWindowEx(NULL,NULL,TEXT("#32770"),TEXT("模型回测报告"));
		hWnd = ::GetDlgItem(hWnd, 1517);
		hWnd = ::GetDlgItem(hWnd, 0);
		hWnd = ::GetDlgItem(hWnd, 3137);

	BOOL b = IsCoveredByOtherWindow(hWnd);
	if (b == TRUE) {
		pDlg->ShowWindow(SW_HIDE);
	}
	else {
		pDlg->ShowWindow(SW_SHOW);
		RECT targetRect;
		::GetWindowRect(hWnd, &targetRect);
		targetRect.left += 100;
		::SetWindowPos(pDlg->m_hWnd, HWND_TOPMOST, targetRect.left, targetRect.top, 0, 0, SWP_NOSIZE);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
