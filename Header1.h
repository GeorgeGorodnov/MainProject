#pragma once
#define OnMenuClicked1			1
#define ExitClicked				201
#define OnMenuClicked3			3
#define SubMenuClicked1			101
#define SubMenuClicked2			102
#define SubMenuClicked3			103
#define SubMenuClicked4			104
#define OnButtonClicked         301
#define OnReadClicked           302
#define TextBufferSize			2048
#define TaskMessageSize			2048

char Buffer[TextBufferSize];

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
HWND hEditControl;
HWND hStaticControl;

void MainWindowAddMenu(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
