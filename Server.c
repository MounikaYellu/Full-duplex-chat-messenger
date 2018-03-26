#include"headers.h"
main(int argc,char **argv)
{
if(argc<2)
{
	puts(" Input format: server.exe well_known_portno \n");
	return;
}
int sfd;
printf(" Creating server socket ...\n");
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{
	perror("socket");
	return;
}
printf(" Server socket created successfully \n");
struct sockaddr_in saddr;
puts(" bind ...\n");
saddr.sin_family=AF_INET;
saddr.sin_port=htons(atoi(argv[1]));
saddr.sin_addr.s_addr=inet_addr("0.0.0.0");
if(bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr))<0)
{
	perror("bind");
	close(sfd);
	return;
}
puts(" Bind success \n");
puts(" Creating connection queue for only 1 \n");
if(listen(sfd,1)<0)
{
	perror("listen");
	close(sfd);
	return;
}
puts("Listen success \n");
struct sockaddr_in caddr;
int clen = sizeof(caddr);
puts(" Waiting to accept connection from any client ..\n");
int newfd;
newfd=accept(sfd,&caddr,&clen);
if(newfd<0)
{
	perror("accept");
	close(sfd);
	return ;
}
puts(" Connection accepted from client ..\n");
unsigned short portno;
char *ip;
portno=ntohs(caddr.sin_port);
another:ip=inet_ntoa(caddr.sin_addr);
printf(" Whose ephemeral port is : %d\n",portno);
printf(" &ip address is : %s \n",ip);
printf(" using fd %d on this host : \n",newfd);
char buff[100];
int status ;
while(1)
{
	printf(" Waiting for message from client ..\n");
	status=recv(newfd,buff,100,0);
	if(status<0)
	{
		perror("recv");
		close(newfd);
	}
	else if(status==0)
	{
		puts(" Client abnormally terminated \n");
		close(newfd);
	goto another;
	}
	else
	{
		printf(" Server received : %s\n",buff);
		printf(" Echo back to client ..\n");
	}
	if(send(newfd,buff,100,0)<0)
	{
		perror("send");
		close(newfd);
	}
	else
	{
		if(strcmp(buff,"quit")==0)
		{
			puts("Client formally terminating \n");
			break;		
		}
		printf("echoed : %s \n",buff);
		
	}
}
close(newfd);
close(sfd);
puts(" Server terminated \n");
}



