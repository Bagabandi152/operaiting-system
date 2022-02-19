#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
//int argc, TCHAR *argv[]
void _tmain(int argc, TCHAR *argv[])
{

    HANDLE hProcess;
    HANDLE hThread;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;

    ZeroMemory( &si, sizeof(si) );
    ZeroMemory( &pi, sizeof(pi) );

    char pname[20];
    printf("Enter a name of process: ");
    scanf("%s", pname);
    BOOL bCreateProcess = NULL;
    char p_path[] = "C:\\Users\\Bagaa\\OneDrive\\Documents\\2021-2022-autumn-semister\\TOS\\Sem03\\";
    strcat(p_path, pname);
    bCreateProcess = CreateProcess(
        NULL,
        p_path,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi);

    // Start the child process.
    if(bCreateProcess){
        printf("CreateProcess successfully.\n");
        return;
    }else{
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles.
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
