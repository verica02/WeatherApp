
QT       += core gui qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weatherpp
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

# Source File Directories
MYUI_DIR = UI
WIDGETS_DIR = $(MYUI_DIR)/Widgets
LOGIC_DIR = Logic
CONTROLLER_DIR = Controller

# Source Files
CONTROLLER_SRC = $(CONTROLLER_DIR)/*.cpp
LOGIC_SRC = $(LOGIC_DIR)/*.cpp
UI_SRC = $(MYUI_DIR)/*.cpp
WIDGETS_SRC = $(WIDGETS_DIR)/*.cpp

# Headers
CONTROLLER_HDR = $(CONTROLLER_DIR)/*.h
LOGIC_HDR = $(LOGIC_DIR)/*.h
UI_HDR = $(MYUI_DIR)/*.h
WIDGETS_HDR = $(WIDGETS_DIR)/*.h

SOURCES +=\
    Controller/weathercontroller.cpp \
    Logic/weatherlogic.cpp \
    UI/Widgets/texteditor.cpp \
    UI/Widgets/textpresentation.cpp \
    UI/Widgets/uiwidget.cpp \
    UI/Widgets/weatherwidget.cpp \
    UI/mainwindow.cpp \
    WeatherApp/weatherapp.cpp \
    main.cpp \
    UI/Widgets/flyingbox.cpp \
    UI/Widgets/weatherspec.cpp \
    UI/Widgets/briefwidget.cpp \
    Logic/weatherservice.cpp \
    Logic/htttqueryservice.cpp

HEADERS += \
    Controller/weathercontroller.h \
    Logic/weatherlogic.h \
    UI/Widgets/texteditor.h \
    UI/Widgets/textpresentation.h \
    UI/Widgets/uiwidget.h \
    UI/Widgets/weatherwidget.h \
    UI/mainwindow.h \
    WeatherApp/weatherapp.h \
    UI/Widgets/flyingbox.h \
    UI/Widgets/weatherspec.h \
    UI/Widgets/briefwidget.h \
    Logic/ihttpservice.h \
    Logic/weatherservice.h \
    Logic/htttqueryservice.h

DISTFILES += \
    UI/Rsc/Layouts/MainWindowLayout.json

RESOURCES += \
    UI/Rsc/hovering-icons.qrc \
    UI/Rsc/views.qrc \
    UI/Rsc/components.qrc \
    Logic/Rsc/NVData.qrc \
    Credentials/credentials.qrc
