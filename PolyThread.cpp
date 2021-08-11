
#include <thread>
using std::thread;
#include <vector>
using std::vector;
#include <stdio.h>
#include "PolyUtils.h"
#include "PolyDraw.cpp"
#include "PolyWindow.cpp"

struct ThreadItem {
	char* result; // could've used stringstream too, but don't like their syntax
	thread worker;
};

int n = std::thread::hardware_concurrency();

extern int ThreadWindow()
{
    return 0;
}

extern int ThreadDraw(void (**scene)())
{
    
	int n = std::thread::hardware_concurrency();

    Draw(&scene);
    
	vector<ThreadItem> threadlist;
	threadlist.resize(n);

    for(int i = 0;i < n;i++) {
		threadlist[i].worker = thread(Draw,&threadlist[i].result); // pass rand() as data argument
	}

    
	threadlist[2].worker.join();

    return 0;
}
extern int ThreadWindow()
{
    
	int n = std::thread::hardware_concurrency();

    CreatePWindow();
    
	vector<ThreadItem> threadlist;
	threadlist.resize(n);

    for(int i = 0;i < n;i++) {
		threadlist[i].worker = thread(Draw,&threadlist[i].result); // pass rand() as data argument
	}

    
	threadlist[2].worker.join();

    return 0;
}