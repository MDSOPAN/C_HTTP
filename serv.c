#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
struct addrinfo *result = NULL;
struct addrinfo *ptr = NULL;
struct addrinfo hints;

LPSOCKADDR sockaddr_ip;
int iResult;
WSADATA wsaData;
int main(){
    struct sockaddr_in service;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    struct hostent* localhost = gethostbyname("localhost");
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    SOCKET s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    DWORD err = getaddrinfo("", "", &hints, &result);
    if ( err != 0 ) {
        printf("getaddrinfo failed with error: %d\n", err);
        WSACleanup();
        return 1;
    }
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(8080);
    iResult = bind(s, (SOCKADDR *) &service, sizeof(service));
    if(iResult == SOCKET_ERROR){
        printf("Binding Failed with err: %d",iResult);
        WSACleanup();
        return 1;
    }
    printf("Bind Successful\n");
    
    // iResult = connect( s, (SOCKADDR *) &service.sin_addr, sizeof(service.sin_addr));
    // if (iResult == SOCKET_ERROR) {
    //     closesocket(s);
    //     s = INVALID_SOCKET;
    // }
    SOCKET ClientSocket;
    iResult = listen(s,SOMAXCONN);
    if(iResult != 0){
        printf("listen failed with error: %d\n", iResult);
    }
    printf("listen Successful\n");
    while(TRUE){
        ClientSocket = INVALID_SOCKET;
        ClientSocket = accept(s, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            break;
        }
        printf("accept Successful\n");
        send(s)

    }
    WSACleanup();
    closesocket(s);
    freeaddrinfo(result);
    return 0;
}