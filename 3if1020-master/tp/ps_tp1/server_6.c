/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_6.c
 * cc -o server_6 server_6.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int random_number;

    // Creer une socket (domaine IPv4, type flux, protocole par defaut)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erreur lors de la creation de la socket");
        exit(EXIT_FAILURE);
    }

    // Associer l'adresse IPv4 et le port au socket
    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Toutes les interfaces locales
    address.sin_port = htons(PORT); // Numero de port (conversion hote -> reseau)

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erreur lors du bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Ecouter les connexions entrantes
    if (listen(server_fd, 3) < 0) {
        perror("Erreur lors du listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Serveur en ecoute sur le port %d...\n", PORT);

    // Accepter une connexion entrante
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Erreur lors de l'acceptation");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connexion acceptee.\n");

    // Envoyer des nombres aleatoires au client
    srand(time(0)); // Initialiser le generateur de nombres aleatoires
    for (int i = 0; i < 5; i++) {
        random_number = rand() % 100; // Generer un nombre aleatoire entre 0 et 99
        snprintf(buffer, BUFFER_SIZE, "%d", random_number); // Convertir en chaine de caracteres
        send(new_socket, buffer, strlen(buffer), 0); // Envoyer au client
        printf("Serveur - Nombre envoye : %d\n", random_number);
        sleep(1); // Pause de 1 seconde entre chaque envoi
    }

    // Fermer la socket
    close(new_socket);
    close(server_fd);
    printf("Connexion terminee.\n");

    return 0;
}
