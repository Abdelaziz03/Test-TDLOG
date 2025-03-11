/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <string>
#include <utility>

#include <cstdlib>
#include <ctime>


#include <gtest/gtest.h>

#include "Number.hpp"

 
TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}
 
TEST( TestNumber, TestNumberRandom )
{
    auto r{ std::rand() };
    Number n{ static_cast< unsigned long >( r )};
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), std::to_string( r ));
}


// Test du constructeur de copie
TEST(NumberTests, CopyConstructor) {
    Number original(12345);
    Number copy = original;

    std::ostringstream os1, os2;
    os1 << original;
    os2 << copy;

    // Vérifie que le contenu est identique
    EXPECT_EQ(os1.str(), os2.str());

    // Modifie `copy` et vérifie que `original` reste inchangé
    Number modifiedCopy(67890);
    modifiedCopy = copy;
    os2.str(""); os2 << modifiedCopy;
    EXPECT_EQ(os2.str(), "12345");

    // Modifie `copy` et vérifie que `original` reste inchangé
    modifiedCopy = Number(67890);  // Assignation avec une valeur différente
    os1.str(""); os1 << original;
    os2.str(""); os2 << modifiedCopy;
    EXPECT_NE(os1.str(), os2.str());
}

// Test de l'opérateur d'affectation par copie
TEST(NumberTests, CopyAssignmentOperator) {
    Number num1(54321);
    Number num2 = num1;

    std::ostringstream os1, os2;
    os1 << num1;
    os2 << num2;

    // Vérifie que le contenu est identique après l'affectation
    EXPECT_EQ(os1.str(), os2.str());

    // Test d'auto-affectation
    num1 = num1;
    os1.str(""); os1 << num1;
    EXPECT_EQ(os1.str(), "54321");

    // Modifie `num2` et vérifie que `num1` reste inchangé
    num2 = Number(12345);
    os2.str(""); os2 << num2;
    EXPECT_NE(os1.str(), os2.str());
}

// Test de la méthode swap
TEST(NumberTests, SwapMethod) {
    Number num1(11111);
    Number num2(22222);

    std::ostringstream os1, os2;
    os1 << num1;
    os2 << num2;

    // Vérifie les valeurs initiales
    EXPECT_EQ(os1.str(), "11111");
    EXPECT_EQ(os2.str(), "22222");

    // Effectue le swap
    num1.swap(num2);

    // Vérifie que les valeurs ont été échangées
    os1.str(""); os1 << num1;
    os2.str(""); os2 << num2;
    EXPECT_EQ(os1.str(), "22222");
    EXPECT_EQ(os2.str(), "11111");
}

// Test du constructeur et du destructeur avec une grande valeur
TEST(NumberTests, LargeValue) {
    unsigned long large_value = 1234567890123456789;
    Number large_number(large_value);

    std::ostringstream os;
    os << large_number;

    // Vérifie que le nombre est correctement stocké et affiché
    EXPECT_EQ(os.str(), "1234567890123456789");
}


// Test de l'addition d'un entier avec un Number
TEST(NumberTests, AddSmallNumber) {
    Number num(123);
    num.add(7);

    std::ostringstream os;
    os << num;

    // Vérifie que 123 + 7 = 130
    EXPECT_EQ(os.str(), "130");
}

TEST(NumberTests, AddWithCarry) {
    Number num(999);
    num.add(1);

    std::ostringstream os;
    os << num;

    // Vérifie que 999 + 1 = 1000, en tenant compte du transport
    EXPECT_EQ(os.str(), "1000");
}

TEST(NumberTests, AddLargeValue) {
    Number num(12345);
    num.add(67890);

    std::ostringstream os;
    os << num;

    // Vérifie que 12345 + 67890 = 80235
    EXPECT_EQ(os.str(), "80235");
}

// Test de la multiplication d'un Number par un entier
TEST(NumberTests, MultiplySmallNumber) {
    Number num(123);
    num.multiply(2);

    std::ostringstream os;
    os << num;

    // Vérifie que 123 * 2 = 246
    EXPECT_EQ(os.str(), "246");
}

TEST(NumberTests, MultiplyWithCarry) {
    Number num(99);
    num.multiply(9);

    std::ostringstream os;
    os << num;

    // Vérifie que 99 * 9 = 891, en tenant compte du transport
    EXPECT_EQ(os.str(), "891");
}

TEST(NumberTests, MultiplyByLargeValue) {
    Number num(12345);
    num.multiply(678);

    std::ostringstream os;
    os << num;

    // Vérifie le résultat de 12345 * 678 = 8369910
    EXPECT_EQ(os.str(), "8369910");
}

