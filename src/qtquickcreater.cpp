#include "qtquickcreater.h"

#define mainsrc "#include <QGuiApplication>\n\
#include <QQmlApplicationEngine>\n\
\n\
int main(int argc, char *argv[])\n\
{\n\
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)\n\
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);\n\
#endif\n\
    QGuiApplication app(argc, argv);\n\
\n\
    QQmlApplicationEngine engine;\n\
    const QUrl url(QStringLiteral(\"qrc:/main.qml\"));\n\
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,\n\
        &app, [url](QObject *obj, const QUrl &objUrl) {\n\
            if (!obj && url == objUrl)\n\
                QCoreApplication::exit(-1);\n\
        }, Qt::QueuedConnection);\n\
    engine.load(url);\n\
\n\
    return app.exec();\n\
}\n\
"

#define qrcsrc "<!-- Qt resource file created by qt5master , the file will be coverd when you add or remove qml file , do not change it !!! -->\n\
<RCC>\n\
    <qresource prefix=\"/\">\n\
        <file>main.qml</file>\n\
    </qresource>\n\
</RCC>\n\
"

#define qmlsrc "import QtQuick 2.15\n\
import QtQuick.Window 2.15\n\
\n\
Window {\n\
    width: 640\n\
    height: 480\n\
    visible: true\n\
    title: qsTr(\"%2\")\n\
}\n\
"

#define cmake "cmake_minimum_required(VERSION 3.5)\n\
\n\
project(%2 VERSION 0.1 LANGUAGES CXX)\n\
\n\
set(CMAKE_INCLUDE_CURRENT_DIR ON)\n\
\n\
set(CMAKE_AUTOUIC ON)\n\
set(CMAKE_AUTOMOC ON)\n\
set(CMAKE_AUTORCC ON)\n\
\n\
set(CMAKE_CXX_STANDARD 17)\n\
set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\
set(CMAKE_PREFIX_PATH $ENV{QTDIR}/mingw_64)\n\
\n\
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Quick REQUIRED)\n\
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)\n\
\n\
aux_source_directory(./src PROJECT_SOURCES)\n\
\n\
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)\n\
    qt_add_executable(%2\n\
        MANUAL_FINALIZATION\n\
        ${PROJECT_SOURCES}\n\
        qml/qml.qrc\n\
    )\n\
endif()\n\
\n\
target_link_libraries(%2 PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)\n\
\n\
set_target_properties(%2 PROPERTIES\n\
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com\n\
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}\n\
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}\n\
    MACOSX_BUNDLE TRUE\n\
    WIN32_EXECUTABLE TRUE\n\
)\n\
\n\
if(QT_VERSION_MAJOR EQUAL 6)\n\
    qt_finalize_executable(%2)\n\
endif()\n\
"

void qtquickcreater::operator()(string path,string projectname)
{
    createdir(path+"\\"+projectname);
    createdir(path+"\\"+projectname+"\\src");
    createdir(path+"\\"+projectname+"\\qml");
    filewriter cmakefilewriter(path+"\\"+projectname+"\\CMakeLists.txt");
    filewriter mainfilewriter(path+"\\"+projectname+"\\src\\main.cpp");
    filewriter qrcfilewriter(path+"\\"+projectname+"\\qml\\qml.qrc");
    filewriter qmlfilewriter(path+"\\"+projectname+"\\qml\\main.qml");
    translator translate;
    cmakefilewriter.write(translate(cmake,"QtQuick",projectname));
    mainfilewriter.write(translate(mainsrc,"qtquick",projectname));
    qrcfilewriter.write(qrcsrc);
    qmlfilewriter.write(translate(qmlsrc,"quick","main"));
    return;
}

void qtquickcreater::createdir(string path)
{
    mkdir(path.c_str());
}