/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Number.hpp"

 
TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

// Tests constructor by copy
TEST( TestNumber, TestNumberConstructorCopy0 )
{
    Number n{ 0 };
    Number n_const(n);
    std::ostringstream os;
    os << n_const;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberConstructorCopy23456789 )
{
    Number n{ 23456789 };
    Number n_const(n);
    std::ostringstream os;
    os << n_const;
    EXPECT_EQ(os.str(), "23456789");
}

TEST( TestNumber, TestNumberConstructorCopyBig )
{
    Number n{ 2345623456234 };
    Number n_const(n);
    std::ostringstream os;
    os << n_const;
    EXPECT_EQ( os.str(), "2345623456234" );
}

// Tests affectation by copy
TEST( TestNumber, TestNumberAffectationCopy0 )
{
    Number n{ 0 };
    Number n_affected(n);
    std::ostringstream os;
    os << n_affected;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberAffectationCopy23456789 )
{
    Number n{ 23456789 };
    Number n_affected(n);
    std::ostringstream os;
    os << n_affected;
    EXPECT_EQ(os.str(), "23456789");

}

TEST( TestNumber, TestNumberAffectationCopyBig )
{
    Number n{ 2345623456234 };
    Number n_affected(n);
    std::ostringstream os;
    os << n_affected;
    EXPECT_EQ( os.str(), "2345623456234" );
}


int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
