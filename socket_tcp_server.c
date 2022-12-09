#include <stdio.h>
#include <stdlib.h>     

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

int main()
{
        char server_message[256] = "Llegaste al server";
        //creamos el socket
        int server_socket;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);

        //definimos la direccion del server
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(4000);//obvio, tiene que tener el mismo puerto que el del cliente
        server_address.sin_addr.s_addr = INADDR_ANY;

        //uniendo el socket a la ip y puerto
        bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

        //empezamos a escuchar conexiones, el segundo parametro es cuantos se pueden conectar
        listen(server_socket, 5);
        
        int client_socket;      
        //el primer parametro es de donde acepto, el segundo seria un struct que contiene informacion de la direccion de la conexion del cliente
        //sirve para saber desde donde se conecta el cliente
        client_socket = accept(server_socket, NULL, NULL);
        //enviamos el mensaje a nuestro cliente
        send(client_socket, server_message, sizeof(server_message), 0);//pasamos a quien le enviamos nuestra respuesta, en el segundo va la informacion que enviamos y el tercero el tamanio de este

        //cerramos el socket   
        close(server_socket);

        return 0;
}