#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int i, j, fd[2];

    for (i = 2; i <= 100; i++) { // loop prime
        int isprime = 1;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isprime = 0;
                break;
            }
        }
        if (isprime) { // print prime
            if (pipe(fd) != 0) {
                printf("pipe error!");
                exit(1);
            }
            int pid = fork();
            if (pid == 0) { // child
                close(fd[0]); // close reading end in child
                if (write(fd[1], &i, sizeof(i)) == -1) {
                    printf("write error");
                    close(fd[1]);
                    exit(1);
                }
                close(fd[1]); // close writing end in child
                exit(0);
            } else { // parent
                close(fd[1]); // close writing end in parent
                int number;
                if (read(fd[0], &number, sizeof(number)) == -1) {
                    printf("read error");
                    close(fd[0]);
                    exit(1);
                }
                close(fd[0]); // close reading end in parent
                printf("prime %d\n", number);
                wait((int*)0); // wait for child to finish
            }
        } // end print prime       
    } // end loop prime
    exit(0);
}
