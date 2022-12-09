#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

int main()
{
        //creamos el socket que guarda informacion de este
        int net_socket; 
        //el primer parametro es que decimos de que es, en mi caso de internet. el segundo que tipo de socket es, tcp o http, el tercero el protocolo
        net_socket = socket(AF_INET, SOCK_STREAM, 0);

        //ahora vamos a conectar el socket a algun lado
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;//Sabe que tipo de addres estamos trabajando
        server_address.sin_port = htons(4000); //el puerto, obvio (usamos el htons para este bien los tipops)
        server_address.sin_addr.s_addr = INADDR_ANY;//la direccion donde nos queremos conectar. INADDR_ANY es el 0 0 0 0
        
        //hay que castearlo noma
        int estado_coneccion = connect(net_socket, (struct sockaddr *)&server_address, sizeof(server_address));
 
        if (estado_coneccion != 0) {
                printf("rompimos");
                return -1;
        }
        //funcion para recibir info del server
        char server_response[256];//aca se guarda la informacion devuelve el server
        recv(net_socket, &server_response, sizeof(server_response), 0);

        //ahora que tenemos la respuesta del servidor, hagamos algo (?

        printf("El servidor devolvio: %s", server_response);

        //cerramos el socket
        close(net_socket);    


        return 0;
}