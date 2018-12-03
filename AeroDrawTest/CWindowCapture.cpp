#include "stdafx.h"
#include "CWindowCapture.h"
#include <dwmapi.h>

#define PW_RENDERFULLCONTENT 2
#define DWMMACLOAKED 14
#define WINDOW_CLOAKED 2

CWindowCapture::CWindowCapture()
{
	count = 0;
}


CWindowCapture::~CWindowCapture()
{
}

HBITMAP CWindowCapture::Capture(HWND hTargetWnd) {

	HDC hDC = ::GetDC(hTargetWnd);
	HDC hdcBitmap = ::CreateCompatibleDC(hDC);
	
	CRect rct, DsRct;
	if (hTargetWnd) {
		::GetWindowRect(hTargetWnd, &rct);
		::GetWindowRect(::GetDesktopWindow(), &DsRct);
	}
	else
		return FALSE;

	HBITMAP hBitmap = NULL;
	BOOL bSuccess = FALSE;

	

	BOOL ckFull = FALSE;
	RECT a, b;
	::GetWindowRect(hTargetWnd, &a);
	::GetWindowRect(::GetDesktopWindow(), &b);

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	hBitmap = ::CreateCompatibleBitmap(hDC, rct.Width(), rct.Height());

	if (!hBitmap)
		return FALSE;

	::SelectObject(hMemDC, hBitmap);

	if (!::PrintWindow(hTargetWnd, hMemDC, 2))
		bSuccess = FALSE;
	else {
		if ((rct.left + 8 == DsRct.left || rct.left + 8 == DsRct.left + DsRct.right) && (rct.top + 8 == DsRct.top || rct.top + 8 == DsRct.top + DsRct.bottom) && (rct.right - 8 == DsRct.right || rct.right - 8 == DsRct.right * 2) && (rct.bottom + 32 == DsRct.bottom || rct.bottom + 32 == DsRct.bottom * 2)) {
			// ��üȭ��

			StretchBlt(hMemDC, -8, -8, rct.right - rct.left + 8, rct.bottom - rct.top + 8, hMemDC, 0, 0, rct.right - rct.left - 8, rct.bottom - rct.top - 8, SRCCOPY);
			// ����Ʈ ���� �� ������ ���ֱ� ���� 8�ȼ��� ����
		}
		else {
			// â���

			StretchBlt(hMemDC, -7, 0, rct.right - rct.left + 7, rct.bottom - rct.top, hMemDC, 0, 0, rct.right - rct.left - 7, rct.bottom - rct.top - 7, SRCCOPY);
			// ����Ʈ ���� �� ������ ���ֱ� ���� 7�ȼ��� ����
		}
		bSuccess = TRUE;
	}
	return hBitmap;
}

HBITMAP CWindowCapture::FindBitmap(HWND CurHwnd, int Flag){
	
	// Windows10�� �����ϴ� Application Frame Window��� ��׶��� Store���� ���͸�
	int CloakedVal;
    DwmGetWindowAttribute( CurHwnd, DWMACLOAKED, &CloakedVal, sizeof( CloakedVal ) );
    if ( CloakedVal == WINDOW_CLOAKED )
    {
        return NULL;
    }
	
	char classname[100] = {0};

	::GetClassName(CurHwnd, (LPTSTR)&classname, 100);

	char  szBuffer[MAX_PATH] = "", szTemp[MAX_PATH] = "";
	HWND	hParent=NULL;
	HWND	myHwnd = NULL;
	char	szPath[100] = "";
	
	BOOL check = TRUE;

	CString strTemp;
	int ni = 0;

	if(CurHwnd == NULL)
	{

		return NULL;
	}

	if(::IsWindow(CurHwnd) == FALSE || ::IsWindowVisible(CurHwnd) == FALSE)
	{
	
		return NULL;
	}

	CRect Protectrect;
	::GetWindowRect(CurHwnd, &Protectrect);	
	if(Protectrect.Width() < 10)
	{
		return NULL;
	}
	count++;
	TRACE("%s Top %d,%d Bottom %d %d\n",szPath, Protectrect.top, Protectrect.left, Protectrect.bottom, Protectrect.right);
	HDC hTmwDC = ::GetDC(CurHwnd);

	HDC hDC = ::GetDC(NULL);

	HDC hMemDC = ::CreateCompatibleDC(hDC);

	WINDOWPLACEMENT wp = {0};
	wp.length = sizeof(WINDOWPLACEMENT);
	::GetWindowPlacement(CurHwnd, &wp);

	ANIMATIONINFO ai = {0};
	bool restoreAnimation = false;
	
	// �ּ�ȭ �Ǿ����� �� ����ȭ �� â �ø��� �۾�
	if (wp.showCmd == SW_SHOWMINIMIZED)
	{
		ai.cbSize = sizeof(ANIMATIONINFO);
		SystemParametersInfo(SPI_GETANIMATION, sizeof(ANIMATIONINFO), &ai, 0);

		if (ai.iMinAnimate != 0)
		{
			ai.iMinAnimate = 0;
			SystemParametersInfo(SPI_SETANIMATION, sizeof(ANIMATIONINFO), &ai, 0);
			restoreAnimation = true;
		}

		::SetWindowLong(CurHwnd, GWL_EXSTYLE, GetWindowLong(CurHwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		::SetLayeredWindowAttributes(CurHwnd, 0, 0, LWA_ALPHA);
		
		::ShowWindow(CurHwnd, SW_SHOWNOACTIVATE);
		Sleep(500);
	}

	HBITMAP hMemBitmap = Capture(CurHwnd);
	
	// â ������ �۾�
	if (wp.showCmd == SW_SHOWMINIMIZED)
	{
		::SetWindowPlacement(CurHwnd, &wp);
		::SetWindowLong(CurHwnd, GWL_EXSTYLE, GetWindowLong(CurHwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		::SetLayeredWindowAttributes(CurHwnd, 0, 255, LWA_ALPHA);

		if (restoreAnimation)
		{
			ai.iMinAnimate = 1;
			SystemParametersInfo(SPI_SETANIMATION, sizeof(ANIMATIONINFO), &ai, 0);
		}
	}

	// �Ʒ��� �ִ� Class���� ���� ���μ����鸸 Child�� �˻��Ѵ�
	if(Flag == 0){
		if((strstr(classname, "Chrome") == NULL &&
			strstr(classname, "Application") == NULL &&
			strstr(classname, "PPTFrameClass") == NULL &&
			strstr(classname, "IEFrame") == NULL &&
			strstr(classname, "XLMAIN") == NULL &&
			strstr(classname, "MozillaWindowClass") == NULL &&
			strstr(classname, "HwpApp") == NULL)){
				return NULL;
		}
	}

	// �Ʒ��� �ִ� Class���� ���� ���μ������� Child �˻� ����� �ߺ��� �� �ֱ� ������ Top Window�� �˻��Ѵ�
	if(Flag == 1){
		if(strstr(classname, "Chrome") ||
			strstr(classname, "ApplicationFrame") ||
			strstr(classname, "PowerPoint") ||
			strstr(classname, "IEFrame") ||
			strstr(classname, "XLMAIN") ||
			strstr(classname, "MozillaWindowClass") ||
			strstr(classname, "HwpApp") ||
			strstr(classname, "PPTFrameClass") ||
			strstr(classname, "Shell_TrayWnd") ||
			strstr(classname, "Windows.UI.Core.CoreWindow") ||
			strstr(classname, "Shell_SecondaryTrayWnd")){
				return NULL;
		}
	}
	return hMemBitmap;
}