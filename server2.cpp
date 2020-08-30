#include <iostream>
#include <iomanip>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

using namespace std;

int main()
{
  struct sockaddr_in saddr, caddr;
  int sockfd, isock;
  char buffer[1024] = {0};
  
  memset(&saddr, '\0', sizeof(saddr));          // zero the structure out
  saddr.sin_family = AF_INET;                   // match the socket() call
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);  // bind to any local address
  saddr.sin_port = htons(PORT);                 // specify port to listen on
  
  // Creation of socket with IPv4 domain, type TCP, protocol 0
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    cout << "Error creating socket" << endl;
    return 0;
  }
  
  // bind
  if((bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr))) < 0){
    cout << "Error binding" << endl;
    return 0;
  }
  else{
    cout << "Is bound" << endl;
  }
  
  // listen for incoming connections (5 is number of pending connections to queue)
  if(listen(sockfd, 5) < 0){
    cout << "Error listening" << endl;
    return 0;
  }
  else{
    cout << "Is listening" << endl;
  }
 
  // accept one
  cout << "1" << endl;
  
  socklen_t clen = sizeof(caddr);
  cout << "2" << endl;
  isock = accept(sockfd, (struct sockaddr*)&caddr,&clen);
  
  if(isock < 0){  
    cout << "Error accepting" << endl;
    return 0;
  }
  
  // While the connection is made
  bool flag = true;
  while(flag)
    {
    cout << "in while"<< endl;
        //receive a message from the client (listen)
        memset(&buffer, 0, sizeof(buffer));
        recv(isock, (char*)&buffer, sizeof(buffer), 0);
        cout << "received" << endl;
        if(!strcmp(buffer, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }
        
        // Display the message from the client
        cout << "Client: " << buffer << endl;
        
        // Prompts for response
        cout << "Your response > ";
        string data;
        getline(cin, data);
        
        // Put response in buffer
        memset(&buffer, 0, sizeof(buffer)); //clear the buffer
        strcpy(buffer, data.c_str());
        
        // If "exit" was typed, exit
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(isock, (char*)&buffer, strlen(buffer), 0);
            break;
        }
        
        //else send the message to client
        send(isock, (char*)&buffer, strlen(buffer), 0);
    }
    
    //close the socket descriptors after we're all done
    close(isock);
    close(sockfd);
  
  
  // send and receive data
  // read(sockfd, buffer, sizeof(buffer);
  // send(sockfd, "hey\n", strlen("hey\n"));
  
  // Compiling:
  // g++ client.c -o client
  // g++ server.c -o server
  
  return 0;
}

