#include "projectcreater.h"

void projectcreater::create_dir(string path)
{
    CreateDirectory(path.c_str(),nullptr);
    return;
}

void projectcreater::operator()(string projectname,string workpath)
{
    translator translate;
    create_dir(workpath+"/"+projectname);
    filewriter cmakewriter(workpath+"/"+projectname+"/CMakeLists.txt");
    cmakewriter.write(translate(R"(cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(%2 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "$ENV{QTDIR}/mingw81_64") # Your Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS
aux_source_directory(./src srcs)
# Specify MSVC UTF-8 encoding
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    WIN32 # If you need a terminal for debug, please comment this statement
    ${srcs}
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets) # Qt5 Shared Library)"
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