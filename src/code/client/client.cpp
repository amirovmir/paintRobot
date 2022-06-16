#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main() {
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    std::string response, x;
    char message[10];
    while (true) {
        std::cout << "Enter command"<< std::endl;
        std::cout << "Command list:\n MoveStraight, Reverse, Clean" << std::endl;
        std::cin >> response;

        if (response == "MoveStraight")
        {
            std::cout << "Enter distance:\n";
            std::cin >> x;
        }
        if (response == "Reverse")
        {
            std::cout << "Enter angle:\n";
            std::cin >> x;
        }
        response = response + " " + x;
        strcpy(message, response.c_str());
        sendto(sock, message, sizeof(message), 0, (struct sockaddr *)&addr, sizeof(addr));
    }
    close(sock);
    return 0;
}
