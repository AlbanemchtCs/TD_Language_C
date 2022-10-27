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
    int multiple{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "---------------- x" << multiple << " ----------------" << std::endl;
    std::forward_list<int> list_map = map_iter(list, [multiple](int a) {return a * multiple;});
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
int fold_left_aux(std::forward_list<int>::const_iterator iterator,
                  std::forward_list<int>::const_iterator end_iterator, int n,
                  std::function<int(int, int)> fonction){
    if (iterator == end_iterator)
        return n;
    else{
        int outcome{fonction(*iterator, n)};
        return fold_left_aux(++iterator, end_iterator, outcome, fonction);
    }
}

// Function fold_left()
int fold_left(const std::forward_list<int> &list, int n, std::function<int(int, int)> fonction){
    return fold_left_aux(list.cbegin(), list.cend(), n, fonction);
}

// Function test_31()
void test_31(){
    std::cout << "*** test_31 ***" << std::endl;
    auto list = random_list(10);
    print_list(list);

    int maximum_int = std::numeric_limits<int>::max();
    int minimum_int = std::numeric_limits<int>::min();

    int minimum_value{fold_left(list, maximum_int,[](int a, int b){
        if (a <= b)
            return a;
        return b;
    })};
    std::cout << "Smallest element: " << minimum_value << std::endl;

    int maximum_value{fold_left(list, minimum_int, [](int a, int b){
        if (a >= b)
            return a;
        return b;
    })};
    std::cout << "Largest element: " << maximum_value << std::endl;
    std::cout << std::endl;
}

// Function map_aux()
std::forward_list<int> map_aux(std::forward_list<int>::const_iterator iterator,
                               std::forward_list<int>::const_iterator end_iterator,
                               std::function<int(int)> fonction,
                               std::forward_list<int> list_mapped){
    if (iterator == end_iterator)
        return list_mapped;
    else{
        int value = fonction(*iterator);
        list_mapped = map_aux(++iterator, end_iterator, fonction, list_mapped);
        list_mapped.push_front(value);
        return list_mapped;
    }
}

// Function map()
std::forward_list<int> map(const std::forward_list<int> &list,
                           std::function<int(int)> fonction){
    std::forward_list<int> list_mapped;
    return map_aux(list.cbegin(), list.cend(), fonction, list_mapped);
}

// Function filter_aux()
std::forward_list<int> filter_aux(std::forward_list<int>::const_iterator iterator,
                                  std::forward_list<int>::const_iterator end_iterator,
                                  std::function<bool(int)> fonction,
                                  std::forward_list<int> list_filtered){
    if (iterator == end_iterator)
        return list_filtered;
    else{
        if (fonction(*iterator)){
            int value = *iterator;
            list_filtered = filter_aux(++iterator, end_iterator, fonction, list_filtered);
            list_filtered.push_front(value);
        }
        else
            return filter_aux(++iterator, end_iterator, fonction, list_filtered);
        return list_filtered;
    }
}

// Function filter()
std::forward_list<int> filter(const std::forward_list<int> &list,
                              std::function<bool(int)> fonction){
    std::forward_list<int> list_filtered;
    return filter_aux(list.cbegin(), list.cend(), fonction, list_filtered);
}

// Function test_32()
void test_32(){
    std::cout << "*** test_32 ***" << std::endl;
    int multiple{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::cout << "---------------- x" << multiple << " ----------------" << std::endl;
    std::forward_list<int> list_map = map(list, [multiple](int a){return a * multiple;});
    print_list(list_map);

    std::cout << "----------- Even numbers -----------" << std::endl;
    std::forward_list<int> list_filter = filter(list_map, [](int a){return (a % 2 == 0);});
    print_list(list_filter);
    std::cout << std::endl;
}

/*
 * Advanced part 4
 */

// Function test_41()
void test_41(){
    std::cout << "*** test_41 ***" << std::endl;
    int multiple{std::rand() % 5 + 1};
    auto list = random_list(10);
    print_list(list);

    std::multiplies<int> multiple_int;

    std::cout << "---------------- x" << multiple << " ----------------" << std::endl;
    std::forward_list<int> list_map = map(list, [multiple, multiple_int](int a){return multiple_int(a, multiple);});
    print_list(list_map);

    std::cout << "----------- Even numbers -----------" << std::endl;
    std::forward_list<int> list_filter = filter(list_map, [](int a){return (a % 2 == 0);});
    print_list(list_filter);
    std::cout << std::endl;
}

// Function main()
int main(){
    std::srand(std::time(nullptr));

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

