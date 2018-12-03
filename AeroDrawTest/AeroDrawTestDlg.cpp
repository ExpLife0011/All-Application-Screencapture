
// AeroDrawTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AeroDrawTest.h"
#include "AeroDrawTestDlg.h"
#include "CxImage/ximage.h"
#include  <Dwmapi.h>
#include "SystemInfo.h"

#pragma comment(lib, "Dwmapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND SetFromPidtoHnd(DWORD dwPid, int nType);
int CheckRunProcess(char* filename);

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAeroDrawTestDlg ��ȭ ����




CAeroDrawTestDlg::CAeroDrawTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAeroDrawTestDlg::IDD, pParent)
	, m_strValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAeroDrawTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strValue);
	DDX_Control(pDX, IDC_COMBO2, m_ProcessCombo);
}

BEGIN_MESSAGE_MAP(CAeroDrawTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CAeroDrawTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CAeroDrawTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAeroDrawTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_GETPROCESSAPP, &CAeroDrawTestDlg::OnBnClickedGetprocessapp)
	ON_BN_CLICKED(IDC_GETHWND, &CAeroDrawTestDlg::OnBnClickedGethwnd)
	ON_BN_CLICKED(IDC_GETDLG, &CAeroDrawTestDlg::OnBnClickedGetdlg)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAeroDrawTestDlg::OnCbnSelchangeCombo2)
	ON_CBN_DROPDOWN(IDC_COMBO2, &CAeroDrawTestDlg::OnCbnDropdownCombo2)
	ON_BN_CLICKED(IDC_ALL, &CAeroDrawTestDlg::OnBnClickedAll)
END_MESSAGE_MAP()


// CAeroDrawTestDlg �޽��� ó����

void SetFromPidtoHnd(DWORD dwPid);

BOOL CAeroDrawTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	BOOL fForceIconic = TRUE;
	BOOL fHasIconicBitmap = TRUE;


	//HWND hParent = ::GetParent(this->GetSafeHwnd());

	//DwmSetWindowAttribute(hParent, 7, &fForceIconic, sizeof(fForceIconic)); // DWMWA_FORCE_ICONIC_REPRESENTATION
	//DwmSetWindowAttribute(hParent, 10, &fHasIconicBitmap, sizeof(fHasIconicBitmap)); // DWMWA_HAS_ICONIC_BITMAP
	//DwmSetWindowAttribute(this->GetSafeHwnd(), 7, &fForceIconic, sizeof(fForceIconic)); // DWMWA_FORCE_ICONIC_REPRESENTATION
	//DwmSetWindowAttribute(this->GetSafeHwnd(), 10, &fHasIconicBitmap, sizeof(fHasIconicBitmap)); // DWMWA_HAS_ICONIC_BITMAP
	
//	hParent = ::GetParent(myHwnd);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CAeroDrawTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAeroDrawTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAeroDrawTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBITMAP CAeroDrawTestDlg::PreviewBitmapMain(HWND hWnd, int nWidth, int nHeight, TCHAR *pszPath)
{
	BITMAPINFO			bi;

	memset(&bi, 0x00, sizeof(BITMAPINFO));

	// ��Ʈ�� ��� �� ����
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = nWidth;
	bi.bmiHeader.biHeight = nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = (nWidth * 3 + 3) / 4 * 4 * nHeight;
	bi.bmiHeader.biXPelsPerMeter = 11811;
	bi.bmiHeader.biYPelsPerMeter = 11811;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	HDC hDC = ::GetDC(NULL);

	// DIB �������� ��Ʈ�� �����
	HDC hMemTarget = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, NULL, NULL, NULL);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemTarget, hBitmap);
	HDC		hWndDCSource = ::GetDC(hWnd);	


	CRect rt;
	::GetClientRect(hWnd, &rt);
	//::StretchBlt(hMemTarget, 0, 0, nWidth, nHeight, hWndDCSource, 0, 0, rt.Width(), rt.Height(), SRCCOPY);


	HDC hMemDCTemp = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);
	HBITMAP hOldMemBitmap = (HBITMAP)::SelectObject(hMemDCTemp, hMemBitmap);

	CxImage xImage;

	xImage.Load(pszPath, CXIMAGE_SUPPORT_BMP);		// �̹��� �ε�

	xImage.Resample(nWidth, nHeight, CxImage::IM_LANCZOS);	// �̹��� ������¡
	xImage.Blt(hMemDCTemp, 0, 0);

	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 150;
