#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define ERR_EXIT(m) \
				do{\
					perror(m);\
					exit(EXIT_FAILURE);\
				}while(0)

void client_exit(int sig){
    printf("subprocess exit\n");
    exit(EXIT_SUCCESS);
}

int main(void){
    int sock;
    //创建套接字
    if( (sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0 ){
        ERR_EXIT("socket");
    }

    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //连接套接字
    if( connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 ){
        ERR_EXIT("connect");
    }

    struct MESSAGE {
        bool is_handsome;
        char name[100];
        int age;
    };
    struct MESSAGE * message = (struct MESSAGE * )malloc(sizeof(struct MESSAGE)) ;
    printf("sizeof(struct MESSAGE) is %d \n",sizeof(struct MESSAGE));
    printf("sizeof(is_handsome) is %d \n",sizeof(message->is_handsome));
    printf("sizeof(age) is %d \n",sizeof(message->age));
    printf("sizeof(name) is %d \n",sizeof(message->name));

    memset(message,0, sizeof(struct MESSAGE));
    strcpy(message->name,"咯肯loken");
    message->age=4;
    message->is_handsome = false;

    write(sock,message,sizeof(struct MESSAGE));

    sleep(1000);

    return 0;

}



