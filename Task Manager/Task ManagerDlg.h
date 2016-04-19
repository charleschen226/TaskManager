
// Task ManagerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include<TlHelp32.h>
#include "afxwin.h"
#include"Block.h"
#include<vector>
using namespace std;

const DWORD ONE_PAGE = 4 * 1024;
const DWORD TWO_GB	 = 2 * 1024 * 1024 * 1024;

// CTaskManagerDlg 对话框
class CTaskManagerDlg : public CDialogEx
{
// 构造
public:
	CTaskManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TASKMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton6();
	DECLARE_MESSAGE_MAP()
public:
	void ShowProcess();	//显示所有进程
	void FirstSearch();
	void NextSearch();
	void SearchOnePage(DWORD dwBaseAddress);
	void Showresults();

public:	
	CListCtrl m_lstctrlprocess;	//显示进程
	CListCtrl m_lisresults;		//显示结果
	CEdit m_edtProcess;
	DWORD m_dwPID;				//选中的进程IP
	DWORD m_dwSearchValue;		//搜索值
	HANDLE m_hProcess;			//选中的进程句柄
	DWORD m_dwchange;			//要修改的数值
	vector<CBlock*> m_vec;
	vector<CBlock*>::iterator ite;
};
