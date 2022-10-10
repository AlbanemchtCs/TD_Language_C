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

int main(){
    std::srand( std::time( nullptr ));

    //Call function test_11()
    test_11();

    return 0;
}
