#include "common.h"

void clientipc();
void client(int sock, struct sockaddr_in serverAddress);
void fillSocketAddress(struct sockaddr_in * sockaddr, int port);

int main(void)
{
    clientipc();
    exit(0);
}

void clientipc()
{
    int sock; /* дескриптор сокета */
    struct sockaddr_in server; /* адрес сервера */

    sock = socket(PF_INET, SOCK_DGRAM, 0);/* создание сокета */
    bzero(&server, sizeof(server));

    fillSocketAddress(&server, PORT_SERVER);

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

void fillSocketAddress(struct sockaddr_in * sockaddr, int port)
{
    struct in_addr *srv;
    unsigned long addr_s;

    (* sockaddr).sin_family = PF_INET;
    srv=&((* sockaddr).sin_addr);
    addr_s = inet_addr("127.0.0.1");
    (*srv).s_addr = addr_s;
    (* sockaddr).sin_port = htons(port);
}