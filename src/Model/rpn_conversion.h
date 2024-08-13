#ifndef CPP3_SMATRCALC_SRC_MODEL_RPN_CONVERSION_H_
#define CPP3_SMATRCALC_SRC_MODEL_RPN_CONVERSION_H_

// C++ standard library headers
#include <stack>
#include <string>
#include <vector>

// --------------------------------------------------------------------------
//                      LEXICAL VALUES OF TOKENS
#define BINARY_OPERATOR 1
#define UNARY_OPERATOR 2
#define OPERAND 3
// --------------------------------------------------------------------------
//                            ERROR CODES
#define TOKEN_DOESNT_EXIST 0
// --------------------------------------------------------------------------

namespace s21 {
class rpnConversion {
 public:
  std::string convert(std::string expression);
  std::string dijkstra_alg(std::string token, int definition,
                           std::string prev_line);
  int define_token(std::string token);

 private:
  int determine_priority(std::string current_operator);
  std::string complete_dijkstra(std::string prev_line);
  bool is_single_operator(char token);
  std::stack<std::string> tokens_stack;  // stack for Dijkstra's algorithm
};
}  // namespace s21

#endif  // CPP3_SMATRCALC_SRC_MODEL_RPN_CONVERSION_H_
