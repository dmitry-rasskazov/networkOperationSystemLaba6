#include "common.h"

void clientipc();
void client(int sock, struct sockaddr_in serverAddress);

int main(void)
{
    clientipc();
    exit(0);
}

void clientipc()
{
    int sock; /* дескриптор сокета */
    struct sockaddr_in server; /* адрес сервера */
    struct in_addr *srv;
    unsigned long addr_s;
    sock = socket(PF_INET, SOCK_DGRAM, 0);/* создание сокета */
    bzero(&server, sizeof(server));
    server.sin_family = PF_INET;
    srv=&(server.sin_addr);
    addr_s = inet_addr("127.0.0.1");
    (*srv).s_addr = addr_s;
    server.sin_port = htons(PORT); /* соединение с сервером */
    bind(sock, (struct sockaddr *) &server, sizeof(server));
    client(sock, server); /* закрытие соединения */
    close(sock);
}

void client(int sock, struct sockaddr_in serverAddress)
{
    char msg[]="Laba6 sockets! \n";
    int ret;

    if((ret = sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &serverAddress, sizeof (serverAddress))) < 0) {
        printf("Ошибка отправки данных в сокет!");
        return;
    }

    printf("Успешная отправка %d байт", ret);
}