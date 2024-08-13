#include "smartcalc_controller.h"

double s21::smartCalcController::calculate_value(QString expression) {
  double value = NAN;
  if (convert_exp_record(&expression)) {
    std::string input = convert_qstring_to_std_string(expression);
    value = model->calculate(input);
  }
  return value;
}

std::string s21::smartCalcController::convert_qstring_to_std_string(
    QString line) {
  return line.toStdString();
}

bool s21::smartCalcController::convert_exp_record(QString *exp_record) {
  bool flag = true;
  qsizetype pos = exp_record->indexOf("e");
  while (pos >= 0) {
    QString prev_symbol = exp_record->mid(pos - 1, 1);
    // if ok = false -> the previous character is not a number
    bool ok;
    prev_symbol.toInt(&ok);
    flag = flag && prev_symbol.compare(".") && !ok;
    exp_record->replace(pos, 1, "10^");
    pos = exp_record->indexOf("e");
  }
  return flag;
}

std::pair<QVector<double>, QVector<double>>
s21::smartCalcController::get_coordinats(double x_min, double x_max,
                                         QString expression) {
  QVector<double> x_coord, y_coord;
  double step = fabs(x_max - x_min) / 1000;
  // variables for calculating the expression
  double x = x_min;
  while (x <= x_max) {
    if (fabs(x) < step) x = 0;
    // replace the variable X in the string with a number
    QString str_x = QString::number(x, 'g', 10);
    QString new_expression = expression;
    new_expression.replace("x", str_x);
    double value = NAN;
    // get rid of exponential notation
    if (convert_exp_record(&new_expression))
      value = model->calculate(convert_qstring_to_std_string(new_expression));

    if (!std::isnan(value)) {
      x_coord.push_back(x);
      if (std::numeric_limits<qreal>::max() < value) value = 1000000;
      if (value < -std::numeric_limits<qreal>::max()) value = -1000000;
      y_coord.push_back(value);
    }
    x += step;
  }
  return std::make_pair(x_coord, y_coord);
}