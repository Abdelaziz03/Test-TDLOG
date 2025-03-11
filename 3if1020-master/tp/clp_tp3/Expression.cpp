/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.cpp
 */

#include <iostream>
#include <string>
#include <utility>

#include "Expression.hpp"

//1
/*
La super-classe Operation joue un rôle clé en offrant un cadre commun pour toutes les opérations arithmétiques, 
comme l'addition ou la multiplication. Elle permet de regrouper et de partager les comportements fondamentaux, 
notamment la gestion des opérandes.

Cette approche respecte le principe de substitution de Liskov (L de SOLID), garantissant que les sous-classes 
peuvent remplacer la super-classe sans modifier le comportement attendu du programme. Elle offre une base robuste 
sur laquelle construire différentes opérations.

Parmi les fonctionnalités communes intégrées à Operation, on trouve :
- La gestion des opérandes via les attributs `op1` et `op2`.
- Une méthode `to_string()` pour générer une représentation textuelle standard.
- Une méthode `derive()` pour calculer la dérivée de l'opération.
- Une méthode `clone()` pour permettre une duplication dynamique des objets.

Grâce à ce design, il est possible d'ajouter de nouvelles opérations, telles que la soustraction ou la division, 
sans toucher au code existant. L'héritage de la super-classe garantit que ces nouvelles opérations bénéficieront 
des fonctionnalités communes tout en permettant une personnalisation spécifique.
*/


//2
/*
Question : Constatez qu'une erreur de compilation est produite.

 * Une erreur de compilation est produite, comme le montre le message suivant :
 
/usr/bin/ld: /tmp/ccaqpc2o.o: in function `ExpressionTest_NombreAffichage_Test::TestBody()':
TestExpression.cpp:(.text+0x1dc): undefined reference to `Nombre::Nombre(float)'
/usr/bin/ld: TestExpression.cpp:(.text+0x22c): undefined reference to `Nombre::~Nombre()'
/usr/bin/ld: TestExpression.cpp:(.text+0x269): undefined reference to `Nombre::~Nombre()'
/usr/bin/ld: /tmp/ccaqpc2o.o: in function `ExpressionTest_VariableAffichage_Test::TestBody()':
TestExpression.cpp:(.text+0x2f1): undefined reference to `Variable::Variable(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
/usr/bin/ld: TestExpression.cpp:(.text+0x34e): undefined reference to `Variable::~Variable()'
/usr/bin/ld: TestExpression.cpp:(.text+0x3cb): undefined reference to `Variable::~Variable()'
collect2: error: ld returned 1 exit status


 * Ces erreurs indiquent que les constructeurs et destructeurs des classes Nombre et Variable sont déclarés dans Expression.hpp 
 * mais pas encore définis dans Expression.cpp. Le linker ne parvient donc pas à trouver leur implémentation, ce qui entraîne les erreurs "undefined reference".
 * 
 * Pour corriger ce problème, il est nécessaire de fournir une définition complète des méthodes de ces classes dans le fichier Expression.cpp.
 */



//3
/*
Question :Quelle est la bonne approche à retenir ici ?
La meilleure approche est de créer une nouvelle instance représentant la dérivée de l'objet courant,
au lieu de modifier l'instance existante. Cela respecte les principes d'immuabilité et de bonne conception
en programmation orientée objet. En procédant ainsi, l'instance courante reste inchangée, ce qui prévient les
effets de bord indésirables et permet une utilisation plus sûre et flexible des objets.
 */


// Implémentation de la surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    os << expr.to_string();
    return os;
}

// Nombre
Nombre::Nombre(float valeur) : valeur_(valeur) {}
Nombre::Nombre(const Nombre& other) : valeur_(other.valeur_) {}
Nombre& Nombre::operator=(const Nombre& other) {
    if (this != &other) {
        valeur_ = other.valeur_;
    }
    return *this;
}
Nombre::~Nombre() {}

std::string Nombre::to_string() const {
    std::ostringstream oss;
    oss << std::scientific << valeur_; // Applique std::scientific pour le format scientifique
    return oss.str();
}

Expression* Nombre::clone() const {
    return new Nombre(*this);
}

// Variable
Variable::Variable(const std::string& nom) : nom_(nom) {}
Variable::Variable(const Variable& other) : nom_(other.nom_) {}
Variable& Variable::operator=(const Variable& other) {
    if (this != &other) {
        nom_ = other.nom_;
    }
    return *this;
}
Variable::~Variable() {}

std::string Variable::to_string() const {
    return nom_;
}

Expression* Variable::clone() const {
    return new Variable(*this);
}

Expression* Nombre::derive(const std::string& variable) const {
    return new Nombre(0.0f); // Retourne une nouvelle instance de Nombre avec la valeur 0
}

