/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression,.hpp"

// Test Number
TEST(TestExpression, TestNumber1) {
    Nombre nbr{1};
    std::ostringstream os;
    os << nbr;
    EXPECT_EQ(os.str(), "1");
}

TEST(TestExpression, TestNumber2) {
    Nombre nbr{2};
    std::ostringstream os;
    os << nbr;
    EXPECT_EQ(os.str(), "2");
}

// Test Variable
TEST(TestExpression, TestVariable1) {
    Variable var{"Var1"};
    std::ostringstream os;
    os << var;
    EXPECT_EQ(os.str(), "Var1");
}

TEST(TestExpression, TestVariable2) {
    Variable var{"Var2"};
    std::ostringstream os;
    os << var;
    EXPECT_EQ(os.str(), "Var2");
}

// Test Derivation
TEST(TestExpression, TestDerive1) {
    Expression* exp = new Nombre{1};
    std::ostringstream os;
    Expression* derive = exp->derive("Var_name1");
    os << *derive;
    EXPECT_EQ(os.str(), "0");
}

TEST(TestExpression, TestDerive2) {
    Expression* exp = new Variable{"Var_name2"};
    std::ostringstream os;
    Expression* derive = exp->derive("Var_name2");
    os << *derive;
    EXPECT_EQ(os.str(), "1");
}

TEST(TestExpression, TestDerive3) {
    Expression* exp = new Variable{"Var_name3"};
    std::ostringstream os;
    Expression* derive = exp->derive("var3");
    os << *derive;
    EXPECT_EQ(os.str(), "0");
}

// Main
int main( int argc, char * argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
