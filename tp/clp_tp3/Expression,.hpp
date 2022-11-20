/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <memory>

// Class Expression
class Expression {
public:
    Expression() { count++; };
    virtual ~Expression() { count--; };
    static int count;

    /* Corresponding display method:
            - virtual & constant methods: the virtual method enables to redefine it in the two subclasses (Nombre and Variable) and the constant method enables to not change the object
            - argument: output stream
            - return value: print
            - behaviour: returns the description of the expression after adding it to the output stream
    */
    virtual std::ostream &print(std::ostream &out) const = 0;

    /* Specification of the derivation operation:
            - argument: var_name, the name of the variable that we derive
            - return type: a pointer to the new expression which is the derivative of the initial expression, enabling to not modify the initial expression
    */
    virtual std::shared_ptr<Expression> derive(std::string var_name) const = 0;

    /*
    // Cloning
    virtual Expression *clone() const = 0;
    */

    // Simplification
    virtual std::shared_ptr<Expression> simplification() const = 0;

private:
};

inline std::ostream &operator<<(std::ostream &out, const Expression &expression) {
    expression.print(out);
    return out;
}

// Class Nombre
class Nombre : public Expression {
public:
    Nombre(float value) : value_(value) {}
    ~Nombre() {}

    virtual std::ostream &print(std::ostream &out) const override {
        return out << value_;
    }

    /* Derivation for Number:
            - we choose to return an expression and not a number because otherwise it could return an operation. No constructor exists for an expression, so we cannot return an expression
            - in order to run an expression, we generate a new number in a new pointer. This enables to create a number & an expression and to not modify the initial number that has been derived
    */
    std::shared_ptr<Expression> derive(std::string var_name) const override { return std::shared_ptr<Nombre>(new Nombre(0)); }

    /*
    // Cloning
    Nombre *clone() const override { return new Nombre{value_}; };
    */

    // Simplification
    std::shared_ptr<Expression> simplification() const override {
        return std::shared_ptr<Nombre>(new Nombre(value_));
    };
    float value() const {return value_;}

private:
    const float value_;
};

// Class Variable
class Variable : public Expression
{
public:
    Variable(std::string name) : name_(name) {}
    ~Variable() {}

    virtual std::ostream &print(std::ostream &out) const override {
        return out << name_;
    }

    /* Derivation for Variable:
            - we choose to return an expression and not a variable because otherwise it could return an operation. No constructor exists for an expression, so we cannot return an expression
            - in order to run an expression, we generate a new number in a new pointer. This enables to create a number & an expression and to not modify the initial variable that has been derived
    */
    std::shared_ptr<Expression> derive(std::string var_name) const override {
        if (var_name == name_) {
            return std::shared_ptr<Nombre>(new Nombre(1));
        }
        else {
            return std::shared_ptr<Nombre>(new Nombre(0));
        }
    };

    /*
    // Cloning
    Variable *clone() const override { return new Variable{name_}; };
    */

    // Simplification
    std::shared_ptr<Expression> simplification() const override { return std::shared_ptr<Variable>(new Variable(name_)); };

private:
    std::string name_;
};

// Class Operation
/*
Use of operation_left and operation_right attributes to link the operator and its operands.
These will take the form of pointers that will allow to point to Expression objects of different forms.
It must make a copy of the arguments received, in order to be able to use them afterwards.
Addition and Multiplication use Operation as their parent class.
*/
class Operation : public Expression {
public:
    // Constructor
    Operation(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
        operation_left = left;
        operation_right = right;
    }

    // Destructor
    ~Operation() {}

    // Simplification
    virtual std::shared_ptr<Expression> simplification() const override = 0;

    // Operands
protected:
    std::shared_ptr<Expression> operation_left;
    std::shared_ptr<Expression> operation_right;

private:
};

class Addition : public Operation {
public:
    // Constructor
    Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : Operation(left, right) {}

    // Destructor
    ~Addition() {}

    // Simplification
    std::shared_ptr<Expression> simplification() const override {

        std::shared_ptr<Expression> operation_left_simplified = operation_left->simplification();
        std::shared_ptr<Expression> operation_right_simplified = operation_right->simplification();

        std::shared_ptr<Nombre> left_simple = std::dynamic_pointer_cast<Nombre>(operation_left_simplified);
        std::shared_ptr<Nombre> right_simple = std::dynamic_pointer_cast<Nombre>(operation_right_simplified);

        // Return addition of the operands if they are both numbers
        if (left_simple != 0 && right_simple != 0) {
            return std::shared_ptr<Nombre>(new Nombre(left_simple->value() + right_simple->value()));

        } // If one of the operand is O
        else if (left_simple != 0 && left_simple->value() == 0) {
            return operation_right_simplified;
        }
        else if (right_simple != 0 && right_simple->value() == 0) {
            return operation_left_simplified;
        }
        // Return new addition with the simplified operands
        return std::shared_ptr<Addition>(new Addition(operation_left_simplified, operation_right_simplified));
    }

