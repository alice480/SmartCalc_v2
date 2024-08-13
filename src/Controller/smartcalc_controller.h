#ifndef CPP3_SMARTCALC_SRC_CONTROLLER_SMARTCALC_CONTROLLER_H_
#define CPP3_SMARTCALC_SRC_CONTROLLER_SMARTCALC_CONTROLLER_H_

// related headers
#include <QString>
#include <QVector>
#include <string>

#include "../Model/smartcalc_model.h"

namespace s21 {

class smartCalcController {
 public:
  smartCalcController(smartCalcModel *m) : model(m){};
  ~smartCalcController() = default;

  double calculate_value(QString expression);
  std::pair<QVector<double>, QVector<double>> get_coordinats(
      double x_min, double x_max, QString expression);

 private:
  std::string convert_qstring_to_std_string(QString line);
  bool convert_exp_record(QString *exp_record);
  smartCalcModel *model;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_CONTROLLER_SMARTCALC_CONTROLLER_H_