
// AeroDrawTestDlg.h : ��� ����
//

#pragma once

#include <vector>
#include "afxwin.h"


#define ERR_NONE	                    0
#define ERR_RUN_CHECK_PROCESS			413
#define NOT_FOUND_PID					104

typedef struct _tagProcessInfo
{
	int			nPid;
	char		szName[MAX_PATH];
}PROCESSINFO, *LPPROCESSINFO;


// CAeroDrawTestDlg ��ȭ ����
class CAeroDrawTestDlg : public CDialog
{


protected:
	CArray<LPPROCESSINFO, LPPROCESSINFO> m_arrProcessInfo;


	HBITMAP CreateAeroBitmap(HWND hWnd, int nWidth, int nHeight);
	HBITMAP CreateAeroBitmapMain(HWND hWnd, int nWidth, int nHeight);
	HBITMAP CreateAeroBitmapView(HWND hWnd, int nWidth, int nHeight);
	HBITMAP PreviewBitmapMain(HWND hWnd, int nWidth, int nHeight, TCHAR *pszPath);
// �����Դϴ�.
public:
	CAeroDrawTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	std::vector<RECT> m_vRect;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AERODRAWTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	void	SaveDlgImage(int nIndex, DWORD dwPid);
	void	SaveImageIE(HWND hnd);

	int		m_nWidth;
	int		m_nHeight;
	HWND	m_TmwhHwnd; 
	HWND	_hwnd;
    int     _iTab;
	//HDC		m_TmwhHdc;
	//HDC		m_hMemDC;
	//HBITMAP m_hMemBitmap;
	//HBITMAP m_hOldMemBitmap;

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void LoadProcessInfo(BOOL bIsSystem);
	void SortProcessInfo();
	void SetProcess() ;


	HBITMAP _CreateDIB(int nWidth, int nHeight);
	HRESULT _SendLivePreviewBitmap();


	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedGetprocessapp();
	CString m_strValue;
	afx_msg void OnBnClickedGethwnd();
	afx_msg void OnBnClickedGetdlg();
	CComboBox m_ProcessCombo;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnDropdownCombo2();
	afx_msg void OnBnClickedAll();
};
