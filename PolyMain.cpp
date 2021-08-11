#ifndef _POLYMAIN_CPP_
#define _POLYMAIN_CPP_

#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <stdlib.h>
#include <cwchar>
#include <future>
#include <memory>
#include <thread>
#include <clocale>
#include <iostream>
#include <inttypes.h>
#include <vector>
#include "PolyDraw.cpp"
#include "PolyWindow.cpp"
#include "PolyUtils.h"

#include <chrono>
#include <vector>
#include <list>
#include <atomic>
#include <condition_variable>

float FPS = 1/60.0f * 1000.0f;
using namespace std;

bool DebugGrid = false;

extern void setcursor(bool visible, DWORD size);

SHORT isKeyPressed(int vk) {
	return (GetAsyncKeyState(vk));
}
static int i = 0;
HANDLE curScreenBufferHandle;

static std::atomic<bool> AtomActive;

void ChangeScreenSize (int x, int y )
{
	HANDLE                     hOut        = GetStdHandle( STD_OUTPUT_HANDLE );
	SMALL_RECT                 DisplayArea = { 0, 0, 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;


	GetConsoleScreenBufferInfo( hOut, &SBInfo );

	DisplayArea.Bottom = y;
	DisplayArea.Right  = x;

	SetConsoleWindowInfo( hOut, true, &DisplayArea );
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   
   const HWND hDesktop = GetDesktopWindow();
   
   GetWindowRect(hDesktop, &desktop);
   
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

extern int Window(void (*scene)(), int ps) 
{ 
	
	AtomActive = true;
	std::thread threadDraw(scene);
	std::thread threadWin(CreatePWindow);
	threadWin.join();
	threadDraw.join();

	int sw;
	int sh;
	GetDesktopResolution(sw, sh);
	while(AtomActive)
	{
		MoveWindow(console, 300, 300, WIDTH, HEIGHT, TRUE);
		setPixelSize(ps);
		
		if(i%2==0){
			curScreenBufferHandle = hNewScreenBuffer;
		} else {
			curScreenBufferHandle = hNewScreenBuffer2;
		}

		// clear
		
		if(DebugGrid == true)
		{
			for (int y = 0; y < HEIGHT; ++y)
			{
				for (int x = 0; x < WIDTH; ++x)
				{
					chiBuffer[x + WIDTH * y].Char.UnicodeChar = '.';
					chiBuffer[x + WIDTH * y].Attributes = FG_WHITE;
				}
			}
		}
		else 
		{
			for (int y = 0; y < HEIGHT; ++y)
			{
				for (int x = 0; x < WIDTH; ++x)
				{
					chiBuffer[x + WIDTH * y].Char.UnicodeChar = ' ';
					chiBuffer[x + WIDTH * y].Attributes = FG_WHITE;
				}
			}
		}
		// present
		scene();

		fSuccess = WriteConsoleOutput( 
				curScreenBufferHandle, // screen buffer to write to 
				chiBuffer,        // buffer to copy from 
				{ (short)WIDTH, (short)HEIGHT }, 
				{ 0,0 },    // top left src cell in chiBuffer 
				&srctWriteRect);
			
			if (! SetConsoleActiveScreenBuffer(curScreenBufferHandle)) {
				printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError()); 
				system("pause");
				exit(0);
			}

		
		memset(chiBuffer, 0, sizeof(CHAR_INFO) * WIDTH * HEIGHT);

		Sleep(FPS);
		i++;
	}
	//memset(curScreenBufferHandle, 0, sizeof(HANDLE));
		
    return 0;
}


/*
extern void initThread(int n)
{
	
	std::vector<thread> threads(n);
    // spawn n threads:
    for (int i = 0; i < n; i++) {
        threads[i] = thread(Window, i + 1);
    }

    for (auto& th : threads) {
        th.join();
    }
}*/


#endif
