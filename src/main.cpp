#include <bits/stdc++.h>
#include <direct.h>
#include "fileremover.h"
#include "projectcreater.h"
#include "qtquickcreater.h"
using namespace std;
//example: qt5master <options> <classname>
int main(int argc,char *argv[])
{
    if(argc != 3)
        puts("qt5master ERROR:You give wrong options!"),exit(-1);
    char s[1010];
    _getcwd(s,1010);
    string workpath = s, option = argv[1], classname = argv[2];
    if (option == "remove")
    {
        if(classname == "main")
        {
            puts("qt5master ERROR:You can not remove the main code!");
            exit(-1);
        }
        fileremover remover;
        remover(workpath+"/src/"+classname+".cpp");
        remover(workpath+"/src/"+classname+".h");
        if(remover.test_exist(workpath+"/src/"+classname+".ui"))
        remover(workpath+"/src/"+classname+".ui");
    }
    if (option == "addclass")
    {
        filewriter cppwriter(workpath+"/src/"+classname+".cpp");
        translator tran;
        cppwriter.write(tran(R"(#include "%2.h"

%2::%2(%1* parent)
    : %1(parent)
{

}

%2::~%2()
{

})","QObject",classname));
        filewriter headwriter(workpath+"/src/"+classname+".h");
        headwriter.write(tran(R"(#pragma once
#include <%1>

class %2 : public %1 {
    Q_OBJECT

public:
    %2(%1* parent = nullptr);
    ~%2();
};)","QObject",classname));
    }
    if (option == "addwidget")
    {
        filewriter cppwriter(workpath+"/src/"+classname+".cpp");
        translator tran;
        cppwriter.write(tran(R"(#include "%2.h"

%2::%2(%1* parent)
    : %1(parent)
    , ui(new Ui::%2)
{
    ui->setupUi(this);
}

%2::~%2()
{
    delete ui;
})","QWidget",classname));
        filewriter headwriter(workpath+"/src/"+classname+".h");
        headwriter.write(tran(R"(#pragma once
#include <%1>
#include "ui_%2.h"

class %2 : public %1 {
    Q_OBJECT

public:
    %2(%1* parent = nullptr);
    ~%2();

private:
    Ui::%2* ui;
};)","QWidget",classname));
        filewriter uiwriter(workpath+"/src/"+classname+".ui");
        uiwriter.write(tran(R"(<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>%2</class>
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
 </widget>
 <resources/>
 <connections/>
</ui>)","QWidget",classname));
    }
    if (option == "adddialog")
    {
        filewriter cppwriter(workpath+"/src/"+classname+".cpp");
        translator tran;
        cppwriter.write(tran(R"(#include "%2.h"

%2::%2(%1* parent)
    : %1(parent)
    , ui(new Ui::%2)
{
    ui->setupUi(this);
}

%2::~%2()
{
    delete ui;
})","QDialog",classname));
        filewriter headwriter(workpath+"/src/"+classname+".h");
        headwriter.write(tran(R"(#pragma once
#include <%1>
#include "ui_%2.h"

class %2 : public %1 {
    Q_OBJECT

public:
    %2(%1* parent = nullptr);
    ~%2();

private:
    Ui::%2* ui;
};)","QDialog",classname));
        filewriter uiwriter(workpath+"/src/"+classname+".ui");
        uiwriter.write(tran(R"(<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>%2</class>
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
 </widget>
 <resources/>
 <connections/>
</ui>)","QDialog",classname));
    }
    if (option == "addmainwindow")
    {
        filewriter cppwriter(workpath+"/src/"+classname+".cpp");
        translator tran;
        cppwriter.write(tran(R"(#include "%2.h"

%2::%2(%1* parent)
    : %1(parent)
    , ui(new Ui::%2)
{
    ui->setupUi(this);
}

%2::~%2()
{
    delete ui;
})","QMainWindow",classname));
        filewriter headwriter(workpath+"/src/"+classname+".h");
        headwriter.write(tran(R"(#pragma once
#include <%1>
#include "ui_%2.h"

class %2 : public %1 {
    Q_OBJECT

public:
    %2(%1* parent = nullptr);
    ~%2();

private:
    Ui::%2* ui;
};)","QMainWindow",classname));
        filewriter uiwriter(workpath+"/src/"+classname+".ui");
        uiwriter.write(tran(R"(<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>%2</class>
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
</ui>)","QMainWindow",classname));
    }
    if (option == "newwidgetproject")
    {
        projectcreater create;
        create(classname,workpath);
    }
    if (option == "newquickproject")
    {
        qtquickcreater create;
        create(workpath,classname);
    }
    if (option == "addqml")
    {
        
    }
    return 0;
}