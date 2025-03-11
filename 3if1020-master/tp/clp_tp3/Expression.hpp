/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

/*
 * Méthode `derive` :
 * - Objectif : Retourner une nouvelle expression représentant la dérivée de l'objet courant
 *   par rapport à une variable donnée.
 * - Argument : 
 *   - `const std::string& variable` : Le nom de la variable par rapport à laquelle
 *     la dérivation doit être effectuée.
 * - Type de retour : 
 *   - `Expression*` : Un pointeur vers une nouvelle instance de type `Expression`
 *     représentant la dérivée. La mémoire est allouée dynamiquement.
 * - Effet sur l'objet récepteur : Aucun. L'instance courante reste inchangée.
 * - Allocation :
 *   - Une nouvelle instance est allouée dynamiquement avec `new`. Il revient à l'appelant
 *     de gérer cette mémoire (par exemple, via `delete` ou en utilisant des pointeurs intelligents).
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>

// Classe abstraite Expression
class Expression {
public:
    virtual ~Expression() { ++instances_detruites_; }
    virtual std::string to_string() const = 0;
    virtual Expression* clone() const = 0;
    virtual Expression* derive(const std::string& variable) const = 0;

    /*
    Méthode `simplifie` :
    - Objectif : Retourner une expression simplifiée de l'objet courant.
    - Arguments : Aucun.
    - Type de retour :
      - `Expression*` : Un pointeur vers une nouvelle instance de type `Expression` représentant l'expression simplifiée.
        La mémoire est allouée dynamiquement.
    - Effet sur l'objet récepteur : Aucun. L'instance courante reste inchangée.
    - Allocation :
      - Une nouvelle instance est allouée dynamiquement avec `new`. Il revient à l'appelant
        de gérer cette mémoire (par exemple, via `delete` ou en utilisant des pointeurs intelligents).
    */
    virtual Expression* simplifie() const = 0;

    static int get_instances_creees() { return instances_creees_; }
    static int get_instances_detruites() { return instances_detruites_; }

protected:
    Expression() { ++instances_creees_; }

private:
    static inline int instances_creees_ = 0;    // Compteur d'instances créées
    static inline int instances_detruites_ = 0; // Compteur d'instances détruites
};

// Déclaration de la surcharge de l'opérateur << pour Expression
std::ostream& operator<<(std::ostream& os, const Expression& expr);

// Classe Nombre
class Nombre : public Expression {
public:
    explicit Nombre(float valeur);
    Nombre(const Nombre& other);
    Nombre& operator=(const Nombre& other);
    ~Nombre();

    std::string to_string() const override;
    Expression* clone() const override;
    Expression* derive(const std::string& variable) const override; // Dérivation
    float get_valeur() const { return valeur_; };
    Expression* simplifie() const override;

private:
    float valeur_;
};

// Classe Variable
class Variable : public Expression {
public:
    explicit Variable(const std::string& nom);
    Variable(const Variable& other);
    Variable& operator=(const Variable& other);
    ~Variable();

    std::string to_string() const override;
    Expression* clone() const override;
    Expression* derive(const std::string& variable) const override; // Dérivation
    Expression* simplifie() const override;

private:
    std::string nom_;
};

/*
Classe Operation : Réponses aux questions

1. Comment représenter les liens entre un opérateur et ses opérandes ?
Les liens sont représentés en utilisant deux pointeurs (op1 et op2) vers des objets de type Expression.
Cela permet de gérer dynamiquement les opérandes, quel que soit leur type concret (e.g., Nombre, Variable, ou une autre opération).

2. Signature du constructeur :
Le constructeur doit recevoir deux pointeurs vers des objets de type Expression, représentant les opérandes.
Signature : Operation(Expression* op1, Expression* op2);

3. Une opération doit-elle s'approprier les arguments reçus ou en faire une copie ?
Une opération doit **prendre possession** des opérandes reçus sans les cloner dans le constructeur. 
Cela signifie que l'opération est responsable de la destruction des opérandes. Cette approche évite les copies 
inutiles et simplifie la gestion de la mémoire.

4. Mode d’allocation mémoire des opérandes :
Les opérandes sont alloués dynamiquement avec new. Cela permet une gestion flexible des types
concrets dérivés d’Expression (e.g., Nombre, Variable). Il est donc crucial de libérer cette mémoire
dans le destructeur pour éviter les fuites.

5. Solution pour le constructeur de copie :
Le constructeur de copie alloue dynamiquement des copies des opérandes en appelant leur méthode clone.
Exemple : 
    Operation(const Operation& other) : op1_(other.op1_->clone()), op2_(other.op2_->clone()) {}

6. Méthode justifiant l’existence de la classe Operation :
La méthode to_string justifie l’existence de cette classe. Elle fournit une représentation textuelle générique
des opérations (e.g., (op1 + op2) ou (op1 * op2)) et peut être spécialisée dans les sous-classes.

7. Choix effectués :
- Les opérandes sont stockés sous forme de pointeurs et copiés dynamiquement.
- La classe est abstraite et définit des méthodes virtuelles pures pour permettre la spécialisation dans les sous-classes.
- Les sous-classes pourront ajouter leur propre logique en surchargeant to_string et derive.
*/


// Classe abstraite Operation (hérite de Expression)
class Operation : public Expression {
public:
    Operation(Expression* op1, Expression* op2); // Constructeur
    Operation(const Operation& other);           // Constructeur par copie
    Operation& operator=(const Operation& other); // Opérateur d’affectation
    ~Operation();                                 // Destructeur

    virtual std::string to_string() const override = 0;  // Méthode virtuelle pure
    virtual Expression* clone() const override = 0;      // Méthode virtuelle pure
    virtual Expression* derive(const std::string& variable) const override = 0; // Méthode virtuelle pure
    virtual Expression* simplifie() const override = 0;
protected:
    Expression* op1_;
    Expression* op2_;
};



// Classe Addition (hérite de Operation)
class Addition : public Operation {
public:
    Addition(Expression* op1, Expression* op2) : Operation(op1, op2) {}

    std::string to_string() const override;

    Expression* clone() const override;

    Expression* derive(const std::string& variable) const override;

    Expression* simplifie() const override;
};

// Classe Multiplication (hérite de Operation)
class Multiplication : public Operation {
public:
    Multiplication(Expression* op1, Expression* op2) : Operation(op1, op2) {}

    std::string to_string() const override;

    Expression* clone() const override;

    Expression* derive(const std::string& variable) const override;

    Expression* simplifie() const override;
};




#endif 