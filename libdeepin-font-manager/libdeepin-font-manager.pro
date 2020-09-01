######################################################################
# Automatically generated by qmake (3.0) ?? 12? 20 11:42:33 2017
######################################################################

QT += core gui sql dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = deepin-font-manager
TEMPLATE = lib
CONFIG += c++11 link_pkgconfig
PKGCONFIG += freetype2 fontconfig gsettings-qt

CONFIG += create_pc create_prl no_install_prl

DEFINES += QT_MESSAGELOGCONTEXT

# Input
HEADERS += \
	   dfontpreview.h \
	   dfontinfomanager.h \
	   dfontmanager.h \
           dfontloadthread.h \
           dfontwidget.h \
           dfmdbmanager.h \
           dsqliteutil.h \
           dfontpreviewitemdef.h \
           signalmanager.h \
           dcopyfilesmanager.h

SOURCES += \
	   dfontpreview.cpp \
	   dfontinfomanager.cpp \
	   dfontmanager.cpp \
           dfontloadthread.cpp \
           dfontwidget.cpp \
           dfmdbmanager.cpp \
           dsqliteutil.cpp \
           signalmanager.cpp \
           dcopyfilesmanager.cpp

QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_VERSION = $$VERSION
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_NAME = deepin-font-manager
QMAKE_PKGCONFIG_DESCRIPTION = Deepin Font Manager Header Files
QMAKE_PKGCONFIG_INCDIR = $$includes.path

includes.path = $$INCLUDE_INSTALL_DIR/deepin-font-manager
includes.files += $$PWD/*.h

isEmpty(PREFIX) {
    PREFIX = /usr
}

isEmpty(LIB_INSTALL_DIR) {
    target.path = $$[QT_INSTALL_LIBS]
} else {
    target.path = $$LIB_INSTALL_DIR
}

isEmpty(INCLUDE_INSTALL_DIR) {
    includes.path = $$PREFIX/include/deepin-font-manager
} else {
    includes.path = $$INCLUDE_INSTALL_DIR/deepin-font-manager
}


translations.path = /usr/share/deepin-font-manager/translations
translations.files = $$PWD/../translations/*.qm

contents_file.path = /usr/share/deepin-font-manager/
contents_file.files += $$PWD/CONTENTS.txt

install_gsettings.files = ./schemas/com.deepin.font-manager.gschema.xml
install_gsettings.path = /usr/share/glib-2.0/schemas/

INSTALLS += target install_gsettings includes contents_file translations

TRANSLATIONS += ../translations/deepin-font-manager.ts
