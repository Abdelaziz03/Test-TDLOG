/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Number.hpp"
#include <stdexcept> // Pour std::invalid_argument

// Implémentation du constructeur de Number
Number::Number(unsigned long l) : first_(nullptr) {
    if (l == 0) { // Cas particulier pour 0
        first_ = new Digit{0, nullptr};
        return;
    }

    Digit* current = nullptr;
    while (l > 0) {
        Digit* new_digit = new Digit{static_cast<DigitType>(l % number_base)};
        
        if (!first_) {
            first_ = new_digit;
        } else {
            current->next_ = new_digit;
        }

        current = new_digit;
        l /= number_base;
    }
}

// Implémentation du destructeur de Number
Number::~Number() {
    delete first_; // Appelle le destructeur de Digit qui libère récursivement
}

// Implémentation du constructeur de Digit
Number::Digit::Digit(DigitType d, Digit* n) : digit_(d), next_(n) {}

// Implémentation du destructeur de Digit (récursif)
Number::Digit::~Digit() {
    delete next_; // Appelle récursivement le destructeur du maillon suivant
}

// Méthode d'affichage récursive dans Digit
void Number::Digit::print(std::ostream& out) const {
    if (next_) {
        next_->print(out); // Appel récursif pour aller jusqu’au dernier Digit
    }
    out << digit_; // Affiche le chiffre courant une fois les suivants affichés
}

// Méthode d'affichage de Number
void Number::print(std::ostream& out) const {
    if (first_) {
        first_->print(out); // Appelle la méthode print de Digit sur le premier chiffre
    } else {
        out << '0'; // Cas où le nombre est 0
    }
}

// Constructeur de copie de Number
Number::Number(const Number& other) : first_(nullptr) {
    if (other.first_) {
        first_ = new Digit(other.first_->digit_);
        Digit* current = first_;
        for (Digit* other_digit = other.first_->next_; other_digit != nullptr; other_digit = other_digit->next_) {
            current->next_ = new Digit(other_digit->digit_);
            current = current->next_;
        }
    }
}

// Opérateur d'affectation par copie
Number& Number::operator=(const Number& other) {
    if (this != &other) {
        delete first_;
        first_ = nullptr;

        if (other.first_) {
            first_ = new Digit(other.first_->digit_);
            Digit* current = first_;
            for (Digit* other_digit = other.first_->next_; other_digit != nullptr; other_digit = other_digit->next_) {
                current->next_ = new Digit(other_digit->digit_);
                current = current->next_;
            }
        }
    }
    return *this;
}

// Opérateur d'affectation par déplacement
Number& Number::operator=(Number&& other) noexcept {
    if (this != &other) {
        delete first_;
        first_ = other.first_;
        other.first_ = nullptr;
    }
    return *this;
}

// Méthode swap
void Number::swap(Number& other) {
    std::swap(first_, other.first_);
}

// Méthode add pour ajouter un entier au Number
void Number::add(unsigned int i) {
    Digit* current = first_;
    unsigned int carry = i;

    while (current != nullptr || carry > 0) {
        if (current == nullptr) {
            current = new Digit{carry % number_base};
            first_ = current;
        } else {
            carry += current->digit_;
            current->digit_ = carry % number_base;
            carry /= number_base;
            
            if (current->next_ == nullptr && carry > 0) {
                current->next_ = new Digit{0};
            }
            current = current->next_;
        }
    }
}

// Méthode multiply pour multiplier le Number par un entier
void Number::multiply(unsigned int i) {
    Digit* current = first_;
    unsigned int carry = 0;

    while (current != nullptr) {
        unsigned long product = static_cast<unsigned long>(current->digit_) * i + carry;
        current->digit_ = product % number_base;
        carry = product / number_base;

        if (current->next_ == nullptr && carry > 0) {
            current->next_ = new Digit{0};
        }
        current = current->next_;
    }
}

// Fonction pour calculer la factorielle d'un entier
Number factorial(unsigned int i) {
    Number result(1); // Initialise la factorielle à 1
    for (unsigned int n = 2; n <= i; ++n) {
        result.multiply(n); // Multiplie result par n successivement
    }
    return result;
}

// Constructeur de Number à partir d'une chaîne de caractères
Number::Number(const std::string& s) : first_(nullptr) {
    if (s.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    first_ = new Digit{0, nullptr}; // Initialise le premier Digit

    for (char c : s) {
        if (!std::isdigit(c)) {
            throw std::invalid_argument("Input string contains non-digit characters");
        }

        unsigned int d = static_cast<unsigned int>(c - '0'); // Convertit le caractère en chiffre
        this->multiply(10); // Décale en multipliant par 10
        this->add(d);       // Ajoute le chiffre
    }
}

// Opérateur de lecture pour lire un Number depuis un flux d'entrée
std::istream& operator>>(std::istream& in, Number& n) {
    in >> std::ws; // Ignore les espaces blancs initiaux
    
    Number temp(0); // Temporaire pour éviter de modifier `n` en cas d'échec
    bool has_read_digit = false;

    while (in.good()) {
        int c = in.get();
        if (std::isdigit(c)) {
            unsigned int d = static_cast<unsigned int>(c - '0');
            temp.multiply(10); // Décale le nombre actuel
            temp.add(d);       // Ajoute le chiffre lu
            has_read_digit = true;
        } else {
            in.putback(c); // Remet le caractère dans le flux s'il n'est pas un chiffre
            break;
        }
    }

    if (has_read_digit) {
        n = std::move(temp); // Affectation par déplacement pour éviter les copies inutiles
    }

    return in;
}

// Opérateur += pour ajouter un entier au Number courant
Number& Number::operator+=(unsigned int i) {
    this->add(i);
    return *this;
}

// Opérateur *= pour multiplier le Number courant par un entier
Number& Number::operator*=(unsigned int i) {
    this->multiply(i);
    return *this;
}

// Opérateur + pour additionner un Number et un unsigned int
Number operator+(const Number& n, unsigned int i) {
    Number result = n;   // Copie de l'objet existant
    result += i;         // Utilise l'opérateur +=
    return result;       // Renvoie le résultat
}

// Opérateur * pour multiplier un Number et un unsigned int
Number operator*(const Number& n, unsigned int i) {
    Number result = n;   // Copie de l'objet existant
    result *= i;         // Utilise l'opérateur *=
    return result;       // Renvoie le résultat
}