//	blend.SourceConstantAlpha = 0;
	blend.AlphaFormat = 0;

	::AlphaBlend(hMemTarget, 0, 0, nWidth, nHeight, hMemDCTemp, 0, 0, nWidth, nHeight, blend);

	::SelectObject(hMemDCTemp, hOldMemBitmap);
	::DeleteObject(hMemBitmap);
	::DeleteDC(hMemDCTemp);


	::SelectObject(hMemTarget, hOldBitmap);
	::DeleteDC(hMemTarget);
	::ReleaseDC(NULL, hDC);
	::ReleaseDC(hWnd, hWndDCSource);

	return hBitmap;
}


HBITMAP CAeroDrawTestDlg::CreateAeroBitmapMain(HWND hWnd, int nWidth, int nHeight)
{
	BITMAPINFO			bi;

	memset(&bi, 0x00, sizeof(BITMAPINFO));

	// ��Ʈ�� ��� �� ����
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = nWidth;
	bi.bmiHeader.biHeight = nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = (nWidth * 3 + 3) / 4 * 4 * nHeight;
	bi.bmiHeader.biXPelsPerMeter = 11811;
	bi.bmiHeader.biYPelsPerMeter = 11811;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	HDC hDC = ::GetDC(NULL);

	// DIB �������� ��Ʈ�� �����
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, NULL, NULL, NULL);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

//	HWND hnd = ::FindWindow(NULL, "MultiMornitor");
//	HWND hnd = ::FindWindow("Afx:00007FF7EC1E0000:3", NULL);
	
//	hnd = (HWND)0x001A1DAC;
//	hnd = (HWND)0x00032864;

	HDC hWndDC = ::GetDC(hWnd);		
	HDC hWndDC2 = ::GetDC(hWnd);

	CRect rt;
	::GetClientRect(hWnd, &rt);
	::StretchBlt(hMemDC, 0, 0, nWidth, nHeight, hWndDC2, 0, 0, rt.Width(), rt.Height(), SRCCOPY);
	//::StretchBlt(hMemDC, 0, 0, rt.Width(), rt.Height(), hWndDC2, 0, 0, rt.Width(), rt.Height(), SRCCOPY);

	HDC hMemDCTemp = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);
	HBITMAP hOldMemBitmap = (HBITMAP)::SelectObject(hMemDCTemp, hMemBitmap);

	CxImage xImage;

	xImage.Load("c:\\temp\\test.bmp", CXIMAGE_SUPPORT_BMP);		// �̹��� �ε�

	xImage.Resample(nWidth, nHeight, CxImage::IM_LANCZOS);	// �̹��� ������¡
	xImage.Blt(hMemDCTemp, 0, 0);

	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 50;
	blend.AlphaFormat = 0;

	::AlphaBlend(hMemDC, 0, 0, nWidth, nHeight, hMemDCTemp, 0, 0, nWidth, nHeight, blend);

	::SelectObject(hMemDCTemp, hOldMemBitmap);
	::DeleteObject(hMemBitmap);
	::DeleteDC(hMemDCTemp);
	
	RECT DrawTextrt;
	DrawTextrt.left = 0;
	DrawTextrt.top = 0;
	DrawTextrt.right = nWidth;
	DrawTextrt.bottom = nHeight;
	::DrawText(hMemDC, "Main ���͸�ũ �ؽ�Ʈ ���", 20, &DrawTextrt, DT_VCENTER);

	::SelectObject(hMemDC, hOldBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hDC);
	::ReleaseDC(hWnd, hWndDC);

	return hBitmap;
}

