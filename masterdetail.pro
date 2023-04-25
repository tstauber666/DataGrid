HEADERS   = database.h \
            dialog.h \
            helper.h \
            mainwindow.h \
            meinmodel.h
RESOURCES = masterdetail.qrc
SOURCES   = dialog.cpp \
            helper.cpp \
            main.cpp \
            mainwindow.cpp \
            meinmodel.cpp

QT += sql widgets quick  core
QT += xml widgets
requires(qtConfig(tableview))

EXAMPLE_FILES = albumdetails.xml

# install
target.path = $$[QT_INSTALL_EXAMPLES]/sql/masterdetail
INSTALLS += target
