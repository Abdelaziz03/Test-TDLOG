/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression.hpp"

// Fonction utilitaire pour tester l'affichage d'une expression
void verifier_affichage(const Expression& expr, const std::string& resultat_attendu) {
    EXPECT_EQ(expr.to_string(), resultat_attendu);
}

// // Test unitaire pour l'affichage avec std::scientific
// TEST(ExpressionTest, NombreScientific) {
//     Nombre n(123.456789f);
//     std::ostringstream oss;
//     oss << std::scientific << n;
//     EXPECT_EQ(oss.str(), "1.234568e+02"); // Vérifie le format scientifique
// }

// // Test unitaire pour l'affichage d'une variable
// TEST(ExpressionTest, VariableAffichage) {
//     Variable v("x");
//     std::ostringstream oss;
//     oss << v;
//     EXPECT_EQ(oss.str(), "x");
// }

// // Test unitaire pour la dérivation d'un Nombre
// TEST(ExpressionTest, NombreDerive) {
//     Nombre n(42.0f); // Un Nombre quelconque
//     Expression* derivee = n.derive("x"); // Dérivation par rapport à "x"
//     verifier_affichage(*derivee, "0.000000e+00"); // Vérifie que la dérivée est 0
//     delete derivee; // Libère la mémoire allouée dynamiquement
// }

// // Test unitaire pour la dérivation d'une Variable
// TEST(ExpressionTest, VariableDerive) {
//     Variable v("x"); // Une Variable "x"
//     Expression* derivee1 = v.derive("x"); // Dérivation par rapport à "x"
//     verifier_affichage(*derivee1, "1.000000e+00"); // Vérifie que la dérivée est 1
//     delete derivee1; // Libère la mémoire allouée dynamiquement

//     Expression* derivee2 = v.derive("y"); // Dérivation par rapport à une autre variable "y"
//     verifier_affichage(*derivee2, "0.000000e+00"); // Vérifie que la dérivée est 0
//     delete derivee2; // Libère la mémoire allouée dynamiquement
// }


// TEST(ExpressionTest, AdditionDerive) {
//     Variable* x = new Variable("x");
//     Nombre* n1 = new Nombre(3.0f);
//     Addition addition(x, n1);

//     // Dérivation par rapport à "x"
//     Expression* derivee = addition.derive("x");
//     verifier_affichage(*derivee, "(1.000000e+00 + 0.000000e+00)"); // Vérifie la dérivée

//     delete derivee; // Libère la mémoire allouée dynamiquement
//     // Pas besoin de supprimer x et n1, ils seront supprimés par le destructeur de Addition
// }

// // Test unitaire pour l'affichage d'une Multiplication
// TEST(ExpressionTest, MultiplicationAffichage) {
//     Variable* x = new Variable("x");
//     Nombre* n1 = new Nombre(3.0f);
//     Multiplication multiplication(x, n1);

//     verifier_affichage(multiplication, "(x * 3.000000e+00)");
//     // Pas besoin de supprimer x et n1, ils seront supprimés par le destructeur de Multiplication
// }


// // Test unitaire pour la dérivation d'une Multiplication
// TEST(ExpressionTest, MultiplicationDerive) {
//     Variable* x = new Variable("x");
//     Nombre* n1 = new Nombre(3.0f);
//     Multiplication multiplication(x, n1);

//     // Dérivation par rapport à "x"
//     Expression* derivee = multiplication.derive("x");
//     verifier_affichage(*derivee, "((1.000000e+00 * 3.000000e+00) + (x * 0.000000e+00))");

//     delete derivee; // Libère la mémoire allouée dynamiquement
//     // Pas besoin de supprimer x et n1, ils seront supprimés par le destructeur de Multiplication
// }

// // Test unitaire pour la simplification d'un Nombre
// TEST(ExpressionTest, NombreSimplifie) {
//     Nombre* n = new Nombre(5.0f);
//     Expression* simplifiee = n->simplifie();
//     verifier_affichage(*simplifiee, "5.000000e+00");
//     delete simplifiee;
//     delete n;
// }

// // Test unitaire pour la simplification d'une Variable
// TEST(ExpressionTest, VariableSimplifie) {
//     Variable* x = new Variable("x");
//     Expression* simplifiee = x->simplifie();
//     verifier_affichage(*simplifiee, "x");
//     delete simplifiee;
//     delete x;
// }

// // Test unitaire pour la simplification d'une Addition de deux Nombres
// TEST(ExpressionTest, AdditionSimplifieNombre) {
//     Nombre* n1 = new Nombre(3.0f);
//     Nombre* n2 = new Nombre(5.0f);
//     Addition* addition = new Addition(n1, n2);
//     Expression* simplifiee = addition->simplifie();
//     verifier_affichage(*simplifiee, "8.000000e+00"); // 3.0 + 5.0 = 8.0
//     delete simplifiee;
//     delete addition; // `addition` supprime `n1` et `n2`
// }

 
//  // Test unitaire pour la simplification d'une Addition avec 0
// TEST(ExpressionTest, AdditionSimplifieZero) {
//     Nombre* zero = new Nombre(0.0f);
//     Variable* x = new Variable("x");
//     Addition* addition1 = new Addition(zero, x);
//     Expression* simplifiee1 = addition1->simplifie();
//     verifier_affichage(*simplifiee1, "x"); // 0 + x simplifié en x
//     delete simplifiee1;
//     delete addition1; // Supprime `zero` et `x`

