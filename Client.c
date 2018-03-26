#include"headers.h"
main(int argc,char **argv)
{
if(argc<3)
{
	puts(" Input format: Client.exe well_known_portno Server_IP \n");
	return;
}
int fd;
printf(" Creating client socket ...\n");
fd=socket(AF_INET,SOCK_STREAM,0);
if(fd<0)
{
	perror("socket");
	return;
}
printf(" Client socket created successfully \n");
struct sockaddr_in addr;
puts(" bind & connect ...\n");
addr.sin_family=AF_INET;
addr.sin_port=htons(atoi(argv[1]));
addr.sin_addr.s_addr=inet_addr(argv[2]);
if(connect(fd,(struct sockaddr *)&addr,sizeof(addr))<0)
{
	perror("connect");
	close(fd);
	return;
}
puts(" Connect success \n");
char buff[100];
int status ;
while(1)
{
	printf(" Enter message for server ..\n");
	gets(buff);
	printf(" Sending ...\n");	
	status=send(fd,buff,100,0);
	if(status<0)
	{
		perror("recv");
		close(fd);
		return;
	}
	printf("sent : %s \n",buff);
	printf(" waiting for reply ......\n");
	memset(buff,'\0',100);
	status=recv(fd,buff,100,0);
	if(status<0)
	{
		perror("recv");
		close(fd);
		return;
	}
	else if(status==0)
	{
		puts("Server terminated abnormally \n");
		close(fd);
		return;
	}
	else
	{
		printf(" Client received : %s \n",buff);
		if(strcmp(buff,"quit")==0)
		{
			puts(" Server formally terminated connection with client \n");
			break;
		}
	}
}
close(fd);
puts(" Client terminated \n");
}



