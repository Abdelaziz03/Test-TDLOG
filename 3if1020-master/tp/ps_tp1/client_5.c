/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
 * cc -o client_5 client_5.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>

int running = 1;          
int client_pid;           
int server_pid;           


void handle_pipe_closed(int signal) {
    fprintf(stderr, "Client (PID: %d) - FIFO closed, exiting gracefully.\n", client_pid);
    exit(EXIT_SUCCESS);
}


void handle_server_termination(int signal) {
    fprintf(stderr, "Client (PID: %d) - Server (PID: %d) has terminated, exiting gracefully.\n", client_pid, server_pid);
    exit(EXIT_SUCCESS);
}


void handle_client_termination(int signal) {
    fprintf(stderr, "Client (PID: %d) - Client received termination signal, exiting gracefully.\n", client_pid);
    exit(EXIT_SUCCESS);
}

int main() {
    int fifo_fd;                
    int received_number;        
    client_pid = getpid();      

    
    if ((fifo_fd = open("myfifo", O_RDONLY)) == -1) {
        perror("Error opening FIFO for reading");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Client is running (PID: %d)...\n", client_pid);

    // Set up signal handler pour SIGPIPE
    if (signal(SIGPIPE, handle_pipe_closed) == SIG_ERR) {
        perror("Error setting SIGPIPE handler");
        exit(EXIT_FAILURE);
    }

    // Set up signal handler pour SIGCHLD
    if (signal(SIGCHLD, handle_server_termination) == SIG_ERR) {
        perror("Error setting SIGCHLD handler");
        exit(EXIT_FAILURE);
    }

    // Set up signal handler pour SIGTERM 
    if (signal(SIGTERM, handle_client_termination) == SIG_ERR) {
        perror("Error setting SIGTERM handler");
        exit(EXIT_FAILURE);
    }

    // Client main loop
    while (running) {
        ssize_t bytes_read = read(fifo_fd, &received_number, sizeof(received_number));
        
        if (bytes_read == -1) {
            perror("Error reading from FIFO");
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0) {
            // Fin de fifo donc le serveur est près du pip
            break;
        }

        // Lecture des nombre de la fifo
        printf("Client (PID: %d) - Received number = %d\n", client_pid, received_number);
    }

    // Close the fifo
    close(fifo_fd);
    fprintf(stderr, "Client (PID: %d) - Client exiting gracefully.\n", client_pid);
    exit(EXIT_SUCCESS);
}
