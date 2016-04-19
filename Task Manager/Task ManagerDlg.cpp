
// Task ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Task Manager.h"
#include "Task ManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CTaskManagerDlg 对话框



CTaskManagerDlg::CTaskManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTaskManagerDlg::IDD, pParent)
	, m_dwPID(0)
	, m_dwSearchValue(0)
	, m_hProcess(NULL)
	, m_dwchange(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstctrlprocess);
	DDX_Control(pDX, IDC_EDIT1, m_edtProcess);
	DDX_Control(pDX, IDC_LIST2, m_lisresults);
	DDX_Text(pDX, IDC_EDIT3, m_dwchange);
	DDX_Text(pDX, IDC_EDIT2, m_dwSearchValue);
}

BEGIN_MESSAGE_MAP(CTaskManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CTaskManagerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTaskManagerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CTaskManagerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CTaskManagerDlg::OnBnClickedButton7)
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CTaskManagerDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CTaskManagerDlg::OnBnClickedButton4)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON6, &CTaskManagerDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CTaskManagerDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CTaskManagerDlg 消息处理程序

BOOL CTaskManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	CRect  Rect;
	CString str;
	m_lstctrlprocess.GetWindowRect(&Rect);
	int wight = Rect.Width() / 3;
	for (int i = 0; i < 3; i++)
	{
		str.LoadString(IDS_NAME + i);
		m_lstctrlprocess.InsertColumn(i, str, LVCFMT_LEFT, wight);
	}

	m_lisresults.GetWindowRect(&Rect);
	wight = Rect.Width() / 3;
	for (int i = 0; i < 3; i++)
	{
		str.LoadString(IDS_NUM + i);
		m_lisresults.InsertColumn(i, str, LVCFMT_LEFT, wight);
	}
	////设置窗口大小
	//CRect  m_Rect;
	//CRect  g_Rect;
	//GetWindowRect(&m_Rect);//得到主窗口大小
	//GetDlgItem(IDC_Search)->GetClientRect(&g_Rect);	//获得groupbox句柄 得到groupbox大小
	//SetWindowPos(NULL, 0, 0, m_Rect.Width() - g_Rect.Width() - 20, m_Rect.Height(), SWP_NOMOVE);

	//显示所有进程
	ShowProcess();

	//设置样式
	m_lstctrlprocess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lisresults.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//显示所有进程
void CTaskManagerDlg::ShowProcess()
{
	//先清空
	m_lstctrlprocess.DeleteAllItems();

	CString str;
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32)};
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);	//获取进程快照
	BOOL bMore = Process32First(hProcessSnap, &pe32);	//是否有第一个进程
	
	while (bMore)
	{
		//显示名字
		m_lstctrlprocess.InsertItem(0, pe32.szExeFile);

		//显示PID
		//DWORD to LPCTSTR
		str.Format(_T("%d"), pe32.th32ProcessID);
		m_lstctrlprocess.SetItemText(0, 1, str);

		//显示线程数
		str.Format(_T("%d"), pe32.cntThreads);
		m_lstctrlprocess.SetItemText(0, 2, str);

		bMore = Process32Next(hProcessSnap, &pe32);//是否有下一个进程
	}
}

void CTaskManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTaskManagerDlg::OnPaint()
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
HCURSOR CTaskManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//刷新
void CTaskManagerDlg::OnBnClickedButton2()
{
	ShowProcess();
}

//关闭线程
void CTaskManagerDlg::OnBnClickedButton1()
{
	//获取当前选中项
	int nindex = m_lstctrlprocess.GetSelectionMark();
	if (nindex == -1)
		return;

	//获得PID 第一列
	CString sPID = m_lstctrlprocess.GetItemText(nindex, 1);
	DWORD dPID = _ttoi(sPID);	//CString 转成 DWORD

	//打开线程 获得进程句柄
	HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dPID);
	if (hprocess)
	{
		if(TerminateProcess(hprocess, -1))
		{
			hprocess = NULL;
			m_lstctrlprocess.DeleteItem(nindex);	//删除当前行
		}
	}
}

//关机
void CTaskManagerDlg::OnBnClickedButton3()
{
	int i = ::MessageBox(AfxGetMainWnd()->m_hWnd, L"Are U sure to Shutdown?", NULL, MB_OKCANCEL);
	if (i == 1)
		ExitWindowsEx(EWX_SHUTDOWN, SHTDN_REASON_MAJOR_OTHER);
}

