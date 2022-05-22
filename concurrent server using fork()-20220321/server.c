/****TCP concurrent server using fork()******/
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
  int sfd,newsfd;
  struct sockaddr_in srv,cln;
  char rdbuf[128];
  /***1) create a socket **********/
  printf("Creating a socket^^^^^^^^^.\n");
  sfd= socket(AF_INET,SOCK_STREAM,0);
  if(sfd<0)
  {
    perror("socket");
    return 0;
  }
  printf("Socket created successfully!!!!!!!!!!!!!!!!!!!.\n");
  /*****end of socket creation******/

  /*2) assign address information to the socket address structure members****/
    srv.sin_family      = AF_INET;
    srv.sin_addr.s_addr = inet_addr("0.0.0.0");
    srv.sin_port        = htons(atoi(argv[1]));
  /**************************************************************/

 /**3) binding the socket with the address******/
   if(bind(sfd,(struct sockaddr *)&srv,sizeof(srv))==0)
      printf("Binding address to the socket is successfull....\n");
   else
    {
      perror("bind");
      return 0;
    }
 /**********************************************/

 /****4) to mark the socket as passive use listen() ******/
  if(listen(sfd,1)==0)
    printf("Now it is listening to incoming connections!!!!!!!!!!\n");
  else
    {
      perror("listen");
      return 0;
    }
 /********************************************************/

 /***5) accept the new connection*************************/
    int len = sizeof(cln);
 while(1)
 {//5th step while loop start
    newsfd = accept(sfd,(struct sockaddr *)&cln,&len); 
     if(newsfd < 0)
     {
       perror("accept");
       return 0; 
     }
    
     printf("New connection accepted successfully!!!!!!!!!!!!!!!!!!\n");
    if(fork()==0)
    {
      while(1)
     { 
       bzero(rdbuf,128);
       if(read(newsfd,rdbuf,128)>0)
       printf("recieved data is : %s\n",rdbuf);
       else
       {
         printf("client terminated!!!!!!!!!!!\n");
         exit(0);
       }
   
     }
    } 
  /**********************************************************/
 }//5th step while loop close
}
