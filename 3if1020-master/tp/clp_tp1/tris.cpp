/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>


//1.1


using int_tab_t = std::vector< int >;

void print_tab(const int_tab_t & tab){
    std :: cout << "[ ";
    for (auto v : tab) std :: cout << " " << v;
    std :: cout << " ]" << std :: endl;

}

void test11(){
    const int_tab_t tab{ 1, -2, 3, -4, 5, -6 };
    print_tab(tab);

}

//int main()
//{
//    std::srand( std::time( nullptr ));
//    test11();
//    return 0;
//}




//1.2


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction qui remplace tous les éléments du tableau par des valeurs aléatoires comprises entre -10 et 10
void random_tab(int *tab, int size) {
    for (int i = 0; i < size; i++) {
        tab[i] = (rand() % 21) - 10;  // Génère des valeurs entre -10 et 10
    }
}

// Fonction qui affiche les éléments du tableau
void print_tab(int *tab, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

// Fonction de test qui crée un tableau, le remplit avec des nombres aléatoires et l'affiche
void test_12() {
    int tab[10];  // Crée un tableau de 10 entiers
    random_tab(tab, 10);  // Remplace les valeurs du tableau par des nombres aléatoires entre -10 et 10
    print_tab(tab, 10);   // Affiche le contenu du tableau
}

//int main() {
//    srand(time(NULL));  // Initialise le générateur de nombres aléatoires avec le temps actuel
//    test_12();  // Appelle la fonction de test
//    return 0;
//}



//1.3



// On va trier sans utiliser la magie des libs de tri !
void sort_tab_1(int* tab, int taille) {
    // Petit tri à bulles classique;
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                // On swappe si c’est plus grand
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}


void test_13() {
    int tab[10];
    
    // On genere des nombres aleatoires
    random_tab(tab, 10);
    
    // On les affiche avant le tri, histoire de comparer apres
    printf("Avant tri :\n");
    print_tab(tab, 10);
    
    // Et hop, tri en place
    sort_tab_1(tab, 10);
    
    // Maintenant, on check le resultat
    printf("Après tri :\n");
    print_tab(tab, 10);
}

//int main() {
    // On lance notre test
//    test_13();
//    return 0;
//}




//1.4

bool less(int a, int b) {
    return a < b;
}

bool greater(int a, int b) {
    return a > b;
}



void sort_tab_2(int *tab, int size, bool (*compare)(int, int)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (!compare(tab[j], tab[j + 1])) {
                // Echanger les elements si necessaire
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}


void test_14() {
    int tab[10];

    random_tab(tab, 10); // Genere un Tableau aleatoire
    printf("Tableau initial : ");
    print_tab(tab, 10);

    // Tri avec less()
    sort_tab_2(tab, 10, less);
    printf("Tableau trie avec less() : ");
    print_tab(tab, 10);

    // genere a nouveau un tableau aleatoire
    random_tab(tab, 10);
    printf("Tableau initial : ");
    print_tab(tab, 10);

    // Tri avec greater()
    sort_tab_2(tab, 10, greater);
    printf("Tableau trie avec greater() : ");
    print_tab(tab, 10);
}


//int main() {
//    test_14();
//    return 0;
//}




//1.5 


using int_tab_t = std::vector<int>;

void random_tab(int_tab_t& tab) {
    for (auto& num : tab) {
        num = rand() % 201 - 100;
    }
}

// Garder uniquement une version de print_tab
void print_tab_std(const int_tab_t& tab) {
    for (const auto& num : tab) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void sort_tab_3(int_tab_t& tab, std::function<bool(int, int)> compare) {
    for (std::size_t i = 0; i < tab.size(); ++i) {
        std::size_t optimal_idx = i;
        for (std::size_t j = i + 1; j < tab.size(); ++j) {
            if (compare(tab[j], tab[optimal_idx])) {
                optimal_idx = j;
            }
        }
        std::swap(tab[i], tab[optimal_idx]);
    }
}

void test_15() {
    std::cout << "*** test_15 ***" << std::endl;

    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);

    sort_tab_3(tab, [](int a, int b) { return std::abs(a) < std::abs(b); });
    std::cout << "Trie par valeur absolue (croissant) : ";
    print_tab(tab);

    sort_tab_3(tab, [](int a, int b) { return std::abs(a) > std::abs(b); });
    std::cout << "Trie par valeur absolue (decroissant) : ";
    print_tab(tab);
}

int main() {
    std::srand(std::time(nullptr));
    test_15();
    return 0;
}