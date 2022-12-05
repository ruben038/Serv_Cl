
source =
copie = 
cp= 
client: client.c
	gcc client.c -o client
cl: client.c
	gcc client.c -o cl
server: server.c
	gcc server.c -o server	
		
start: server client $(source) 
	gnome-terminal -- ./server $(source)
	gnome-terminal -- ./client $(copie) 
	gnome-terminal -- ./cl $(cp) 
