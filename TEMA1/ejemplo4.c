#include <stdio.h>
#include <unistd.h>
//Se crea un proceso hijo y se obtiene y muestra el pid de los dos procesos
//Se utilizan las funciones getpid() y getppid()
int main(void)
{
	pid_t pid_actual, pid_padre;
	pid_actual = getpid();
	pid_padre = getppid();

	printf("El identificador (PID) del proceso padre es %d,\ny el del proceso actual es %d\n", 
    pid_padre,pid_actual);
}