HBITMAP CAeroDrawTestDlg::CreateAeroBitmap(HWND hWnd, int nWidth, int nHeight)
{
	BITMAPINFO			bi;
	
	memset(&bi, 0x00, sizeof(BITMAPINFO));

	// ��Ʈ�� ��� �� ����
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = nWidth;
	bi.bmiHeader.biHeight = nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = (nWidth * 3 + 3) / 4 * 4 * nHeight;
	bi.bmiHeader.biXPelsPerMeter = 11811;
	bi.bmiHeader.biYPelsPerMeter = 11811;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	HDC hDC = ::GetDC(NULL);

	// DIB �������� ��Ʈ�� �����
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, NULL, NULL, NULL);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

	HDC hWndDC = ::GetDC(hWnd);

	CRect rt;
	::GetClientRect(hWnd, &rt);
	::StretchBlt(hMemDC, 0, 0, nWidth, nHeight, hWndDC, 0, 0, rt.Width(), rt.Height(), SRCCOPY);

	//RECT DrawTextrt;
	//DrawTextrt.left = 0;
	//DrawTextrt.top = 0;
	//DrawTextrt.right = nWidth;
	//DrawTextrt.bottom = nHeight;

	//::DrawText(hMemDC, "���͸�ũ �ؽ�Ʈ ���", 20, &DrawTextrt, DT_VCENTER);

	::SelectObject(hMemDC, hOldBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hDC);
	::ReleaseDC(hWnd, hWndDC);

	return hBitmap;
}
//
//BOOL(__stdcall *Real_TranslateMessage)(CONST MSG *lpMsg) = TranslateMessage;
//#define TranslateMessage(__name__) BOOL  WINAPI __name__(CONST MSG *lpMsg)

typedef HRESULT(WINAPI *t_DwmSetIconicThumbnail)(HWND hwnd, HBITMAP hbmp, DWORD dwSITFlags);
typedef HRESULT(WINAPI *t_DwmSetIconicLivePreviewBitmap)(HWND hwnd, HBITMAP hbmp, POINT *pptClient, DWORD dwSITFlags);

t_DwmSetIconicThumbnail set_iconic_thumbnail = NULL;
t_DwmSetIconicLivePreviewBitmap set_live_preview = NULL;

HMODULE g_shell = NULL;

#define WM_DWMSENDICONICTHUMBNAIL           0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP   0x0326

#if 1
BOOL CAeroDrawTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (g_shell == NULL)
	{
		g_shell = LoadLibrary("dwmapi.dll");
		set_iconic_thumbnail = (t_DwmSetIconicThumbnail)GetProcAddress(g_shell, "DwmSetIconicThumbnail");
		set_live_preview = (t_DwmSetIconicLivePreviewBitmap)GetProcAddress(g_shell, "DwmSetIconicLivePreviewBitmap");
	}

	// TODO: Add your specialized code here and/or call the base class
//	if (pMsg->message == WM_DWMSENDICONICLIVEPREVIEWBITMAP)
	if(0)
	{
//		CRect rt;
//		::GetClientRect(pMsg->hwnd, &rt);
//
////		CreateAeroBitmapMain(this->GetSafeHwnd(), rt.Width(), rt.Height());
//	
//		HBITMAP hBitmap = PreviewBitmapMain(this->GetSafeHwnd(), rt.Width(), rt.Height(), "c:\\temp\\test.bmp");
//
		_hwnd=pMsg->hwnd;
//		set_live_preview(pMsg->hwnd, hBitmap, NULL, 1);
//		DeleteObject(hBitmap);
		_SendLivePreviewBitmap();
	}
	else if (pMsg->message == WM_DWMSENDICONICTHUMBNAIL)
	{
		CRect rt;
		::GetClientRect(pMsg->hwnd, &rt);

		HBITMAP hBitmap = PreviewBitmapMain(this->GetSafeHwnd(), HIWORD(pMsg->lParam), LOWORD(pMsg->lParam), "c:\\temp\\test.bmp");

//		HBITMAP hBitmap = CreateAeroBitmap(this->GetSafeHwnd(), HIWORD(pMsg->lParam), LOWORD(pMsg->lParam));
		
		set_iconic_thumbnail(pMsg->hwnd, hBitmap, 0);
		DeleteObject(hBitmap);
	}

	return CDialog::PreTranslateMessage(pMsg);
}
#endif 

