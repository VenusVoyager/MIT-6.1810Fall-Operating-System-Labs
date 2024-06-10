#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int p[2];
    char c;

    if(pipe(p)!=0){
        printf("pipe error!");
        exit(-1);
    };
    if (fork()==0){
        int Childid=getpid();
        if (write(p[1],&c,1)!=1){
            printf("write error!");
            exit(-1);
        }
        printf("%d: receiving ping\n",&Childid);
        exit(0);
    }
    else{
        wait((int*)0);
        int Parentid=getpid();
        if (read(p[0],&c,1)!=1){
            printf("read error!");
            exit(-1);
        }
        printf("%d: receiving pong\n",&Parentid);
        
        exit(0);
    }

}