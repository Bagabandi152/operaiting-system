#include <winsock2.h>'
#include <windows.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib,"ws2_32.dll") //Winsock Library

int main(){
    printf("\t\t---------- TCP SERVER ----------\n");
    //local variable
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET TCPServerSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClientAdd = sizeof(TCPClientAdd);

    int iBind;

    int iListen;

    SOCKET sAcceptSocket;

    int iSend;
    char SenderBuffer[512];
    printf("Enter a messages: ");
    gets(SenderBuffer);
    int iSenderBuffer = strlen(SenderBuffer) + 1;

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = strlen(RecvBuffer) + 1;

    //STEP-1 WSAStartup Fun
    iWsaStartup = WSAStartup(MAKEWORD(2,2), &Winsockdata);
    if(iWsaStartup != 0){
        printf("WSAStartUp Failed\n");
    }else
        printf("WSAStartUp Success\n");

    //STEP-2 Fill the Structure
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //STEP-3 Socket Creation
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(TCPServerSocket == INVALID_SOCKET){
        printf("TCP Server Socket Creation Failed\n");
    }else
        printf("TCP Server Socket Creation Success\n");

    //STEP-4 Bind Fun
    iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if(iBind == SOCKET_ERROR){
        printf("Binding Failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("Binding Success\n");

    //STEP-5 Listen Fun
    iListen = listen(TCPServerSocket, 2);
    if(iListen == SOCKET_ERROR){
        printf("Listen Fun failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("Listen Fun success\n");

    //STEP-6 Accept
    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
    if(sAcceptSocket == INVALID_SOCKET){
        printf("Accept Failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("Connection Accepted\n");

    //STEP-7 Send Data to Client
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
    if(iSend == SOCKET_ERROR){
        printf("Sending Failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("Data Sending Success\n");

    //STEP-8 Recv Data from Client
    iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
    if(iRecv == SOCKET_ERROR){
        printf("Recieve Data Failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("Data Recieved Success\n");

    //STEP-9 Close Socket
    iCloseSocket = closesocket(TCPServerSocket);
    if(iCloseSocket == SOCKET_ERROR){
        printf("Closing Socket Failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("Closing Socket Success\n");

    //STEP-10 CleanUp from DLL
    iWsaCleanup = WSACleanup();
    if(iWsaCleanup == SOCKET_ERROR){
        printf("CleanUp Fun Failed & Error No -> %d\n", WSAGetLastError());
    }else
        printf("CleanUp Fun Success\n");
    return 0;
}
