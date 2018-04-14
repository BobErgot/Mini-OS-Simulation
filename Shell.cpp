#include <iostream>
#include<conio.h>
#include "Socket.h"

using namespace std;

Socket::Socket()
{
    if( WSAStartup( MAKEWORD(2, 2), &wsaData ) != NO_ERROR )
    {
        cerr<<"Socket Initialization: Error with WSAStartup\n";
        system("pause");
        WSACleanup();
        exit(10);
    }

    //Create a socket
    mySocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if ( mySocket == INVALID_SOCKET )
    {
        cerr<<"Socket Initialization: Error creating socket"<<endl;
        system("pause");
        WSACleanup();
        exit(11);
    }

    myBackup = mySocket;
}

Socket::~Socket()
{
    WSACleanup();
}

bool Socket::SendData( char *buffer )
{
    send( mySocket, buffer, strlen( buffer ), 0 );
    return true;
}

bool Socket::RecvData( char *buffer, int size )
{
    int i = recv( mySocket, buffer, size, 0 );
    buffer[i] = '\0';
    return true;
}

void Socket::CloseConnection()
{
    //cout<<"CLOSE CONNECTION"<<endl;
    closesocket( mySocket );
    mySocket = myBackup;
}

void Socket::GetAndSendMessage()
{
    char message[STRLEN];
    cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Send > ";
    cin.get( message, STRLEN );
    SendData( message );
}

void Socket::GetAndSendMessage(string s)
{
    char message[STRLEN];
    //cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
  //  cout<<"Send > ";
   // cin.get( message, STRLEN );
   strcpy(message,s.c_str());
    SendData( message );
}

void ClientSocket::ConnectToServer( const char *ipAddress, int port )
{
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( ipAddress );
    myAddress.sin_port = htons( port );

    //cout<<"CONNECTED"<<endl;

    if ( connect( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress ) ) == SOCKET_ERROR )
    {
        cerr<<"ClientSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(13);
    }
}

int main()
{
    int choice;
    int port = 666;
    //char *ipAddress = "127.0.0.1";
    string ipAddress;
    bool done = false;
    char recMessage[STRLEN];
    char sendMessage[STRLEN];
    cout<<"Shell Interface\n1)Join server\n2)Quit"<<endl;
    cout<<"Enter your choice:";
    cin>>choice;
    if ( choice == 2 )
        exit(0);
    else if ( choice == 1 )
    {
        //Client
        cout<<"Enter an IP address(127.0.0.1 is the loopback address):";
        cin>>ipAddress;
        ClientSocket sockClient;
        cout<<"ATTEMPTING TO CONNECT..."<<endl;
        sockClient.ConnectToServer( ipAddress.c_str(), port );
        //Connected
        while ( !done )
        {

             if ( strcmp( recMessage, "Enter password:" ) == 0 )
            {
                const char BACKSPACE=8;
  const char RETURN=13;

  string password;
  unsigned char ch=0;

 // cout <<prompt<<endl;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(true)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(true)
                 cout <<'*';
         }
    }
             sockClient.GetAndSendMessage(password);
            }
            else sockClient.GetAndSendMessage();
            cout<<"\t--WAIT--"<<endl;
            sockClient.RecvData( recMessage, STRLEN );
            if ( strcmp( recMessage, "------Chat System------" ) == 0 )
            {
                system("cls");
            }
            cout<<"----Recv ----"<<endl;
            cout<<recMessage<<endl;


            if ( strcmp( recMessage, "end" ) == 0 ||
                        strcmp( sendMessage, "end" ) == 0 )
            {
                done = true;
            }
        }
        sockClient.CloseConnection();
    }


}
