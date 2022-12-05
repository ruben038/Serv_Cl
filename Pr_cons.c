#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{   
	int MaxMem =atoi(argv[0]);
    int Npr=atoi(argv[1]);
    int Ncn=atoi(argv[2]);
    sem_t vide;
    sem_t plein;
    int in = 0;
    int out = 0;
    
    int buffer[MaxMem];

 

    sem_init(&vide,0,MaxMem);
    sem_init(&plein,0,0);

  
  pid_t pid = fork();
  if(pid < 0){
    fprintf(stderr, "Erreur de création du processus (%d) (%d)\n", pid, errno);
    return 1;
  }
  if(pid == 0){  
  		printf("Le consommateur" ); 
        for(int i = 0; i < Ncn; i++) {
            sem_wait(&plein);
            int item = buffer[out];
            printf("Le consommateur : consomme  l'item %d \n",item);
            out = (out+1)%MaxMem;
            sem_post(&vide);
            sleep(6);
    	}
  }
  else{
    int status;
    pid_t pid2 = wait(&status);
    int item;
    printf("Le producteur "); 
	for(int i = 0; i < Npr; i++) {
	    item = rand();
	    sem_wait(&vide);
	    buffer[in] = item;
	    printf("Producteur : Insertion d'un élément %d \n",buffer[in]);
	    in = (in+1)%MaxMem;
	    sem_post(&plein);
	    sleep(2);
		}
    }
    
    sem_destroy(&vide);
    sem_destroy(&plein);  
  return 0;
}

