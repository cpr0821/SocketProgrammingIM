#include <iostream>
#include <iomanip>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080

using namespace std;

int main()
{
    struct sockaddr_in serv_addr;
    int sockfd, connfd;
    char buffer[1024] = { 0 };


    // Creation of socket with IPv4 domain, type TCP, protocol 0
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Error creating socket" << endl;
        return 0;
    }
    else {
        cout << "Socket created" << endl;
    }

    serv_addr.sin_family = AF_INET; // match the socket() call
    serv_addr.sin_port = htons(PORT); // bind to port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // bind to address

    // connect
    if ((connfd = connect(sockfd, (struct sockaddr*) & serv_addr, sizeof(serv_addr))) < 0) {
        cout << "Cannot connect" << endl;
    }
    else {
        cout << "Connected" << endl;
        
        while(1){
          string data;
          getline(cin, data);
          memset(&buffer, 0, sizeof(buffer));   //clear buffer
          strcpy(buffer, data.c_str());
          
          if (data == "exit")
          {
              send(sockfd, (char*)&buffer, strlen(buffer), 0);
              break;
          }
          
          send(sockfd, (char*)&buffer, strlen(buffer),0); 
          cout << "Waiting for server response" << endl;
          
          
          memset(&buffer, 0, sizeof(buffer));  //clear buffer
          
          recv(sockfd, (char*)&buffer, sizeof(buffer),0);
          if(!strcmp(buffer, "exit"))
          {
              cout << "Server has quit the session" << endl;
              break;
          }
  
          cout << "Server: " << buffer << endl;
        }
        
    }



    // send and receive data
    // read(sockfd, buffer, sizeof(buffer);
    // write(sockfd, "hey\n", strlen("hey\n"));

    // Compiling:
    // gcc client.c -o client
    // gcc server.c -o server
    close(socket(AF_INET, SOCK_STREAM, 0));
    cout << "Connection Closed" << endl;
    
    
    return 0;
}





