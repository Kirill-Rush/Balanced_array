QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    comboboxdelegate.cpp \
    delegateforvalidation.cpp \
    dialogaboutprogramm.cpp \
    equipment.cpp \
    main.cpp \
    mainwindow.cpp \
    tablemodel.cpp

HEADERS += \
    chart.h \
    comboboxdelegate.h \
    delegateforvalidation.h \
    dialogaboutprogramm.h \
    equipment.h \
    mainwindow.h \
    tablemodel.h

FORMS += \
    chart.ui \
    dialogaboutprogramm.ui \
    mainwindow.ui

TRANSLATIONS += tr/course-work_ru_RU.ts \
                tr/course-work_en_EN.ts \
                tr/course-work_fr_FR.ts \
                tr/course-work_es_ES.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
