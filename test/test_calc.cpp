//#include <gtest.h>
//#include "ArithmeticExpression.h"
//#include <cmath>
//#include <map>
//using namespace std;
//
//TEST(ArithmeticExpresion, SimpleIntegerAddition)
//{
//    ArithmeticExpression expr("2+3");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 5.0);
//}
//
//TEST(ArithmeticExpresion, SimpleDecimalAddition)
//{
//    ArithmeticExpression expr("2.5+3.5");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 6.0);
//}
//
//TEST(ArithmeticExpresion, MixedAddition)
//{
//    ArithmeticExpression expr("2.5+3");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 5.5);
//}
//
//TEST(ArithmeticExpresion, MultiplicationAndDivision)
//{
//    ArithmeticExpression expr("6*4/2");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 12.0);
//}
//
//TEST(ArithmeticExpresion, SubtractionWithNegativeResult)
//{
//    ArithmeticExpression expr("3-7");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, -4.0);
//}
//
//TEST(ArithmeticExpresion, UnaryMinus)
//{
//    ArithmeticExpression expr("-5+3");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, -2.0);
//}
//
//TEST(ArithmeticExpresion, DoubleUnaryMinus)
//{
//    ArithmeticExpression expr("-(-5)");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 5.0);
//}
//
//TEST(ArithmeticExpresion, ExpressionWithOneVariable)
//{
//    ArithmeticExpression expr("x+5");
//    map<string, double> values = { {"x", 3.5} };
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 8.5);
//}
//
//TEST(ArithmeticExpresion, ExpressionWithMultipleVariables)
//{
//    ArithmeticExpression expr("a*b+c");
//    map<string, double> values = { {"a", 2.0}, {"b", 3.0}, {"c", 4.0} };
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 10.0);
//}
//
//TEST(ArithmeticExpresion, ComplexExpressionWithVariables)
//{
//    ArithmeticExpression expr("(a+b)*(c-d)");
//    map<string, double> values = { {"a", 2.5}, {"b", 3.5}, {"c", 10.0}, {"d", 4.0} };
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 36.0); 
//}
//
//TEST(ArithmeticExpresion, DivisionWithDecimalResult)
//{
//    ArithmeticExpression expr("5/2");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 2.5);
//}
//
//TEST(ArithmeticExpresion, OperatorPrecedence)
//{
//    ArithmeticExpression expr("2+3*4");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 14.0); 
//}
//
//
//TEST(ArithmeticExpresion, OperatorPrecedenceWithParentheses)
//{
//    ArithmeticExpression expr("(2+3)*4");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 20.0); 
//}
//
//TEST(ArithmeticExpresion, NestedParentheses)
//{
//    ArithmeticExpression expr("((2+3)*(4-1))/2");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 7.5);
//}
//
//
//TEST(ArithmeticExpresion, ComplexExampleFromMain)
//{
//    ArithmeticExpression expr("(a+b*c)*(c/d-e)");
//    map<string, double> values = { {"a", 1.0}, {"b", 2.0}, {"c", 3.0}, {"d", 1.0}, {"e", 2.0} };
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 7.0); 
//}
//
//
//
//TEST(ArithmeticExpresion, CombinationOfUnaryOperators)
//{
//    ArithmeticExpression expr("-5+(-3)");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, -8.0);
//}
//
//
//TEST(ArithmeticExpresion, LargeNumbers)
//{
//    ArithmeticExpression expr("1000*1000");
//    map<string, double> values;
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 1000000.0);
//}
//
//
//
//TEST(ArithmeticExpresion, VariablesWithDecimalValues)
//{
//    ArithmeticExpression expr("x*y+z");
//    map<string, double> values = { {"x", 2.5}, {"y", 1.5}, {"z", 0.25} };
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 4.0); 
//}
//
//TEST(ArithmeticExpresion, MultipleSameVariables)
//{
//    ArithmeticExpression expr("x*x+x");
//    map<string, double> values = { {"x", 3.0} };
//
//    double result = expr.GetResult(values);
//
//    ASSERT_DOUBLE_EQ(result, 12.0); 
//}