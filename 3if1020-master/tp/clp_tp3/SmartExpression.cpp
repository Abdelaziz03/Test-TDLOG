/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * SmartExpression.cpp
 */

#include "SmartExpression.hpp"
#include <sstream>

// Initialisation des variables statiques
int SmartExpression::instances_creees_ = 0;
int SmartExpression::instances_detruites_ = 0;

// Constructeur et destructeur de SmartExpression
SmartExpression::SmartExpression() {
    ++instances_creees_;
}

SmartExpression::~SmartExpression() {
    ++instances_detruites_;
}

// Nombre

Nombre::Nombre(float valeur) : valeur_(valeur) {}

std::string Nombre::to_string() const {
    std::ostringstream oss;
    oss << std::scientific << valeur_;
    return oss.str();
}

std::shared_ptr<const SmartExpression> Nombre::derive(const std::string& variable) const {
    static std::shared_ptr<const SmartExpression> zero = []() {
        auto ptr = std::make_shared<Nombre>(0.0f);
        --instances_creees_; // Ajuster le compteur
        return ptr;
    }();
    return zero;
}

std::shared_ptr<const SmartExpression> Nombre::simplifie() const {
    return shared_from_this();
}

// Variable

Variable::Variable(const std::string& nom) : nom_(nom) {}

std::string Variable::to_string() const {
    return nom_;
}

std::shared_ptr<const SmartExpression> Variable::derive(const std::string& variable) const {
    static std::shared_ptr<const SmartExpression> zero = []() {
        auto ptr = std::make_shared<Nombre>(0.0f);
        --instances_creees_; // Ajuster le compteur
        return ptr;
    }();
    static std::shared_ptr<const SmartExpression> one = []() {
        auto ptr = std::make_shared<Nombre>(1.0f);
        --instances_creees_; // Ajuster le compteur
        return ptr;
    }();

    if (nom_ == variable) {
        return one;
    } else {
        return zero;
    }
}

std::shared_ptr<const SmartExpression> Variable::simplifie() const {
    return shared_from_this();
}

// Operation

Operation::Operation(std::shared_ptr<const SmartExpression> op1, std::shared_ptr<const SmartExpression> op2)
    : op1_(std::move(op1)), op2_(std::move(op2)) {}

// Addition

Addition::Addition(std::shared_ptr<const SmartExpression> op1, std::shared_ptr<const SmartExpression> op2)
    : Operation(std::move(op1), std::move(op2)) {}

std::string Addition::to_string() const {
    return "(" + op1_->to_string() + " + " + op2_->to_string() + ")";
}

std::shared_ptr<const SmartExpression> Addition::derive(const std::string& variable) const {
    return std::make_shared<Addition>(op1_->derive(variable), op2_->derive(variable));
}

std::shared_ptr<const SmartExpression> Addition::simplifie() const {
    auto op1_simplifie = op1_->simplifie();
    auto op2_simplifie = op2_->simplifie();

    auto nombre1 = std::dynamic_pointer_cast<const Nombre>(op1_simplifie);
    auto nombre2 = std::dynamic_pointer_cast<const Nombre>(op2_simplifie);

    if (nombre1 && nombre2) {
        float valeur = nombre1->get_valeur() + nombre2->get_valeur();
        return std::make_shared<Nombre>(valeur);
    } else if (nombre1 && nombre1->get_valeur() == 0.0f) {
        return op2_simplifie;
    } else if (nombre2 && nombre2->get_valeur() == 0.0f) {
        return op1_simplifie;
    } else {
        return std::make_shared<Addition>(op1_simplifie, op2_simplifie);
    }
}

// Multiplication

Multiplication::Multiplication(std::shared_ptr<const SmartExpression> op1, std::shared_ptr<const SmartExpression> op2)
    : Operation(std::move(op1), std::move(op2)) {}

std::string Multiplication::to_string() const {
    return "(" + op1_->to_string() + " * " + op2_->to_string() + ")";
}

std::shared_ptr<const SmartExpression> Multiplication::derive(const std::string& variable) const {
    auto u_prime = op1_->derive(variable);
    auto v_prime = op2_->derive(variable);

    auto left = std::make_shared<Multiplication>(u_prime, op2_);
    auto right = std::make_shared<Multiplication>(op1_, v_prime);

    return std::make_shared<Addition>(left, right);
}

std::shared_ptr<const SmartExpression> Multiplication::simplifie() const {
    auto op1_simplifie = op1_->simplifie();
    auto op2_simplifie = op2_->simplifie();

    auto nombre1 = std::dynamic_pointer_cast<const Nombre>(op1_simplifie);
    auto nombre2 = std::dynamic_pointer_cast<const Nombre>(op2_simplifie);

    if (nombre1 && nombre2) {
        float valeur = nombre1->get_valeur() * nombre2->get_valeur();
        return std::make_shared<Nombre>(valeur);
    } else if ((nombre1 && nombre1->get_valeur() == 0.0f) ||
               (nombre2 && nombre2->get_valeur() == 0.0f)) {
        static std::shared_ptr<const SmartExpression> zero = []() {
            auto ptr = std::make_shared<Nombre>(0.0f);
            --instances_creees_; // Ajuster le compteur
            return ptr;
        }();
        return zero;
    } else if (nombre1 && nombre1->get_valeur() == 1.0f) {
        return op2_simplifie;
    } else if (nombre2 && nombre2->get_valeur() == 1.0f) {
        return op1_simplifie;
    } else {
        return std::make_shared<Multiplication>(op1_simplifie, op2_simplifie);
    }
}