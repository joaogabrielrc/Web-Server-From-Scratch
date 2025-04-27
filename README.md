# README - webserver.c

## Descrição

Este arquivo, `webserver.c`, implementa um servidor web simples em C. Ele utiliza sockets para estabelecer conexões TCP e responde a requisições de clientes com uma mensagem HTTP básica. O código é projetado para fins educacionais, demonstrando os conceitos fundamentais de redes e programação de sockets.

---

## Funcionalidades

1. **Criação de um socket TCP**: O servidor cria um socket IPv4 para comunicação baseada em fluxo.
2. **Configuração do endereço e porta**: O servidor é configurado para escutar na porta 8080 em qualquer interface de rede disponível.
3. **Bind do socket**: O socket é associado à porta configurada.
4. **Modo de escuta**: O servidor entra em modo de escuta, aguardando conexões de clientes.
5. **Aceitação de conexões**: O servidor aceita conexões de clientes, uma por vez.
6. **Leitura de dados**: O servidor lê os dados enviados pelo cliente.
7. **Resposta HTTP**: O servidor responde com uma mensagem HTTP simples contendo "Hello world!".
8. **Encerramento da conexão**: Após enviar a resposta, o servidor encerra a conexão com o cliente.

---

## Estrutura do Código

O código segue uma sequência lógica para implementar o servidor:

1. **Inclusão de bibliotecas**:

   - `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`: Funções padrão de C.
   - `sys/socket.h`, `netinet/in.h`: Funções e estruturas para manipulação de sockets e endereços de rede.

2. **Definições**:

   - `APP_MAX_BUFFER`: Tamanho do buffer para leitura de dados (1024 bytes).
   - `PORT`: Porta onde o servidor escuta conexões (8080).

3. **Funções principais**:

   - Criação do socket.
   - Configuração do endereço e porta.
   - Bind do socket.
   - Entrada em modo de escuta.
   - Loop principal para aceitar conexões e processar requisições.

4. **Processamento de requisições**:
   - Leitura de dados enviados pelo cliente.
   - Construção de uma resposta HTTP simples.
   - Envio da resposta ao cliente.
   - Encerramento da conexão.

---

## Como Executar

1. **Compilar o código**:
   Use o GCC para compilar o arquivo:

   ```bash
   gcc -o webserver webserver.c
   ```

2. **Executar o servidor**: Execute o binário gerado:

   ```bash
   ./webserver
   ```

3. **Testar o servidor**: Abra um navegador ou use ferramentas como curl para enviar uma requisição:

   ```bash
   curl http://localhost:8080
   ```

4. **O servidor responderá com**:
   ```bash
   HTTP/1.1 200 OK
   Content-Type: text/plain
   Content-Length: 13
   Hello world!
   ```

## Observações

Este servidor é básico e não implementa todas as funcionalidades de um servidor HTTP completo.
Ele não trata múltiplas conexões simultaneamente (não é multithreaded).
Para uso em produção, melhorias como suporte a HTTPS, tratamento de erros robusto e segurança devem ser implementadas.
Requisitos
Sistema operacional Linux.
Compilador GCC.
Conhecimento básico de redes e programação em C.

## Licença

Este código é fornecido para fins educacionais e pode ser usado livremente.
