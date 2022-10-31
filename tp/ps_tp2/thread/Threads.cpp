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
    // Création générateur de nombres aléatoires
    Random rdm_number(50);
    
    // Création  boîte à lettres
    MessageBox msg_box;

    // Création entre 10 et 20 consommateurs et 2 fois plus de producteurs 
    Random rdm_number_bis(10);
    int thread_sum = rdm_number_bis() + 10;
    for (int i = 0; i < 2; i++) {
        Consumer cons(i, msg_box, rdm_number, 20);
        std::thread thread_cons(cons);
        Producer prod(2 * i, msg_box, rdm_number, 10);
        Producer prod_bis(2 * i + 1, msg_box, rdm_number, 10);

        // Création des threads correspondants
        std::thread thread_prod(prod);
        std::thread thread_prod_bis(prod_bis);
        thread_prod.join();
        thread_prod_bis.join();
        thread_cons.join();
    }
}

int main() {
    // one_producer_one_consumer();
    several_producers_and_consumers();
    return 0;
}

