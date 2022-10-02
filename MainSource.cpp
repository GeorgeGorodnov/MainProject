#include <Windows.h>
#include "Header.h"
#include <iostream>
#include <string>

int WINAPI main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	setlocale(LC_ALL, "ru");
	HBRUSH greenBrush = CreateSolidBrush(RGB(172, 255, 196));

	WNDCLASS SoftWareMainClass = NewWindowClass((HBRUSH)greenBrush, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftWareMainClass)) { return -1; }

	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWindClass", L"ElProgramma", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 1400, 720, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {

	WNDCLASS NWC = { 0 };
	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;
	return NWC;
}

char backmsg[TextBufferSize];
char task[TaskMessageSize] = "Имеется набор данных, состоящий из пар положительных целых чисел.Необходимо выбрать из каждой пары ровно одно число так, чтобы сумма всех выбранных чисел не делилась на 3 и при этом была максимально возможной.Гарантируется, что искомую сумму получить можно.Программа должна напечатать одно число — максимально возможную сумму, соответствующую условиям задачи.\nВходные данные.\nДаны два входных файла(файл A и файл B), каждый из которых содержит в первой строке количество пар N(1 < N < 10000).Каждая из следующих N строк содержит два натуральных числа, не превышающих 10 000.\nПример организации исходных данных во входном файле : \n6\n1 3\n5 12\n6 9\n5 4\n3 3\n1 1\nДля указанных входных данных значением искомой суммы должно быть число 32.\nВ ответе укажите два числа : сначала значение искомой суммы для файла А, затем для файла B.\nПредупреждение : для обработки файла B не следует использовать переборный алгоритм, вычисляющий сумму для всех возможных вариантов, поскольку написанная по такому алгоритму программа будет выполняться слишком долго.";

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnMenuClicked1:
			std::cout << "\a";
			MessageBoxA(hWnd, "Menu was clicked", "Menu Worked", MB_OK);
			break;
		case OnButtonClicked:
			SetWindowTextA(hEditControl, "");
			MessageBoxA(hWnd, "Button clicked down", "Button Worked up", MB_OK);
			break;


		case OnReadClicked:
			//считываем текст из окна hEditControl (ВВОД)
			//Buffer - массив символов, которые мы считали
			GetWindowTextA(hEditControl, Buffer, TextBufferSize);
			//выводим текст в окно hStaticControl (ИТОГ)
			SetWindowTextA(hStaticControl, Buffer);
			break;


		case ExitClicked:
			PostQuitMessage(0);
			break;
		case SubMenuClicked1:
			MessageBoxA(hWnd, "DOWN", "UP", MB_OK);
			break;
		case SubMenuClicked2:
			MessageBoxA(hWnd, "DOWN2", "UP2", MB_OK);
			break;
		case SubMenuClicked3:
			MessageBoxA(hWnd, "DOWN3", "UP3", MB_OK);
			break;
		default: break;
		}
		break;
	case WM_CREATE:
		MainWindowAddMenu(hWnd);
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWindowAddMenu(HWND hWnd) {
	HMENU MainMenu = CreateMenu();
	HMENU SecMenu = CreateMenu();

	AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)SecMenu, L"Второе меню");
	AppendMenu(SecMenu, MF_STRING, SubMenuClicked1, L"Меню1");
	AppendMenu(SecMenu, MF_STRING, SubMenuClicked2, L"Меню2");
	AppendMenu(SecMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SecMenu, MF_STRING, SubMenuClicked3, L"Меню3");
	AppendMenu(MainMenu, MF_STRING, OnMenuClicked1, L"Вариант1");
	AppendMenu(MainMenu, MF_STRING, ExitClicked, L"Выйти");
	SetMenu(hWnd, MainMenu);
}

void MainWndAddWidgets(HWND hWnd) {
	CreateWindowA("static", task, WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 1000, 300, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Итог:", WS_VISIBLE | WS_CHILD, 5, 585, 490, 20, hWnd, NULL, NULL, NULL);
	hEditControl = CreateWindowA("edit", "Ввод", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 5, 325, 490, 200, hWnd, NULL, NULL, NULL);
	//CreateWindowA("button", "Очистить", WS_VISIBLE | WS_CHILD, 5, 60, 120, 30, hWnd, (HMENU)OnButtonClicked, NULL, NULL);
	CreateWindowA("button", "Отправить", WS_VISIBLE | WS_CHILD, 5, 545, 120, 30, hWnd, (HMENU)OnReadClicked, NULL, NULL);
	hStaticControl = CreateWindowA("static", "", WS_VISIBLE | WS_CHILD, 65, 585, 420, 20, hWnd, NULL, NULL, NULL);
}
