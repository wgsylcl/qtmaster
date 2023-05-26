#include "projectcreater.h"

void projectcreater::create_dir(string path)
{
    mkdir(path.c_str());
    return;
}

void projectcreater::operator()(string projectname,string workpath)
{
    translator translate;
    create_dir(workpath+"/"+projectname);
    filewriter cmakewriter(workpath+"/"+projectname+"/CMakeLists.txt");
    cmakewriter.write(translate(R"(cmake_minimum_required(VERSION 3.5)

project(%2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR}/mingw_64)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

aux_source_directory(./src PROJECT_SOURCES)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(%2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(%2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(%2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(%2)
endif())"
,"qproject",projectname));
    create_dir(workpath+"/"+projectname+"/src");
    filewriter mainwriter(workpath+"/"+projectname+"/src/main.cpp");
    mainwriter.write(translate(R"(#include "%2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    %2 w;
    w.show();
    return a.exec();
})","main","mainwindow"));
    filewriter srcwriter(workpath+"/"+projectname+"/src/mainwindow.cpp");
    srcwriter.write(translate(R"(#include "%2.h"

%2::%2(%1* parent)
    : %1(parent)
    , ui(new Ui::%2)
{
    ui->setupUi(this);
}

%2::~%2()
{
    delete ui;
})","QMainWindow","mainwindow"));
    filewriter headerwriter(workpath+"/"+projectname+"/src/mainwindow.h");
    headerwriter.write(translate(R"(#pragma once
#include <%1>
#include "ui_%2.h"

class %2 : public %1 {
    Q_OBJECT

public:
    %2(%1* parent = nullptr);
    ~%2();

private:
    Ui::%2* ui;
};)","QMainWindow","mainwindow"));
    filewriter uiwriter(workpath+"/"+projectname+"/src/mainwindow.ui");
    uiwriter.write(translate(R"(<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>mainwindow</class>
 <widget class="%1" name="%2">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>800</width>
    <height>600</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>%2</string>
  </property>
  <widget class="QWidget" name="centralwidget"/>
  <widget class="QMenuBar" name="menubar"/>
  <widget class="QStatusBar" name="statusbar"/>
 </widget>
 <resources/>
 <connections/>
</ui>)","QMainWindow",projectname));
}