#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>

#define MAX 2

int _tmain(int argc, TCHAR *argv[]) {
    HANDLE hProcessSnap =
            CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //print current pid
    DWORD c = GetCurrentProcessId();
    printf("Current PID is %lu \n", c);
    //snapshot all process
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        _tprintf(_T("CreateToolhelp32Snapshot error \n"));
        exit(EXIT_FAILURE);
    }
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    //retrieve the process information
    if (!Process32First(hProcessSnap, &pe32)) {
        _tprintf(_T("Process32First error ! \n"));
        CloseHandle(hProcessSnap);
        exit(EXIT_FAILURE);
    }

    _tprintf(_T("\t[Process name] \t[PID]\t[ThreadID]\t[PPID] \n"));
    //print all process information
    do {
        if (pe32.th32ProcessID == c) {
            _tprintf(_T("%25s %8d %8d %8d This process\n"),
                     pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID);
        } else {
            _tprintf(_T("%25s %8d %8d %8d \n"),
                     pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    char name[MAX];
    printf("Waiting for enter: ");
    fgets(name, MAX, stdin);

    return 0;
}
