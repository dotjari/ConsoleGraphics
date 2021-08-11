#ifndef _POLYDRAW_CPP_
#define _POLYDRAW_CPP_
#define _WIN32_WINNT 0x0500
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
#include "PolyUtils.h"
using namespace std;

#define	FG_BLACK		  0x0000
#define FG_DARK_BLUE      0x0001
#define	FG_DARK_GREEN     0x0002
#define	FG_DARK_CYAN      0x0003
#define	FG_DARK_RED       0x0004
#define	FG_DARK_PINK      0x0005
#define	FG_DARK_YELLOW    0x0006
#define	FG_GREY			  0x0007
#define	FG_DARK_GREY      0x0008
#define	FG_BLUE			  0x0009
#define	FG_GREEN		  0x000A
#define	FG_CYAN			  0x000B
#define	FG_MAGENTA		  0x000D
#define	FG_YELLOW		  0x000E
#define	FG_WHITE		  0x000F
#define	BG_BLACK		  0x0000
#define	BG_DARK_BLUE	  0x0010
#define	BG_DARK_GREEN	  0x0020
#define	BG_DARK_CYAN	  0x0030
#define	BG_DARK_RED		  0x0040
#define	BG_DARK_PINK      0x0050
#define	BG_DARK_YELLOW	  0x0060
#define	BG_GREY			  0x0070
#define	BG_DARK_GREY	  0x0080
#define	BG_BLUE			  0x0090
#define	BG_GREEN		  0x00A0
#define	BG_CYAN			  0x00B0
#define	BG_RED			  0x00C0
#define	BG_PINK		      0x00D0
#define	BG_YELLOW		  0x00E0
#define	BG_WHITE		  0x00F0

/*
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;*/
//the function declaration begins
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

void setPixelSize(int pixelSize)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = pixelSize;
	cfi.dwFontSize.Y = pixelSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(hNewScreenBuffer, FALSE, &cfi);
	SetCurrentConsoleFontEx(hNewScreenBuffer2, FALSE, &cfi);
}

void Draw(void (*draw)())
{
    draw();
}
void drawpixel(int x, int y, int color)
{
	int pixelCoord = (int)(x) + WIDTH * (int)(y);

	if( 0 < pixelCoord && pixelCoord < WIDTH * HEIGHT ){
		chiBuffer[pixelCoord].Char.UnicodeChar = ' ';
		chiBuffer[pixelCoord].Attributes = color;
	}

}


void drawcircle(int xc, int yc, int r, int col)
{
	int x = 0;
	int y = r;
	int p = 3 - 2 * r;
	if (!r) return;

	while (y >= x) // only formulate 1/8 of circle
	{
		drawpixel(xc - x, yc - y, col);//upper left left
		drawpixel(xc - y, yc - x, col);//upper upper left
		drawpixel(xc + y, yc - x, col);//upper upper right
		drawpixel(xc + x, yc - y, col);//upper right right
		drawpixel(xc - x, yc + y, col);//lower left left
		drawpixel(xc - y, yc + x, col);//lower lower left
		drawpixel(xc + y, yc + x, col);//lower lower right
		drawpixel(xc + x, yc + y, col);//lower right right
		if (p < 0) p += 4 * x++ + 6;
		else p += 4 * (x++ - y--) + 10;
	}
}

#endif