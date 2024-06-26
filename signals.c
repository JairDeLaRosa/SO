#include <stdio.h>    // Para funciones de entrada/salida como printf.
#include <stdlib.h>   // Para la macro EXIT_SUCCESS.
#include <unistd.h>   // Para las funciones pipe, fork, getpid, sleep, write y read.
#include <string.h>   // Para funciones de manejo de strings como strlen.
#include <sys/wait.h> // Para la función wait.
#include <signal.h> 

//Función que se realiza cuando se llama la señal
void manejador (int sig){
    printf("Señal %d recibida \n", sig);
}

int main(){
    int i;

    //Recibodor de señal
    signal(SIGUSR1, manejador);

    //Guardar pits
    pid_t hijos[5];
    pid_t nietos[2];
    pid_t subNietos[2];
    pid_t root=getpid();
    //creación de procesos
    for (i = 0; i < 5; i++)
    {
        hijos[i]=fork();
        if (hijos[i]==0)
        {
            break;
        }
    }
    //Creación de procesos nietos
    if (i==1||i==3)
    {
        switch (i)
        {
        case 1:
        //Creación de procesos sub nietos
            nietos[0]=fork();
            if (nietos[0]==0)
            {
                subNietos[0]=fork();
            }
            
            break;
        case 3:
        //Creación de procesos sub nietos
            nietos[1]=fork();
            if (nietos[1]==0)
            {
                subNietos[1]=fork();
            }
            break;    
        
        default:
            break;
        }
    }
    if(root == getpid()){
        usleep(10000);//pequeña pausa para esperar a los hijos, nietos y sub nietos
        printf("soy a y mi pid: %d \n",getpid()); // Imprime el padre
        kill(hijos[i-1], SIGUSR1); // manda la señal al hijo 
        pause();
        printf("soy a y mi pid: %d \n",getpid());
        for ( i = 0; i < 5; i++)
        {
            wait(NULL);
        }
    }else
    {
        pause(); // Todos los hijos esperan recibir la señal
        switch (i)
        {
        case 0: // hijo b 
            printf("soy b y mi pid: %d \n",getpid());
            kill(root, SIGUSR1); //manda la señal al padre
            break;
        case 1:
            if (nietos[0]!=0)
        {
            printf("soy c y mi pid: %d \n",getpid());
            kill(nietos[0], SIGUSR1);
            pause();
            printf("soy c  y mi pid: %d \n",getpid());
            kill(hijos[i-1], SIGUSR1);
        }else if (subNietos[0]!=0)
        {
            printf("soy g   y mi pid: %d \n",getpid());
            kill(subNietos[0], SIGUSR1);
            pause();
            printf("soy g y mi pid: %d \n",getpid());
            kill(getppid(), SIGUSR1);
        }else{
            printf("soy i y mi pid: %d \n",getpid());
            kill(getppid(), SIGUSR1);
        }
            break;

        case 2:
          printf("soy d y mi pid: %d \n",getpid());
            kill(hijos[i-1], SIGUSR1);
        break;     
        case 3:
        if (nietos[1]!=0)
        {
            printf("soy e y mi pid: %d \n",getpid());
            kill(nietos[1], SIGUSR1);
            pause();
            printf("soy e y mi pid: %d \n",getpid());
            kill(hijos[i-1], SIGUSR1);
        }else if (subNietos[1]!=0)
        {
            printf("soy h y mi pid: %d \n",getpid());
            kill(subNietos[1], SIGUSR1);
            pause();
            printf("soy h y mi pid: %d \n",getpid());
            kill(getppid(), SIGUSR1);
        }else{
            printf("soy j y mi pid: %d \n",getpid());
            kill(getppid(), SIGUSR1);
        }
        
        
        break;
        case 4:
            printf("soy f y mi pid: %d \n",getpid());
            kill(hijos[i-1], SIGUSR1);

            
        break;    
        
        default:
            break;
        }
        
    }
    
    return EXIT_SUCCESS;
}