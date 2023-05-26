#pragma once
#include <bits/stdc++.h>
#include <direct.h>
#include "translator.h"
#include "filewriter.h"
using namespace std;
class qtquickcreater
{
    void createdir(string path);
    public:
    void operator()(string path,string projectname);
};
