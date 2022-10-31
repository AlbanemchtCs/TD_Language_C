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
#include <math.h>

class Number{
public:
    // Constructor
    Number( unsigned long l ) { first_ = new Digit(l); }

    // Destructor
    ~Number() { delete first_; }

    // Constructor by copy
    Number(const Number& n) { first_ = new Digit(*n.first_); }

    // Affectation by copy
    Number& operator=(const Number& n) { first_ = new Digit(*n.first_); return (*this); }

    // Print
    void print( std::ostream & out ) const { first_->print( out ); }

    // Add
    void add(unsigned int i) { first_->add(i); }

    // Multiply
    void multiply(unsigned int i) { first_->multiply(i); }


private:
    using DigitType = unsigned int;
    // Un seul chiffre décimal par maillon : l'objectif ici n'est pas la performance
    static const DigitType number_base{ 10u };
    struct Digit {
        DigitType digit_;
        Digit * next_;

        // Number constructor
        Digit( unsigned long l ) {
            if ( l >= number_base ) {
                digit_ = l % number_base;
                next_ = new Digit( l/number_base );
            } else {
                digit_ = l;
                next_ = nullptr;
            }
        }

        // Number destructor
        ~Digit() {
            if ( next_ != nullptr ) {
                delete next_;
            }
        }

        // Constructor by copy
        Digit( const Digit & d ) {
            digit_ = d.digit_;
            if ( d.next_ != nullptr ) {
                next_ = new Digit( *d.next_ );
            } else {
                next_ = nullptr;
            }
        }

        // Affectation by copy
        Digit& operator=( const Digit& d ) {
            if ( d.next_ == nullptr ) {
                digit_ = d.digit_;
                next_ = nullptr;
            } else {
                digit_ = d.digit_;
                next_ = new Digit( *d.next_ );
            }
            return (*this);
        }

        void print( std::ostream & out ) {
            if ( next_ != nullptr ) {
                next_->print( out );
            }
            out << digit_;
        }

        // Add
        void add( unsigned int i ) {
            DigitType result = static_cast<unsigned long>( digit_ + i ) / number_base;
            digit_ = static_cast<unsigned long>( digit_ + i ) % number_base;
            if ( next_ != nullptr ) {
                next_->add( result );
            }
            else if ( result != 0 ) {
                next_ = new Digit( result );
            }
        }

        // Multiply
        void multiply( unsigned int i ) {
            unsigned long l = digit_ * i;
            DigitType result = l / number_base;
            digit_ = l % number_base;
            if ( next_ != nullptr ) {
                next_->multiply( i );
                next_->add( result );
            }
            else if ( result != 0 ) {
                next_ = new Digit( result );
            }
        }

    };
    Digit * first_;
};

Number factorial(unsigned int i) {
    if ( i <= 1 ) return Number{1};
    Number n{i};
    while (--i > 0) n.multiply(i);
    return n;
}

inline std::ostream & operator<<( std::ostream & out, const Number & n ) {
    n.print( out );
    return out;
}

#endif

