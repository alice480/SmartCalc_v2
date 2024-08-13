#include "smartcalc_model.h"

double s21::smartCalcModel::calculate(std::string expression) {
  std::string new_expression = overwrite_string(expression);
  std::string rpn_expression = rpn_convertor->convert(new_expression);
  split_tokens(rpn_expression);
  double result = get_calculation_result();
  stack = {};  // clearing the stack after calculation
  return result;
}

double s21::smartCalcModel::get_calculation_result() {
  double value = NAN;
  if (stack.size()) {
    value = stack.top();
    stack.pop();
  }
  // if the stack is not empty after that => error!
  return (stack.size()) ? NAN : value;
}

// private method
std::string s21::smartCalcModel::overwrite_string(std::string expression) {
  // a new string with replaced characters for easy processing
  std::string modified_string = expression + ">";
  // replace "Mod" substring to "M" character
  size_t mod_index = modified_string.find("mod");
  while (mod_index != std::string::npos) {
    modified_string.replace(mod_index, 3, "M");
    mod_index = modified_string.find("mod");
  }
  // replacing unary operators with special simulations
  for (size_t i = 0; i < modified_string.size(); ++i) {
    if (modified_string[i] == '-') {
      if (i == 0 || check_for_unarity(modified_string[i - 1]))
        modified_string.replace(i, 1, "~");
    } else if (modified_string[i] == '+') {
      if (i == 0 || check_for_unarity(modified_string[i - 1]))
        modified_string.replace(i, 1, "#");
    }
  }
  return modified_string;
}

bool s21::smartCalcModel::check_for_unarity(char symbol) {
  std::string unary_sym_predecessors = "<(+-*/^";
  return unary_sym_predecessors.find(symbol) != std::string::npos;
}

void s21::smartCalcModel::split_tokens(std::string rpn_expression) {
  std::string token;
  int token_length = 0;
  for (auto i = 0; rpn_expression[i]; ++i) {
    if (rpn_expression[i] == '_') {
      if (token_length) {
        token = rpn_expression.substr(i - token_length, token_length);
        calculate_postfix_expression(token);
        token.clear();
      }
      token_length = 0;
    } else
      token_length++;
  }
}

void s21::smartCalcModel::calculate_postfix_expression(std::string token) {
  // definition of what a token is: (operand)/(operator, function)
  double result;
  int definition = rpn_convertor->define_token(token);
  if (definition == OPERAND)
    stack.push(std::stod(token));
  else if (definition == BINARY_OPERATOR) {
    // getting two operands from the top of the stack
    double number1, number2;
    number2 = stack_pop();
    number1 = stack_pop();
    // passing operands and operator to perform the operation
    result = perform_operations(number1, number2, token[0]);
    // putting the result on the stack with numbers
    stack.push(result);
  } else if (definition == UNARY_OPERATOR) {
    double number = stack_pop();
    result = perform_function(number, token);
    stack.push(result);
  }
}

double s21::smartCalcModel::stack_pop() {
  double value = NAN;
  if (stack.size()) {
    value = stack.top();
    stack.pop();
  }
  return value;
}

double s21::smartCalcModel::perform_operations(double number1, double number2,
                                               char operand) {
  double result = NAN;
  if (operand == '+')
    result = number1 + number2;
  else if (operand == '-')
    result = number1 - number2;
  else if (operand == '*')
    result = number1 * number2;
  else if (operand == '/') {
    result = number1 / number2;
  } else if (operand == '^')
    result = pow(number1, number2);
  else if (operand == 'M')
    result = fmod(number1, number2);
  return result;
}

double s21::smartCalcModel::perform_function(double number,
                                             std::string function) {
  double result = NAN;
  // compare: 0 -> equal strings
  if (!function.compare("asin"))
    result = asin(number);
  else if (!function.compare("sin"))
    result = sin(number);
  else if (!function.compare("acos"))
    result = acos(number);
  else if (!function.compare("cos"))
    result = cos(number);
  else if (!function.compare("atan"))
    result = atan(number);
  else if (!function.compare("tan"))
    result = tan(number);
  else if (!function.compare("sqrt"))
    result = sqrt(number);
  else if (!function.compare("ln"))
    result = log(number);
  else if (!function.compare("log"))
    result = log10(number);
  else if (!function.compare("~"))
    result = number * (-1);
  else if (!function.compare("#"))
    result = number;
  return result;
}
