#pragma once
#define DWMACLOAKED 14
#define WINDOW_CLOAKED 2

class CWindowCapture
{
public:
	CWindowCapture();
	~CWindowCapture();

	// ���ڷ� �޾ƿ� HWND�� ȭ���� ĸ���� HBITMAP �������� ��ȯ���ִ� �Լ�
	HBITMAP Capture(HWND);

	// HWND���� �޾ƿ� ĸ�� �ؾ� �ϴ� �ڵ����� Ȯ�� �� Capture�Լ����� ��ȯ�� HBITMAP�� AeroDrawTestDlgSub.cpp �� ����
	HBITMAP FindBitmap(HWND, int);
	int count;
};

