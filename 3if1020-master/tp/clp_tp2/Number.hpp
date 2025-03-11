/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.hpp
 */

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>

class Number {
public:
    Number(unsigned long l);
    ~Number();
    Number(const std::string& s); // Constructeur à partir d'une chaîne de caractères
    
    // Constructeur de copie
    Number(const Number& other);

    // Opérateur d'affectation par copie
    Number& operator=(const Number& other);

    // Opérateur d'affectation par déplacement
    Number& operator=(Number&& other) noexcept;

    // Opérateurs arithmétiques
    Number& operator+=(unsigned int i);
    Number& operator*=(unsigned int i);

    // Opérateurs arithmétiques externes
    friend Number operator+(const Number& n, unsigned int i);
    friend Number operator*(const Number& n, unsigned int i);

    // Méthode d'affichage
    void print(std::ostream& out) const;

    // Méthode swap pour échanger les données entre deux Numbers
    void swap(Number& other);

    // Ajoute un unsigned int au Number courant
    void add(unsigned int i);

    // Multiplie le Number courant par un unsigned int
    void multiply(unsigned int i);

    friend std::istream& operator>>(std::istream& in, Number& n); // Déclaration de l'opérateur de lecture

private:
    using DigitType = unsigned int;
    // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
    static const DigitType number_base{ 10u };
    struct Digit {
        DigitType digit_;
        Digit* next_;

        // Déclaration du constructeur de Digit
        Digit(DigitType d, Digit* n = nullptr);

        // Déclaration du destructeur de Digit (récursif)
        ~Digit();

        // Méthode d'affichage récursive
        void print(std::ostream& out) const;
    };
    Digit* first_;

    friend std::istream& operator>>(std::istream& in, Number& n); // Déclaration de l'opérateur de lecture
};

// Déclaration de la fonction factorial
Number factorial(unsigned int i);

inline std::ostream& operator<<(std::ostream& out, const Number& n) {
    n.print(out);
    return out;
}

#endif
