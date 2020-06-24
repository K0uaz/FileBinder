
// ������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <compressapi.h>
#pragma comment(lib,"Cabinet.lib")

// C������Dlg �Ի���
class C������Dlg : public CDialogEx
{
// ����
public:
	C������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	void ChangeExeIcon(LPCTSTR lpIconFile, LPCTSTR lpExeName);
	// ���ɵ���Ϣӳ�亯��
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
