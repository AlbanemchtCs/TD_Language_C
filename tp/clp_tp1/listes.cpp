/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>

#include <cstdlib>
#include <ctime>

// Function random_list()
std::forward_list<int> random_list(int nb){
    std::forward_list<int> list;
    for (int i = 0; i < nb; i++)
    {
        int random_number{std::rand() % 100};
        list.push_front(random_number);
    }
    return list;
}

// Function print_list
void print_list(std::forward_list<int> &list)
{
    std::cout << "( ";
    for (int i : list)
        std::cout << i << " ";
    std::cout << ")" << std::endl;
}

// Function test_21()
void test_21(){
    std::cout << "*** test_21 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);
    std::cout << std::endl;
}

// Function map_iter()
std::forward_list<int> map_iter(const std::forward_list<int> &list, std::function<int(int)> fct){
    //the integers will appear in the reverse order
    std::forward_list<int> results;
    for (int i : list)
        results.push_front(fct(i));
    return results;
}

// Function test_22()
void test_22(){
    std::cout << "*** test_22 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list, [](int a)
                                              { return a * 3; });
    print_list(results);
    std::cout << std::endl;
}

// Function main()
int main()
{
    std::srand( std::time( nullptr ));

    //tests
    test_21();
    test_22();

    return 0;
}

