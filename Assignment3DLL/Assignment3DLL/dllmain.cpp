// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <Windows.h> //imports windows message boxes
#include <process.h> //process information
#include <tlhelp32.h> //CreateToolhelp32Snapshot

extern "C" __declspec(dllexport) void sayHello(void) {
    MessageBoxW(NULL, L"Hello World!", L"Message from sayHello", MB_OK);
}

extern "C" __declspec(dllexport) void sleepFun(int timeoutDuration) {
    //initialization
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    char timeoutCommand[30];
    sprintf_s(timeoutCommand, "cmd.exe /c timeout %d", timeoutDuration);
    //printf("%s\n", timeoutCommand); test code
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    //createprocess
    if (CreateProcessA(NULL, timeoutCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("sleepFun Process ID: %d\n", _getpid());
        printf("CreateProcessA Process ID: %d\n", pi.dwProcessId);

        //CreateToolhelp32Snapshot
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 proc;
        proc.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(snapshot, &proc)) {
            do {
                if (proc.th32ProcessID == pi.dwProcessId) {
                    printf("Th32 Process ID: %d\n", proc.th32ProcessID);
                    break;
                }
            } while (Process32Next(snapshot, &proc));
        }
        CloseHandle(snapshot); //closes snapshot
    }
    else {
        printf("Cannot create process\n");
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    printf("Hello from DLLMain\n");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

