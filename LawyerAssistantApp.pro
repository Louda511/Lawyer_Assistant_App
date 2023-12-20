QT       += core gui
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authenticationpageapi.cpp \
    main.cpp \
    loginandsignupdialog.cpp \
    \  # todocomponent.cpp # This line is added by qmake for the generated moc file
    todo.cpp \
    todocomponent.cpp \
    todosboardwindow.cpp \
    user.cpp

HEADERS += \
    authenticationpageapi.h \
    loginandsignupdialog.h \
    todo.h \
    todocomponent.h \
    todosboardwindow.h \
    user.h

FORMS += \
    loginandsignupdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
