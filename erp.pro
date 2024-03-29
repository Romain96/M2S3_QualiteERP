#-------------------------------------------------
#
# Project created by QtCreator 2018-09-19T18:01:50
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = erp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/erp_config.cpp \
    src/project.cpp \
    src/team.cpp \
    src/employee_dialog.cpp \
    src/project_dialog.cpp \
    src/event.cpp \
    src/event_stack.cpp \
    src/recruitement_center.cpp \
    src/result_dialog.cpp \
    src/date_dialog.cpp \
    src/efficiency_dialog.cpp

HEADERS += \
    include/mainwindow.h \
    include/erp_config.h \
    include/project.h \
    include/team.h \
    lib/cpptoml.h \
    include/employee_dialog.h \
    include/project_dialog.h \
    include/event.h \
    include/event_stack.h \
    include/recruitement_center.h \
    include/result_dialog.h \
    include/date_dialog.h \
    include/efficiency_dialog.h

FORMS += \
    mainwindow.ui \
    project_dialog.ui \
    employee_dialog.ui \
    result_dialog.ui \
    date_dialog.ui \
    efficiency_dialog.ui

RESOURCES += \
    src.qrc
