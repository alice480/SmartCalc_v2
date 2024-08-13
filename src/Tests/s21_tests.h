#ifndef CPP3_SMATRCALC_SRC_TESTS_S21_TESTS_H_
#define CPP3_SMATRCALC_SRC_TESTS_S21_TESTS_H_

#include <gtest/gtest.h>
#include <cmath>

#include "../Model/smartcalc_model.h"
#include "../Model/rpn_conversion.h"

#define ACCURACY 1e-7

struct MVCTest : public testing::Test {
    s21::smartCalcModel model;
};

#endif  // CPP3_SMATRCALC_SRC_TESTS_S21_TESTS_H_