#include <Windows.h>

// Global Variables
HWND plainText, encryptedText;

// Forwrd Declarations
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND hWnd);
void AddControls(HWND hWnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Text Encoder/Decoder";

	// Register wondow class
	WNDCLASS wc = { 0 };
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	if (!RegisterClassW(&wc)) return -1;

	// Create window
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		CLASS_NAME,
		CLASS_NAME,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		720,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Message loop
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd)
{
	HMENU hMenu = CreateMenu();

	AppendMenu(hMenu, MF_STRING, NULL, L"Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd)
{
	CreateWindowW(L"static", L"Plain Text", WS_VISIBLE | WS_CHILD, 20, 20, 158, 20, hWnd, NULL, NULL, NULL);
	plainText = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 20, 50, 540, 200, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"button", L"Encrypt", WS_VISIBLE | WS_CHILD, 460, 270, 100, 50, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Encrypted Text", WS_VISIBLE | WS_CHILD, 20, 330, 158, 20, hWnd, NULL, NULL, NULL);
	encryptedText = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 20, 360, 540, 200, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"button", L"Decrypt", WS_VISIBLE | WS_CHILD, 460, 580, 100, 50, hWnd, NULL, NULL, NULL);
}