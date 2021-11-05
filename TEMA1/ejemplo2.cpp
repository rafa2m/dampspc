#include <unistd.h>
#include <stdio.h>

int main(){
    printf("Llamando al comando ls -l con la función execl()");
    printf("Lista de archivos del directorio actual:\n");
    execl("/bin/ls", "ls","l",(char *)NULL);
    printf("Aquí no llega\n");
}