HBITMAP CAeroDrawTestDlg::CreateAeroBitmapView(HWND hWnd, int nWidth, int nHeight)
{
	//BITMAPINFO			bi;

	//memset(&bi, 0x00, sizeof(BITMAPINFO));

	//// ��Ʈ�� ��� �� ����
	//bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bi.bmiHeader.biWidth = nWidth;
	//bi.bmiHeader.biHeight = nHeight;
	//bi.bmiHeader.biPlanes = 1;
	//bi.bmiHeader.biBitCount = 32;
	//bi.bmiHeader.biCompression = BI_RGB;
	//bi.bmiHeader.biSizeImage = (nWidth * 3 + 3) / 4 * 4 * nHeight;
	//bi.bmiHeader.biXPelsPerMeter = 11811;
	//bi.bmiHeader.biYPelsPerMeter = 11811;
	//bi.bmiHeader.biClrUsed = 0;
	//bi.bmiHeader.biClrImportant = 0;

	//HDC hDC = ::GetDC(NULL);

	//// DIB �������� ��Ʈ�� �����
	//HDC hMemDC = CreateCompatibleDC(hDC);
	//HBITMAP hBitmap = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, NULL, NULL, NULL);
	
	CRect rt;
	::GetClientRect(hWnd, &rt);

//	HWND hnd = ::FindWindow(NULL, "MultiMornitor");
	//HWND hnd = ::FindWindow("Afx:00007FF7EC1E0000:3", NULL);

//	hnd = (HWND)0x

	HDC hDC = ::GetDC(NULL);
	HDC hWndDC = ::GetDC(hWnd);
	// �Ƕ���
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, rt.Width(), rt.Height());
	HBITMAP hOldMemBitmap = (HBITMAP)::SelectObject(hMemDC, hMemBitmap);

	::BitBlt(hMemDC, 0, 0, rt.Width(), rt.Height(), hWndDC, 0, 0, SRCCOPY);

	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 50;
	blend.AlphaFormat = 0;
	
	//Sleep(4000);
	//::BitBlt(hMemDC, 0, 0, rt.Width(), rt.Height(), hDC, 0, 0, SRCAND);
	::AlphaBlend(hMemDC, 0, 0, rt.Width(), rt.Height(), hDC, 0, 0, rt.Width(), rt.Height(), blend);

	::BitBlt(hWndDC, 0, 0, rt.Width(), rt.Height(), hMemDC, 0, 0, SRCCOPY);

	::SelectObject(hMemDC, hOldMemBitmap);
	::DeleteObject(hMemBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hDC);
	::ReleaseDC(hWnd, hWndDC);
//	HGDIOBJ h_bitmap = GetCurrentObject(h_mem_dc, OBJ_BITMAP);

//��� �ҽ�
/*
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

	HWND hnd = ::FindWindow(NULL, "MultiMornitor");
	//HWND hnd = ::FindWindow("Afx:00007FF7EC1E0000:3", NULL);

	hnd = (HWND)0x0003176A;
	//hnd = (HWND)0x00032864;
	CRect rt;
	::GetClientRect(hnd, &rt);
	HDC hWndDC2 = ::GetDC(hnd);
	HDC hWndDC = ::GetDC(hWnd);

	::StretchBlt(hWndDC, 0, 0, nWidth, nHeight, hWndDC2, 0, 0, rt.Width(), rt.Height(), SRCCOPY);
*/
	//::StretchBlt(hMemDC, 0, 0, rt.Width(), rt.Height(), hWndDC2, 0, 0, rt.Width(), rt.Height(), SRCCOPY);

	//RECT DrawTextrt;
	//DrawTextrt.left = 0;
	//DrawTextrt.top = 0;
	//DrawTextrt.right = nWidth;
	//DrawTextrt.bottom = nHeight;

	//::DrawText(hMemDC, "Main ���͸�ũ �ؽ�Ʈ ���", 20, &DrawTextrt, DT_VCENTER);

	//::SelectObject(hMemDC, hOldBitmap);
	//::DeleteDC(hMemDC);
	//::ReleaseDC(NULL, hDC);
	//::ReleaseDC(hWnd, hWndDC);

	return NULL;
}

void CAeroDrawTestDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CRect rt;
	HWND  hnd = NULL;

	hnd = this->GetSafeHwnd();

	::GetClientRect(hnd, &rt);

	HBITMAP hBitmap = CreateAeroBitmapView(hnd, rt.Width(), rt.Height());

}

RECT	m_rcFull;

BOOL CAeroDrawTestDlg::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	std::vector< RECT >* pvRect = (std::vector< RECT >*)dwData;

	MONITORINFOEX mi;
	mi.cbSize = sizeof(MONITORINFOEX);

	GetMonitorInfo(hMonitor, &mi);

	RECT rt;
	rt.top = lprcMonitor->top + 2;
	rt.bottom = lprcMonitor->bottom - 2;
	rt.left = lprcMonitor->left + 2;
	rt.right = lprcMonitor->right - 2;

	pvRect->push_back(rt);

	if(m_rcFull.top > lprcMonitor->top)
		m_rcFull.top = lprcMonitor->top + 2;
	if(m_rcFull.left > lprcMonitor->left)
		m_rcFull.left = lprcMonitor->left + 2;
	if(m_rcFull.bottom < lprcMonitor->bottom)
		m_rcFull.bottom = lprcMonitor->bottom - 2;
	if(m_rcFull.right < lprcMonitor->right)
		m_rcFull.right = lprcMonitor->right - 2;

	return TRUE;
}

void CAeroDrawTestDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_vRect.clear();
	m_rcFull.top = 0;
	m_rcFull.bottom = 0;
	m_rcFull.left = 0;
	m_rcFull.right = 0;
	//memset(m_rcFull, 0, sizeof(m_rcFull));
	::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&m_vRect);

	CString strTemp;
	int ni = 0;
	//strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);
	//strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);
	
	m_nHeight = m_vRect[0].bottom - m_vRect[0].top;
	m_nWidth = m_vRect[0].right - m_vRect[0].left;
	
	HWND hwnd = (HWND)0x0006152A;;
	HDC hTmwDC = ::GetDC(hwnd);

	HDC hDC = ::GetDC(NULL);

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, m_nWidth, m_nHeight);
	HBITMAP hOldMemBitmap = (HBITMAP)::SelectObject(hMemDC, hMemBitmap);

	::BitBlt(hMemDC, 0, 0, m_nWidth, m_nHeight, hTmwDC, 0, 0, SRCCOPY);

	CxImage xImage;
	xImage.CreateFromHBITMAP(hMemBitmap);
	xImage.Save("c:\\temp\\test.bmp", CXIMAGE_SUPPORT_BMP);

	//BITMAP Bitmap;
	//int error = GetObject( &Bitmap, sizeof( BITMAP  ), &m_hMemBitmap );

	::SelectObject(hMemDC, hOldMemBitmap);
	::DeleteObject(hMemBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hDC);
	::ReleaseDC(hwnd, hTmwDC);
}

void CAeroDrawTestDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_vRect.clear();
	m_rcFull.top = 0;
	m_rcFull.bottom = 0;
	m_rcFull.left = 0;
	m_rcFull.right = 0;
	//memset(m_rcFull, 0, sizeof(m_rcFull));
	::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&m_vRect);

	CString strTemp;
	int ni = 0;
	//strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);
	//strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);

	m_nHeight = m_vRect[0].bottom - m_vRect[0].top;
	m_nWidth = m_vRect[0].right - m_vRect[0].left;


	HDC hDC = ::GetDC(NULL);
