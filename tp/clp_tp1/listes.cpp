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

// Function print_list()
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

// Function filter_iter()
std::forward_list<int> filter_iter(const std::forward_list<int> &list, std::function<bool(int)> predicat){
    //the integers will appear in the reverse order
    std::forward_list<int> results;
    for (int i : list)
    {
        if (predicat(i))
        {
            results.push_front(i);
        }
    }
    return results;
}

// Function test_23()
void test_23()
{
    std::cout << "*** test_23 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list, [](int a)
                                              { return a * 3; });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter_iter(results, [](int a)
                                                  { return (a % 2 == 0); });
    print_list(filtered);

    std::cout << std::endl;
}

// Function test_24()
void test_24(){
    std::cout << "*** test_24 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "-----------Using: " << coef << "-----------" << std::endl;
    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map_iter(list, [coef](int a)
                                              { return a * coef; });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter_iter(results, [](int a)
                                                  { return (a % 2 == 0); });
    print_list(filtered);
    std::cout << std::endl;
}

// Function reduce()
int reduce(const std::forward_list<int> &list, int n, std::function<int(int, int)> fct){
    //the integers will appear in the reverse order
    int result{n};
    for (int i : list)
    {
        result = fct(result, i);
    }
    return result;
}

// Function test_25()
void test_25(){
    std::cout << "*** test_25 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();

    int min_value{reduce(list, max_int, [](int a, int b){
                             if (a <= b)
                                 return a;
                             return b;
                         })};
    std::cout << "Minimum: " << min_value << std::endl;

    int max_value{reduce(list, min_int, [](int a, int b){
                             if (a >= b)
                                 return a;
                             return b;
                         })};
    std::cout << "Maximum: " << max_value << std::endl;
    std::cout << std::endl;
}

// Function main()
int main()
{
    std::srand( std::time( nullptr ));

    //tests
    test_21();
    test_22();
    test_23();
    test_24();
    test_25();

    return 0;
}

