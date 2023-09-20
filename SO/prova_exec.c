#include <stdio.h>
#include <unistd.h>
int main() {
    printf("provo a eseguire ls\n");

    //execl("/bin/ls","/bin/ls","-l",NULL);
    execlp("ls","ls","-l",NULL);

    printf("non scrivo questo! \n");
    // questa printf non viene eseguita, se la exec va a buon fine
}