
// 捆绑器Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <compressapi.h>
#pragma comment(lib,"Cabinet.lib")

// C捆绑器Dlg 对话框
class C捆绑器Dlg : public CDialogEx
{
// 构造
public:
	C捆绑器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	void ChangeExeIcon(LPCTSTR lpIconFile, LPCTSTR lpExeName);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl FileList;
	CString In_Filepath;
	CString Out_Filepath;
	CComboBox Evpath;
	CString FileName;
	CString IcoPath;
	afx_msg void OnBnClickedBuild();
	afx_msg void OnBnClickedBrowser();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedCheck1();
	BOOL boolEnvPath;
	afx_msg void OnEditDelit();
	afx_msg void OnEditDelall();
	afx_msg void OnNMRClickFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddico();
	BOOL m_compress;
};

struct  FILEINFO
{
	int method;
	char path[MAX_PATH] = { 0 };
	int fileSzie;
};

struct DIRFILEINFO
{
	UINT method;
	char path[MAX_PATH] = { 0 };
};

typedef struct tagHEADER
{
	WORD idReserved;
	WORD idType;
	WORD idCount;
}HEADER, *LPHEADER;

typedef struct tagICONDIRENTRY
{
	BYTE bWidth;
	BYTE bHeight;
	BYTE bColorCount;
	BYTE bReserved;
	WORD wPlanes;
	WORD wBitCount;
	DWORD dwBytesInRes;
	DWORD dwImageOffset;
}ICONDIRENTRY, *LPICONDIRENTRY;

typedef struct tagGRPICONDIRENTRY
{
	BYTE bWidth;
	BYTE bHeight;
	BYTE bColorCount;
	BYTE bReserved;
	WORD wPlanes;
	WORD wBitCount;
	DWORD dwBytesInRes;
	WORD nID;
}GRPICONDIRENTRY, *LPGRPICONDIRENTRY;;

typedef struct tagGRPICONDIR
{
	WORD idReserved;
	WORD idType;
	WORD idCount;
	GRPICONDIRENTRY idEntries[1];
}GRPICONDIR, *LPGRPICONDIR;
