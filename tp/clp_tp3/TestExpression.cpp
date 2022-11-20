/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <utility>
#include <memory>

#include <gtest/gtest.h>

#include "Expression,.hpp"

int Expression::count = 0;

// Test Number
TEST(TestExpression, TestNumber1) {
    std::shared_ptr<Nombre> nbr(new Nombre(1));
    std::ostringstream os;
    os << *nbr;
    EXPECT_EQ(os.str(), "1");
}

TEST(TestExpression, TestNumber2) {
    std::shared_ptr<Nombre> nbr(new Nombre(2));
    std::ostringstream os;
    os << *nbr;
    EXPECT_EQ(os.str(), "2");
}

// Test Variable
TEST(TestExpression, TestVariable1) {
    std::shared_ptr<Variable> var(new Variable("Var1"));
    std::ostringstream os;
    os << *var;
    EXPECT_EQ(os.str(), "Var1");
}

TEST(TestExpression, TestVariable2) {
    std::shared_ptr<Variable> var(new Variable("Var2"));
    std::ostringstream os;
    os << *var;
    EXPECT_EQ(os.str(), "Var2");
}

// Test Derivation
TEST(TestExpression, TestDerive1) {
    std::shared_ptr<Expression> exp(new Nombre(1));
    std::ostringstream os;
    std::shared_ptr<Expression> derivation = exp->derive("Var_name1");
    os << *derivation;
    EXPECT_EQ(os.str(), "0");
}

TEST(TestExpression, TestDerive2) {
    std::shared_ptr<Expression> exp(new Variable("Var_name2"));
    std::ostringstream os;
    std::shared_ptr<Expression> derivation = exp->derive("Var_name2");
    os << *derivation;
    EXPECT_EQ(os.str(), "1");
}

TEST(TestExpression, TestDerive3) {
    std::shared_ptr<Expression> exp(new Variable("Var_name3"));
    std::ostringstream os;
    std::shared_ptr<Expression> derivation = exp->derive("var3");
    os << *derivation;
    EXPECT_EQ(os.str(), "0");
}

// Test count instances
TEST(TestExpression, TestCount1) {
    std::ostringstream os;
    std::shared_ptr<Expression> exp(new Variable("Var_count1"));
    os << Expression::count;
    EXPECT_EQ(os.str(), "1");
}

TEST(TestExpression, TestCount2) {
    std::ostringstream os;
    std::shared_ptr<Expression> exp(new Variable("Var_count2"));
    std::shared_ptr<Expression> number(new Nombre(21));
    os << Expression::count;
    EXPECT_EQ(os.str(), "2");
}

// Test class Addition
TEST(TestExpression, TestAddition1) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("4"));
    std::shared_ptr<Expression> r(new Variable("6"));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( l, r ));
    os << *add;
    EXPECT_EQ(os.str(), "4 + 6");
}

TEST(TestExpression, TestAddition2) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("4"));
    std::shared_ptr<Expression> r(new Variable("r"));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( l, r ));
    os << *add;
    EXPECT_EQ(os.str(), "4 + r");
}

TEST(TestExpression, TestAdditionDerivation1) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("l"));
    std::shared_ptr<Expression> r(new Nombre(5));
    std::shared_ptr<Expression> derivation = std::shared_ptr<Addition>(new Addition( l, r ));
    os << *derivation->derive("l");
    // we delete the 0
    EXPECT_EQ(os.str(), "1");
}

TEST(TestExpression, TestAdditionDerivation2) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("l"));
    std::shared_ptr<Expression> r(new Variable("r"));
    std::shared_ptr<Expression> derivation = std::shared_ptr<Addition>(new Addition( l, r ));
    os << *derivation->derive("l");
    // we delete the 0
    EXPECT_EQ(os.str(), "1");
}

/*
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
*/

// Class Multiplication
TEST(TestExpression, TestMultiplication1) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("a"));
    std::shared_ptr<Expression> r(new Nombre(5));
    std::shared_ptr<Expression> mult = std::shared_ptr<Multiplication>(new Multiplication( l, r ));
    os << *mult;
    EXPECT_EQ(os.str(), "a * 5");
}

TEST(TestExpression, TestMultiplication2) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("a"));
    std::shared_ptr<Expression> r(new Variable("b"));
    std::shared_ptr<Expression> mult = std::shared_ptr<Multiplication>(new Multiplication( l, r ));
    os << *mult;
    EXPECT_EQ(os.str(), "a * b");
}

TEST(TestExpression, TestMultiplicationDerivation1) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("a"));
    std::shared_ptr<Expression> r(new Nombre(5));
    std::shared_ptr<Expression> derivation = std::shared_ptr<Multiplication>(new Multiplication( l, r ));
    os << *derivation->derive("a");
    // we delete the 1 and 0
    EXPECT_EQ(os.str(), "5");
}

