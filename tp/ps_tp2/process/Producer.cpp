/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Producer
    using ProdOrCons::ProdOrCons;
    using milliseconds = std::chrono::duration<int, std::milli>;

    void operator()() override {
        
        // Dépose dans box nb_messages nombres entiers positifs avec attente aléatoire entre chaque dépôt
        // Affiche des messages pour suivre l'avancement
        for (int m = 0; m < nb_messages_; m++) {
            int message = m;
            box_.put(message);
            std::cout << "Producer message " << m << "\n";
            std::this_thread::sleep_for(milliseconds{random_engine_()});
        }
    }
};

int main() {
    using namespace boost::interprocess;

    // Création mémoire partagée, projète en mémoire, y construit la boîte à lettres, lance le producteur
    int memory_box = sizeof(MessageBox);

    struct sharedbox_remove {
        sharedbox_remove() { shared_memory_object::remove("Memory box shared"); }
        ~sharedbox_remove() { shared_memory_object::remove("Memory box shared"); }
    } remover;

    shared_memory_object memory_shared(create_only, "Memory box shared", read_write);
    memory_shared.truncate(memory_box);
    mapped_region reg_mapped = mapped_region(memory_shared, read_write, 0, memory_box);
    MessageBox *msg_box = new (reg_mapped.get_address()) MessageBox();
    Random rdm_number{50};
    Producer prod = Producer(2, *msg_box, rdm_number, 20);
    prod();

    return 0;
}


