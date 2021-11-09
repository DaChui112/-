QT       += core gui
QT       += sql
QT       += widgets
QT       += serialport
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Tools/RS232Com/RS232ComProtocal.cxx \
    Tools/RS232Com/RS232ComThread.cxx \
    Tools/RS232Com/RS232ComThreadLis.cxx \
    Tools/RS232Com/RS232ComUserDeal.cxx \
    Tools/Sqlite/sqlitedriver.cxx \
    Tools/TCPCom/communicationTcp.cpp \
    diaaddnewparameter.cpp \
    diaedittestshow.cpp \
    diasampleno.cpp \
    diatestmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    sqlhelper.cpp

HEADERS += \
    Tools/Configer/confighelper.hpp \
    Tools/RS232Com/RS232ComProtocal.hpp \
    Tools/RS232Com/RS232ComThread.hpp \
    Tools/RS232Com/RS232ComThreadLis.hpp \
    Tools/RS232Com/RS232ComUserDeal.hpp \
    Tools/Sqlite/sqlitedriver.hpp \
    Tools/TCPCom/communicationTcp.h \
    diaaddnewparameter.h \
    diaedittestshow.h \
    diasampleno.h \
    diatestmanager.h \
    mainwindow.h \ \
    spdlog/sinks/rotating_file_sink.h

FORMS += \
    diaaddnewparameter.ui \
    diaedittestshow.ui \
    diasampleno.ui \
    diatestmanager.ui \
    mainwindow.ui

INCLUDEPATH += Tools/
INCLUDEPATH += spdlog/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