//	HDC hDC = NULL;

	m_nWidth = m_nWidth / 2;
	m_nHeight = m_nHeight / 2;

	CxImage xImage;
	xImage.Load("c:\\temp\\test.bmp", CXIMAGE_SUPPORT_BMP);		// �̹��� �ε�
	xImage.Resample(m_nWidth, m_nHeight, CxImage::IM_LANCZOS);	// �̹��� ������¡

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, xImage.GetWidth(), xImage.GetHeight());
	HBITMAP hOldMemBitmap = (HBITMAP)::SelectObject(hMemDC, hMemBitmap);

	xImage.Blt(hMemDC, 0, 0);

	//::BitBlt(hDC, 0, 0, m_nWidth, m_nHeight, hMemDC, 0, 0, SRCCOPY);
	BLENDFUNCTION blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 50;
	blend.AlphaFormat = 0;

	::AlphaBlend(hDC, 0, 0, m_nWidth, m_nHeight, hMemDC, 0, 0, m_nWidth, m_nHeight, blend);

	::SelectObject(hMemDC, hOldMemBitmap);
	::DeleteObject(hMemBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hDC);
}

void CAeroDrawTestDlg::OnBnClickedGetprocessapp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	DWORD dwPid = 0;
	char  szBuffer[MAX_PATH] = "";
	HWND	hParent=NULL;
	HWND	myHwnd = NULL;


	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	BOOL fForceIconic = TRUE;
	BOOL fHasIconicBitmap = TRUE;

	if(m_strValue.IsEmpty())
		m_strValue = "notepad.exe";

	//(LPSTR)(LPCSTR)
	strcpy(szBuffer, m_strValue.GetBuffer());


	dwPid = CheckRunProcess(szBuffer);

	if(dwPid)
	{
		SystemWindowInformation wi( dwPid, TRUE );

		if ( wi.m_WindowInfos.GetHeadPosition() == NULL )
		{
			return ;
		}

		for ( POSITION pos = wi.m_WindowInfos.GetHeadPosition(); pos != NULL; )
		{
			SystemWindowInformation::WINDOW_INFO& w = wi.m_WindowInfos.GetNext(pos);

			//TRACE("caption %s \n", w.Caption);
			if(dwPid == wi.m_processId)
			{
				myHwnd = w.hWnd;
				if(myHwnd == NULL)
					continue;


				if(IsWindow(myHwnd) == FALSE || ::IsWindowVisible(myHwnd ) == FALSE)
					continue;

				hParent = ::GetParent(myHwnd);

				if(hParent == NULL)
					hParent = myHwnd;

				// Aero �� ��Ÿ���� �ش� �������� �̺�Ʈ ���� ��û ���
				DwmSetWindowAttribute(hParent, 7, &fForceIconic, sizeof(fForceIconic)); // DWMWA_FORCE_ICONIC_REPRESENTATION
				DwmSetWindowAttribute(hParent, 10, &fHasIconicBitmap, sizeof(fHasIconicBitmap)); // DWMWA_HAS_ICONIC_BITMAP

				break;
			}
		}
	}

	dwPid = dwPid ;

}

//for ( POSITION pos = wi.m_WindowInfos.GetHeadPosition(); pos != NULL; )
//{
//	SystemWindowInformation::WINDOW_INFO& w = wi.m_WindowInfos.GetNext(pos);
//
//	//TRACE("caption %s \n", w.Caption);
//	if(dwPid == wi.m_processId)
//	{
//		myHwnd = w.hWnd;
//		if(myHwnd == NULL)
//			continue;
//
//
//		if(IsWindow(myHwnd) == FALSE || IsWindowVisible(myHwnd ) == FALSE)
//			continue;
//
//		hParent = ::GetParent(myHwnd);
//
//		if(hParent == NULL)
//			hParent = myHwnd;

void CAeroDrawTestDlg::OnBnClickedGethwnd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// Aero �� ��Ÿ���� �ش� �������� �̺�Ʈ ���� ��û ���
	DWORD dwPid = GetCurrentProcessId();
	HWND	CurHwnd = NULL;

	CurHwnd = this->m_hWnd;

	SetFromPidtoHnd(dwPid, 1);

//	dwPid = CheckRunProcess("notepad.exe");
//	SetFromPidtoHnd(dwPid);

}

