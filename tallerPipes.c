#include <stdio.h>    // Para funciones de entrada/salida como printf.
#include <stdlib.h>   // Para la macro EXIT_SUCCESS.
#include <unistd.h>   // Para las funciones pipe, fork, getpid, sleep, write y read.
#include <string.h>   // Para funciones de manejo de strings como strlen.
#include <sys/wait.h> // Para la función wait.

int main() {
    FILE *file = fopen("minas100x100.txt", "r");  // Abre el archivo en modo lectura
    if (file == NULL) {  // Verifica si el archivo se abrió correctamente
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    int filas, columnas;
    int h;
    pid_t padre=getpid();
    
    fscanf(file, "%d", &filas);  // Lee las dimensiones de la matriz

    fscanf(file, "%d", &columnas);
    // Asigna memoria para la matriz
    int **matriz = (int **)malloc(filas * sizeof(int *));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int *)malloc(columnas * sizeof(int));
    }
    printf("Filas: %d Columnas: %d\n",filas, columnas);
    int tub[filas][2];
    // Lee los elementos de la matriz del archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            char dato;
            fscanf(file, "%c", &dato);
            matriz[i][j] = atoi((char*)(&dato));
        }
    }
    // Creación de la tuberiás
    for (int k = 0; k < filas; k++)
    {
        if (pipe(tub[k])==-1)
    {
    printf("Error al crear la tubería.");
    return EXIT_FAILURE;
    }
    }
    

    // Creación de hijos
    for (h = 0; h < filas; h++)
    {
        if (!fork())
        {
            break;
        }
        
    }

    
    if (padre!=getpid())
    {
        close (tub[h][0]);
        int cont=0;
        int minaEncontrada[columnas];
        for (int i = 0; i < columnas; i++)
        {
            if (matriz[h][i]==1)//posible mina
            {
                if(matriz[h-1][i]==2||matriz[h+1][i]==2||matriz[h-1][i-1]==2||matriz[h-1][i+1]==2||matriz[h][i-1]==2||matriz[h][i+1]==2||matriz[h+1][i-1]==2||matriz[h+1][i+1]==2){
                    cont++;
                    minaEncontrada[i]=1;
                }
            }
            
        }
        int datos[cont][2];
        int contPos=0;
        for (int i = 0; i < columnas; i++)
        {
            if(minaEncontrada[i]==1){
                datos[contPos][0]=h;
                datos[contPos][1]=i;
            }
        }

        for (int i = 0; i < cont; i++)
        {
            printf("Mina encontrada en la fila %d y la columna %d\n",datos[i][0], datos[i][1]);
            
        }
        
        
        
        
    }
    

    // Imprime la matriz para verificar la lectura
    printf("Matriz leída:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d", matriz[i][j]);
        }
        printf("\n");
    }



    // Libera la memoria
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    fclose(file);  // Cierra el archivo
    return 0;
}
