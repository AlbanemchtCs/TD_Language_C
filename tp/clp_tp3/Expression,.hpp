/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <memory>

class Expression {
public:
    Expression() {}
    virtual ~Expression() {}

private:
};


class Nombre : public Expression {
public:
    Nombre(float value) : value_(value) {}
    ~Nombre() {}

private:
    const float value_;
};


class Variable : public Expression {
public:
    Variable(std::string name) : name_(name) {}
    ~Variable() {} 

private:
    const std::string name_;
};

#endif
