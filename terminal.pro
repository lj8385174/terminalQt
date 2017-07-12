QT += widgets serialport
QT += charts

TARGET = terminal
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    mydialog.cpp \
    chart.cpp \
    chartview.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    mydialog.h \
    chart.h \
    chartview.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    mydialog.ui

RESOURCES += \
    terminal.qrc


target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
INSTALLS += target


QT += widgets
