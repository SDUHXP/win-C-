#include <winsock2.h>
#include <iostream>
#include <sstream>
using namespace std;
int main()
{
    WSADATA wsaData;
    PHOSTENT hostinfo;
    SOCKET server, accSock;
    SOCKADDR_IN addr,addrout;
    int port, len = sizeof(SOCKADDR), count = 0;
    char buf[128], *ip;
    ostringstream strout;
    if(WSAStartup(0x202,&wsaData)!=0){
        cout<<"initiate Winsocket DLL error"<<endl;
        return -1;
    }

    //1. create TCP socket server
    server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //2.bind ip address and host port
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(666);
    bind(server,(SOCKADDR*)&addr,sizeof(addr));
    gethostname(buf,sizeof(buf));
    hostinfo = gethostbyname(buf);
    ip = inet_ntoa(*(IN_ADDR*)*hostinfo->h_addr_list);

    //3. listen connection request
    listen(server,1);
    cout<<"server "<<ip<<" waiting for connectiong...."<<endl;

    //4. wait for client request, create socket connection
    accSock = accept(server,(SOCKADDR*)&addrout,&len);
    ip = inet_ntoa(addrout.sin_addr);
    port = htons(addrout.sin_port);
    cout<<"[S] accept client "<<ip<<":"<<port<<endl;

    //5.receive service request, deal with service, send response
    while(1){
        recv(accSock,buf,sizeof(buf),0);
        cout<<"[C] "<<buf<<endl;
        if(strcmp(buf,"quit")==0) break;
        strout<<"echo "<<++count;
        string ostr = strout.str();
        send(accSock,ostr.c_str(),ostr.length()+1,0);
    }

    //6.close socket
    closesocket(accSock);
    closesocket(server);
    WSACleanup();
    return 0;
}
