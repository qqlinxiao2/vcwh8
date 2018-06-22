
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
}

BEGIN_MESSAGE_MAP(Cvcwh8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, &Cvcwh8Dlg::OnBnClickedBtnLoad)
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
