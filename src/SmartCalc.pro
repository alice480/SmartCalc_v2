QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    View/smartcalc_view.cc \
    Controller/smartcalc_controller.cc \
    Model/smartcalc_model.cc \
    Model/rpn_conversion.cc \
    qcustomplot/qcustomplot.cc

HEADERS += \
    View/smartcalc_view.h \
    Controller/smartcalc_controller.h \
    Model/smartcalc_model.h \
    Model/rpn_conversion.h \
    qcustomplot/qcustomplot.h

FORMS += \
    View/SmartCalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
