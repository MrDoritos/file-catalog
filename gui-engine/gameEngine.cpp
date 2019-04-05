#pragma once
#include "pch.h"
#include "gameEngine.h"
#include "box.h"

#include <Windows.h>
#include <chrono>
#include <ctime>

gameEngine* gameEngine::_currentInstance = nullptr;

gameEngine::gameEngine(box* gamecamera, HANDLE originalConsoleBuffer, CHAR_INFO* framebuffer, bool spawnDrawingThread)
	:box(gamecamera)
{
	_currentInstance = this;
	_spawnDrawingThread = spawnDrawingThread;
	closed = false;
	SetTargetTicksPerSecond(20);

	this->framebuffer = framebuffer;
	this->originalConsoleBuffer = originalConsoleBuffer;
	this->screenSize = { (short)sizeX, (short)sizeY };

	for (int i = 0; i < _framebuffersize; i++)
	{
		framebuffer[i].Attributes = 0x000F;
		framebuffer[i].Char.UnicodeChar = 32;
		framebuffer[i].Char.AsciiChar = 0x00;
	}

	memset(keyNewState, 0, 256);
	memset(keyOldState, 0, 256);

	memset(mouseOldState, 0, 5);
	memset(mouseNewState, 0, 5);
}


gameEngine::~gameEngine()
{
	if (originalConsoleBuffer != INVALID_HANDLE_VALUE)
		SetConsoleActiveScreenBuffer(originalConsoleBuffer);
	_currentInstance = nullptr;
}

bool gameEngine::OnUpdate(float elapsedTime)
{
	return false;
}

bool gameEngine::OnFrame()
{
	return false;
}

void gameEngine::OnClose()
{

}

bool gameEngine::OnCreate()
{
	return false;
}

HANDLE gameEngine::CreateBuffer()
{
	return CreateConsoleScreenBuffer(0x80000000U | 0x40000000U, 0, 0, 0x00000001, 0);
}

void gameEngine::Start()
{
	GameThread();
}

int gameEngine::ConstructConsole(int width, int height, int fontw, int fonth, wchar_t * font)
{
	if (consoleOut == INVALID_HANDLE_VALUE)
		return Error(L"Bad Handle", 2);

	sizeX = width;
	sizeY = height;

	rectWindow = { 0,0,1,1 };
	SetConsoleWindowInfo(consoleOut, TRUE, &rectWindow);

	COORD coord = { (short)sizeX, (short)sizeY };
	
	if (!SetConsoleScreenBufferSize(consoleOut, coord))
		return Error(L"SetConsoleScreenBufferSize", 3);
	if (!SetConsoleActiveScreenBuffer(consoleOut))
		return Error(L"SetConsoleActiveScreenBuffer", 4);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

#ifdef GCC
	wcscpy(cfi.FaceName, font);
#else
	wcscpy_s(cfi.FaceName, font);
#endif // GCC

	if (!SetCurrentConsoleFontEx(consoleOut, false, &cfi))
		return Error(L"SetCurrentConsoleFontEx", 5);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(consoleOut, &csbi))
		return Error(L"GetConsoleScreenBufferInfo", 6);
	if (sizeY > csbi.dwMaximumWindowSize.Y)
		return Error(L"Screen Height / Font Height Too Big", 7);
	if (sizeX > csbi.dwMaximumWindowSize.X)
		return Error(L"Screen Width / Font Width Too Big", 8);

	rectWindow = { 0,0,(short)sizeX - 1, (short)sizeY - 1 };
	if (!SetConsoleWindowInfo(consoleOut, TRUE, &rectWindow))
		return Error(L"SetConsoleWindowInfo", 9);

	if (!SetConsoleMode(consoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		return Error(L"SetConsoleMode", 10);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);

	return 0;

}

void gameEngine::Close()
{
	closed = true;
	OnClose();
	SetConsoleActiveScreenBuffer(originalConsoleBuffer);
}

void gameEngine::SetTargetTicksPerSecond(int target)
{
	_targetTicksPerSecond = target > 0 && target < 1000 ? target : 20;
	_tickTime = (int)(1000 / _targetTicksPerSecond);
}

int gameEngine::GetTargetTicksPerSecond()
{
	return _targetTicksPerSecond;
}

