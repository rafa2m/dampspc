#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
/*
Ejemplo 1.9, comunicación encadenada de procesos usando pipes
*/
int main()
{
    pid_t pid_hijo1, pid_hijo2;

    int fd1[2]; //padre->hijo fd1[0]=escritura, fd1[1]=lectura
    int fd2[2]; //hijo->padre fd2[0]=escritura, fd2[1]=lectura

    char saludoAbuelo[] = "Saludos del Abuelo.\0";
    char saludoPadre[] = "Saludos del Padre..\0";
    char saludoHijo[] = "Saludos del Hijo...\0";
    char saludoNieto[] = "Saludos del Nieto..\0";

    char buffer[80] = "";

    pipe(fd1); //pipe para comunicación de padre a hijo
    pipe(fd2); //pipe para comunicación de hijo a padre

    pid_hijo1 = fork(); //Soy el  Abuelo, creo a Hijo

    if (pid_hijo1 == -1) //Ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }

    if (pid_hijo1 == 0) 
    {
        //Nos encontramos en Proceso hijo 
        pid_hijo2 = fork(); //creo a Nieto
        switch (pid_hijo2)
        {
        case -1: // error
            printf("No se ha podido crear el proceso hijo en el HIJO...");
            exit(-1);
            break;
        case 0: // proceso hijo
            //NIETO RECIBE
            close(fd2[1]);//cierra el descriptor de entrada
            read(fd2[0], buffer, sizeof(buffer)); //leo el pipe
            printf("\t\tNIETO RECIBE mensaje de su padre: %s\n", buffer);

            //NIETO ENVIA
            printf("\t\tNIETO ENVIA MENSAJE a su padre...%s\n",saludoHijo);
            close(fd1[0]);
            write(fd1[1], saludoHijo, strlen(saludoHijo));

            break;
        default: // proceso padre
            //HIJO RECIBE
            close(fd1[1]); //cierra el descriptor de entrada
            read(fd1[0], buffer, sizeof(buffer)); //leo el pipe
            printf("\tHIJO recibe mensaje de ABUELO:%s\n", buffer);

            //HIJO ENVIA a su hijo
            close(fd2[0]); //cierra el flujo de lectura
            //escribe en el flujo de escritura, pipe
            write(fd2[1], saludoPadre,
                  strlen(saludoPadre));
            wait(NULL); //espero al hijo

            //RECIBE de su hijo
            close(fd1[1]);                        //cierra el descriptor de entrada
            read(fd1[0], buffer, sizeof(buffer)); //leo el pipe
            printf("\tHIJO RECIBE mensaje de su hijo:%s\n", buffer);

            //HIJO ENVIA a su PADRE
            printf("\tHIJO ENVIA MENSAJE a su padre... %s\n", buffer);
            close(fd2[0]);
            write(fd2[1], buffer,
                  strlen(buffer)); //escribo en pipe
        }
    }
    else 
    {
        //Nos encontramos en Proceso padre
        //PADRE ENVIA
        printf("ABUELO ENVIA MENSAJE AL HIJO:%s\n",saludoPadre);
        close(fd1[0]); //cierra el flujo de lectura
        write(fd1[1], saludoPadre, strlen(saludoPadre)); //escribo en pipe
        wait(NULL);//espera la finalización del proceso hijo

        //PADRE RECIBE
        close(fd2[1]);//cierra el flujo de escritura
        read(fd2[0], buffer, sizeof(buffer)); //leo del pipe
        printf("El ABUELO RECIBE MENSAJE del HIJO: %s\n", buffer);
    }
    exit(0);
}
