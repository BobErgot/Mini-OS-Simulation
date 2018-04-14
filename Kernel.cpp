#include "Socket.h"
#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
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

void Socket::GetAndSendMessage(string s)
{
    char message[STRLEN];
    strcpy(message,s.c_str());
   // cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Data Sent"<<endl;
    SendData( message );
}


void Socket::GetAndSendMessage()
{
    char message[STRLEN]="10000011";
    //cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Send > ";
    //cin.get( message, STRLEN );
    SendData( message );
}

string Socket::password()
    {
        char recMessage[STRLEN];
        char pass[100];
        GetAndSendMessage("Enter password:");
        cout<<"\t--WAIT--"<<endl;
        RecvData( recMessage, STRLEN );
        cout<<"Recv < "<<recMessage<<endl;
        strcpy(pass,recMessage);
        //cout<<pass;
        return pass;

    }

void Socket::newlogin(string filename,string filepass)
{

     char name[100];
    ofstream outfile,outfile1;
    outfile.open(filename.data(), ios::ate|ios::app);
     ServerSocket sockServer;
     char recMessage[STRLEN];
    char sendMessage[STRLEN];
    GetAndSendMessage("Name:");
    back:
    RecvData( recMessage, STRLEN );
    cout<<"Recv < "<<recMessage<<endl;
    strcpy(name,recMessage);
    //check(name);
    if(check(name)==0) goto back;
    ifstream infile1;
    unsigned int curline1=0;
    string line1;
    infile1.open(filename.data());
    if (infile1.is_open())
    {

        while(getline(infile1,line1))
        {
            curline1++;
            if(line1.find(name,0)!= string::npos)
        {
             if(line1.compare(name) == 0)
           {
          GetAndSendMessage("Username already exists.\nName:");
          infile1.close();
          goto back;
            }
        }
}
}

        outfile<<name<<endl;
        outfile.close();

        outfile1.open(filepass.data(), ios ::ate|ios::app);
      outfile1<<encryption(password())<<endl;
        outfile1.close();
        GetAndSendMessage("Registration successful.");
    }

void Socket::login(string filename,string filepass)
{

   ifstream infile,infile1;
   string line;
   char search1[100];
   char recMessage[STRLEN];
   char sendMessage[STRLEN];
   char pass1[100];
   int flag1;
   infile.open(filename.data());
   infile1.open(filepass.data());
   GetAndSendMessage("Enter the username:");
   back10:
    RecvData( recMessage, STRLEN );
    cout<<"Recv < "<<recMessage<<endl;

    strcpy(search1,recMessage);
     if (check(search1)==0) goto back10;

    if (infile.is_open())
{
        unsigned int curline=0;
        while(getline(infile,line))
        {
            curline++;
            if(line.find(search1,0)!= string::npos)
        {
             if(line.compare(search1) == 0)
           {
            GetAndSendMessage("Enter password:");
            RecvData( recMessage ,STRLEN);
          cout<<"Recv < "<<recMessage<<endl;
            strcpy(pass1,recMessage);
          string line1;
          unsigned int curline1=0;

          if(infile1.is_open())
          {
             while(getline(infile1,line1))
             {
                 curline1++;
                 if(curline1==curline)
                 {
                     if(line1.compare(encryption(pass1))== 0)
                     {
                         system("cls");
                         GetAndSendMessage("------Chat System------");
                         cout<<"\n------Chat System------\n";
                         flag1=1;
                         chat();
                     }

                     else
                        {
                        flag1=0;
                     }

                 }
             }
          }
           }
        }
else flag1=0;
        }
    }
if (flag1==0)
    {
        GetAndSendMessage("Wrong login.\nSession Ended.");
        exit(1);
    }
infile.close();
infile1.close();
}

int Socket::check(string check1)
{
    int c;
    if (check1.find(' ') != std::string::npos)
{
    GetAndSendMessage("Enter data without space.\nName:");
    return c=0;
}
else return c=1;
}
string Socket::encryption(string encrypt)
{
    char code[3] = {'B', 'K', 'S'};
    string cypher = encrypt;

    for (int i = 0; i < encrypt.size(); i++)
        cypher[i] = encrypt[i] ^ code[i % (sizeof(code) / sizeof(char))];

    return cypher;
}

void Socket::chat()
{
         char recMessage[100];
         char sendMessage[100];
            while ( 1 )
        {
            cout<<"\t--WAIT--"<<endl;
            RecvData( recMessage, STRLEN );
            cout<<"Recv > "<<recMessage<<endl;
            GetAndSendMessage();
            if ( strcmp( recMessage, "end" ) == 0 ||strcmp( sendMessage, "end" ) == 0 )
            {
                    GetAndSendMessage("Connection ended.");
                    exit(10);
            }
}
}

