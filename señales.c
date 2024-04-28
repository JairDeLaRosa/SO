#include <stdio.h>   
#include <stdlib.h>  
#include <unistd.h>   
#include <sys/wait.h> 
#include <signal.h>

void sighandler(int sig){

}


int main(){
    signal(SIGUSR1,sighandler);
    pid_t child[3];
    pid_t nieto[1];
    int i;

    int root = getpid();

    for (i = 0; i < 3; i++)
    {
        child[i] = fork();
        if(child[i] == 0){
            break;
        }

    }
    
    if(i == 1){
        nieto[i] = fork();    
    }




    if(root == getpid()){

         printf("soy el padre y mi pid: %d \n",getpid());
        
        kill(child[i-1], SIGUSR1);

        usleep(9000);
        printf("soy el padre y mi pid: %d 2\n",getpid());
        for ( i = 0; i < 3; i++)
        {
            wait(NULL);
        }


    }else{
        switch (i)
        {
        case 2:
            if(child[i-1] != 0){
                printf("soy el hilo y mi pid: %d h3\n",getpid());
                usleep(5000);
                kill(child[i-1], SIGUSR1);
            }
            
            break;
        case 1:
            if(child[i-1] != 0){
                printf("soy el hijo y mi pid: %d h2\n",getpid());
                usleep(4000);
                kill(nieto[i], SIGUSR1);
                usleep(3000);

                printf("soy el hijo y mi pid: %d otra h2\n",getpid());
                kill(child[i-1], SIGUSR1);

            }else{
                printf("soy el nieto y mi pid: %d h21\n",getpid());
                usleep(2000);
                kill(getppid(),SIGUSR1);

            }
        break;
            
            
        case 0:
            if(child[i] == 0){
                usleep(6000);
                printf("soy el hijo y mi pid: %d h1\n",getpid());
                
                kill(getppid(), SIGUSR1);
            }
        break;
        
        }

    }


   
    

}