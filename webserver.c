#include <stdio.h>      // Biblioteca padrão para entrada e saída. (printf, perror)
#include <stdlib.h>     // Biblioteca padrão para funções gerais. (exit)
#include <string.h>     // Biblioteca para manipulação de strings. (strlen)
#include <unistd.h>     // Biblioteca para funções POSIX. (close, read, write)
#include <sys/socket.h> // Biblioteca para criação e manipulação de sockets. (socket, bind, listen, accept)
#include <netinet/in.h> // Biblioteca para estruturas e funções relacionadas a endereços de rede. (sockaddr_in, htons)

#define APP_MAX_BUFFER 1024 // Definimos um buffer de 1024 bytes para leitura da conexão
#define PORT 8080           // Porta onde o servidor vai escutar as conexões

int main()
{
  int server_fd, client_fd;            // File descriptors: um para o servidor, outro para cada cliente
  struct sockaddr_in address;          // Estrutura que guarda as informações de IP e porta
  int address_len = sizeof(address);   // Tamanho da estrutura address
  char buffer[APP_MAX_BUFFER] = {0};    // Buffer onde vamos armazenar os dados recebidos

  // (1) Criação do socket TCP
  // -> Aqui a aplicação cria um socket IPv4 (AF_INET) de fluxo (SOCK_STREAM)
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  // (2) Configuração do endereço e porta
  // -> Preenchemos a estrutura com informações: aceitar qualquer IP (INADDR_ANY) e escutar na porta 8080
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT); // htons() transforma o número da porta para o padrão da rede (big-endian)

  // (3) Faz o bind do socket
  // -> Aqui associamos o socket criado à porta 8080. 
  // -> Até agora, o kernel ainda não está aceitando conexões, apenas reservamos a porta.
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  // (4) Coloca o socket em modo de escuta
  // -> Agora o kernel começa a aceitar conexões TCP e coloca as conexões completas na accept queue.
  if (listen(server_fd, 10) < 0)
  {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }

  // (5) Loop principal para aceitar conexões uma a uma
  while (1)
  {
    printf("\nWaiting for a connection...\n");

    // (6) Accept: pegamos uma conexão da accept queue do kernel
    // -> Aqui o kernel já fez todo o TCP handshake. A aplicação apenas consome a conexão pronta.
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&address_len)) < 0)
    {
      perror("Accept failed");
      exit(EXIT_FAILURE);
    }

    // (7) Leitura dos dados enviados pelo cliente
    // -> O cliente já enviou dados, e eles foram armazenados na recv queue do kernel.
    // -> Chamamos read() para copiar os bytes da fila do kernel para o nosso buffer.
    read(client_fd, buffer, APP_MAX_BUFFER);

    // (8) Exibição da mensagem recebida
    // -> Nesse ponto, ainda é um stream de bytes. Não tratamos se é HTTP corretamente — apenas exibimos.
    printf("%s\n", buffer);

    // (9) Construção de uma resposta HTTP simples
    // -> Preparamos uma resposta já formatada no protocolo HTTP
    char *http_response = "HTTP/1.1 200 OK\n"
                          "Content-Type: text/plain\n"
                          "Content-Length: 13\n\n"
                          "Hello world!\n";

    // (10) Escrita da resposta de volta ao cliente
    // -> Chamamos write() para copiar o stream de resposta para a send queue do kernel.
    write(client_fd, http_response, strlen(http_response));

    // (11) Fechamos a conexão com o cliente
    // -> Após responder, encerramos a conexão TCP chamando close().
    close(client_fd);
  }

  return 0;
}
