#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#define PNAME "/tmp/aPipe"
int main() {
    int fd;
    char leggi;
    
    mkfifo(PNAME,0666); // crea la pipe con nome, se esiste gia' non fa nulla

    fd = open(PNAME,O_RDONLY); // apre la pipe in lettura
    if ( fd < 0 ) { 
        perror("errore apertura pipe"); 
        exit(1);
    }
    
    while (read(fd,&leggi,1)) { // legge un carattere alla volta fino a EOF
        if (leggi == '\0'){
            printf("\n"); // a capo dopo ogni stringa
        } else {
            printf("%c",leggi);
        }
    }

    close(fd);          // chiude il descrittore
    unlink(PNAME);      // rimuove la pipe

    return 0;
}