BOOL gameEngine::CloseHandler(DWORD evt)
{
	if (_currentInstance) {
		_currentInstance->Close();
		_currentInstance = nullptr;
	}
	return 1;
}

void gameEngine::set(std::wstring& str, int count, int x, int y) {
	while (isDrawing);
	isDrawing = true;
	int length = str.length();
	int offset = get(x, y);
	int max = characters();
	for (int i = offset, b = 0; b < length && b < count && i < offset + count && i < offset + length && i < max; i++, b++) {
		_framebuffer[i] = str[b];
	}
	isDrawing = false;
}


void gameEngine::GameThread()
{
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	float fElapsedTime = 50.0f;

	OnCreate();

	while (!closed) {
		Sleep(_tickTime);

		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		fElapsedTime = elapsedTime.count();

		_HandleInput();

		OnUpdate(fElapsedTime);

		if (!_spawnDrawingThread)
			BeginRaster();

	}	

	Close();
}

void gameEngine::BeginRaster()
{
	if (!closed && OnFrame()) {
		_Translate();
		_WriteFrame();
		clear();
	}	
}


void gameEngine::_WriteFrame()
{
	WriteConsoleOutput(consoleOut, framebuffer, screenSize, { 0,0 }, &rectWindow);
}

void gameEngine::_Translate()
{
	wchar_t b;
	for (int character = 0; character < _framebuffersize; character++) {
		b = _framebuffer[character];
		char* bss = (char*)&b;
		bss[1] = '\0';
		if (b != L'\0'){
			framebuffer[character].Char.UnicodeChar = b;
		} else {
			framebuffer[character].Char.UnicodeChar = L' ';
		}
		//framebuffer[character].Char.UnicodeChar = _framebuffer[character];
		//framebuffer[character].Char.UnicodeChar = 0x2588;
		//framebuffer[character].Attributes = 0x000F;
	}
}

keyState* gameEngine::getKey(int keyId) {
	return &(keys[keyId]);
}

void gameEngine::getKey(int keyId, keyState & keyState)
{
	keyState = keys[keyId];
}

void gameEngine::_HandleInput()
{
	// Handle Keyboard Input
	for (int i = 0; i < 256; i++)
	{
		keyNewState[i] = GetAsyncKeyState(i);

		keys[i].bPressed = false;
		keys[i].bReleased = false;

		if (keyNewState[i] != keyOldState[i])
		{
			if (keyNewState[i] & 0x8000)
			{
				keys[i].bPressed = !keys[i].bHeld;
				keys[i].bHeld = true;
			}
			else
			{
				keys[i].bReleased = true;
				keys[i].bHeld = false;
			}
		}

		keyOldState[i] = keyNewState[i];
	}

	// Handle Mouse Input - Check for window events
	INPUT_RECORD inBuf[32];
	DWORD events = 0;
	GetNumberOfConsoleInputEvents(consoleIn, &events);
	if (events > 0)
		ReadConsoleInput(consoleIn, inBuf, events, &events);

	// Handle events - we only care about mouse clicks and movement
	// for now
	for (DWORD i = 0; i < events; i++)
	{
		switch (inBuf[i].EventType)
		{
		case FOCUS_EVENT:
		{
			consoleFocused = inBuf[i].Event.FocusEvent.bSetFocus;
		}
		break;

		case MOUSE_EVENT:
		{
			switch (inBuf[i].Event.MouseEvent.dwEventFlags)
			{
			case MOUSE_MOVED:
			{
				mousePosX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
				mousePosY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
			}
			break;

			case 0:
			{
				for (int m = 0; m < 5; m++)
					mouseNewState[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;

			}
			break;

			default:
				break;
			}
		}
		break;

		default:
			break;
			// We don't care just at the moment
		}
	}

	for (int m = 0; m < 5; m++)
	{
		mouse[m].bPressed = false;
		mouse[m].bReleased = false;

		if (mouseNewState[m] != mouseOldState[m])
		{
			if (mouseNewState[m])
			{
				mouse[m].bPressed = true;
				mouse[m].bHeld = true;
			}
			else
			{
				mouse[m].bReleased = true;
				mouse[m].bHeld = false;
			}
		}

		mouseOldState[m] = mouseNewState[m];
	}
}
