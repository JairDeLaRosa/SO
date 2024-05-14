#include <stdio.h>    // Para funciones de entrada/salida como printf.
#include <stdlib.h>   // Para la macro EXIT_SUCCESS.
#include <unistd.h>   // Para las funciones pipe, fork, getpid, sleep, write y read.
#include <string.h>   // Para funciones de manejo de strings como strlen.
#include <sys/wait.h> // Para la función wait.

int main() {
    FILE *file;
    int num_elements,i; 
    int *vector;
    int padre=getpid();
    int fd1[2],fd2[2]; //dos tuberias 
    if (pipe(fd1)==-1)
    {
    printf("Error al crear la tubería.");
    return EXIT_FAILURE;
    }
    if (pipe(fd2)==-1)
    {
    printf("Error al crear la tubería.");
    return EXIT_FAILURE;
    }

    // Abre el archivo para lectura
    file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    // Lee el primer número para obtener la cantidad de elementos
    if (fscanf(file, "%d", &num_elements) != 1) {
        perror("Error al leer el primer número");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Aloca memoria para el vector
    vector = (int *)malloc(num_elements * sizeof(int));
    if (vector == NULL) {
        perror("Error al alocar memoria");
        fclose(file);
        return EXIT_FAILURE;
    }
    int mitad=num_elements/2;
    // Lee el resto de los enteros y guárdalos en el vector
    for (int i = 0; i < num_elements; i++) {
        if (fscanf(file, "%d", &vector[i]) != 1) {
            perror("Error al leer un número");
            free(vector); // Libera la memoria asignada
            fclose(file);
            return EXIT_FAILURE;
        }
    }
    for (i = 0; i < 2; i++)//creación de hijos
    {
        if (!fork())
        {   
            break;
        }
        
    }
    if (padre==getpid())//padre
    {
        int suma1,suma2,total;
        close(fd1[1]); //Escritura
        close(fd2[1]); //Escritura
        wait(NULL);
        read(fd1[0],&suma1,sizeof(int));
        read(fd2[0],&suma2,sizeof(int));
        total=suma1+suma2;
        printf("El total de la suma es: %d \n", total);
        close(fd1[0]); //Lectura
        close(fd2[0]); //Lectura
    }
    
    if (i==0) //hijo 1
    {
        close(fd1[0]); //Lectura
        close(fd2[0]); //Lectura
        close(fd2[1]); //Escritura
        /* code */
        
        int suma=0;
        for (int j = 0; j < mitad; j++)
        {
            suma=suma+vector[j];
        }
        printf("La suma del hijo 1 es: %d \n", suma);
        write(fd1[1],&suma,sizeof(int));
        close(fd1[1]); //Escritura
    }
    if (i==1)//hijo 2
    {
        close(fd2[0]); //Lectura
        close(fd1[0]); //Lectura
        close(fd1[1]); //Escritura
        /* code */
        int suma=0;
        for (int j = mitad; j < num_elements; j++)
        {
            suma=suma+vector[j];
        }  
        usleep(1000);
        printf("La suma del hijo 2 es: %d \n", suma);
        write(fd2[1],&suma,sizeof(int));
        close(fd2[1]); //Escritura
    }
    


    // Cierra el archivo y libera la memoria
    fclose(file);
    free(vector);
    return EXIT_SUCCESS; // Indica que el programa terminó exitosamente.
}