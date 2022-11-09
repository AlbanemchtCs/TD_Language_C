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
    Expression() {}
    virtual ~Expression() {}

    /* Corresponding display method : 
            - virtual & constant methods: the virtual method enables to redefine it in the two subclasses (Nombre and Variable) and the constant method enables to not change the object
            - argument: output stream 
            - return value: print
            - behaviour: returns the description of the expression after adding it to the output stream
    */
    
    virtual std::ostream & print(std::ostream& out) const = 0;

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

    virtual std::ostream & print(std::ostream & out) const {
        return out << value_;
    }

private:
    const float value_;
};

// Class Variable
class Variable : public Expression {
public:
    Variable(std::string name) : name_(name) {}
    ~Variable() {} 

    virtual std::ostream & print(std::ostream & out) const {
        return out << name_;
    }

private:
    const std::string name_;
};

#endif
