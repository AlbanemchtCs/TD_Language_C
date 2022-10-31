/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
 
/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        using milliseconds = std::chrono::duration<int, std::milli>;
        Random rdm_number(50);
        for (int m = 0; m < nb_messages_; m++) {
            // Retire de box_ nb_messages_ entiers avec attente aléatoire avant chaque retrait
            std::this_thread::sleep_for(milliseconds{rdm_number()});
            int message = box_.get();
            // Affiche des messages entre chaque étape pour suivre l'avancement
            std::cout << "Consumer message " << m << "\n";
            // Affiche un message d'erreur si un nombre négatif est extrait
            if (message < 0) {
                osyncstream(std::cerr) << "Negative consumer message " << message << "\n";
            }
        }
    }
};


