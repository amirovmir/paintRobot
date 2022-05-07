#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

int main() {
  char msg[10];
  std::cin.getline(msg, 10, '\n');
  int sock;
  struct sockaddr_in addr;
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&addr, sizeof(addr));
  close(sock);
  return 0;
}
