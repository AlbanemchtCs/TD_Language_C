/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <sstream>
#include <thread>
 
 
#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"
 
/*
 * Test avec 1 producteur et 1 consommateur
 */
void one_producer_one_consumer() {
    // Générateur de nombres aléatoires
    Random rdm_number(50);

    // Boîte à lettres
    MessageBox msg_box{};

    // Création d'un producteur et un consommateur
    Producer prod(1, msg_box, rdm_number, 20);
    Consumer cons(1, msg_box, rdm_number, 20);

    // Création des threads correspondants
    std::thread thread_prod(prod);
    std::thread thread_cons(cons);
    thread_prod.join();
    thread_cons.join();
}

void several_producers_and_consumers() {
    // TODO :
    // - Créer un générateur de nombres aléatoires
    // - Créer une boîte à lettres
    // - Créer entre 10 et 20 consommateurs et 2 fois plus de producteurs 
    // - Créer les threads correspondants
    // - Attendre la fin des threads
 
}

int main() {
    one_producer_one_consumer();
    //several_producers_and_consumers();
    return 0;
}