TEST(NumberTests, MultiplyResultingInLargeNumber) {
    Number num(98765);
    num.multiply(43210);

    std::ostringstream os;
    os << num;

    // Vérifie le résultat de 98765 * 43210 = 4268425650
    EXPECT_EQ(os.str(), "4267635650");
}

// Test de la fonction factorial pour calculer 123!
TEST(TestNumber, TestFactorial123) {
    std::ostringstream os;
    os << factorial(123);

    EXPECT_EQ(os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                        "358923621676688311569606126402021707358352212940477825910915704116514"
                        "72186029519906261646730733907419814952960000000000000000000000000000");
}

// Test du constructeur avec une chaîne de caractères valide
TEST(NumberTests, ConstructFromString) {
    Number num("12345");
    std::ostringstream os;
    os << num;

    // Vérifie que le nombre est construit correctement
    EXPECT_EQ(os.str(), "12345");
}

// Test pour une chaîne de caractères vide
TEST(NumberTests, ConstructFromEmptyString) {
    EXPECT_THROW(Number(""), std::invalid_argument);
}

// Test pour une chaîne contenant des caractères non numériques
TEST(NumberTests, ConstructFromInvalidString) {
    EXPECT_THROW(Number("12a45"), std::invalid_argument);
}


// Test de l'opérateur >> avec une entrée valide
TEST(NumberTests, InputOperatorValidNumber) {
    std::istringstream input("12345");
    Number num(0);
    input >> num;

    std::ostringstream output;
    output << num;

    // Vérifie que le nombre est bien lu et affiché comme prévu
    EXPECT_EQ(output.str(), "12345");
}

// Test de l'opérateur >> avec des espaces avant et après le nombre
TEST(NumberTests, InputOperatorWithWhitespace) {
    std::istringstream input("   6789   ");
    Number num(0);
    input >> num;

    std::ostringstream output;
    output << num;

    // Vérifie que les espaces sont ignorés et que le nombre est correctement lu
    EXPECT_EQ(output.str(), "6789");
}

// Test de l'opérateur >> avec un caractère non numérique après le nombre
TEST(NumberTests, InputOperatorStopsAtNonDigit) {
    std::istringstream input("4567abc");
    Number num(0);
    input >> num;

    std::ostringstream output;
    output << num;

    // Vérifie que la lecture s'arrête au premier caractère non numérique
    EXPECT_EQ(output.str(), "4567");
}

// Test de l'opérateur >> avec une entrée vide
TEST(NumberTests, InputOperatorEmptyInput) {
    std::istringstream input("");
    Number num(0);
    input >> num;

    std::ostringstream output;
    output << num;

    // Si aucune donnée n'est lue, le nombre devrait rester inchangé (initialisé à 0 ici)
    EXPECT_EQ(output.str(), "0");
}

// Test de l'opérateur >> avec des caractères non numériques en début de chaîne
TEST(NumberTests, InputOperatorInvalidStart) {
    std::istringstream input("abc123");
    Number num(0);
    input >> num;

    std::ostringstream output;
    output << num;

    // La lecture échoue immédiatement, donc le nombre reste inchangé
    EXPECT_EQ(output.str(), "0");
}

#include <gtest/gtest.h>
#include "Number.hpp"

// Test des opérateurs += et +
TEST(NumberTests, AdditionOperators) {
    Number num1(12345);
    num1 += 55;

    std::ostringstream os1;
    os1 << num1;
    EXPECT_EQ(os1.str(), "12400");

    Number num2 = num1 + 100;
    std::ostringstream os2;
    os2 << num2;
    EXPECT_EQ(os2.str(), "12500");
}

// Test des opérateurs *= et *
TEST(NumberTests, MultiplicationOperators) {
    Number num1(123);
    num1 *= 10;

    std::ostringstream os1;
    os1 << num1;
    EXPECT_EQ(os1.str(), "1230");

    Number num2 = num1 * 2;
    std::ostringstream os2;
    os2 << num2;
    EXPECT_EQ(os2.str(), "2460");
}

// Test des constructeurs et opérateurs de déplacement
TEST(NumberTests, MoveConstructorAndAssignment) {
    Number num1(12345);
    
    // Test du constructeur de déplacement
    Number num2 = std::move(num1);
    std::ostringstream os;
    os << num2;
    EXPECT_EQ(os.str(), "12345");

    // Test de l'affectation par déplacement
    Number num3(67890);
    num3 = std::move(num2);
    os.str("");
    os << num3;
    EXPECT_EQ(os.str(), "12345");
}

int main( int argc, char * argv[] )
{
    std::srand( std::time( nullptr ));
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
