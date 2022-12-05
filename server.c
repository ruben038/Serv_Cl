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
int init();

struct message{
  long source;
  long dest;
  long opcode;
};

int main(int argc, char *argv[]){
  
   int ret, size_inbytes = 0, sd, csd;
   char *file;
   file=argv[1];
   
 /*   if(argc >2){
     fprintf(stdout, "trop d'arguments\n");	
   } */
   fd_set readset, writeset;
   struct sockaddr client_addr;
   int clen;
   sd = init();
   while (1)
   {
      if((csd = accept(sd, &client_addr, &clen)) < 0){ 
         fprintf(stderr, "Un petit problème lors du accept %d\n", errno);
         return -1;
      }

      pid_t pid = fork();

      if(pid < 0)
      {
         fprintf(stderr, "Erreur de création du processus (%d) (%d)\n", pid, errno);
         return -1;
      }
      if(pid == 0){
         close(sd);
         fprintf(stdout, "tentative de connexion\n");
         
         int desc =open(file,O_RDONLY);
         char buffer[MAX];
         int reader,writer;
         while (1) {
            reader = read(desc, buffer, MAX);
            if (reader <=0) break;
            writer =  write(csd,buffer,reader);
            //if (buffer == "") break;  
            if (writer<=0) break;
         } 
         close(desc);

         close(csd);
         exit(0);
         
      }
   }
   
   
   
   for(;;){}
   while (1){
  
       fprintf(stdout, "tentative de connexion\n");
    }
    fprintf(stderr , "La taille du buffer du clavier est %d", size_inbytes);
    
}

int init(){
   int sd, ret;
   struct sockaddr_in serv_addr;
   sd = socket(AF_INET, SOCK_STREAM, 0);
   if(sd<0){
      printf("Error in socket creation\n");
      return sd;
   }
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(8080);

   ret=bind(sd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
   if(ret<0){
      printf("Error in bind\n");
      close(sd);
      return ret;
    }

    if(listen(sd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }
    
    return sd;

}
