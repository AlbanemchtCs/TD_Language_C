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

int Expression::count = 0;

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
    delete exp;
    delete derive;
}

TEST(TestExpression, TestDerive2) {
    Expression* exp = new Variable{"Var_name2"};
    std::ostringstream os;
    Expression* derive = exp->derive("Var_name2");
    os << *derive;
    EXPECT_EQ(os.str(), "1");
    delete exp;
    delete derive;
}

TEST(TestExpression, TestDerive3) {
    Expression* exp = new Variable{"Var_name3"};
    std::ostringstream os;
    Expression* derive = exp->derive("var3");
    os << *derive;
    EXPECT_EQ(os.str(), "0");
    delete exp;
    delete derive;
}

// Test count instances
TEST(TestExpression, TestCount1) {
    std::ostringstream os;
    Expression* exp = new Variable{"Var_count1"};
    delete exp;
    os << Expression::count;
    EXPECT_EQ(os.str(), "0");
}

TEST(TestExpression, TestCount2) {
    std::ostringstream os;
    Expression* exp = new Variable{"Var_count2"};
    Expression* number = new Nombre{21};
    os << Expression::count;
    EXPECT_EQ(os.str(), "2");
}

// Test class Addition
TEST(TestExpression, TestAddition1) {
    std::ostringstream os;
    Expression* l = new Variable{"4"};
    Expression* r = new Variable{"6"};
    Addition* exp = new Addition{l, r};
    os << *exp;
    EXPECT_EQ(os.str(), "4 + 6");
}

TEST(TestExpression, TestAddition2) {
    std::ostringstream os;
    Expression* l = new Variable{"4"};
    Expression* r = new Variable{"r"};
    Addition* exp = new Addition{l, r};
    os << *exp;
    EXPECT_EQ(os.str(), "4 + r");
}

TEST(TestExpression, TestAdditionDerivation1) {
    std::ostringstream os;
    Expression* l = new Variable{"l"};
    Expression* r = new Nombre{5};
    Expression* derivation = new Addition{l, r};
    os << *derivation->derive("l");
    EXPECT_EQ(os.str(), "1 + 0");
}

TEST(TestExpression, TestAdditionDerivation2) {
    std::ostringstream os;
    Expression* l = new Variable{"l"};
    Expression* r = new Variable{"r"};
    Expression* derivation = new Addition{l, r};
    os << *derivation->derive("l");
    EXPECT_EQ(os.str(), "1 + 0");
}

// Main
int main( int argc, char * argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