void ServerSocket::StartHosting( int port )
{
     Bind( port );
     Listen();
}

void ServerSocket::Listen()
{
    //cout<<"LISTEN FOR CLIENT..."<<endl;

    if ( listen ( mySocket, 1 ) == SOCKET_ERROR )
    {
        cerr<<"ServerSocket: Error listening on socket\n";
        system("pause");
        WSACleanup();
        exit(15);
    }

    //cout<<"ACCEPT CONNECTION..."<<endl;

    acceptSocket = accept( myBackup, NULL, NULL );
    while ( acceptSocket == SOCKET_ERROR )
    {
        acceptSocket = accept( myBackup, NULL, NULL );
    }
    mySocket = acceptSocket;
}

void ServerSocket::Bind( int port )
{
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( "0.0.0.0" );
    myAddress.sin_port = htons( port );

    //cout<<"BIND TO PORT "<<port<<endl;

    if ( bind ( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress) ) == SOCKET_ERROR )
    {
        cerr<<"ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
    }
}

string donor::sendname()
{
    string filename("dname.dat");
    return(filename);
}

string donor::sendpass()
{
    string filepass("dpass.dat");
    return(filepass);
}

string ngo::sendname1()
{
    string filename1("nname.dat");
    return(filename1);
}
string ngo::sendpass1()
{
    string filepass1("npass.dat");
    return(filepass1);
}

int main()
{
    ngo ng;
    donor d;
    char n1[10];
    char n[10];
    int choice;
    int port = 666;
    //char *ipAddress = "127.0.0.1";
    string ipAddress;
    bool done = false;
    char recMessage[STRLEN];
    char sendMessage[STRLEN];
    cout<<"Kernel Manager\n1)Host server\n2) Quit"<<endl;
    cout<<"Enter your choice:";
    cin>>choice;
    if ( choice == 2 )
        exit(0);

    else if ( choice == 1 )
    {
        //SERVER
        ServerSocket sockServer;
        cout<<"HOSTING..."<<endl;
        sockServer.StartHosting( port );
        //Connected
        while( !done )
        {
            cout<<"\t--WAIT--"<<endl;
            sockServer.RecvData( recMessage, STRLEN );
            cout<<"Recv < "<<recMessage<<endl;
            sockServer.GetAndSendMessage("Login/Register as:\n1.Admin\n2.Member\n3.End");
            cout<<"\t--WAIT--"<<endl;
            sockServer.RecvData( recMessage, STRLEN );
            cout<<"Recv < "<<recMessage<<endl;
            strcpy(n1,recMessage);

if (atoi(n1)==1)
{
    sockServer.GetAndSendMessage("\n1.Login\n2.Register-\n");
    cout<<"\t--WAIT--"<<endl;
    back2:
    sockServer.RecvData( recMessage, STRLEN );
    cout<<"Recv < "<<recMessage<<endl;
    strcpy(n,recMessage);
    if(atoi(n)==1)
    {
     sockServer.login(d.sendname(),d.sendpass());

    }
        else if(atoi(n)==2)
        {
         sockServer.newlogin(d.sendname(),d.sendpass());
        }
        else sockServer.GetAndSendMessage("Error\n1.Login\n2.Register-\n");
        goto back2;
    }

else if (atoi(n1)==2)
{
    sockServer.GetAndSendMessage("\n1.Login\n2.Register-\n");
    cout<<"\t--WAIT--"<<endl;
    back1:
    sockServer.RecvData( recMessage, STRLEN );
    cout<<"Recv < "<<recMessage<<endl;
    strcpy(n,recMessage);
    if(atoi(n)==1)
    {
     sockServer.login(ng.sendname1(),ng.sendpass1());

    }
        else if(atoi(n)==2)
        {
         sockServer.newlogin(ng.sendname1(),ng.sendpass1());
        }
       else sockServer.GetAndSendMessage("Error.\n1.Login\n2.Register-\n");
        goto back1;
    }
else if(atoi(n1)==3)
{
    sockServer.GetAndSendMessage("The connection is closed.");
    done = true;
    break;
}
else
{
    break;
}
}
          /* if ( strcmp( recMessage, "end" ) == 0 ||
                    strcmp( sendMessage, "end" ) == 0 )
            {
                done = true;
            }*/
        }
    }

