#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
int main(){
        pid_t pid1,pid2;
        pid1 = fork();
        if ( pid1 < 0 ) {
                perror("errore fork"); exit(EXIT_FAILURE);
        } else if (pid1 == 0)
                while(1) { // primo figlio
                        printf("%d è vivo !\n",getpid());
                        sleep(1);
                        }
        pid2 = fork();
        if ( pid2 < 0 ) {
                perror("errore fork"); exit(EXIT_FAILURE);
        } else if (pid2 == 0)
                while(1) { // secondo figlio
                        printf("%d è vivo !\n",getpid());
                        sleep(1);
                        }
        // processo genitore
        sleep(2);
        kill(pid1,SIGSTOP); // sospende il primo figlio
        sleep(5);
        kill(pid1,SIGCONT); // risveglia il primo figlio
        sleep(2);
        kill(pid1,SIGINT); // termina il primo figlio
        kill(pid2,SIGINT); // termina il secondo figlio       
}