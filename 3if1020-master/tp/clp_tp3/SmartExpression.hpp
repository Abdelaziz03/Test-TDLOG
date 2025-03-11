/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * SmartExpression.hpp
 */

#ifndef SMART_EXPRESSION_HPP_INCLUDED
#define SMART_EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <memory>

// Classe de base abstraite SmartExpression
class SmartExpression : public std::enable_shared_from_this<SmartExpression> {
public:
    SmartExpression();
    virtual ~SmartExpression();

    virtual std::string to_string() const = 0;
    virtual std::shared_ptr<const SmartExpression> derive(const std::string& variable) const = 0;
    virtual std::shared_ptr<const SmartExpression> simplifie() const = 0;

    static int get_instances_creees() { return instances_creees_; }
    static int get_instances_detruites() { return instances_detruites_; }

protected:
    static int instances_creees_;
    static int instances_detruites_;
};


// Classe Nombre
class Nombre : public SmartExpression {
public:
    explicit Nombre(float valeur);

    std::string to_string() const override;
    std::shared_ptr<const SmartExpression> derive(const std::string& variable) const override;
    std::shared_ptr<const SmartExpression> simplifie() const override;

    float get_valeur() const { return valeur_; }

private:
    float valeur_;
};

// Classe Variable
class Variable : public SmartExpression {
public:
    explicit Variable(const std::string& nom);

    std::string to_string() const override;
    std::shared_ptr<const SmartExpression> derive(const std::string& variable) const override;
    std::shared_ptr<const SmartExpression> simplifie() const override;

private:
    std::string nom_;
};

// Classe abstraite Operation
class Operation : public SmartExpression {
public:
    Operation(std::shared_ptr<const SmartExpression> op1, std::shared_ptr<const SmartExpression> op2);

protected:
    std::shared_ptr<const SmartExpression> op1_;
    std::shared_ptr<const SmartExpression> op2_;
};

// Classe Addition
class Addition : public Operation {
public:
    Addition(std::shared_ptr<const SmartExpression> op1, std::shared_ptr<const SmartExpression> op2);

    std::string to_string() const override;
    std::shared_ptr<const SmartExpression> derive(const std::string& variable) const override;
    std::shared_ptr<const SmartExpression> simplifie() const override;
};

// Classe Multiplication
class Multiplication : public Operation {
public:
    Multiplication(std::shared_ptr<const SmartExpression> op1, std::shared_ptr<const SmartExpression> op2);

    std::string to_string() const override;
    std::shared_ptr<const SmartExpression> derive(const std::string& variable) const override;
    std::shared_ptr<const SmartExpression> simplifie() const override;
};

#endif


/* Pourquoi doit-on continuer à créer des instances dans Nombre::simplifie() et Variable::simplifie() ?

La création d'instances dans Nombre::simplifie() et Variable::simplifie() est essentielle pour garantir que chaque appel renvoie un objet distinct, même si l'expression est déjà simplifiée. 
Cela permet d'éviter toute modification accidentelle de l'état partagé dans des contextes où l'expression pourrait être manipulée ou modifiée.
Cette approche est particulièrement importante en l'absence de mécanismes comme `shared_from_this`, car elle respecte le principe d'immuabilité implicite : un objet simplifié ne doit pas être altéré. 
Cela contribue à une gestion plus sûre et prévisible des objets dans le programme.
*/