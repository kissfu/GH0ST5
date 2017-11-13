/* ~ */
#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
using namespace std;

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("received SIGINT\n");
}


void error( char *msg)
{
 perror(msg);
 exit(EXIT_FAILURE);
}
int main()
{
	int sockfd;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in serv,client;
 
	/* Network setup */
	serv.sin_family = AF_INET;
	serv.sin_port = htons(53000);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buffer[256];
	socklen_t l = sizeof(client);
	socklen_t m = sizeof(serv);
	//socklen_t m = client;
	//cout<<"\ngoing to send\n";
	//cout<<"\npls enter the mssg to be sent\n";
	//fgets(buffer,256,stdin);

	/* Signal setup */
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGINT\n");

	while(true)
	{
		sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&serv,m);
	}
	recvfrom(sockfd,buffer,256,0,(struct sockaddr *)&client,&l);
}