Expression* Variable::derive(const std::string& variable) const {
    if (nom_ == variable) {
        return new Nombre(1.0f); // Retourne une nouvelle instance de Nombre avec la valeur 1
    }
    return new Nombre(0.0f); // Retourne une nouvelle instance de Nombre avec la valeur 0
}

// Constructeur de Operation
Operation::Operation(Expression* op1, Expression* op2) : op1_(op1), op2_(op2) {}

// Constructeur par copie
Operation::Operation(const Operation& other) : 
    op1_(other.op1_->clone()), op2_(other.op2_->clone()) {}

// Opérateur d’affectation
Operation& Operation::operator=(const Operation& other) {
    if (this != &other) {
        delete op1_;
        delete op2_;
        op1_ = other.op1_->clone();
        op2_ = other.op2_->clone();
    }
    return *this;
}

// Destructeur
Operation::~Operation() {
    delete op1_;
    delete op2_;
}

// Addition
std::string Addition::to_string() const {
    return "(" + op1_->to_string() + " + " + op2_->to_string() + ")";
}

Expression* Addition::clone() const {
    return new Addition(op1_->clone(), op2_->clone());
}

Expression* Addition::derive(const std::string& variable) const {
    return new Addition(op1_->derive(variable), op2_->derive(variable));
}

// Multiplication
std::string Multiplication::to_string() const {
    return "(" + op1_->to_string() + " * " + op2_->to_string() + ")";
}

Expression* Multiplication::clone() const {
    return new Multiplication(op1_->clone(), op2_->clone());
}

Expression* Multiplication::derive(const std::string& variable) const {
    // Dérivée de (u * v) = u' * v + u * v'
    return new Addition(
        new Multiplication(op1_->derive(variable), op2_->clone()),
        new Multiplication(op1_->clone(), op2_->derive(variable))
    );
}
Expression* Nombre::simplifie() const {
    // Un nombre est déjà simplifié
    return new Nombre(*this); // On retourne une copie du nombre courant
}

Expression* Variable::simplifie() const {
    // Une variable est déjà simplifiée
    return new Variable(*this); // On retourne une copie de la variable courante
}

Expression* Addition::simplifie() const {
    // Simplifie les opérandes
    Expression* op1_simplifie = op1_->simplifie();
    Expression* op2_simplifie = op2_->simplifie();

    // Tente de caster les opérandes simplifiés en Nombre
    Nombre* nombre1 = dynamic_cast<Nombre*>(op1_simplifie);
    Nombre* nombre2 = dynamic_cast<Nombre*>(op2_simplifie);

    if (nombre1 && nombre2) {
        // Les deux opérandes sont des Nombres, on peut les additionner
        float valeur = nombre1->get_valeur() + nombre2->get_valeur();
        delete op1_simplifie;
        delete op2_simplifie;
        return new Nombre(valeur);
    } else if (nombre1 && nombre1->get_valeur() == 0.0f) {
        // op1 est 0, on retourne op2_simplifie
        delete op1_simplifie;
        return op2_simplifie;
    } else if (nombre2 && nombre2->get_valeur() == 0.0f) {
        // op2 est 0, on retourne op1_simplifie
        delete op2_simplifie;
        return op1_simplifie;
    } else {
        // Sinon, on retourne une nouvelle Addition simplifiée
        return new Addition(op1_simplifie, op2_simplifie);
    }
}

Expression* Multiplication::simplifie() const {
    // Simplifie les opérandes
    Expression* op1_simplifie = op1_->simplifie();
    Expression* op2_simplifie = op2_->simplifie();

    // Tente de caster les opérandes simplifiés en Nombre
    Nombre* nombre1 = dynamic_cast<Nombre*>(op1_simplifie);
    Nombre* nombre2 = dynamic_cast<Nombre*>(op2_simplifie);

    if (nombre1 && nombre2) {
        // Les deux opérandes sont des Nombres, on peut les multiplier
        float valeur = nombre1->get_valeur() * nombre2->get_valeur();
        delete op1_simplifie;
        delete op2_simplifie;
        return new Nombre(valeur);
    } else if ((nombre1 && nombre1->get_valeur() == 0.0f) || (nombre2 && nombre2->get_valeur() == 0.0f)) {
        // Si l'un des opérandes est 0, le résultat est 0
        delete op1_simplifie;
        delete op2_simplifie;
        return new Nombre(0.0f);
    } else if (nombre1 && nombre1->get_valeur() == 1.0f) {
        // op1 est 1, on retourne op2_simplifie
        delete op1_simplifie;
        return op2_simplifie;
    } else if (nombre2 && nombre2->get_valeur() == 1.0f) {
        // op2 est 1, on retourne op1_simplifie
        delete op2_simplifie;
        return op1_simplifie;
    } else {
        // Sinon, on retourne une nouvelle Multiplication simplifiée
        return new Multiplication(op1_simplifie, op2_simplifie);
    }
}

