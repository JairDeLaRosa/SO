#include <stdio.h>    // Para funciones de entrada/salida como printf y read/write
#include <stdlib.h>   // Para la macro EXIT_SUCCESS
#include <unistd.h>   // Para las funciones pipe(), fork(), close() y getpid()
#include <sys/wait.h> 



int main(){

    FILE *file = fopen("matriz10x10.txt","r");
    if(file==NULL){
        printf("\n");
    }
    int fila;
    int columna;
    fscanf(file,"%d",&fila);
    fscanf(file,"%d",&columna);

    int matriz[fila][columna];

    for (int i = 0; i < fila; i++)
    {
        for (int j = 0; j < columna; j++)
        {
            fscanf(file,"%d",&matriz[i][j]);
        }
        
    }
    


     for (int i = 0; i < fila; i++)
    {
        for (int j = 0; j < columna; j++)
        {
            printf( " [%d] ",matriz[i][j]);
        }
        printf("\n");
    }
}