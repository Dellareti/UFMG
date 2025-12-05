#include "rede.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int criar_socket_servidor_ipv4(int porta) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket IPv4");
        return -1;
    }

    struct sockaddr_in endereco;
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(porta);

    if (bind(sock, (struct sockaddr*)&endereco, sizeof(endereco)) < 0) {
        perror("Erro ao fazer bind IPv4");
        close(sock);
        return -1;
    }

    return sock;
}

int criar_socket_servidor_ipv6(int porta) {
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket IPv6");
        return -1;
    }

    struct sockaddr_in6 endereco;
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin6_family = AF_INET6;
    endereco.sin6_addr = in6addr_any;
    endereco.sin6_port = htons(porta);

    if (bind(sock, (struct sockaddr*)&endereco, sizeof(endereco)) < 0) {
        perror("Erro ao fazer bind IPv6");
        close(sock);
        return -1;
    }

    return sock;
}

int criar_socket_cliente_ipv4(const char* ip, int porta, struct sockaddr_storage* addr, socklen_t* len) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket IPv4");
        return -1;
    }

    struct sockaddr_in* endereco = (struct sockaddr_in*)addr;
    memset(endereco, 0, sizeof(struct sockaddr_in));
    endereco->sin_family = AF_INET;
    endereco->sin_port = htons(porta);

    if (inet_pton(AF_INET, ip, &endereco->sin_addr) <= 0) {
        perror("Endereço IP inválido");
        close(sock);
        return -1;
    }

    *len = sizeof(struct sockaddr_in);
    return sock;
}

int criar_socket_cliente_ipv6(const char* ip, int porta, struct sockaddr_storage* addr, socklen_t* len) {
    int sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket IPv6");
        return -1;
    }

    struct sockaddr_in6* endereco = (struct sockaddr_in6*)addr;
    memset(endereco, 0, sizeof(struct sockaddr_in6));
    endereco->sin6_family = AF_INET6;
    endereco->sin6_port = htons(porta);

    if (inet_pton(AF_INET6, ip, &endereco->sin6_addr) <= 0) {
        perror("Endereço IP inválido");
        close(sock);
        return -1;
    }

    *len = sizeof(struct sockaddr_in6);
    return sock;
}
