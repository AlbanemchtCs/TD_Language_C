/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>

// For tables
#include <vector>

// Function print_tab()
void print_tab(const std::vector<int> &tab){
    std::cout << "[ ";
    for (int i(0); i < tab.size(); i++){
        std::cout << tab[i] << " ";
    }
    std::cout << "]";
}

//Function test_11()
void test_11(){
    const std::vector< int > tab{ 1, -2, 3, -4, 5, -6 };
    std::cout << "*** test_11 *** " << std::endl;
    print_tab(tab);
    std::cout << std::endl;
}

//Function random
void random_tab(std::vector<int> &tab){
    for (int i{0}; i < tab.size(); i++) {
        tab[i] = (rand()%21)-10;
    }
}

//Function test_12()
void test_12() {
    std::cout << "*** test_12 ***" << std::endl;
    std::vector<int>tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << std::endl;
}

// Function sort_tab_1()
void sort_tab_1(std::vector<int> &tab){
    for (int i{0}; i < tab.size() - 1; i++) {
        int min_index{i};
        int min_value{tab[i]};
        for (int j{i+1}; j < tab.size(); j++) {
            if (tab[j] < min_value) {
                min_value = tab[j];
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(tab[i], tab[min_index]);
            }
    }
}

// Function test_13()
void test_13(){
    std::cout << "*** test_13 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << " >> SORTED LIST >> ";
    sort_tab_1(tab);
    print_tab(tab);
    std::cout << std::endl;
}

int main(){
    std::srand( std::time( nullptr ));

    //Call functions tests
    test_11();
    test_12();
    test_13();

    return 0;
}
