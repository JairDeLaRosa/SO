

#include <stdio.h>    // Para funciones de entrada/salida como printf.
#include <stdlib.h>   // Para la macro EXIT_SUCCESS.
#include <unistd.h>   // Para las funciones pipe, fork, getpid, sleep, write y read.
#include <string.h>   // Para funciones de manejo de strings como strlen.
#include <sys/wait.h> // Para la función wait.
#include <stdbool.h>  // Para booleanos
#include <signal.h>   // Para usar señales


struct node
{
    int id, i, j;
};

bool hay_mina(int **m, int r, int c, int i, int j){
    int ti, tj;
    if (m[i][j]!=1)
    {
        return false;
    }else{
        for (int vi = -1; vi <= 1; vi++)
        {
            for (int vj = -1; vj <= 1; vj++)
            {
                ti=i+vi; tj=j+vj;
                if ((ti<0 || ti>r) || (tj<0 || tj>c))
                {
                    continue;
                }
                if(m[ti][tj]==2){
                    return true;
                }
                
                
            }
            
        }
        
    }
    return false;
}

int main(){
    
    int r, c, nh, id;

    int **dat;
    dat = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        dat[i] = (int *)malloc(c * sizeof(int));
    }


    int fd[2];
    if (pipe(fd)==-1)
    {
    printf("Error al crear la tubería.");
    return EXIT_FAILURE;
    }

    printf("Ingrese numero de hijos: ");
    scanf("%d", &nh);
    FILE *file=fopen("minas100x100.txt", "r");
    fscanf(file,"%d", &r);
    fscanf(file,"%d", &c);
    printf("%d-%d\n",r,c);
    int num;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            
            fscanf(file,"%1d", &num);
            dat[i][j] = num;
            printf("%d",dat[i][j]);
        } 
        printf("\n");
    }
   
    
    for (id = 0; id < nh; id++)
    {
        if (!fork())
        {
            break;
        }
        
    }
    if(id<nh){
        struct node nodo;
        int fi, ff, delta=r/nh;
        fi=id*delta; ff=fi+delta;
        close(fd[0]);
        for (int rw = fi; rw < ff; rw++)
        {
            for (int cl = 0; cl < c; cl++)
            {
                if (hay_mina(dat,r, c, rw, cl))
                {
                    nodo.id=id; nodo.i=rw; nodo.j=cl;
                    write(fd[1],&nodo,sizeof(struct node));
                }
                
            }
            
        }
        close(fd[1]);
    }else{
        close(fd[1]);
        struct node nodo;
        for (int i = 0; i < nh; i++)wait(NULL);
            while (read(fd[0], &nodo, sizeof(struct node)))
        {
            printf("El proceso %d encontró una mina en fila %d y columna %d.\n", nodo.id, nodo.i, nodo.j);
        }
        
        
        
        
        
    }
    return EXIT_SUCCESS;
}