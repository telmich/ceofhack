# -------------------------------------------------
# Project created by QtCreator 2009-06-04T10:36:50
# -------------------------------------------------
TARGET = eofhack
TEMPLATE = app

RCC_DIR = temp/qrc
UI_DIR  = temp/ui
MOC_DIR = temp/moc
OBJECTS_DIR = temp/obj

SOURCES += main.cpp \
           MainWindow.cpp \
           addpeer.cpp \
           settingsgui.cpp \
           aboutgui.cpp 
    
HEADERS += MainWindow.h \
           addpeer.h \
           settingsgui.h \
           aboutgui.h 
    
FORMS   += MainWindow.ui \
           addpeer.ui \
           settingsgui.ui \
           aboutgui.ui 

RESOURCES += images.qrc

win32 {

    RC_FILE = images/eof_win.rc
    
}

