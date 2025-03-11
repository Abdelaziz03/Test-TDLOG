/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestSmartExpression.cpp
 * c++ -std=c++20 -o TestSmartExpression TestSmartExpression.cpp SmartExpression.cpp -lgtest -lpthread
 */

#include <gtest/gtest.h>
#include "SmartExpression.hpp"
#include <memory>
#include <sstream>

// Fonction utilitaire pour tester l'affichage d'une expression
void verifier_affichage(const SmartExpression& expr, const std::string& resultat_attendu) {
    EXPECT_EQ(expr.to_string(), resultat_attendu);
}

// // Test pour Nombre
// TEST(SmartExpressionTest, NombreAffichage) {
//     auto n = std::make_shared<Nombre>(123.456789f);
//     std::ostringstream oss;
//     oss << std::scientific << n->to_string();
//     EXPECT_EQ(oss.str(), "1.234568e+02");
// }

// // Test pour Variable
// TEST(SmartExpressionTest, VariableAffichage) {
//     auto x = std::make_shared<Variable>("x");
//     EXPECT_EQ(x->to_string(), "x");
// }

// // Test pour Addition
// TEST(SmartExpressionTest, AdditionAffichage) {
//     auto x = std::make_shared<Variable>("x");
//     auto n = std::make_shared<Nombre>(3.0f);
//     auto addition = std::make_shared<Addition>(x, n);
//     verifier_affichage(*addition, "(x + 3.000000e+00)");
// }

// // Test pour Multiplication
// TEST(SmartExpressionTest, MultiplicationAffichage) {
//     auto x = std::make_shared<Variable>("x");
//     auto n = std::make_shared<Nombre>(3.0f);
//     auto multiplication = std::make_shared<Multiplication>(x, n);
//     verifier_affichage(*multiplication, "(x * 3.000000e+00)");
// }

// // Test pour la dérivation d'une Variable
// TEST(SmartExpressionTest, VariableDerive) {
//     auto x = std::make_shared<Variable>("x");
//     auto derivee = x->derive("x");
//     verifier_affichage(*derivee, "1.000000e+00");
// }

// // Test pour la dérivation d'une Addition
// TEST(SmartExpressionTest, AdditionDerive) {
//     auto x = std::make_shared<Variable>("x");
//     auto n = std::make_shared<Nombre>(3.0f);
//     auto addition = std::make_shared<Addition>(x, n);
//     auto derivee = addition->derive("x");
//     verifier_affichage(*derivee, "(1.000000e+00 + 0.000000e+00)");
// }

// // Test pour la simplification d'une Addition de deux Nombres
// TEST(SmartExpressionTest, AdditionSimplifieNombre) {
//     auto n1 = std::make_shared<Nombre>(3.0f);
//     auto n2 = std::make_shared<Nombre>(5.0f);
//     auto addition = std::make_shared<Addition>(n1, n2);
//     auto simplifiee = addition->simplifie();
//     verifier_affichage(*simplifiee, "8.000000e+00");
// }


// Test pour une expression complexe
TEST(SmartExpressionTest, ComplexExpression) {
    {
        // Expression f(x) = (x + 2) * (x + 3)
        auto x = std::make_shared<Variable>("x");
        auto n2 = std::make_shared<Nombre>(2.0f);
        auto n3 = std::make_shared<Nombre>(3.0f);

        auto x_plus_2 = std::make_shared<Addition>(x, n2);
        auto x_plus_3 = std::make_shared<Addition>(x, n3);

        auto f = std::make_shared<Multiplication>(x_plus_2, x_plus_3);

        // Dérivée f'(x)
        auto f_prime = f->derive("x");

        // Simplification de f'(x)
        auto f_prime_simplifiee = f_prime->simplifie();

        // Afficher l'expression simplifiée
        std::cout << "f'(x) simplifiée : " << f_prime_simplifiee->to_string() << std::endl;
    }
    
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
    std::cout << "Instances créées : " << SmartExpression::get_instances_creees() << std::endl;
    std::cout << "Instances détruites : " << SmartExpression::get_instances_detruites() << std::endl;

    return result;
}
