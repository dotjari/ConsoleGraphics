#ifndef _POLYWINDOW_CPP_
#define _POLYWINDOW_CPP_

#include <windows.h> 
#include <WinUser.h>
#include <stdio.h>
#include <stdlib.h>
#include <cwchar>
#include <thread>
#include <memory>
#include <clocale>
#include <inttypes.h>
#include <vector>
#include "PolyDraw.cpp"
#include "PolyUtils.h"

int CreatePWindow()
{
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hStdin, &prev_mode); 
	SetConsoleMode(hStdin, ENABLE_EXTENDED_FLAGS | 
    	(prev_mode & ~ENABLE_QUICK_EDIT_MODE));

	coordBufSize.X = WIDTH;
	coordBufSize.Y = HEIGHT;

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	srctWriteRect.Left = srctWriteRect.Top = 0;
	srctWriteRect.Right = WIDTH - 1;
	srctWriteRect.Bottom = HEIGHT - 1;

	hNewScreenBuffer = CreateConsoleScreenBuffer( 
       GENERIC_WRITE, 
       0,
       NULL,                    // default security attributes 
       CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
       NULL);                   // reserved; must be NULL 
	hNewScreenBuffer2 = CreateConsoleScreenBuffer( 
       GENERIC_WRITE, 
       0,
       NULL,                    // default security attributes 
       CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
       NULL);                   // reserved; must be NULL 
    if (hNewScreenBuffer2 == INVALID_HANDLE_VALUE || 
            hNewScreenBuffer == INVALID_HANDLE_VALUE) 
    {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError()); 
        return 1;
    }
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);


	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &srctWriteRect);
	SetConsoleScreenBufferSize(hNewScreenBuffer, coordBufSize);
	SetConsoleWindowInfo(hNewScreenBuffer2, TRUE, &srctWriteRect);
	SetConsoleScreenBufferSize(hNewScreenBuffer2, coordBufSize);
	return 0;
}

#endif