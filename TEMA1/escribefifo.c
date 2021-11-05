#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
//Ejemplo de proceso que crea un FIFO para comunicarse con otro proceso no relacionado
int main()
{
  int fp;
  char saludo[] = "Un saludo!!!\n";
  fp = open("FIFO2", 1);
 
  if(fp == -1) {
    printf("ERROR AL ABRIR EL FICHERO...");
    exit(-1);
  } 
  printf("Mandando información al FIFO...\n");
  write(fp,saludo, strlen(saludo));
  close(fp);   
  return 0; 
}
