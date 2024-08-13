#ifndef CPP3_SMARTCALC_SRC_MODEL_SMARTCALC_MODEL_H_
#define CPP3_SMARTCALC_SRC_MODEL_SMARTCALC_MODEL_H_

// C++ standard library headers
#include <gtest/gtest.h>

#include <cmath>
#include <string>

#include "rpn_conversion.h"

namespace s21 {

class smartCalcModel {
 public:
  smartCalcModel() : rpn_convertor(new rpnConversion()){};
  ~smartCalcModel() { delete rpn_convertor; };

  double calculate(std::string expression);

 private:
  std::string overwrite_string(std::string expression);
  bool check_for_unarity(char symbol);
  void split_tokens(std::string rpn_expression);
  void calculate_postfix_expression(std::string token);

  double perform_operations(double number1, double number2, char operand);
  double perform_function(double number, std::string function);
  double get_calculation_result();
  double stack_pop();

  s21::rpnConversion *rpn_convertor;
  // stack for performing operations on numbers
  std::stack<double> stack;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_MODEL_SMARTCALC_MODEL_H_