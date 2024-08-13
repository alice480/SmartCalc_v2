#include "rpn_conversion.h"

std::string s21::rpnConversion::convert(std::string expression) {
  std::string output_line;
  std::string token;
  size_t token_length = 0;
  for (size_t i = 0; i < expression.size(); ++i) {
    // is the token a single character
    if (is_single_operator(expression[i])) {
      // checking whether the token was up to a single character
      if (token_length) {
        token = expression.substr(i - token_length, token_length);
        // writing operators and operands to the stack and output string
        output_line = dijkstra_alg(token, define_token(token), output_line);
        token_length = 0;
        token.clear();
      }  // single token is operator
      // definition of binary and unarity
      if (expression[i] == '~' || expression[i] == '#')
        output_line =
            dijkstra_alg(expression.substr(i, 1), UNARY_OPERATOR, output_line);
      else
        output_line =
            dijkstra_alg(expression.substr(i, 1), BINARY_OPERATOR, output_line);
    } else
      token_length++;
  }
  if (tokens_stack.size())
    // adding the remaining tokens: stack -> output_string
    output_line = complete_dijkstra(output_line);
  return output_line;
}

bool s21::rpnConversion::is_single_operator(char token) {
  // ~ unary minus || # unary plus || M mod
  std::string single_sign_operators = "()+-*/^~#M>";
  size_t is_single_sign = single_sign_operators.find(token);
  return (is_single_sign != std::string::npos);
}

/*  return codes
    0 - ERROR
    1 - BINARY_OPERATOR
    2 - UNARY_OPERATOR
    3 - OPERAND  */
int s21::rpnConversion::define_token(std::string token) {
  int definition = TOKEN_DOESNT_EXIST;
  std::string binary_operators = "+-*/^M";
  // contains a pointer to the corresponding operand
  size_t is_binary_operator = binary_operators.find(token);
  std::string unary_operators = "sin cos tan asin acos atan sqrt log ln ~ #";
  // contains a pointer to the corresponding substring of the function
  size_t is_unary_operator = unary_operators.find(token);
  int integer;
  double real;
  // contain 1 if token is a number
  int is_real = std::sscanf(token.c_str(), "%lf", &real);
  int is_int = std::sscanf(token.c_str(), "%d", &integer);

  if (is_binary_operator != std::string::npos)
    definition = BINARY_OPERATOR;
  else if (is_unary_operator != std::string::npos)
    definition = UNARY_OPERATOR;
  else if (is_real || is_int)
    definition = OPERAND;
  return definition;
}

std::string s21::rpnConversion::dijkstra_alg(std::string token, int definition,
                                             std::string prev_line) {
  std::string output_line = prev_line;
  if (definition == OPERAND)
    // copying operands to the output string
    output_line.append("_" + token);
  else {
    if (token[0] == '(')
      // a copy of the string to be added to the stack
      tokens_stack.push(token);
    else if (token[0] == ')') {
      std::string last_operator;
      if (!tokens_stack.empty()) last_operator = tokens_stack.top();
      while (!tokens_stack.empty() && last_operator[0] != '(') {
        output_line.append("_" + last_operator);
        tokens_stack.pop();
        if (!tokens_stack.empty()) last_operator = tokens_stack.top();
      }
      if (!tokens_stack.empty()) tokens_stack.pop();
    } else {
      if (!tokens_stack.empty()) {
        // operations in stack with higher or equal priority -> output_string
        std::string last_operator = tokens_stack.top();
        int last_operator_priority = determine_priority(last_operator);
        int current_operator_priority = determine_priority(token);
        while (current_operator_priority <= last_operator_priority &&
               !tokens_stack.empty()) {
          output_line.append("_" + last_operator);
          tokens_stack.pop();
          if (!tokens_stack.empty()) {
            last_operator = tokens_stack.top();
            last_operator_priority = determine_priority(last_operator);
          }
        }
      }
      // a copy of the string to be added to the stack
      tokens_stack.push(token);
    }
  }
  return output_line;
}

/*  return codes
  0 - ERROR
  1 - (
  2 - BINARY OPERATORS +|-
  3 - BINARY OPERATORS *|/|M
  4 - BINARY OPERATOR  ^
  5 - UNARY  OPERATORS cos|sin|...|log|~ */
int s21::rpnConversion::determine_priority(std::string current_operator) {
  int priority = TOKEN_DOESNT_EXIST;

  std::string unary_operators = "sin cos tan asin acos atan sqrt log ln ~ #";
  size_t is_unary_operator = unary_operators.find(current_operator);

  if (is_unary_operator != std::string::npos)
    priority = 5;
  else {
    if (current_operator[0] == '(')
      priority = 1;
    else if (current_operator[0] == '+' || current_operator[0] == '-')
      priority = 2;
    else if (current_operator[0] == '*' || current_operator[0] == '/' ||
             current_operator[0] == 'M')
      priority = 3;
    else if (current_operator[0] == '^')
      priority = 4;
  }
  return priority;
}

std::string s21::rpnConversion::complete_dijkstra(std::string prev_line) {
  std::string token;
  std::string output_line = prev_line;
  while (tokens_stack.size()) {
    token = tokens_stack.top();
    output_line.append("_" + token);
    tokens_stack.pop();
  };
  return output_line;
}
