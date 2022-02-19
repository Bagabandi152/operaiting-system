// 2 матрицийн үржвэр матрицийг бодох. Ингэхдээ шинэ матрицийн элементийн
//тоо болгоноор thread үүсгэж бодно.
#include <windows.h>
#include <stdio.h>

DWORD Sum = 0;
DWORD first[10][10], second[10][10], multiply[10][10];

DWORD WINAPI MultiElements(LPVOID Param)
{
    Sum = 0;
    DWORD row = *(DWORD*)(Param);
    DWORD i = *(DWORD*)(Param + 4);
    DWORD j = *(DWORD*)(Param + 8);
    for (DWORD k = 0; k < row; k++){
        Sum += first[i][k]*second[k][j];
    }
    return 0;
}
int main()
{
    int row1, col1, row2, col2, i, j, k, sum = 0;
    printf("Enter number of rows and columns of first matrix /row col/: \n");
    scanf("%d%d", &row1, &col1);
    printf("Enter elements of first matrix: \n");
    for (i = 0; i < row1; i++)
        for (j = 0; j < col1; j++)
            scanf("%d", &first[i][j]);
    printf("Enter number of rows and columns of second matrix /row col/: \n");
    scanf("%d%d", &row2, &col2);
    while (col1 != row2)
    {
        printf("The multiplication is not possible.\n");
        printf("Enter number of rows of second matrix again: \n");
        scanf("%d", &row2);
    }
    printf("Enter elements of second matrix: \n");
    for (i = 0; i < row2; i++)
        for (j = 0; j < col2; j++)
            scanf("%d", &second[i][j]);
    for (i = 0; i < row1; i++) {
        for (j = 0; j < col2; j++) {
            DWORD ThreadId;
            HANDLE ThreadHandle;
            int Param[3] = {row2, i , j};
            ThreadHandle = CreateThread(
                NULL,
                0,
                MultiElements,
                &Param,
                0,
                &ThreadId);

            WaitForSingleObject(ThreadHandle, INFINITE);
            multiply[i][j] = Sum;
            CloseHandle(ThreadHandle);
        }
    }
    printf("Product of the matrices:\n");
    for (i = 0; i < row1; i++) {
        for (j = 0; j < col2; j++)
            printf("%d ", multiply[i][j]);
        printf("\n");
    }
}
