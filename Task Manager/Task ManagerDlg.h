
// Task ManagerDlg.h : ͷ�ļ�
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

// CTaskManagerDlg �Ի���
class CTaskManagerDlg : public CDialogEx
{
// ����
public:
	CTaskManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TASKMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	void ShowProcess();	//��ʾ���н���
	void FirstSearch();
	void NextSearch();
	void SearchOnePage(DWORD dwBaseAddress);
	void Showresults();

public:	
	CListCtrl m_lstctrlprocess;	//��ʾ����
	CListCtrl m_lisresults;		//��ʾ���
	CEdit m_edtProcess;
	DWORD m_dwPID;				//ѡ�еĽ���IP
	DWORD m_dwSearchValue;		//����ֵ
	HANDLE m_hProcess;			//ѡ�еĽ��̾��
	DWORD m_dwchange;			//Ҫ�޸ĵ���ֵ
	vector<CBlock*> m_vec;
	vector<CBlock*>::iterator ite;
};
