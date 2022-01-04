#include <Windows.h>

const int ENCRYPT_TEXT = 1;
const int DECRYPT_TEXT = 2;

// Global Variables
HWND plainText, encryptedText, plugBoard, rotor1_p, rotor1_r, rotor2_p, rotor2_r, rotor3_p, rotor3_r;

// Forwrd Declarations
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND hWnd);
void AddControls(HWND hWnd);
void encrypt_text();
void decrypt_text();

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
		1000,
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
	case WM_COMMAND:
		switch (wp)
		{
		case ENCRYPT_TEXT:
			encrypt_text();
			break;
		case DECRYPT_TEXT:
			decrypt_text();
			break;
		}
		break;
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
	int left_x = 20;
	int left_y = 20;
	int text_width = 158;
	int text_height = 20;
	int textbox_width = 540;
	int textbox_height = 200;

	// Text Area
	CreateWindowW(L"static", L"Plain Text", WS_VISIBLE | WS_CHILD, left_x, left_y, text_width, text_height, hWnd, NULL, NULL, NULL);
	plainText = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, left_x, left_y+30, textbox_width, textbox_height, hWnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Encrypt", WS_VISIBLE | WS_CHILD, left_x + 440, left_y + textbox_height + 30, 100, 50, hWnd, (HMENU)ENCRYPT_TEXT, NULL, NULL);

	CreateWindowW(L"static", L"Encrypted Text", WS_VISIBLE | WS_CHILD, left_x, left_y +300, text_width, text_height, hWnd, NULL, NULL, NULL);
	encryptedText = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, left_x, left_y+350, textbox_width, textbox_height, hWnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Decrypt", WS_VISIBLE | WS_CHILD, left_x + 440, left_y + 550, 100, 50, hWnd, (HMENU)DECRYPT_TEXT, NULL, NULL);

	// Enigma Machine Settings
	int e_settings_x = left_x + 600;
	CreateWindowW(L"static", L"Enigma Machine Settings", WS_VISIBLE | WS_CHILD, e_settings_x, left_y, text_width+50, textbox_height, hWnd, NULL, NULL, NULL);

	// Roter 1
	CreateWindowW(L"static", L"Roter 1", WS_VISIBLE | WS_CHILD, e_settings_x, 50, text_width, text_height, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Position", WS_VISIBLE | WS_CHILD, e_settings_x+20, 70, text_width, text_height, hWnd, NULL, NULL, NULL);
	rotor1_p = CreateWindowW(L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, e_settings_x+80, 70, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"MSCTLS_UPDOWN32", L"", WS_VISIBLE | WS_CHILD, e_settings_x+130, 70, 20, 20, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Ring", WS_VISIBLE | WS_CHILD, e_settings_x + 170, 70, text_width, text_height, hWnd, NULL, NULL, NULL);
	rotor1_r = CreateWindowW(L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, e_settings_x + 210, 70, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"MSCTLS_UPDOWN32", L"", WS_VISIBLE | WS_CHILD, e_settings_x + 260, 70, 20, 20, hWnd, NULL, NULL, NULL);

	// Roter 2
	CreateWindowW(L"static", L"Roter 2", WS_VISIBLE | WS_CHILD, e_settings_x, 100, text_width, text_height, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Position", WS_VISIBLE | WS_CHILD, e_settings_x + 20, 120, text_width, text_height, hWnd, NULL, NULL, NULL);
	rotor2_p = CreateWindowW(L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, e_settings_x + 80, 120, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"MSCTLS_UPDOWN32", L"", WS_VISIBLE | WS_CHILD, e_settings_x + 130, 120, 20, 20, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Ring", WS_VISIBLE | WS_CHILD, e_settings_x + 170, 120, text_width, text_height, hWnd, NULL, NULL, NULL);
	rotor2_r = CreateWindowW(L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, e_settings_x + 210, 120, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"MSCTLS_UPDOWN32", L"", WS_VISIBLE | WS_CHILD, e_settings_x + 260, 120, 20, 20, hWnd, NULL, NULL, NULL);

	// Roter 3
	CreateWindowW(L"static", L"Roter 3", WS_VISIBLE | WS_CHILD, e_settings_x, 150, text_width, text_height, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Position", WS_VISIBLE | WS_CHILD, e_settings_x + 20, 170, text_width, text_height, hWnd, NULL, NULL, NULL);
	rotor3_p = CreateWindowW(L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, e_settings_x + 80, 170, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"MSCTLS_UPDOWN32", L"", WS_VISIBLE | WS_CHILD, e_settings_x + 130, 170, 20, 20, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Ring", WS_VISIBLE | WS_CHILD, e_settings_x + 170, 170, text_width, text_height, hWnd, NULL, NULL, NULL);
	rotor3_r = CreateWindowW(L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, e_settings_x + 210, 170, 50, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"MSCTLS_UPDOWN32", L"", WS_VISIBLE | WS_CHILD, e_settings_x + 260, 170, 20, 20, hWnd, NULL, NULL, NULL);

	// Plug Board
	CreateWindowW(L"static", L"Plug Board", WS_VISIBLE | WS_CHILD, e_settings_x, 200, text_width, text_height, hWnd, NULL, NULL, NULL);
	plugBoard = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, e_settings_x, 225, text_width+120, text_height, hWnd, NULL, NULL, NULL);
	
}

void encrypt_text()
{
	wchar_t text[100];
	GetWindowTextW(plainText, text, 100);		// get text from text box
	SetWindowTextW(encryptedText, text);		// update encryptedText box
}
void decrypt_text()
{
	wchar_t text[100];
	GetWindowTextW(encryptedText, text, 100);	// get text from text box
	SetWindowTextW(plainText, text);			// update plaintext box
}