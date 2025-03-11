/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_6.c
 * cc -o client_6 client_6.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Creer une socket (domaine IPv4, type flux, protocole par defaut)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erreur lors de la creation de la socket");
        exit(EXIT_FAILURE);
    }

    // Configurer l'adresse du serveur
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); // Numero de port (conversion hote -> reseau)

    // Convertir l'adresse loopback en format reseau (127.0.0.1)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Adresse non valide ou non supportee");
        exit(EXIT_FAILURE);
    }

    // Se connecter au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur lors de la connexion");
        exit(EXIT_FAILURE);
    }

    printf("Connecte au serveur.\n");

    // Recevoir les nombres envoyes par le serveur
    for (int i = 0; i < 5; i++) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(sock, buffer, BUFFER_SIZE); // Lire depuis la socket
        if (valread > 0) {
            printf("Client - Nombre recu : %s\n", buffer);
        }
        sleep(1); // Pause de 1 seconde entre chaque reception
    }

    // Fermer la socket
    close(sock);
    printf("Connexion terminee.\n");

    return 0;
}
