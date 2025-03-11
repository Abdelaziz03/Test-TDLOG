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
#include <algorithm> 
#include <cstdlib>
#include <ctime>
#include <climits> // Pour que l'on utilise INT_MAX and INT_MIN

//2

//2.1

using int_list_t = std::forward_list<int>;

int_list_t random_list() {
    int_list_t list;
    int num_elements = rand() % 10;   
    for (int i = 0; i < num_elements; ++i) {
        list.push_front(rand() % 100);   
    }
    return list;
}

 
void print_list(const int_list_t& list) {
    std::cout << "( ";
    for (const auto& elem : list) {
        std::cout << elem << " ";
    }
    std::cout << ")" << std::endl;
}

 
void test_21() {
    std::cout << "*** test_21 ***" << std::endl;
    int_list_t list = random_list();
    print_list(list);
}

//int main() {
//    std::srand(std::time(nullptr));  
//    test_21();
//    return 0;
//}


//int main()
//{
//   std::srand( std::time( nullptr ));

//    return 0;
//}






//2.2

int_list_t map_iter(const int_list_t& list, int (*func)(int)) {
    int_list_t result;
    for (auto i : list) {
        result.push_front(func(i));
    }
    return result;
}

void test_22() {
    std::cout << "*** test_22 ***\n";
    int_list_t list = random_list();
    print_list(list);
    auto result = map_iter(list, [](int x) { return x * 3; });
    print_list(result);
}

//int main() {
//    std::srand(std::time(0));
//    test_21();
//    test_22();
//    return 0;
//}


// 2.3



int_list_t filter_iter(const int_list_t& list, bool (*pred)(int)) {
    int_list_t result;
    for (auto i : list) {
        if (pred(i)) {
            result.push_front(i);
        }
    }
    return result;
}

void test_23() {
    std::cout << "*** test_23 ***\n";
    int_list_t list = random_list();
    print_list(list);
    auto mapped = map_iter(list, [](int x) { return x * 3; });
    print_list(mapped);
    auto filtered = filter_iter(mapped, [](int x) { return x % 2 == 0; });
    print_list(filtered);
}

//int main() {
//    std::srand(std::time(0));
//    test_21();
//    test_22();
//    test_23();
//    return 0;
//}



// 2.4




int_list_t map_iter(const int_list_t& list, std::function<int(int)> func) {
    int_list_t result;
    for (auto i : list) {
        result.push_front(func(i));
    }
    return result;
}

void test_24() {
    std::cout << "*** test_24 ***\n";
    int coefficient = rand() % 5 + 1;
    std::cout << "Coefficient: " << coefficient << "\n";
    int_list_t list = random_list();
    print_list(list);
    auto result = map_iter(list, [coefficient](int x) { return x * coefficient; });
    print_list(result);
}

//int main() {
//    std::srand(std::time(0));
//    test_24();
//    return 0;
//}



// 2.5

int reduce(const int_list_t& list, int init, std::function<int(int, int)> func) {
    for (auto i : list) {
        init = func(init, i);
    }
    return init;
}

void test_25() {
    std::cout << "*** test_25 ***\n";
    int_list_t list = random_list();
    print_list(list);
    int min = reduce(list, INT_MAX, [](int a, int b) { return std::min(a, b); });
    int max = reduce(list, INT_MIN, [](int a, int b) { return std::max(a, b); });
    std::cout << "Min: " << min << ", Max: " << max << "\n";
}

//int main() {
//    std::srand(std::time(0));
//    test_25();
//    return 0;
//}


// 3


// 3.1


int fold_left_aux(int_list_t::const_iterator it, int_list_t::const_iterator end, int init, int (*func)(int, int)) {
    if (it == end) return init;
    return fold_left_aux(std::next(it), end, func(init, *it), func);
}

int fold_left(const int_list_t& list, int init, int (*func)(int, int)) {
    return fold_left_aux(list.cbegin(), list.cend(), init, func);
}

void test_31() {
    std::cout << "*** test_31 ***\n";
    int_list_t list = random_list();
    print_list(list);
    int min = fold_left(list, INT_MAX, [](int a, int b) { return std::min(a, b); });
    int max = fold_left(list, INT_MIN, [](int a, int b) { return std::max(a, b); });
    std::cout << "Min: " << min << ", Max: " << max << "\n";
}

