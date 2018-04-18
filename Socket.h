//Socket.h
#pragma once
#include <iostream>
#include "WinSock2.h"

using namespace std;

const int STRLEN = 256;

class Socket
{
    protected:
        WSADATA wsaData;
        SOCKET mySocket;
        SOCKET myBackup;
        SOCKET acceptSocket;
        sockaddr_in myAddress;
        string encryption(string);
    public:
        Socket();
        ~Socket();
        bool SendData( char* );

        bool RecvData( char*, int );
        void CloseConnection();
        void GetAndSendMessage(string);

       void GetAndSendMessage();
       void newlogin(string,string);
       void login(string,string);
       int check(string);
       string password();
       void chat();
};

class ServerSocket : public Socket
{
    public:
        void Listen();
        void Bind( int port );
        void StartHosting( int port );
};

class ClientSocket : public Socket
{
    public:
        void ConnectToServer( const char *ipAddress, int port );
};
class donor:public Socket
{
//protected:
  //  string filename,filepass;
    public:
    string sendname();
    string sendpass();

};
class ngo:public Socket
{
//protected:
 //   string filename1,filepass1;
    public:
    string sendname1();
    string sendpass1();

};
