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
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(n));//�˿ڸ��ã������ǿͻ��˿�����һ�����ض˿�ͬʱ���Ӷ������ˡ�


    struct sockaddr_in sin;
    bzero(&sin,sizeof(sin));//ÿ���ֽ���0���
    sin.sin_family = AF_INET;//ʹ��IPv4����Э����
    sin.sin_port = htons(8888);//htons�����ͱ����Ķ˿ںţ������ֽ�˳��ת����TCP/IPЭ���е������ֽ�˳��
    sin.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANYת����������0.0.0.0����ָ��������˼����������ж���������ɼ�������˿ڡ�
    int r = bind (fd,(struct sockaddr *)&sin,sizeof(sin));//��IP��ַ���˿ڵ���Ϣ��socket�����С�
    if(r == -1)
    {
        perror("bind");
        exit(-1);
    }
    r = listen(fd,10);//10Ϊ�ȴ����Ӷ��е���󳤶ȡ��ڶ��������ǵȴ����Ӷ��е���󳤶ȣ��ȷ�˵���㽫backlog��Ϊ10, ����15�����������ʱ��ǰ��10����������ͱ���������������У�����5�����󱻾ܾ���ǧǧ����Ҫע�⣺���10�����Ǳ�ʾ�ͻ�������������Ϊ10�� ʵ���Ͽ����кܶ�ܶ�Ŀͻ���
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
int fd = accept(sockfd,NULL,NULL);//���ܿͻ��˷�������������	����û����������ڴ˴���
   char buffer[1024]={0};

   int rlen = read(fd,buffer,sizeof(buffer));
   printf("�ͻ��˷����������ǣ�%s\n",buffer);
   work(fd,buffer);
   
}
   
close(sockfd);
   
   
   return 0;

}
