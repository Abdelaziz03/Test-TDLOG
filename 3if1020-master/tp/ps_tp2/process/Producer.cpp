/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * Programmation système - TP n°2
 *
 * Producer.cpp
 * Compilation : c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"

#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Hérite du constructeur
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // Boucle : générer et déposer les messages, pause aléatoire
        for (unsigned i = 0; i < nb_messages_; ++i) {
            int message = random_engine_(); // Entier aléatoire
            box_.put(message); // Dépôt
            std::cout << "Produit : " << message << std::endl; // Log
            std::this_thread::sleep_for(std::chrono::milliseconds(random_engine_())); // Pause
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // Config mémoire partagée, sémaphore, lancement producteur
    shared_memory_object shm(open_or_create, "SharedMemory", read_write);
    shm.truncate(65536); // Dimensionnement
    mapped_region region(shm, read_write); // Mappage
    MessageBox* box = new(region.get_address()) MessageBox(); // Construction
    named_semaphore semaphore(open_or_create, "Semaphore", 0); // Sémaphore
    semaphore.post(); // Signal prêt
    Random random(1000); // Aide aléatoire
    const unsigned int numMessages = 20; // Compte des messages
    Producer producer(1, *box, random, numMessages); // Configuration producteur
    producer(); // Exécution

    return 0;
}
