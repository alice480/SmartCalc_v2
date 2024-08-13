#include <QApplication>

#include "View/smartcalc_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::smartCalcModel model;
  s21::smartCalcController controller(&model);
  s21::smartCalcView view(&controller);
  view.show();
  a.exec();
  return 0;
}
