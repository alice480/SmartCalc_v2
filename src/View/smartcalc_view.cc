#include "smartcalc_view.h"

s21::smartCalcView::smartCalcView(s21::smartCalcController *c, QWidget *parent)
    : QMainWindow(parent), controller(c), ui(new Ui::smartCalcView) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(get_button_value()));
  // signal handlers from functions buttons
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(get_function_value()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(get_button_value()));
  connect(ui->pushButton_exp, SIGNAL(clicked()), this,
          SLOT(get_button_value()));
  // signal handler from truncate button
  connect(ui->pushButton_truncate, SIGNAL(clicked()), this,
          SLOT(on_pushButton_truncate_cliked()));
}

s21::smartCalcView::~smartCalcView() { delete ui; }

void s21::smartCalcView::get_button_value() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + button->text());
}

void s21::smartCalcView::get_function_value() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + button->text() + "(");
}

void s21::smartCalcView::on_pushButton_eq_clicked() {
  QString expression = ui->label->text();
  std::pair<QVector<double>, QVector<double>> x_y_coords;
  if (expression.contains("x"))
    x_y_coords = get_coords_for_drawing_with_x(expression);
  else {
    // transmitting the read value to the controller
    double calculation_result = controller->calculate_value(expression);
    size_t integer_length =
        QString::number(calculation_result, 'g', 0).length();
    ui->label->setText(
        QString::number(calculation_result, 'g', integer_length + 7));
    x_y_coords = get_coords_for_drawing(calculation_result);
  }
  draw_graph(x_y_coords.first, x_y_coords.second);
}

void s21::smartCalcView::on_pushButton_truncate_cliked() {
  ui->label->clear();
  ui->widget->clearGraphs();
}

std::pair<QVector<double>, QVector<double>>
s21::smartCalcView::get_coords_for_drawing_with_x(QString expression) {
  setlocale(LC_NUMERIC, "C");
  double x_min = ui->doubleSpinBox->value();
  double x_max = ui->doubleSpinBox_2->value();
  std::pair<QVector<double>, QVector<double>> coords;
  if (x_min != x_max)
    coords = controller->get_coordinats(x_min, x_max, expression);
  return coords;
}

std::pair<QVector<double>, QVector<double>>
s21::smartCalcView::get_coords_for_drawing(double y) {
  setlocale(LC_NUMERIC, "C");
  double x_min = ui->doubleSpinBox->value();
  double x_max = ui->doubleSpinBox_2->value();
  QVector<double> x_coords, y_coords;
  if (x_min != x_max) {
    double x = x_min;
    double step = fabs(x_max - x_min) / 1000;
    while (x <= x_max) {
      x_coords.push_back(x);
      y_coords.push_back(y);
      x += step;
    }
  }
  return std::make_pair(x_coords, y_coords);
}

void s21::smartCalcView::draw_graph(QVector<double> x_coords,
                                    QVector<double> y_coords) {
  double x_min, x_max;
  if (x_coords.length() == y_coords.length()) {
    x_min = *std::min_element(x_coords.begin(), x_coords.end());
    x_max = *std::max_element(x_coords.begin(), x_coords.end());
    double y_min = *std::min_element(y_coords.begin(), y_coords.end());
    double y_max = *std::max_element(y_coords.begin(), y_coords.end());
    double y_delta = (y_max - y_min) / 10;
    if (!y_delta) y_delta = 10;
    set_graph_settings();
    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min - y_delta, y_max + y_delta);
    ui->widget->graph(0)->rescaleAxes();
    ui->widget->graph(0)->addData(x_coords, y_coords);
    ui->widget->replot();
  } else
    ui->label->setText("Impossible to build a graph");
}

void s21::smartCalcView::set_graph_settings() {
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
}