//     Nombre* zero2 = new Nombre(0.0f);
//     Variable* y = new Variable("y");
//     Addition* addition2 = new Addition(y, zero2);
//     Expression* simplifiee2 = addition2->simplifie();
//     verifier_affichage(*simplifiee2, "y"); // y + 0 simplifié en y
//     delete simplifiee2;
//     delete addition2; // Supprime `zero2` et `y`
// }

// // Test unitaire pour la simplification d'une Multiplication de deux Nombres
// TEST(ExpressionTest, MultiplicationSimplifieNombre) {
//     Nombre* n1 = new Nombre(2.0f);
//     Nombre* n2 = new Nombre(3.0f);
//     Multiplication* multiplication = new Multiplication(n1, n2);
//     Expression* simplifiee = multiplication->simplifie();
//     verifier_affichage(*simplifiee, "6.000000e+00"); // 2.0 * 3.0 = 6.0
//     delete simplifiee;
//     delete multiplication; // `multiplication` supprime `n1` et `n2`
// }


// // Test unitaire pour la simplification d'une Multiplication avec 1 et 0
// TEST(ExpressionTest, MultiplicationSimplifieUnEtZero) {
//     Nombre* un = new Nombre(1.0f);
//     Variable* x = new Variable("x");
//     Multiplication* multiplication1 = new Multiplication(un, x);
//     Expression* simplifiee1 = multiplication1->simplifie();
//     verifier_affichage(*simplifiee1, "x"); // 1 * x simplifié en x
//     delete simplifiee1;
//     delete multiplication1; // Supprime `un` et `x`

//     Nombre* zero = new Nombre(0.0f);
//     Variable* y = new Variable("y");
//     Multiplication* multiplication2 = new Multiplication(zero, y);
//     Expression* simplifiee2 = multiplication2->simplifie();
//     verifier_affichage(*simplifiee2, "0.000000e+00"); // 0 * y simplifié en 0
//     delete simplifiee2;
//     delete multiplication2; // Supprime `zero` et `y`
// }


// Test pour une expression complexe
TEST(ExpressionTest, ComplexExpression) {
    // Expression f(x) = (x + 2) * (x + 3)
    // Allouer dynamiquement les objets
    Variable* x = new Variable("x");
    Nombre* n2 = new Nombre(2.0f);
    Nombre* n3 = new Nombre(3.0f);

    // Cloner x pour éviter les problèmes de double suppression
    Addition* x_plus_2 = new Addition(x->clone(), n2);
    Addition* x_plus_3 = new Addition(x->clone(), n3);

    Multiplication* f = new Multiplication(x_plus_2, x_plus_3);

    // Dérivée f'(x)
    Expression* f_prime = f->derive("x");

    // Simplification de f'(x)
    Expression* f_prime_simplifiee = f_prime->simplifie();

    // Afficher l'expression simplifiée
    std::cout << "f'(x) simplifiée : " << f_prime_simplifiee->to_string() << std::endl;

    // Nettoyage de la mémoire
    delete f;
    delete f_prime;
    delete f_prime_simplifiee;
    delete x;
}

/*
Ce test compare, sur une expression un peu compliquée, le nombre d'instances créées lors de la dérivation
et de la simplification entre cette version et la version sans pointeurs intelligents.

Expression complexe choisie :
  f(x) = (x + 2) * (x + 3)

Output de la version sans pointeurs intelligents :
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from ExpressionTest
[ RUN      ] ExpressionTest.ComplexExpression
f'(x) simplifiée : ((x + 3.000000e+00) + (x + 2.000000e+00))
[       OK ] ExpressionTest.ComplexExpression (0 ms)
[----------] 1 test from ExpressionTest (0 ms total)
[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
Instances créées : 36
Instances détruites : 36

Output de la version avec pointeurs intelligents :
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from SmartExpressionTest
[ RUN      ] SmartExpressionTest.ComplexExpression
f'(x) simplifiée : ((x + 3.000000e+00) + (x + 2.000000e+00))
[       OK ] SmartExpressionTest.ComplexExpression (0 ms)
[----------] 1 test from SmartExpressionTest (0 ms total)
[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
Instances créées : 16
Instances détruites : 16

Comparaison :
- La version sans pointeurs intelligents a créé et détruit 36 instances.
- La version avec pointeurs intelligents a créé et détruit 16 instances.
- La version avec pointeurs intelligents a donc créé 20 instances de moins.
- Cette réduction est due aux optimisations suivantes :
  * Éviter le clonage inutile grâce à l'utilisation de `std::shared_ptr`.
  * Réutilisation des instances statiques pour les constantes (`0` et `1`) dans les méthodes `derive()`.
  * Utilisation de `shared_from_this()` dans `simplifie()` pour éviter de créer de nouvelles instances lorsque ce n'est pas nécessaire.
- Ces optimisations améliorent les performances et la gestion de la mémoire en réduisant le nombre total d'instances créées.
*/


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    // Afficher les compteurs
    std::cout << "Instances créées : " << Expression::get_instances_creees() << std::endl;
    std::cout << "Instances détruites : " << Expression::get_instances_detruites() << std::endl;

    return result;
}
