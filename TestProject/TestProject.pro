TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Generator.cpp \
    Terrain.cpp \
    ShaderObject.cpp \
    object.cpp \
    tree.cpp \
    branch.cpp \
    leaf.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/release/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/debug/ -losg
else:unix: LIBS += -L$$PWD/../../Build/osg3-2/lib/ -losg

INCLUDEPATH += $$PWD/../../Source/osg3-2/include
DEPENDPATH += $$PWD/../../Source/osg3-2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/release/ -losgViewer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/debug/ -losgViewer
else:unix: LIBS += -L$$PWD/../../Build/osg3-2/lib/ -losgViewer

INCLUDEPATH += $$PWD/../../Source/osg3-2/include
DEPENDPATH += $$PWD/../../Source/osg3-2/include

HEADERS += \
    Generator.h \
    Terrain.h \
    ShaderObject.h \
    object.h \
    tree.h \
    branch.h \
    leaf.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/release/ -losgDB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/debug/ -losgDB
else:unix: LIBS += -L$$PWD/../../Build/osg3-2/lib/ -losgDB

INCLUDEPATH += $$PWD/../../Source/osg3-2/include
DEPENDPATH += $$PWD/../../Source/osg3-2/include

OTHER_FILES += \
    ../media/shaders/terrain.frag \
    ../media/shaders/terrain.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/release/ -losgUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Build/osg3-2/lib/debug/ -losgUtil
else:unix: LIBS += -L$$PWD/../../Build/osg3-2/lib/ -losgUtil

INCLUDEPATH += $$PWD/../../Source/osg3-2/include/osgUtil
DEPENDPATH += $$PWD/../../Source/osg3-2/include/osgUtil
