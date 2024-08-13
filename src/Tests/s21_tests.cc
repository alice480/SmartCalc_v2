#include "s21_tests.h"

TEST_F(MVCTest, function_sin) {
  // Act
  double result = model.calculate("sin(0.7)");
  // Assert
  ASSERT_NEAR(result, sin(0.7), ACCURACY);
}

TEST_F(MVCTest, function_cos) {
  // Act
  double result = model.calculate("cos(0.7)");
  // Assert
  ASSERT_NEAR(result, cos(0.7), ACCURACY);
}

TEST_F(MVCTest, function_asin) {
  // Act
  double result = model.calculate("asin(0.7)");
  // Assert
  ASSERT_NEAR(result, asin(0.7), ACCURACY);
}

TEST_F(MVCTest, function_acos) {
  // Act
  double result = model.calculate("acos(0.7)");
  // Assert
  ASSERT_NEAR(result, acos(0.7), ACCURACY);
}

TEST_F(MVCTest, function_atan) {
  // Act
  double result = model.calculate("atan(0.7)");
  // Assert
  ASSERT_NEAR(result, atan(0.7), ACCURACY);
}

TEST_F(MVCTest, function_tan) {
  // Act
  double result = model.calculate("tan(0.7)");
  // Assert
  ASSERT_NEAR(result, tan(0.7), ACCURACY);
}

TEST_F(MVCTest, function_sqrt) {
  // Act
  double result = model.calculate("sqrt(56.88)");
  // Assert
  ASSERT_NEAR(result, sqrt(56.88), ACCURACY);
}

TEST_F(MVCTest, function_ln) {
  // Act
  double result = model.calculate("ln(50)");
  // Assert
  ASSERT_NEAR(result, log(50), ACCURACY);
}

TEST_F(MVCTest, function_log) {
  // Act
  double result = model.calculate("log(50)");
  // Assert
  ASSERT_NEAR(result, log10(50), ACCURACY);
}

TEST_F(MVCTest, function_unary_minus) {
  // Act
  double result = model.calculate("-3");
  // Assert
  ASSERT_EQ(result, -3);
}

TEST_F(MVCTest, function_unary_plus) {
  // Act
  double result = model.calculate("+3");
  // Assert
  ASSERT_EQ(result, 3);
}

TEST_F(MVCTest, operation_plus) {
  // Act
  double result = model.calculate("100+200");
  // Assert
  ASSERT_EQ(result, 300);
}

TEST_F(MVCTest, operation_minus) {
  // Act
  double result = model.calculate("100-200");
  // Assert
  ASSERT_EQ(result, -100);
}

TEST_F(MVCTest, operation_multiplication) {
  // Act
  double result = model.calculate("100*200");
  // Assert
  ASSERT_EQ(result, 20000);
}

TEST_F(MVCTest, operation_division) {
  // Act
  double result = model.calculate("17.5/8.3");
  // Assert
  ASSERT_NEAR(result, (17.5/8.3), ACCURACY);
}

TEST_F(MVCTest, operation_degree) {
  // Act
  double result = model.calculate("100^2");
  // Assert
  ASSERT_EQ(result, 10000);
}

TEST_F(MVCTest, operation_mod) {
  // Act
  double result = model.calculate("100mod200");
  // Assert
  ASSERT_EQ(result, 100);
}

TEST_F(MVCTest, operation_brackets) {
  // Act
  double result = model.calculate("4*(5+6)");
  // Assert
  ASSERT_EQ(result, 44);
}

TEST_F(MVCTest, operators_some_operators) {
  // Act
  double result = model.calculate("(11.754-15.8163*2.9)/3.1");
  // Assert
  ASSERT_NEAR(result, ((11.754-15.8163*2.9)/3.1), ACCURACY);
}

TEST_F(MVCTest, operators_mod_with_operators) {
  // Act
  double result = model.calculate("6.4*5mod(2+1.4)*3");
  // Assert
  ASSERT_NEAR(result, (fmod(6.4*5, 3.4) * 3), ACCURACY);
}

TEST_F(MVCTest, peek_last_opeartor_from_stack) {
  // Act
  double result = model.calculate("3*sin(1+2.1)+4");
  // Assert
  ASSERT_NEAR(result, (3*sin(1+2.1)+4), ACCURACY);
}

TEST_F(MVCTest, error_expression) {
  // Act
  double result = model.calculate(")");
  // // Assert
  ASSERT_TRUE(std::isnan(result));
}

TEST_F(MVCTest, error_expression_without_operators) {
  // Act
  double result = model.calculate("2(3)");
  // Assert
  ASSERT_TRUE(std::isnan(result));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
