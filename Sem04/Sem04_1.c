// 1 - ээс 100 хүртэлх анхны тоонуудыг 100 ширхэг thread ашиглан дэлгэцэнд хэвлэ.
#include <windows.h>
#include <stdio.h>
DWORD WINAPI PrintPrimeNumbers(LPVOID Param)
{
    DWORD Upper = *(DWORD*)Param;
    for(DWORD i = 1; i <= Upper; i++)
    {
        DWORD div = 0;
        if(i == 1) continue;
        else if(i == 2) printf("%d ", i);
        else
        {
            for(DWORD j = 2; j <= i/2; j++)
            {
                if(i%j == 0)
                {
                    div++;
                }
            }

            if(div == 0)
            {
                printf("%d ", i);
            }
        }
    }
    return 0;
}

int main()
{
    DWORD ThreadId;
    HANDLE ThreadHandle;
    int Param;
    Param = 100;

    ThreadHandle = CreateThread(
        NULL,
        0,
        PrintPrimeNumbers,
        &Param,
        0,
        &ThreadId);

    WaitForSingleObject(ThreadHandle, INFINITE);

    CloseHandle(ThreadHandle);
}
