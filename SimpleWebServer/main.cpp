#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int createlistenfd()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int n = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(n));//端口复用，作用是客户端可以用一个本地端口同时连接多个服务端。


    struct sockaddr_in sin;
    bzero(&sin,sizeof(sin));//每个字节用0填充
    sin.sin_family = AF_INET;//使用IPv4网络协议族
    sin.sin_port = htons(8888);//htons将整型变量的端口号（主机字节顺序）转换成TCP/IP协议中的网络字节顺序
    sin.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY转换过来就是0.0.0.0，泛指本机的意思。如果本机有多个网卡，可监听多个端口。
    int r = bind (fd,(struct sockaddr *)&sin,sizeof(sin));//绑定IP地址，端口等信息到socket函数中。
    if(r == -1)
    {
        perror("bind");
        exit(-1);
    }
    r = listen(fd,10);//10为等待连接队列的最大长度。第二个参数是等待连接队列的最大长度，比方说，你将backlog定为10, 当有15个连接请求的时候，前面10个连接请求就被放置在请求队列中，后面5个请求被拒绝。千千万万要注意：这个10并不是表示客户端最大的连接数为10， 实际上可以有很多很多的客户端
    if(r == -1)
    {
        perror("listen");
        exit(-1);
    }
    return fd;
}


    void work(int fd, char* s)
{
    char filename[100]={0};
    sscanf(s,"GET /%s",filename);
    printf("The client request filename is: %s\n",filename);
    
    
    char* mime;
    if(strstr(filename,".html"))
        mime = "text/html";
    else if(strstr(filename,".jpg"))
        mime = "image/jpeg";
    
    char response[100] = {0};
    sprintf(response,"HTTP/1.0 200 OK\r\nContent-Type:%s\r\n\r\n",mime);
    write(fd,response,strlen(response));
    
    int filefd=open(filename,O_RDONLY);
    bzero(response,sizeof(response));
    
    while(1)
    {
	int rlen = read(filefd,response,100);
        if(rlen>0)
        {
            write(fd,response,rlen);
        }
        else
        {
            break;
        }
    }
    close(fd);
    close(filefd);
    
}



int main()
{
   int sockfd = createlistenfd();
while(1)
{
int fd = accept(sockfd,NULL,NULL);//接受客户端发来的连接请求	，若没有则会阻塞在此处。
   char buffer[1024]={0};

   int rlen = read(fd,buffer,sizeof(buffer));
   printf("客户端发来的请求是：%s\n",buffer);
   work(fd,buffer);
   
}
   
close(sockfd);
   
   
   return 0;

}
