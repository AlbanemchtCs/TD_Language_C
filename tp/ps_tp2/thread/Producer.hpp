/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        using milliseconds = std::chrono::duration<int, std::milli>;
        Random rdm_number(50);
        for (int m = 0; m < nb_messages_; m++) {
            // Dépose dans box_ nb_messages_ entiers positifs avec attente aléatoire avant chaque dépôt
            std::this_thread::sleep_for(milliseconds{rdm_number()});
            // Affiche des messages entre chaque étape pour suivre l'avancement
            box_.put(m);
            std::cout << "Producer message " << m << "\n";
        }
    }
};

