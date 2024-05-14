//Escriba un programa que lea una matriz de un archivo y 
#include <stdio.h>    // Para funciones de entrada/salida como printf
#include <stdlib.h>   // Para EXIT_SUCCESS y EXIT_FAILURE
#include <unistd.h>   // Para fork(), shmat(), shmdt()
#include <sys/wait.h> // Para wait()
#include <sys/shm.h>  // Para shmget(), shmctl(), shmat(), shmdt()
#include <sys/stat.h> 
int main(){
    int shmid, *ptr=NULL, f, c, **matriz,nh, id;
    FILE *file=fopen("minas100x100.txt","r");
    if(file==NULL){
        printf("Error al abrir el archivo\n");
        return EXIT_FAILURE;
    }
    printf("Digite la cantidad de hijos: \n");
    scanf("%d",&nh);
    fscanf(file,"%d",&f);
    fscanf(file,"%d",&c);
    printf("%d-%d\n",f,c);

    matriz=(int **)malloc(f * sizeof(int *));
    for (int i = 0; i < f; i++) {
        matriz[i] = (int *)malloc(c * sizeof(int));
    }

    shmid = shmget(IPC_PRIVATE, nh * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    // Adjunta el segmento de memoria compartida al espacio de direcciones del proceso
    ptr = (int *)shmat(shmid, 0, 0);
    for (id = 0; id < nh; id++)
    {
        if (!fork())
        {
            break;
        }
        
    }
    if (id==nh)
    {
        for (size_t i = 0; i < count; i++)
        {
            /* code */
        }
        
    }
    
    


    return EXIT_SUCCESS;
}