//修改内存
//static bool bflag = false;
void CTaskManagerDlg::OnBnClickedButton7()
{
	//CRect  m_Rect;
	//CRect  g_Rect;
	//GetWindowRect(&m_Rect);//得到主窗口大小
	//GetDlgItem(IDC_Search)->GetClientRect(&g_Rect);	//获得groupbox句柄 得到groupbox大小
	//if (!bflag)
	//{
	//	MoveWindow(m_Rect.left, m_Rect.right, m_Rect.Width() + g_Rect.Width(), m_Rect.Height());
	//	//SetWindowPos(NULL, 0, 0, m_Rect.Width(), m_Rect.Height(), SWP_NOMOVE);
	//	//显示窗口
	//	//SetTimer(10, 10, NULL);
	//	bflag = true;
	//}
	//else
	//{
	//	SetWindowPos(NULL, 0, 0, m_Rect.Width() - g_Rect.Width() - 20, m_Rect.Height(), SWP_NOMOVE);
	//	//隐藏窗口
	//	//SetTimer(20, 10, NULL);
	//	bflag = false;
	//}
}

void CTaskManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	//CRect  m_Rect;
	//CRect  g_Rect;
	//GetWindowRect(&m_Rect);//得到主窗口大小
	//GetDlgItem(IDC_Search)->GetClientRect(&g_Rect);	//获得groupbox句柄 得到groupbox大小
	//if (nIDEvent == 10)
	//{
	//	//显示
	//	SetWindowPos(NULL, 0, 0, m_Rect.Width(), m_Rect.Height(), SWP_NOMOVE);
	//}
	//if (nIDEvent == 20)
	//{
	//	//隐藏
	//	SetWindowPos(NULL, 0, 0, m_Rect.Width() - g_Rect.Width() - 20, m_Rect.Height(), SWP_NOMOVE);
	//}

	CDialogEx::OnTimer(nIDEvent);
}

void CTaskManagerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

	//获得选中的信息
	CString proname = m_lstctrlprocess.GetItemText(pNMItemActivate->iItem, 0);
	CString proPID = m_lstctrlprocess.GetItemText(pNMItemActivate->iItem, 1);

	m_dwPID = _ttoi(proPID);

	SetDlgItemText(IDC_EDIT1, proname);
	*pResult = 0;
}

void CTaskManagerDlg::SearchOnePage(DWORD dwBaseAddress)
{
	BYTE buffer[ONE_PAGE] = { 0 };
	CBlock *pblock = NULL;
	BOOL b = ReadProcessMemory(m_hProcess, (LPCVOID)dwBaseAddress, buffer, ONE_PAGE, NULL);
	int i = GetLastError();
	//读取指定进程的私有地址空间
	if (b)
	{
		//遍历buffer
		//TWO_BYTE
		short *pshort = NULL;
		for (int i = 0; i < ONE_PAGE - 1; i++)
		{
			pshort = (short *)(buffer + i);
			if (*pshort == m_dwSearchValue)
			{
				//存入向量中
				pblock = new CBlock(dwBaseAddress + i, TWO_BYTE);
				m_vec.push_back(pblock);
			}
		}

		//FOUR_BYTE
		int *pint = NULL;
		for (int i = 0; i < ONE_PAGE - 1; i++)
		{
			pint = (int *)(buffer + i);
			if (*pint == m_dwSearchValue)
			{
				//存入向量中
				pblock = new CBlock(dwBaseAddress + i, FOUR_BYTE);
				m_vec.push_back(pblock);
			}
		}

		//EIGHT_BYTE
		int *plong = NULL;
		for (int i = 0; i < ONE_PAGE - 1; i++)
		{
			plong = (int *)(buffer + i);
			if (*plong == m_dwSearchValue)
			{
				//存入向量中
				pblock = new CBlock(dwBaseAddress + i, EIGHT_BYTE);
				m_vec.push_back(pblock);
			}
		}
	}
}

void CTaskManagerDlg::FirstSearch()
{
	//分页 6k-2G
	for (DWORD dwBaseAddress = 64 * 1024; dwBaseAddress <= TWO_GB; dwBaseAddress += ONE_PAGE)
	{
		SearchOnePage(dwBaseAddress);
	}
	Showresults();
}

