QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Location.cpp \
    destinationsdb.cpp \
    driver.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindowrider.cpp \
    signup_driver.cpp \
    signup_rider.cpp \
    transaction.cpp \
    transactionhistory.cpp \
    travelreceipt.cpp \
    trip.cpp

HEADERS += \
    AppWindows.h \
    Location.h \
    destinationsdb.h \
    driver.h \
    loginwindow.h \
    mainwindowrider.h \
    signup_driver.h \
    signup_rider.h \
    transaction.h \
    transactionhistory.h \
    travelreceipt.h \
    trip.h

FORMS += \
    loginwindow.ui \
    mainwindowrider.ui \
    signup_driver.ui \
    signup_rider.ui \
    transactionhistory.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
