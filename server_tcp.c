

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_CONNECTIONS 5

struct sockaddr_in server;
struct sockaddr_in client;
socklen_t len;
char msg[100];
int n;
//char MSG1[50];

int main(int argc,char *argv[])
{
	int sockfd,newsockfd,ch;
	char buff[100];
	strcpy(buff,argv[1]);
        char ip[20],port[10];
	int recvLen;
        int i,j=0,k=0;
	
	if(argc < 1)
	{
		printf("\n Usage : <./ser> <ip_add> <port> \n");
		return 1;
	}	
	for(i=0;buff[i]!= ':';i++)
	{
	ip[k]=buff[i];
	k++;	
	}
	ip[k]='\0';
        printf("%s\n",ip);
	i++;
	for(;buff[i]!='\0';i++)
	{
		port[j]=buff[i];
		j++;
	}
	port[j]='\0';
	printf("%s\n",port);
	/* server is binding itself */
	server.sin_family = AF_INET;
	server.sin_port   = htons(atoi(port));
	server.sin_addr.s_addr = inet_addr(ip);
//	server.sin_addr.s_addr = inet_addr("192.168.0.145");
        
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("ERROR:couldn't create socket \n");
		exit(1);
	}
	if(bind(sockfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("ERROR: bind fails \n");
		exit(1);
	}
	listen(sockfd,MAX_CONNECTIONS);
	printf("\n Waiting For client Connection........ \n");
	len = sizeof(client);
	//newsockfd = accept(sockfd,(struct sockaddr *)&client,&len);
	while(1)
        {
		newsockfd = accept(sockfd,(struct sockaddr *)&client,&len);
    		n=recv(newsockfd,msg,100,0);
    		if(n==0)
    		{
     		 	close(newsockfd);
    		 	break;
    		}
    		msg[n]=0;
    		send(newsockfd,msg,n,0);

    		printf("Receive and set:%s\n",msg);
   		//close interior while
  		//return 0;
  	}
	close(newsockfd);
	return 0;
}

		
#if 0
		printf("\n\n\t\t\t1.SEND\n");
		printf("\n\n\t\t\t2.RECV\n");
		printf("\n\n\t\t\t3.EXIT\n");
		printf("\n\n\t\t\tEnter U r Choice:");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				__fpurge(stdin);
				printf("\n\n\t\t\tEnter the data to Send:");
				fgets(MSG,100,stdin);
				send(newsockfd,MSG,strlen(MSG)+1,0);
				break;
			case 2:
				printf("\n\t Client IP address = %s\n",inet_ntoa(client.sin_addr));	
				recv(newsockfd,MSG1,sizeof(MSG1),0);
				printf("\n\t Received : %s\n",MSG1);
				break;
			case 3:
				close(newsockfd);
				close(sockfd);
				exit(0);
		}
#endif
	

				
		

		

	
 


