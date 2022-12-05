#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>     
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 8000000
int init(const char *file);

struct message{
  long source;
  long dest;
  long opcode;
};

int main(int argc, char *argv[]){

   int ret, size_inbytes = 0, sd;
   fd_set readset, writeset;
   char *copie =argv[1];
   sd = init(copie);
   if(argc >2){
   	fprintf(stdout, "trop d'arguments\n");
   }
   
   while (1){
      
      fprintf(stdout, "tentative de connexion\n");
    }
    fprintf(stderr , "La taille du buffer du clavier est %d", size_inbytes);
}

int init(const char *file){
   struct sockaddr_in serv_addr;
   int sd;
   /* Creation du socket*/
   if((sd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("\n Erreur  de socket \n");
        return sd;
   }

   /* Initialisation du strucutre du socket */
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(8080); // port
   serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
   if(connect(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("\n Error: Connect Failed (%d) \n", errno);
        return -1;
   }
  
   int desc =open(file	,O_WRONLY|O_CREAT,0642);
   char buffer[MAX];
   int reader, writer ;
   while(1){
   	reader = read(sd, buffer, MAX);
   	if (reader <=0) break;
   	writer =  write(desc,buffer,reader);
      //if (buffer == "") break; 
   	if (writer <=0) break;
   }

   fprintf(stdout,"Copie terminé");
   
   for(;;){}
   printf("end %d\n", sd);
   return sd;
}
