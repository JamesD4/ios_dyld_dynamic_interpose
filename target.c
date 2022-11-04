#include <stdio.h>
#include <unistd.h>
#include <string.h> 

int print_me(){
    printf("[%s]\n",  strdup("123"));
}

int main(int argc, char *argv[]){
    while(1==1){
        printf("TARGET PID [%d]\n", getpid());
        print_me();
        sleep(5);
    }
    return 0;
}
