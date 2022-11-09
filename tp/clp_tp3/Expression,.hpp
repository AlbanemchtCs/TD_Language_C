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

// Class Expression
class Expression {
public:
    Expression() {};
    virtual ~Expression() {}

    /* Corresponding display method: 
            - virtual & constant methods: the virtual method enables to redefine it in the two subclasses (Nombre and Variable) and the constant method enables to not change the object
            - argument: output stream 
            - return value: print
            - behaviour: returns the description of the expression after adding it to the output stream
    */
    virtual std::ostream & print(std::ostream& out) const = 0;

    /* Specification of the derivation operation:
            - argument: var_name, the name of the variable that we derive
            - return type: a pointer to the new expression which is the derivative of the initial expression, enabling to not modify the initial expression
    */
    virtual Expression *derive(std::string var_name) const = 0;

private:
};

inline std::ostream & operator<<( std::ostream & out, const Expression & expression ) {
    expression.print( out );
    return out;
}

// Class Nombre
class Nombre : public Expression {
public:
    Nombre(float value) : value_(value) {}
    ~Nombre() {}

    virtual std::ostream & print(std::ostream & out) const override{
        return out << value_;
    }

    /* Derivation for Number:
            - we choose to return an expression and not a number because otherwise it could return an operation. No constructor exists for an expression, so we cannot return an expression
            - in order to run an expression, we generate a new number in a new pointer. This enables to create a number & an expression and to not modify the initial number that has been derived
    */
    Expression *derive(std::string var_name) const override {
        return (new Nombre(0));
    }

private:
    const float value_;
};

// Class Variable
class Variable : public Expression {
public:
    Variable(std::string name) : name_(name) {}
    ~Variable() {} 

    virtual std::ostream & print(std::ostream & out) const override{
        return out << name_;
    }

    /* Derivation for Variable:
            - we choose to return an expression and not a variable because otherwise it could return an operation. No constructor exists for an expression, so we cannot return an expression
            - in order to run an expression, we generate a new number in a new pointer. This enables to create a number & an expression and to not modify the initial variable that has been derived
    */
    Expression *derive(std::string var_name) const override {
        if (var_name == name_) {
            return (new Nombre(1));
        } else {
            return (new Nombre(0));
        }
    }

private:
    const std::string name_;
};

#endif
