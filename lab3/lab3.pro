QT += qml quick widgets sql

CONFIG += c++11

QTPLUGIN +=

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    riverlistsql.cpp

HEADERS += \
    riverlistsql.h

FORMS +=

RESOURCES += qml.qrc \
    qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    DelegateForRiver.qml \
    DialogForAdd.qml \
    DialogForAnswer.qml \
    DialogForEdit.qml \
    main.qml
