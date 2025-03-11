/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO : 
        // - Déposer dans box_ nb_messages_ entiers positifs avec attente
        //   aléatoire avant chaque dépôt.
        // - Afficher des messages entre chaque étape pour suivre l'avancement.
    Random generator(50); // Création du générateur pour des attentes entre 0 et 50 µs
    for (int i = 0; i < nb_messages_; ++i) {
        std::this_thread::sleep_for(std::chrono::microseconds(generator()));
        box_.put(i); 
        osyncstream{ std::cout } << "Producteur a déposé le message " << i << "\n";
    }
}
};

 
