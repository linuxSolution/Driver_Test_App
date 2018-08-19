#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T16:19:11
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Revised_Test_App
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        doutform.cpp \
        ledconlroleform.cpp \
        dinform.cpp \
        gpo.cpp \
        gpi.cpp \
        gpio.cpp \
        worker.cpp \
        canform.cpp \
        canhelper.cpp \
        ethernetform.cpp \
        ethernethelper.cpp \
        gsmform.cpp \
        gsmhelper.cpp \
        rectifierform.cpp \
        rectifierhelper.cpp \
        dhcpstaticform.cpp \
        cmsconfigform.cpp \
        emeterform.cpp \
        mbushelper.cpp \
        adcext.cpp \
        adchelper.cpp \
        adccalibration.cpp \
        rectifierworker.cpp \
        ExternalAdc/extadc.cpp \
        SqlDatabase/db_manager.cpp

HEADERS += \
        mainwindow.h \
        gpio.h \
        doutform.h \
        ledconlroleform.h \
        dinform.h \
        gpo.h \
        gpi.h \
        worker.h \
        canform.h \
        canhelper.h \
        ethernetform.h \
        ethernethelper.h \
        gsmform.h \
        gsmhelper.h \
        rectifierform.h \
        rectifierhelper.h \
        dhcpstaticform.h \
        cmsconfigform.h \
        emeterform.h \
        mbushelper.h \
        adcext.h \
        adchelper.h \
        adccalibration.h \
        rectifierworker.h \
        ExternalAdc/extadc.h \
        SqlDatabase/db_manager.h

FORMS += \
        mainwindow.ui \
        doutform.ui \
        ledconlroleform.ui \
        dinform.ui \
        canform.ui \
        ethernetform.ui \
        gsmform.ui \
        rectifierform.ui \
        dhcpstaticform.ui \
        cmsconfigform.ui \
        emeterform.ui \
        adcext.ui

LIBS += -lmodbus

target.path += /home/launchApps/Apps/TestApps/tR1
INSTALLS += target
