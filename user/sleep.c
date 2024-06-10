#include <time.h>
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    
    int i, time;
    time = 0;
    
    if (argc != 2){
        printf("incorrect input!");
        exit(-1);
    }
    char *time_string = argv[1];
    for (i=0; i<strlen(time_string); i++){
        time = 10*time+time_string[i]-(int)'0';
    }

    sleep(time);

    exit(1);
}