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

// Tests add
TEST( TestNumber, TestNumberAdd0 )
{
    Number n{0};
    n.add(7654);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "7654");
}

TEST( TestNumber, TestNumberAdd7654 )
{
    Number n{ 7654 };
    n.add(500);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "8154");
}

TEST( TestNumber, TestNumberAddBig76543210987 )
{
    Number n{ 76543210987 };
    n.add(3);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "76543210990");
}

// Tests multiply
TEST( TestNumber, TestNumberMultiply0 )
{
    Number n{0};
    n.multiply(150);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "0");
}

TEST( TestNumber, TestNumberMultiply7654 )
{
    Number n{7654};
    n.multiply(2);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "15308");

}

TEST( TestNumber, TestNumberMultiplyBig76543210987 )
{
    Number n{76543210987};
    n.multiply(12);
    std::ostringstream os;
    os << n;
    EXPECT_EQ(os.str(), "918518531844");
}

// Tests factorial
TEST( TestNumber, TestFactorial123 )
{
    std::ostringstream os;
    os << factorial( 123 );;
    EXPECT_EQ( os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                         "358923621676688311569606126402021707358352212940477825910915704116514"
                         "72186029519906261646730733907419814952960000000000000000000000000000" );
}

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
