#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>  // para la función open
#include <unistd.h> // para la función close
/* En este ejemplo se muestra como abrir flujos de ficheros para escribir y leer texto
 * en los mismos
 */
int main(void)
{
    char saludo[] = "Un saludo!!!\n";
    char buffer[10];
    int bytesleidos;
    FILE *fd;
    //fichero se abre solo para escritura
    fd = fopen("texto.txt", "wt");
    if (fd == NULL)
    {
        printf("ERROR AL ABRIR EL FICHERO...\n");
        exit(-1);
    }

    printf("Escribo el saludo...\n");
    //se escribe texto en el fichero, donde 'saludo' es el array de caracteres
    //a escribir, strlen(saludo) es el número de caracteres a escribir,
    //
    fwrite(saludo, sizeof(char), strlen(saludo), fd);
    fclose(fd); //cierro el fichero

    fd = fopen("texto.txt", "rt"); //el fichero se abre solo para lectura
    printf("Contenido del Fichero: \n");

    //leo bytes de uno en uno y lo guardo en buffer
    bytesleidos = fread(buffer, sizeof(char), 1, fd);
    while (bytesleidos != 0)
    {
        printf("%1c", buffer[0]);                         //pinto el byte leido
        bytesleidos = fread(buffer, sizeof(char), 1, fd); //leo otro byte
    }
    fclose(fd);
}
