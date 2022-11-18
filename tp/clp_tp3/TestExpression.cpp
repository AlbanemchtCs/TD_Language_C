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
    Expression* derivation = exp->derive("Var_name1");
    os << *derivation;
    EXPECT_EQ(os.str(), "0");
    delete exp;
    delete derivation;
}

TEST(TestExpression, TestDerive2) {
    Expression* exp = new Variable{"Var_name2"};
    std::ostringstream os;
    Expression* derivation = exp->derive("Var_name2");
    os << *derivation;
    EXPECT_EQ(os.str(), "1");
    delete exp;
    delete derivation;
}

TEST(TestExpression, TestDerive3) {
    Expression* exp = new Variable{"Var_name3"};
    std::ostringstream os;
    Expression* derivation = exp->derive("var3");
    os << *derivation;
    EXPECT_EQ(os.str(), "0");
    delete exp;
    delete derivation;
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
    Addition* add = new Addition{l, r};
    os << *add;
    EXPECT_EQ(os.str(), "4 + 6");
}

TEST(TestExpression, TestAddition2) {
    std::ostringstream os;
    Expression* l = new Variable{"4"};
    Expression* r = new Variable{"r"};
    Addition* add = new Addition{l, r};
    os << *add;
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

// Test cloning
TEST(TestExpression, TestCloningNombre) {
    std::ostringstream os;
    Nombre *nbr = new Nombre(5);
    Nombre *clone = nbr->clone();
    delete nbr;
    os << *clone;
    EXPECT_EQ(os.str(), "5");
}

TEST(TestExpression, TestCloningVariable) {
    std::ostringstream os;
    Variable *var = new Variable("a");
    Variable *clone = var->clone();
    delete var;
    os << *clone;
    EXPECT_EQ(os.str(), "a");
}

TEST(TestExpression, TestCloningAddition) {
    std::ostringstream os;
    Variable *var = new Variable("a");
    Nombre *nbr = new Nombre(5);
    Addition *add = new Addition{ var, nbr };
    Addition *clone = add->clone();
    delete add;
    os << *clone;
    EXPECT_EQ(os.str(), "a + 5");
}

TEST( TestExpressionClonage, TestClonageMultiplication ) {
    std::ostringstream os;
    Variable *var = new Variable("a");
    Nombre *nbr = new Nombre(5);
    Multiplication *mult = new Multiplication{ var, nbr };
    Multiplication *clone = mult->clone();
    delete mult;
    os << *clone;
    EXPECT_EQ(os.str(), "a * 5");
}

// Class Multiplication
TEST(TestExpression, TestMultiplication1) {
    std::ostringstream os;
    Expression* l = new Variable{"a"};
    Expression* r = new Nombre{5};
    Multiplication* mult = new Multiplication{l, r};
    os << *mult;
    EXPECT_EQ(os.str(), "a * 5");
}

TEST(TestExpression, TestMultiplication2) {
    std::ostringstream os;
    Expression* l = new Variable{"a"};
    Expression* r = new Variable{"b"};
    Multiplication* mult = new Multiplication{l, r};
    os << *mult;
    EXPECT_EQ(os.str(), "a * b");
}

TEST(TestExpression, TestMultiplicationDerivation1) {
    std::ostringstream os;
    Expression* l = new Variable{"a"};
    Expression* r = new Nombre{5};
    Expression* derivation = new Multiplication{l, r};
    os << *derivation->derive("a");
    EXPECT_EQ(os.str(), "1 * 5 + a * 0");
}

TEST(TestExpression, TestMultiplicationDerivation2) {
    std::ostringstream os;
    Expression* l = new Variable{"a"};
    Expression* r = new Variable{"b"};
    Expression* derivation = new Multiplication{l, r};
    os << *derivation->derive("a");
    EXPECT_EQ(os.str(), "1 * b + a * 0");
}

// Main
int main( int argc, char * argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
