#include "GL\glew.h"
#include "OpenGLRenderer.h"
#include "DemoApp.h"
#include "Clock.h"
#include "LogManager.h"
#include <Windows.h>

DemoApp app;

void mouseFunc(int button, int state, int x, int y) {
	app.onMouse(button, state, x, y);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		app.logManager->Init();
		app.logManager->Info(std::string("Window Initialized"), __FILE__, __LINE__);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:		// left mouse button
		break;

	case WM_RBUTTONDOWN:		// right mouse button
		break;

	case WM_MOUSEMOVE:			// mouse movement
		break;

	case WM_LBUTTONUP:			// left button release
		break;

	case WM_RBUTTONUP:			// right button release
		break;

	case WM_KEYUP:
		break;

	case WM_KEYDOWN:
		int fwKeys;
		LPARAM keyData;
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 
		app.onInput(wParam, 0, 0);
		switch (fwKeys)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}

		break;
	case WM_CLOSE:
		app.logManager->Info(std::string("Window Closed"), __FILE__, __LINE__);
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		app.logManager->Info(std::string("Window Destroyed"), __FILE__, __LINE__);
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		app.logManager->Info(std::string("Window Quit"), __FILE__, __LINE__);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WCHAR* className = new WCHAR[lstrlen(L"My Window")];
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	HDC hdc;
	HGLRC hglrc;

	Clock clock;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		className,
		L"Window Title",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	int pixelFormat;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// size
		1,							// version
		PFD_SUPPORT_OPENGL |		// OpenGL window
		PFD_DRAW_TO_WINDOW |		// render to window
		PFD_DOUBLEBUFFER,			// support double-buffering
		PFD_TYPE_RGBA,				// color type
		32,							// prefered color depth
		0, 0, 0, 0, 0, 0,			// color bits (ignored)
		0,							// no alpha buffer
		0,							// alpha bits (ignored)
		0,							// no accumulation buffer
		0, 0, 0, 0,					// accum bits (ignored)
		16,							// depth buffer
		0,							// no stencil buffer
		0,							// no auxiliary buffers
		PFD_MAIN_PLANE,				// main layer
		0,							// reserved
		0, 0, 0,					// no layer, visible, damage masks
	};



	hdc = GetDC(hwnd);
	pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
	hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		MessageBox(NULL, L"Glew Initialization failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
		exit(-1);
	}

	app.onStart();
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		app.preRender(clock.GetDeltaTime());

		app.render();
		SwapBuffers(hdc);
		app.postRender();
		clock.Tick();
	}

	app.onEnd();

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(hwnd, hdc);
	return msg.wParam;
}

