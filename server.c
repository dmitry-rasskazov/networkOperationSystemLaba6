#include "common.h"

void serveripc();

int main(void)
{
/*вызов функции, выполняющей специальную обpаботку */
    serveripc();
    exit(0);
}

/*функция, pеализующая специальную обpаботку */
void serveripc()
{
    int sock; /* дескриптор сокета */
    int ret; /* возвращаемое значение */
    unsigned int clientAddrLen;
    struct sockaddr_in server, client; /* адрес сервера */
    sock = socket(PF_INET, SOCK_DGRAM, 0); /* создание сокета */
    bzero( &server, sizeof(server));
    bzero( &client, sizeof(client));
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = INADDR_ANY;/* назначение адреса сокету */
    server.sin_port = htons(PORT_SERVER);
    bind(sock, (struct sockaddr *) &server, sizeof(server));

    char buff[16];


    while (1) {
        ret = recvfrom(sock, buff, 16, 0, (struct sockaddr *) &client, &clientAddrLen);
        if(ret < 0) {
            printf("Ошибка чтения сокета!");
            break;
        } else {
            printf("Client accepted: address=%s, port=%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            printf("Принятые данные: %s\n", buff);
        }
    }

    close (sock);/* закрытие текущей связи */
}
