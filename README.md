# qt5master : 一个管理 vscode + qt 项目的命令行工具
## 由于作者学业紧张，目前只支持qt+mingw开发
众所周知，我们可以使用vscode+cmake来开发Qt项目，但是，文件管理非常麻烦，此工具被开发出来的目的就是为了管理项目文件

## 命令格式
```
qtmaster <type> <name>
```
## 支持命令
1. `remove` 移除一个类或窗口
2. `addclass` 新增一个基于`QObject`的类
3. `addwidget addmainwindow adddialog` 新增对应的窗体文件（带ui默认文件）
4. `newwidgetproject` 新建一个项目文件夹（名为`name`），并在内部建立`CMakeList.txt`和`src`源代码文件夹，在代码文件夹中建立`QMainWindow`类型的窗体以及`main.cpp`文件。
5. `newquickproject` 新建一个项目文件夹（名为`name`），并在内部建立`CMakeList.txt`,`qml`和`src`源代码文件夹，在代码文件夹中建立`main.cpp`文件。

## 构建
直接使用`cmake`构建即可。