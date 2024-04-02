#include <stdio.h>
#include <Windows.h>

typedef void (*dllFunction)(void);

int main(void) {
	HINSTANCE importedDLL = LoadLibrary(L"C:\\Users\\Luke Demi\\source\\repos\\Lcdemi\\CSEC-Assignment3\\Assignment3DLL\\Debug\\Assignment3DLL.dll");
	//dllFunction sayHello;
	//sayHello = (dllFunction)GetProcAddress(importedDLL, "sayHello");
	//sayHello();

	dllFunction sleepFun;
	sleepFun = (dllFunction)GetProcAddress(importedDLL, "sleepFun");
	sleepFun(15);
}