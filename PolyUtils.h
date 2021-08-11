#ifndef _POLYUTILS_H_
#define _POLYUTILS_H_

#include <windows.h> 
#include <WinUser.h>
#include <stdio.h>
#include <stdlib.h>
#include <cwchar>
#include <memory>
#include <clocale>
#include <inttypes.h>
#include <vector>

#define WIDTH 800
#define HEIGHT 600
#define PX_SIZE 2
RECT r;
SMALL_RECT r2;
HWND console = GetConsoleWindow(); 

HANDLE hStdout,hStdin, hNewScreenBuffer, hNewScreenBuffer2;
SMALL_RECT srctWriteRect; 
COORD coordBufSize; 
COORD coordBufCoord; 
BOOL fSuccess; 
CHAR_INFO chiBuffer[WIDTH * HEIGHT];

#endif