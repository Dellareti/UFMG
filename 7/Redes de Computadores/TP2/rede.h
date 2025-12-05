#ifndef REDE_H
#define REDE_H

#include <sys/socket.h>
#include <netinet/in.h>

int criar_socket_servidor_ipv4(int porta);
int criar_socket_servidor_ipv6(int porta);
int criar_socket_cliente_ipv4(const char* ip, int porta, struct sockaddr_storage* addr, socklen_t* len);
int criar_socket_cliente_ipv6(const char* ip, int porta, struct sockaddr_storage* addr, socklen_t* len);

#endif
