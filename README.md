# ConsoleGraphics
A library I made between February and June 2021 for graphics in Microsoft Windows command prompt.
The code might be bad because the Windows API is low level and I've robed a lot of the StackOverflow code, LOL.

To compile just use G++ like this:
```
g++ main.cpp -o main.exe -lwinmm
```
################################################
Example:

```cpp
#include <engine/PolyMain.cpp>
#include <stdio.h>

void display()
{
	drawcircle(20,20,10,BG_PINK);
}

int main()
{
	Window(display, 4);
}

```
################################################
