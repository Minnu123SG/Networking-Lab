#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main() {
int sock = 0;
struct sockaddr_in serv_addr;
char *message = "Hello from the client!";
char buffer[BUFFER_SIZE] = {0};
// Create socket
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
printf("Socket creation error\n");
return -1;
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
// Convert IPv4 and IPv6 addresses from text to binary form
if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
printf("Invalid address/ Address not supported\n");
return -1;
}
// Connect to the server
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
printf("Connection failed\n");
return -1;
}
// Send message to the server
send(sock, message, strlen(message), 0);
printf("Message sent to server.\n");
// Read response from the server
read(sock, buffer, BUFFER_SIZE);
printf("Message from server: %s\n", buffer);
// Close the socket
close(sock);
return 0;
}
