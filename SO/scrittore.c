#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#define PNAME "/tmp/aPipe"
int main() {
    int fd, i, lunghezza;
    char *message;
    mkfifo(PNAME,0666); // crea la pipe con nome, se esiste gia' non fa nulla
    // crea la stringa
    lunghezza = snprintf(NULL,0,"Saluti dal processo %d",getpid());
    message = malloc(lunghezza+1);
    snprintf(message,lunghezza+1,"Saluti dal processo %d",getpid()); 
    fd = open(PNAME,O_WRONLY); // apre la pipe in scrittura
    if ( fd < 0 ) {    
        perror("errore apertura pipe"); exit(1);
    }
    for (i=1; i<=3; i++){     // scrive tre volte la stringa
        write (fd,message,strlen(message)+1); // include terminatore
        sleep(2);
    }
    close(fd);    // chiude il descrittore
    free(message);
    return 0;
}