HRESULT CAeroDrawTestDlg::_SendLivePreviewBitmap()
{
	HRESULT hr = S_OK;

	HWND hwndTabFrame = this->m_hWnd;
	DWORD dwStyle = GetWindowLong(hwndTabFrame, GWL_STYLE);
	DWORD dwStyleEx = GetWindowLong(hwndTabFrame, GWL_EXSTYLE);

	// Compute the actual size the thumbnail will occupy on-screen in order to
	// render the live preview bitmap. We use the tab window outer frame window
	// to compute this. In case that window is minimized, we use GetWindowPlacement
	// to give the correct information.
	RECT rcClient = {};
	RECT rcNCA = {};
	WINDOWPLACEMENT wp;
	if (AdjustWindowRectEx(&rcNCA, dwStyle, FALSE, dwStyleEx) != 0 &&
		::GetWindowPlacement(hwndTabFrame, &wp) != 0)
	{
		if (wp.flags & WPF_RESTORETOMAXIMIZED)
		{
			HMONITOR hmon = MonitorFromRect(&wp.rcNormalPosition, MONITOR_DEFAULTTONULL);
			if (hmon)
			{
				MONITORINFO monitorInfo;
				monitorInfo.cbSize = sizeof(MONITORINFO);
				if (GetMonitorInfo(hmon, &monitorInfo))
				{
					rcClient = monitorInfo.rcWork;
				}
			}
		}
		else
		{
			CopyRect(&rcClient, &wp.rcNormalPosition);
		}

		rcClient.right -= (-rcNCA.left + rcNCA.right);
		rcClient.bottom -= (-rcNCA.top + rcNCA.bottom);
	}

	if ((rcClient.right - rcClient.left) > 0 && (rcClient.bottom - rcClient.top) > 0)
	{
		POINT ptOffset;
		ptOffset.x = ptOffset.y = 10;

		HBITMAP hbm = _CreateDIB(rcClient.right - rcClient.left - 2*ptOffset.x, rcClient.bottom - rcClient.top - 2*ptOffset.y);
		if (hbm)
		{
			hr = set_live_preview(_hwnd, hbm, &ptOffset, 0);
			DeleteObject(hbm);
		}
	}

	return hr;
}

#define RINGWIDTH 10
#define MAXRING 5
#define MAXTABS 20


// This is a helper method to render the tab window contents at a specified
// width and height.
HBITMAP CAeroDrawTestDlg::_CreateDIB(int nWidth, int nHeight)
{
	HBITMAP hbm = NULL;
	HDC hdcMem = CreateCompatibleDC(NULL);

	_iTab = 3;

	if (hdcMem != NULL)
	{
		BITMAPINFO bmi;
		ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = nWidth;
		bmi.bmiHeader.biHeight = -nHeight;  // Use a top-down DIB
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;

		PBYTE pbDS = NULL;
		hbm = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, (VOID**)&pbDS, NULL, NULL);
		if (hbm != NULL)
		{
			int nRed = 0, nBlue = 0, nGreen = 0;

			// Compute tab color: red, orange, yellow, green, blue, indigo, violet
			switch (_iTab % 7)
			{
			case 1:
				nRed = 255;
				break;
			case 2:
				nRed = 255;
				nGreen = 155;
				break;
			case 3:
				nRed = 255;
				nGreen = 255;
				break;
			case 4:
				nGreen = 255;
				break;
			case 5:
				nBlue = 255;
				break;
			case 6:
				nRed = 155;
				nBlue = 255;
				break;
			case 0:
				nRed = 255;
				nBlue = 255;
				break;
			}

			// Fill in the pixels of the bitmap
			for (int y = 0; y < nHeight; y++)
			{
				for (int x = 0; x < nWidth; x++)
				{
					int edgeDistance = min(min(y, nHeight - y), min(x, nWidth - x));
					int ring = min((edgeDistance / RINGWIDTH) + 1, MAXRING);
					int nAlpha = ring * (255 / MAXRING);

					pbDS[0] = (BYTE)(nBlue * nAlpha / 255);
					pbDS[1] = (BYTE)(nGreen * nAlpha / 255);
					pbDS[2] = (BYTE)(nRed * nAlpha / 255);
					pbDS[3] = (BYTE)(nAlpha);

					pbDS += 4;
				}
			}
		}

		DeleteDC(hdcMem);
	}

	return hbm;
}


