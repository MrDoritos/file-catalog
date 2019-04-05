#pragma once
#include "box.h"
#include "Windows.h"
#include <cmath>
#include <iostream>


struct keyState {
	bool bPressed;
	bool bReleased;
	bool bHeld;
};

class gameEngine : protected box
{
public:
	gameEngine(box* gamecamera, HANDLE originalConsoleBuffer, CHAR_INFO* framebuffer, bool spawnDrawingThread);
	~gameEngine();
	//Game update
	virtual bool OnUpdate(float elapsedTime);
	//Return true if any updates ocurred
	virtual bool OnFrame();
	virtual void OnClose();
	virtual bool OnCreate();
	static HANDLE CreateBuffer();
	void Start();
	CHAR_INFO* framebuffer;
	COORD screenSize;
	int ConstructConsole(int width, int height, int fontw, int fonth, wchar_t* font);
	void Close();
	void set(std::wstring & str, int count, int x, int y);
	bool closed;

protected:
	HANDLE originalConsoleBuffer;

	HANDLE consoleOut;
	HANDLE consoleIn;

	void SetTargetTicksPerSecond(int target);
	int GetTargetTicksPerSecond();
	float GetTickTime() { return _tickTime; }
	int GetTickTimeInt() { return std::lroundf(_tickTime); }

private:
	int _targetTicksPerSecond;
	float _tickTime;
	static BOOL CloseHandler(DWORD evt);
	
	static gameEngine* _currentInstance;
	void GameThread();

#pragma region Rastering

public:
	void BeginRaster();

protected:
	bool readyToDraw;	
	SMALL_RECT rectWindow;

private:
	void _WriteFrame();
	void _Translate();
	bool _spawnDrawingThread;

#pragma endregion Rastering

#pragma region UserInput

protected:

	int mousePosX;
	int mousePosY;
	bool consoleFocused;

	short keyOldState[256];
	short keyNewState[256];
	bool mouseOldState[5];
	bool mouseNewState[5];
	keyState keys[256];
	keyState mouse[5];

public:

	void getKey(int keyId, keyState& keyState);
	keyState* getKey(int keyId);
	void getMouse(int mouseId, keyState& keyState);
	int getMouseX() { return mousePosX; }
	int getMouseY() { return mousePosY; }
	bool isFocused() { return consoleFocused; }

private:
	void _HandleInput();
#pragma endregion UserInput

protected:
	int Error(const wchar_t *msg, int err)
	{
#ifdef GCC
		char buf[256];
#else
		wchar_t buf[256];
#endif 

		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		buf[255] = '\0';
		SetConsoleActiveScreenBuffer(originalConsoleBuffer);
		wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
		//std::cout << msg << std::endl;
		//std::cout << buf << std::endl;
		
		//std::cout << "n error ocurred" << std::endl;
		exit(err);
		return err;
	}

};

