QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assigntodo.cpp \
    authenticationpageapi.cpp \
    boardwindowapi.cpp \
    main.cpp \
    loginandsignupdialog.cpp \
    todo.cpp \
    todocomponent.cpp \
    todosboardwindow.cpp \
    user.cpp \
    chat.cpp \
    conversation.cpp \
    mainwindow.cpp

HEADERS += \
    assigntodo.h \
    authenticationpageapi.h \
    boardwindowapi.h \
    loginandsignupdialog.h \
    todo.h \
    todocomponent.h \
    todosboardwindow.h \
    user.h \
    chat.h \
    conversation.h \
    mainwindow.h

FORMS += \
    loginandsignupdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