TEST(TestExpression, TestMultiplicationDerivation2) {
    std::ostringstream os;
    std::shared_ptr<Expression> l(new Variable("a"));
    std::shared_ptr<Expression> r(new Variable("b"));
    std::shared_ptr<Expression> derivation = std::shared_ptr<Multiplication>(new Multiplication( l, r ));
    os << *derivation->derive("a");
    // we delete the 1 and 0
    EXPECT_EQ(os.str(), "b");
}

// Test simplification
TEST(TestExpression, TestSimplificationAddition1) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(0));
    std::shared_ptr<Variable> a(new Variable("a"));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( nbr, a ));
    std::shared_ptr<Expression> add_simplified = add->simplification();
    os << *add_simplified;
    EXPECT_EQ( os.str(), "a" );
}

TEST(TestExpression, TestSimplificationAddition2) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(5));
    std::shared_ptr<Variable> a(new Variable("a"));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( nbr, a ));
    std::shared_ptr<Expression> add_simplified = add->simplification();
    os << *add_simplified;
    EXPECT_EQ( os.str(), "5 + a" );
}

TEST( TestExpression, TestSimplificationAddition3){
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(1));
    std::shared_ptr<Nombre> nbr_bis(new Nombre(0));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( nbr, nbr_bis ));
    std::shared_ptr<Expression> add_simplified = add->simplification();
    os << *add_simplified;
    EXPECT_EQ( os.str(), "1" );
}

TEST( TestExpressionSimplification, TestSimplificationAddition4) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(5));
    std::shared_ptr<Nombre> nbr_bis(new Nombre(2));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( nbr, nbr_bis ));
    std::shared_ptr<Expression> add_simplified = add->simplification();
    os << *add_simplified;
    EXPECT_EQ( os.str(), "7" );
}

TEST(TestExpression, TestSimplificationMultiplication1) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(0));
    std::shared_ptr<Variable> var(new Variable("a"));
    std::shared_ptr<Multiplication> mult = std::shared_ptr<Multiplication>(new Multiplication( nbr, var ));
    std::shared_ptr<Expression> mult_simplified = mult->simplification();
    os << *mult_simplified;
    EXPECT_EQ( os.str(), "0" );
}

TEST(TestExpression, TestSimplificationMultiplication2) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(5));
    std::shared_ptr<Nombre> nbr_bis(new Nombre(0));
    std::shared_ptr<Multiplication> mult = std::shared_ptr<Multiplication>(new Multiplication( nbr, nbr_bis ));
    std::shared_ptr<Expression> mult_simplified = mult->simplification();
    os << *mult_simplified;
    EXPECT_EQ( os.str(), "0" );
}

TEST(TestExpression, TestSimplificationMultiplication3) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(1));
    std::shared_ptr<Variable> var(new Variable("a"));
    std::shared_ptr<Multiplication> mult = std::shared_ptr<Multiplication>(new Multiplication( nbr, var ));
    std::shared_ptr<Expression> mult_simplified = mult->simplification();
    os << *mult_simplified;
    EXPECT_EQ( os.str(), "a" );
}

TEST(TestExpression, TestSimplificationMultiplication4) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(5));
    std::shared_ptr<Nombre> nbr_bis(new Nombre(1));
    std::shared_ptr<Multiplication> mult = std::shared_ptr<Multiplication>(new Multiplication( nbr, nbr_bis ));
    std::shared_ptr<Expression> mult_simplified = mult->simplification();
    os << *mult_simplified;
    EXPECT_EQ( os.str(), "5" );
}

TEST(TestExpression, TestSimplificationMultiplication5) {
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(5));
    std::shared_ptr<Nombre> nbr_bis(new Nombre(2));
    std::shared_ptr<Multiplication> mult = std::shared_ptr<Multiplication>(new Multiplication( nbr, nbr_bis ));
    std::shared_ptr<Expression> mult_simplified = mult->simplification();
    os << *mult_simplified;
    EXPECT_EQ( os.str(), "10" );
}

TEST( TestExpression, TestSimplificationAdditionMultiplication) {
    // (0 + a) * 1 = a
    std::ostringstream os;
    std::shared_ptr<Nombre> nbr(new Nombre(0));
    std::shared_ptr<Variable> var(new Variable("a"));
    std::shared_ptr<Addition> add = std::shared_ptr<Addition>(new Addition( nbr, var ));
    std::shared_ptr<Nombre> nbr_bis(new Nombre(1));
    std::shared_ptr<Multiplication> mult = std::shared_ptr<Multiplication>(new Multiplication( add, nbr_bis ));
    std::shared_ptr<Expression> simplification = mult->simplification();
    os << *simplification;
    EXPECT_EQ(os.str(), "a");
}

// Main
int main( int argc, char * argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
