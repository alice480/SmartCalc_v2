#ifndef CPP3_SMARTCALC_SRC_VIEW_SMARTCALC_VIEW_H_
#define CPP3_SMARTCALC_SRC_VIEW_SMARTCALC_VIEW_H_

// related headers
#include "Controller/smartcalc_controller.h"

// C++ standard library headers
#include <QMainWindow>

// project's headers
#include "ui_SmartCalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class smartCalcView;
}
QT_END_NAMESPACE

namespace s21 {

class smartCalcView : public QMainWindow {
  Q_OBJECT

 public:
  smartCalcView(smartCalcController *c, QWidget *parent = nullptr);
  ~smartCalcView();

 private slots:
  void get_button_value();
  void get_function_value();
  void on_pushButton_eq_clicked();
  void on_pushButton_truncate_cliked();
  // methods for graph construction
  std::pair<QVector<double>, QVector<double>> get_coords_for_drawing(double y);
  std::pair<QVector<double>, QVector<double>> get_coords_for_drawing_with_x(
      QString expression);
  void set_graph_settings();
  void draw_graph(QVector<double> x_coords, QVector<double> y_coords);

 private:
  smartCalcController *controller;
  Ui::smartCalcView *ui;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_SRC_VIEW_SMARTCALC_VIEW_H_
