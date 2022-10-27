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
std::forward_list<int> random_list(int n){
    std::forward_list<int> list;
    for (int i = 0; i < n; i++){
        int rd_numb{std::rand() % 100};
        list.push_front(rd_numb);
    }
    return list;
}

// Function print_list()
void print_list(std::forward_list<int> &list){
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
std::forward_list<int> map_iter(const std::forward_list<int> &list, std::function<int(int)> function){
    //the integers will appear in the reverse order
    std::forward_list<int> list_map;
    for (int i : list)
        list_map.push_front(function(i));
    return list_map;
}

// Function test_22()
void test_22(){
    std::cout << "*** test_22 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "---------------- x3 ----------------" << std::endl;
    std::forward_list<int> list_map = map_iter(list, [](int a) {return a * 3;});
    print_list(list_map);
    std::cout << std::endl;
}

// Function filter_iter()
std::forward_list<int> filter_iter(const std::forward_list<int> &list, std::function<bool(int)> predicate){
    std::forward_list<int> list_filter;
    for (int i : list){
        if (predicate(i))
        {
            list_filter.push_front(i);
        }
    }
    return list_filter;
}

// Function test_23()
void test_23(){
    std::cout << "*** test_23 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    std::cout << "---------------- x3 ----------------" << std::endl;
    std::forward_list<int> list_map = map_iter(list, [](int a) {return a * 3;});
    print_list(list_map);

    std::cout << "----------- Even numbers -----------" << std::endl;
    std::forward_list<int> list_filter = filter_iter(list_map, [](int a) {return (a % 2 == 0);});
    print_list(list_filter);
    std::cout << std::endl;
}

// Function test_24()
void test_24(){
    std::cout << "*** test_24 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "---------------- x" << coef << " ----------------" << std::endl;
    std::forward_list<int> list_map = map_iter(list, [coef](int a) {return a * coef;});
    print_list(list_map);

    std::cout << "----------- Even numbers -----------" << std::endl;
    std::forward_list<int> list_filter = filter_iter(list_map, [](int a) {return (a % 2 == 0);});
    print_list(list_filter);
    std::cout << std::endl;
}

// Function reduce()
int reduce(const std::forward_list<int> &list, int n, std::function<int(int, int)> fonction){
    int outcome{n};
    for (int i : list){
        outcome = fonction(outcome, i);
    }
    return outcome;
}

// Function test_25()
void test_25(){
    std::cout << "*** test_25 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    int maximum_int = std::numeric_limits<int>::max();
    int minimum_int = std::numeric_limits<int>::min();

    int minimum_value{reduce(list, maximum_int, [](int a, int b){
        if (a <= b)
            return a;
        return b;
    })};
    std::cout << "Smallest element: " << minimum_value << std::endl;

    int maximum_value{reduce(list, minimum_int, [](int a, int b){
        if (a >= b)
            return a;
        return b;
    })};
    std::cout << "Largest element: " << maximum_value << std::endl;
    std::cout << std::endl;
}

/*
 * Recursion
 */

// Function fold_left_aux()
int fold_left_aux(std::forward_list<int>::const_iterator it,
                  std::forward_list<int>::const_iterator end, int n,
                  std::function<int(int, int)> fct){
    if (it == end)
        return n;
    else
    {
        int result{fct(*it, n)};
        return fold_left_aux(++it, end, result, fct);
    }
}

// Function fold_left()
int fold_left(const std::forward_list<int> &list, int n, std::function<int(int, int)> fct){
    return fold_left_aux(list.cbegin(), list.cend(), n, fct);
}

// Function test_31()
void test_31(){
    std::cout << "*** test_31 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();

    int min_value{fold_left(list, max_int,
                            [](int a, int b)
                            {
                                if (a <= b)
                                    return a;
                                return b;
                            })};
    std::cout << "Minimum: " << min_value << std::endl;

    int max_value{fold_left(list, min_int, [](int a, int b){
                                if (a >= b)
                                    return a;
                                return b;
                            })};
    std::cout << "Maximum: " << max_value << std::endl;
    std::cout << std::endl;
}

// Function map_aux()
std::forward_list<int> map_aux(std::forward_list<int>::const_iterator it,
                               std::forward_list<int>::const_iterator end,
                               std::function<int(int)> fct,
                               std::forward_list<int> results){
    if (it == end)
        return results;
    else
    {
        int result = fct(*it);
        results = map_aux(++it, end, fct, results);
        results.push_front(result);
        return results;
    }
}

// Function map()
std::forward_list<int> map(const std::forward_list<int> &list,
                           std::function<int(int)> fct){
    std::forward_list<int> results;
    return map_aux(list.cbegin(), list.cend(), fct, results);
}

// Function filter_aux()
std::forward_list<int> filter_aux(std::forward_list<int>::const_iterator it,
                                  std::forward_list<int>::const_iterator end,
                                  std::function<bool(int)> fct,
                                  std::forward_list<int> results){
    if (it == end)
        return results;
    else{
        if (fct(*it)){
            int result = *it;
            results = filter_aux(++it, end, fct, results);
            results.push_front(result);
        }
        else
            return filter_aux(++it, end, fct, results);
        return results;
    }
}

// Function filter()
std::forward_list<int> filter(const std::forward_list<int> &list,
                              std::function<bool(int)> fct){
    std::forward_list<int> results;
    return filter_aux(list.cbegin(), list.cend(), fct, results);
}

// Function test_32()
void test_32(){
    std::cout << "*** test_32 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "-----------Using: " << coef << "-----------" << std::endl;
    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map(list, [coef](int a)
                                         { return a * coef; });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter(results, [](int a)
                                             { return (a % 2 == 0); });
    print_list(filtered);

    std::cout << std::endl;
}

/*
 * Advanced part 4
 */

// Function test_41()
void test_41(){
    std::cout << "*** test_41 ***" << std::endl;
    int coef{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::multiplies<int> mul_int;

    std::cout << "-----------Using: " << coef << "-----------" << std::endl;
    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> results = map(list, [coef, mul_int](int a)
                                         { return mul_int(a, coef); });
    print_list(results);

    std::cout << "--------------v---------------" << std::endl;
    std::forward_list<int> filtered = filter(results, [](int a)
                                             { return (a % 2 == 0); });
    print_list(filtered);

    std::cout << std::endl;
}

// Function main()
int main(){
    std::srand( std::time( nullptr ));

    //tests
    test_21();
    test_22();
    test_23();
    test_24();
    test_25();
    test_31();
    test_32();
    test_41();
    return 0;
}

