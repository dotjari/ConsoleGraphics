# ConsoleGraphics
A library I made between February and June 2021 for graphics in Microsoft Windows command prompt.
The code might be bad because the Windows API is low level and I've robed a lot of the StackOverflow code, LOL.

To compile just use G++ like this:
```
g++ main.cpp -o main.exe -lwinmm
```
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
	return 0;
}

```
If for some reason you want to see the cmd color palette, just do this:
```cpp
#include <engine/PolyMain.cpp>
#include <engine/Pallete.cpp>

void display()
{
	drawpallette(0, 0);
}

int main()
{
	Window(display, 4);
	return 0;
}

```
By the way, drawing the color palette can be quite slow as all the code is based on a lot of drawpixel(), at the time I would fix that by creating a Sprite system but then I saw that it was a bit of a futile effort, because porting this lib to other OS than Windows could be complex, and running this lib is quite slow.
