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

class Number{
public:
    Number( unsigned long l ) { first_ = new Digit(l); }
    ~Number() { delete first_; }

    void print( std::ostream & out ) const { first_->print( out ); }

private:
    using DigitType = unsigned int;
    // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
    static const DigitType number_base{ 10u };
    struct Digit {
        DigitType digit_;
        Digit * next_;

        // Number constructor
        Digit(unsigned long l) {
            if (l >= number_base) {
                digit_ = l % number_base;
                next_ = new Digit(l/number_base);
            } else {
                digit_ = l;
                next_ = nullptr;
            }
        }

        // Number destructor
        ~Digit() {
            if (next_ != nullptr) {
                delete next_;
            }
        }

        void print(std::ostream & out ) {
            if (next_ != nullptr) {
                next_->print(out);
            }
            out << digit_;
        }
    };
    Digit * first_;
};

inline std::ostream & operator<<( std::ostream & out, const Number & n ) {
    n.print( out );
    return out;
}

#endif

