#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
En este ejemplo se muestra como se comunican dos procesos, padre e hijo, a través de una
tubería (pipe)
*/
int main()
{
    int fd[2];
    char buffer[10];
    pid_t pid;

    pipe(fd); //1 se crea la tubería (flujo de escritura/lectura) para los procesos

    pid = fork(); //2 se crea el proceso hijo

    switch (pid)
    {
    case -1: //ERROR
        printf("NO SE HA PODIDO CREAR HIJO...");
        exit(-1);
        break;
    case 0: //HIJO
        printf("El proceso hijo escribe en el pipe...\n");
        //4 Este código sólo lo ejecuta el hijo, que es el que escribe un mensaje en la tubería
        //para el padre, que espera en el otro extremo para leer
        //Atención, los métodos para escribir y leer en un pipe son parecidos a los
        //de flujos de ficheros, pero no iguales
        write(fd[1], "Hola papá", 10);
        break;
    default:        //PADRE
        wait(NULL); //3 Este código sólo lo ejecuta el padre, espera a que el hijo termine
        printf("El proceso padre lee del pipe...\n");
        //5 El padre lee de la tubería lo que el hijo ha escrito
        read(fd[0], buffer, 10);
        printf("\tMensaje leido: %s\n", buffer);
        break;
    }
}