//int main() {
//    std::srand(std::time(0));
//    //test_21();
//    //test_22();
//    //test_23();
//    //test_24();
//    //test_25();
//    test_31();
//    return 0;
//}






// Generates a random list of integers



// Recursive helper function for map
int_list_t map_aux(int_list_t::const_iterator it, int_list_t::const_iterator end, std::function<int(int)> func) {
    if (it == end) return {}; // Base case: if we reach the end, return an empty list
    int_list_t result = map_aux(std::next(it), end, func);
    result.push_front(func(*it)); // Apply function and add to front
    return result;
}

// Recursive map function
int_list_t map(const int_list_t& list, std::function<int(int)> func) {
    return map_aux(list.cbegin(), list.cend(), func);
}

// Recursive helper function for filter
int_list_t filter_aux(int_list_t::const_iterator it, int_list_t::const_iterator end, std::function<bool(int)> pred) {
    if (it == end) return {}; // Base case: if we reach the end, return an empty list
    int_list_t result = filter_aux(std::next(it), end, pred);
    if (pred(*it)) result.push_front(*it); // Add element if it satisfies the predicate
    return result;
}

// Recursive filter function
int_list_t filter(const int_list_t& list, std::function<bool(int)> pred) {
    return filter_aux(list.cbegin(), list.cend(), pred);
}

// Testing function for 3.2
void test_32() {
    std::cout << "*** test_32 ***\n";
    int coefficient = rand() % 5 + 1;
    std::cout << "Coefficient: " << coefficient << "\n";
    
    int_list_t list = random_list();
    print_list(list);
    
    auto mapped = map(list, [coefficient](int x) { return x * coefficient; });
    print_list(mapped);
    
    auto filtered = filter(mapped, [](int x) { return x % 2 == 0; });
    print_list(filtered);
}

//int main() {
//    std::srand(std::time(nullptr));
//    test_32();
//    return 0;
//}



//4

//4.1




void test_41() {
    std::cout << "*** test_41 ***\n";
    int coefficient = rand() % 5 + 1;
    std::cout << "Coefficient: " << coefficient << "\n";
    
    int_list_t list = random_list();
    print_list(list);
    
    auto partial_multiply = std::bind(std::multiplies<int>(), coefficient, std::placeholders::_1);
    
    auto mapped = map(list, partial_multiply);
    print_list(mapped);
    
    auto filtered = filter(mapped, [](int x) { return x % 2 == 0; });
    print_list(filtered);
}


/*
int main() {
    std::srand(std::time(nullptr));
    test_41();
    return 0;
}


*/











//4.2 


int fold_left_aux(int_list_t::const_iterator it, int_list_t::const_iterator end, int init, std::function<int(int, int)> func) {
    if (it == end) return init;
    return fold_left_aux(std::next(it), end, func(init, *it), func);
}

int fold_left_2(const int_list_t& list, int init, std::function<int(int, int)> func) {
    return fold_left_aux(list.cbegin(), list.cend(), init, func);
}

int fold_right_aux(int_list_t::const_iterator it, int_list_t::const_iterator end, int init, std::function<int(int, int)> func) {
    if (it == end) return init;
    int result = fold_right_aux(std::next(it), end, init, func);
    return func(*it, result);
}

int fold_right(const int_list_t& list, int init, std::function<int(int, int)> func) {
    return fold_right_aux(list.cbegin(), list.cend(), init, func);
}

void test_42() {
    std::cout << "*** test_42 ***\n";
    int_list_t list = random_list();
    print_list(list);

    int left_sum = fold_left_2(list, 0, [](int a, int b) { return a + b; });
    int right_sum = fold_right(list, 0, [](int a, int b) { return a + b; });

    int left_concat = fold_left_2(list, 1, [](int a, int b) { return a * b; });
    int right_concat = fold_right(list, 1, [](int a, int b) { return a * b; });

    std::cout << "Sum with fold_left: " << left_sum << ", Sum with fold_right: " << right_sum << "\n";
    std::cout << "Product with fold_left: " << left_concat << ", Product with fold_right: " << right_concat << "\n";
}

int main() {
    std::srand(std::time(nullptr));
    test_42();
    return 0;
}
