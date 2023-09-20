#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void alarmHandler()
{
    printf("questo me lo gestisco io!\n");
    //alarm(3); // ri-setta il timer a 3 secondi
    //exit(0);
}

int main() { 
    signal(SIGALRM, alarmHandler);
    alarm(3);
    printf("ciao\n");
    //while(1){}
    pause();
    printf("termino!\n");
}