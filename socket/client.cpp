#include <winsock2.h>
#include <iostream>
using namespace std;
int main()
{
    WSADATA wsaData;
    SOCKET client;
    SOCKADDR_IN addr;
    char buf[128];
    if(WSAStartup(0x202,&wsaData)!=0){
        cout<<"initiate Winsocket DLL error"<<endl;
        return -1;
    }
    //1¡¢create TCP socket of client
    client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    cout<<"[I] server: ";
    cin>>buf;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(buf);
    addr.sin_port = htons(6666);

    //2. initiate connection, request connection
    if(connect(client,(SOCKADDR*)&addr,sizeof(addr))==SOCKET_ERROR){
        cout<<"connect failed:"<<WSAGetLastError()<<endl;
        WSACleanup();
        return -1;
    }

    //3. send telegram,receive response
    while(1){
        cout<<"[I] message: ";
        cin>>buf;
        send(client,buf,strlen(buf)+1,0);
        if(strcmp(buf,"quit")==0) break;
        recv(client,buf,sizeof(buf),0);
        cout<<"[S] "<<buf<<endl;
    }

    //4. close socket
    closesocket(client);
    WSACleanup();


    cout << "Hello world!" << endl;
    return 0;
}
