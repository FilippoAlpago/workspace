#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[])
{
  int fd[2], bytesread;
 
  pipe(fd);
  if (fork() == 0)  {
    close(fd[0]);       /* chiude in lettura */
    dup2(fd[1],1);      /* fa si che 1 (stdout) sia una copia di fd[1] */
                        /* da qui in poi l'output va sulla pipe */
    close(fd[1]);       /* chiude il descrittore fd[1] */
    execlp(argv[1],argv[1],NULL);   /* esegue il comando */
    perror("errore esecuzione primo comando");
  } else {
    close(fd[1]);       /* chiude in scrittura */
    dup2(fd[0],0);      /* fa si che 0 (stdin) sia una copia di fd[0] */
                        /* da qui in poi l'input proviene dalla pipe */
    close(fd[0]);       /* chiude il descrittore fd[0] */
    execlp(argv[2],argv[2],NULL);   /* esegue il comando */
    perror("errore esecuzione secondo comando");
  }
}