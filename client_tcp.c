#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in server;
static char msg1[1000];
static char msg2[1000];

int main(int argc,char *argv[])
{
	int sockfd,ch,i,j=0,k=0;
	char buff[100],port[10],ip[20];
	strcpy(buff,argv[1]);
        int n; 	
	

       	
	if(argc < 1)
	{
		printf("\nUsage:<./cli> <server ip addrs>:<server portno>\n");
		return 1;
	}
	for(i=0;buff[i] !=':';i++)
	{
		ip[k]=buff[i];
		k++;
	}
	ip[k]='\0';
	printf("%s\n",ip);
	i++;
	for(;buff[i] !='\0';i++)
	{
		port[j]=buff[i];
		j++;
	}
	port[j]='\0';
	printf("%s\n",port);
	/*Fill the info about server */

	server.sin_family 	= AF_INET;
	server.sin_port   	= htons(atoi(port));
	server.sin_addr.s_addr  = inet_addr(ip);


	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("ERROR:couldn't create socket \n");
		exit(1);
	}
	if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		perror("ERROR: connect failed \n");
		exit(1);
	}
	
	 while(1)
	 {
		  printf("\nEnter message to send to server:\n");
  		  fgets(msg1,1000,stdin);
  		  if(msg1[0]=='#')
   		  break;

  		  n=strlen(msg1)+1;
                  send(sockfd,msg1,n,0);

                  n=recv(sockfd,msg2,1000,0);

  		  printf("Receive message from  server::%s\n",msg2);
	}

 return 0;
}

/*	{
		printf("\n\n\t\t\t1.SEND\n");
		printf("\n\n\t\t\t2.RECV\n");
		printf("\n\n\t\t\t3.EXIT\n");
		printf("\n\n\t\t\tEnter U r choice:");
		scanf("%d",&ch);	
		switch(ch)
		{
			case 1:
				__fpurge(stdin);
				printf("\n\n\t\t\tEnter the data to Send:");
				fgets(MSG,100,stdin);		
				send(sockfd,MSG,strlen(MSG)+1,0);
				break;
			case 2:	
				recv(sockfd,MSG1,sizeof(MSG1),0);
				printf("\n\t Received From Server = %s\n",MSG1);
				break;
			case 3:
				close(sockfd);
				exit(0);
		}
	}
}*/

