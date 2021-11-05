#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
/*
Ejemplo para comprobar como dos procesos padre-hijo se comunican mediante
el uso de señales
*/
/*-------------------------------------------*/
/* gestión de señales en proceso padre       */
void manejador( int signal )
{
 printf("Hijo recibe señal..%d\n", signal);
}
/*-------------------------------------------*/
int main()
{
  int pid_hijo;  
  pid_hijo = fork(); //creamos hijo   
  int contador=0;
  switch(pid_hijo)
  {
     case -1:
          printf( "Error al crear el proceso hijo...\n");
          exit( -1 );        
     case 0:   //HIJO     	         
          signal(SIGUSR1, manejador); //MANEJADOR DE SEÑAL EN HIJO
          while(contador<900000000) {              
              printf("%d\n",contador);
              contador++;
          };       
     break;    
     default: //PADRE envia 2 señales
          sleep(1);
          kill(pid_hijo, SIGUSR1);//ENVIA SEÑAL AL HIJO 
          sleep(1);
          kill(pid_hijo, SIGUSR1);//ENVIA SEÑAL AL HIJO 
          sleep(1);
     break;
  } 
  return 0;
}