void CAeroDrawTestDlg::OnBnClickedGetdlg()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	DWORD dwPid = 0;
	char  szBuffer[MAX_PATH] = "", szTemp[MAX_PATH] = "";
	HWND	hParent=NULL;
	HWND	myHwnd = NULL;


	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	UpdateData(TRUE);

	if(m_strValue.IsEmpty())
		m_strValue = "notepad.exe";

	//(LPSTR)(LPCSTR)
	strcpy(szTemp, m_strValue.GetBuffer());

	strcpy(szBuffer, strlwr(szTemp));

	dwPid = CheckRunProcess(szBuffer);

	m_vRect.clear();
	m_rcFull.top = 0;
	m_rcFull.bottom = 0;
	m_rcFull.left = 0;
	m_rcFull.right = 0;
	//memset(m_rcFull, 0, sizeof(m_rcFull));
	::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&m_vRect);

	CString strTemp;
	int ni = 0;
	//strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);
	//strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);

	m_nHeight = m_vRect[0].bottom - m_vRect[0].top;
	m_nWidth = m_vRect[0].right - m_vRect[0].left;
	HWND	CurHwnd = NULL;

//	CurHwnd = this->m_hWnd;

	CurHwnd = SetFromPidtoHnd(dwPid, 0);


//	HWND hwnd = CurHwnd;;
	HDC hTmwDC = ::GetDC(CurHwnd);

	HDC hDC = ::GetDC(NULL);

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, m_nWidth, m_nHeight);
	HBITMAP hOldMemBitmap = (HBITMAP)::SelectObject(hMemDC, hMemBitmap);

	::BitBlt(hMemDC, 0, 0, m_nWidth, m_nHeight, hTmwDC, 0, 0, SRCCOPY);

	CxImage xImage;
	xImage.CreateFromHBITMAP(hMemBitmap);
	xImage.Save("c:\\temp\\Test.bmp", CXIMAGE_SUPPORT_BMP);

	//BITMAP Bitmap;
	//int error = GetObject( &Bitmap, sizeof( BITMAP  ), &m_hMemBitmap );

	::SelectObject(hMemDC, hOldMemBitmap);
	::DeleteObject(hMemBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(NULL, hDC);
	::ReleaseDC(CurHwnd, hTmwDC);
}

void CAeroDrawTestDlg::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex = m_ProcessCombo.GetCurSel();

	if (nIndex < 0)
	{
		return;
	}

	SaveDlgImage(nIndex, m_arrProcessInfo.GetAt(nIndex)->nPid);
}

void CAeroDrawTestDlg::OnCbnDropdownCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HWND hnd= NULL;

	hnd = (HWND)0x00010F12;
	SaveImageIE(hnd);

	hnd = (HWND)0x00020EF6;
	SaveImageIE(hnd);

	hnd = (HWND)0x00010EF2;
	SaveImageIE(hnd);

	hnd = (HWND)0x00010EE8;
	SaveImageIE(hnd);

	SetProcess();
	int nIndex = m_ProcessCombo.GetCurSel();
	if (nIndex < 0)
	{
		return;
	}

	SaveDlgImage(nIndex, m_arrProcessInfo.GetAt(nIndex)->nPid);
}


void CAeroDrawTestDlg::OnBnClickedAll()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	HWND hnd = ::FindWindow(NULL, "Internet Explorer_Server");

	SetProcess();

	int nTotal = m_ProcessCombo.GetCount();

	if (nTotal < 0)
	{
		return;
	}

	// CArray HDC or HBitmap 
	for(int i= 0 ;i <  nTotal ; i++)
	{
		SaveDlgImage(i, m_arrProcessInfo.GetAt(i)->nPid);
	}
	//CString strPID;
	//strPID.Format(_T("%d"), m_arrProcessInfo.GetAt(nIndex)->nPid);


}