void CTaskManagerDlg::NextSearch()
{
	ite = m_vec.begin();
	while (ite != m_vec.end())
	{
		int type = (*ite)->m_type;
		switch (type)
		{
		case TWO_BYTE:
			{
				short s;
				if (ReadProcessMemory(m_hProcess, (void *)(*ite)->m_dwAddress, &s, sizeof(short), NULL))
				{
					if (s != m_dwSearchValue)
					{
						delete (*ite);
						*ite = NULL;
						ite = m_vec.erase(ite);
						continue;
					}
				}
			}
			break;
		case FOUR_BYTE:
			{
				int i;
				if (ReadProcessMemory(m_hProcess, (void *)(*ite)->m_dwAddress, &i, sizeof(short), NULL))
				{
					if (i != m_dwSearchValue)
					{
						delete (*ite);
						*ite = NULL;
						ite = m_vec.erase(ite);
						continue;
					}
				}
			}
			break;
		case EIGHT_BYTE:
			{
				long l;
				if (ReadProcessMemory(m_hProcess, (void *)(*ite)->m_dwAddress, &l, sizeof(short), NULL))
				{
					if (l != m_dwSearchValue)
					{
						delete (*ite);
						*ite = NULL;
						ite = m_vec.erase(ite);
						continue;
					}
				}
			}
			break;
		}
		ite++;
	}
	Showresults();
}

void CTaskManagerDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!m_hProcess)
		m_hProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_OPERATION, FALSE, m_dwPID);
	 
	static bool bflag = FALSE;
	if (!bflag)
	{
		//第一次搜索
		m_lisresults.DeleteAllItems();
		FirstSearch();
		bflag = TRUE;
	}
	else
		NextSearch();
}

void CTaskManagerDlg::Showresults()
{
	ite = m_vec.begin();
	int nindex = 0;
	CString str;
	for (ite; ite != m_vec.end(); ite++)
	{
		//显示序号
		str.Format(L"%d", nindex);
		m_lisresults.InsertItem(nindex, str);

		//显示地址
		str.Format(L"%x", (*ite)->m_dwAddress);
		m_lisresults.SetItemText(nindex, 1, str);

		//显示类型
		str.Format(L"%d", (*ite)->m_type);
		m_lisresults.SetItemText(nindex, 2, str);
		nindex++;
	}
	::MessageBox(AfxGetMainWnd()->m_hWnd, L"搜索完毕！", NULL, MB_OK);
}

void CTaskManagerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	for (ite = m_vec.begin(); ite != m_vec.end(); ite++)
	{
		delete (*ite);
		(*ite) = NULL;
	}
}


void CTaskManagerDlg::OnBnClickedButton6()
{
	UpdateData(TRUE);

	//得到选中的行
	int nindex = m_lisresults.GetSelectionMark();
	if (nindex == -1)
		return;

	//得到选中的地址  和类型
	CString strAddress = m_lisresults.GetItemText(nindex, 1);
	DWORD dwAddresstochange = _ttoi(strAddress);
	DWORD dwtype = _ttoi(m_lisresults.GetItemText(nindex, 2));

	//修改 地址里的值
	switch (dwtype)
	{
	case TWO_BYTE:
		{
			if (WriteProcessMemory(m_hProcess, (LPVOID)dwAddresstochange, &m_dwchange, TWO_BYTE, NULL))
				MessageBox(L"OVER!");
		}
		break;
	case FOUR_BYTE:
		{
			if (WriteProcessMemory(m_hProcess, (LPVOID)dwAddresstochange, &m_dwchange, FOUR_BYTE, NULL))
				MessageBox(L"OVER!");
		}
		break;
	case EIGHT_BYTE:
		{
			if (WriteProcessMemory(m_hProcess, (LPVOID)dwAddresstochange, &m_dwchange, EIGHT_BYTE, NULL))
				MessageBox(L"OVER!");
		}
		break;
	}	
}




void CTaskManagerDlg::OnBnClickedButton8()
{
	int nindex = m_lstctrlprocess.GetSelectionMark();
	CString strName = m_lstctrlprocess.GetItemText(nindex, 0);

	ShellExecute(NULL, L"open", strName, NULL, NULL, SW_SHOWNORMAL);
}
