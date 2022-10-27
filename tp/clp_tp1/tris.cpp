/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <asm-generic/errno.h>
#include <cstdio>
#include <iostream>
#include <utility>
#include <functional>
#include <cstdlib>
#include <ctime>
// For tables
#include <vector>


// Function print_tab()
void print_tab(const std::vector<int> &table){
    std::cout << "[ ";
    for (int i(0); i < table.size(); i++){
        std::cout << table[i] << " ";
    }
    std::cout << "]";
}

//Function test_11()
void test_11(){
    const std::vector< int > tab{ 1, -2, 3, -4, 5, -6 };
    std::cout << "*** test_11 ***" << std::endl;
    print_tab(tab);
    std::cout << std::endl;
}

//Function random
void random_tab(std::vector<int> &table){
    for (int i = 0; i < table.size(); i++){
        table[i] = (rand()%21)-10;
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
void sort_tab_1(std::vector<int> &table){
    for (int i = 0; i < table.size() - 1; i++){
        int min_index{i};
        int min_value{table[i]};
        for (int j = i+1; j < table.size(); j++){
            if (table[j] < min_value){
                min_value = table[j];
                min_index = j;
            }
        }
        if (min_index != i){
            std::swap(table[i], table[min_index]);
            }
    }
}

// Function test_13()
void test_13(){
    std::cout << "*** test_13 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    std::cout << " >>> ASCENDING ORDER LIST >>> ";
    sort_tab_1(tab);
    print_tab(tab);
    std::cout << std::endl;
}

// Function less()
bool less(int a, int b){
    return (a <= b);
}

// Function greater()
bool greater(int a, int b){
    return (a >= b);
}

// Function sort_tab_2()
void sort_tab_2(std::vector<int> &table, bool(*compare)(int,int)){
    // Same sorting as sort_tab_1 but using the compare function passed as argument by pointer
     std::sort(table.begin(),table.end(), compare);
}

// Functiont test_14()
void test_14(){
    std::cout << "*** test_14 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    // Sort in ascending order with less function
    std::cout << " >>> ASCENDING ORDER LIST >>> ";
    sort_tab_2(tab, less);
    print_tab(tab);
    std::cout << std::endl;

    random_tab(tab);
    print_tab(tab);
    // Sort in descending order with greater function
    std::cout << " >>> DESCENDING ORDER LIST >>> ";
    sort_tab_2(tab, greater);
    print_tab(tab);
    std::cout << std::endl;
}

// Function sort_tab_3()
void sort_tab_3(std::vector<int> &table, std::function <bool(int, int)> compare){
   // Same sorting as sort_tab_1 but using here the lambda compare function passed as argument by pointer
   std::sort(table.begin(),table.end(), compare);
}

// Function test_15()
void test_15(){
    std::cout << "*** test_15 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
    // Sort in ascending order in absolute value with the lambda less function
    std::cout << " >>> ASCENDING ORDER LIST IN ABSOLUTE VALUE >>> ";
    sort_tab_3(tab, [](int a, int b) {return abs(a) <= abs(b);});
    print_tab(tab);
    std::cout << std::endl;

    random_tab(tab);
    print_tab(tab);
    // Sort in descending order in absolute value with the lambda less function
    std::cout << " >>> DESCENDING ORDER LIST IN ABSOLUTE VALUE >>> ";
    sort_tab_3(tab, [](int a, int b) {return abs(a) >= abs(b);});
    print_tab(tab);
    std::cout << std::endl;
}

int main(){
    std::srand( std::time( nullptr ));

    //Call functions tests
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();

    return 0;
}