    // Display
    std::ostream &print(std::ostream &out) const override {
        operation_left->print(out);
        out << " + ";
        operation_right->print(out);
        return out;
    }

    // Derivation with elimination of the creations of the numbers 0 and 1 
    std::shared_ptr<Expression> derive(std::string var_name) const override { 
        std::shared_ptr<Expression> der_left = operation_left->derive(var_name);
        std::shared_ptr<Expression> der_right= operation_right->derive(var_name);

        std::shared_ptr<Nombre> der_left_nbr = std::dynamic_pointer_cast<Nombre>(der_left);
        std::shared_ptr<Nombre> der_right_nbr = std::dynamic_pointer_cast<Nombre>(der_right);

        if (der_left_nbr->value() == 0) {
            return der_right;
        } else if (der_right_nbr->value() == 0) {
            return der_left;
        }
        return std::shared_ptr<Addition>(new Addition(der_left, der_right));
    }

    /*
    // Cloning
    Addition *clone() const override { return new Addition(operation_left->clone(), operation_right->clone()); }
    */

private:
};

// Class Multiplication
class Multiplication : public Operation {
public:
    // Constructor
    Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) : Operation(left, right) {}
    
    // Destructor
    ~Multiplication() {}

    // Simplification
    std::shared_ptr<Expression> simplification() const override {

        std::shared_ptr<Expression> operation_left_simplified = operation_left->simplification();
        std::shared_ptr<Expression> operation_right_simplified = operation_right->simplification();

        std::shared_ptr<Nombre> left_simple = std::dynamic_pointer_cast<Nombre>(operation_left_simplified);
        std::shared_ptr<Nombre> right_simple = std::dynamic_pointer_cast<Nombre>(operation_right_simplified);


        // Return multiplication of the operands if they are both numbers
        if (left_simple != 0 && right_simple != 0) {
            return std::shared_ptr<Nombre>(new Nombre(left_simple->value() *right_simple->value()));;
        }

        if (left_simple != 0) {
            // If the right operand is 1
            if (left_simple->value() == 1) {
                return operation_right_simplified;
                // If the operand is 0
            }
            else if (left_simple->value() == 0) {
                return std::shared_ptr<Nombre>(new Nombre(0));
            }
        }
        if (right_simple != 0) {
            // If the right operand is 1
            if (right_simple->value() == 1) {
                return operation_left_simplified;
                // If the operand is 0
            }
            else if (right_simple->value() == 0) {
                return std::shared_ptr<Nombre>(new Nombre(0));
            }
        }
        // Return new multiplication with the simplified operands
        return std::shared_ptr<Multiplication>(new Multiplication(operation_left_simplified, operation_right_simplified));
    }

    // Display
    std::ostream &print(std::ostream &out) const override {
        operation_left->print(out);
        out << " * ";
        operation_right->print(out);
        return out;
    }

    // Derivation with elimination of the creations of the numbers 0 and 1 
    std::shared_ptr<Expression> derive(std::string var_name) const override {
        std::shared_ptr<Expression> der_left = operation_left->derive(var_name);
        std::shared_ptr<Expression> der_right = operation_right->derive(var_name);

        std::shared_ptr<Nombre> der_left_nbr = std::dynamic_pointer_cast<Nombre>(der_left);
        std::shared_ptr<Nombre> der_right_nbr = std::dynamic_pointer_cast<Nombre>(der_right);

        std::shared_ptr<Expression> exp_left;
        std::shared_ptr<Expression> exp_right;

        if (der_left_nbr->value() == 1) {
            exp_left = operation_right;
        } else {
            exp_left = std::shared_ptr<Multiplication>(new Multiplication(der_left, operation_right));
        }
        if (der_right_nbr->value() == 1) {
            exp_right = operation_left;
        } else {
            exp_right = std::shared_ptr<Multiplication>(new Multiplication(operation_left, der_right));
        }
        if (der_left_nbr->value() == 0 && der_right_nbr->value() == 0) {
            return std::shared_ptr<Nombre>(new Nombre(0));
        }
        if (der_left_nbr->value() == 0) {
            return exp_right;
        }
        if (der_right_nbr->value() == 0) {
            return exp_left;
        }
        return std::shared_ptr<Addition>(new Addition(exp_left, exp_right));
    }

    /*
    // Cloning
    Multiplication *clone() const override { return new Multiplication(operation_left->clone(), operation_right->clone()); }
    */
    
private:
};

#endif