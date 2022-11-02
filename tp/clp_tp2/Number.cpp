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
    Number number { 1 };
    while ( i > 0 ) {
        number.multiply ( i );
        i -= 1;
    }
    return number;
};

// Function for in
std::istream &operator>> ( std::istream &in, Number &n ) {
    std::string string { "" };
    in >> std::ws;
    while ( in.good () ) {
        int c { in.get () };
        if ( std::isdigit ( c ) ) {
            unsigned int d { static_cast <unsigned int> (c - '0') };
            string = string + std::to_string(d);
        }
        else {
            in.putback ( c );
            break;
        }
    }
    n = Number { string };
    return in;
}
