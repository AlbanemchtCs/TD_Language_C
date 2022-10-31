/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Number.hpp"

// Factorial
Number factorial( unsigned int i ){
    Number n { 1 };
    while ( i > 0 ) {
        n.multiply ( i );
        i -= 1;
    }
    return n;
};

// Function for in
std::istream &operator>> ( std::istream &in, Number &n ) {
    std::string string { "" };
    in >> std::ws;
    while ( in.good () ) {
        int c{ in.get () };
        if ( std::isdigit ( c ) ) {
            string += c;
        }
        else {
            in.putback ( c );
            break;
        }
    }
    n = Number { string };
    return in;
}


