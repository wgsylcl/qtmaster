#pragma once
#include <bits/stdc++.h>
#include "filewriter.h"
#include <windows.h>
#include "translator.h"

using namespace std;
class projectcreater
{
    public:
    void create_dir(string path);
    void operator()(string projectname,string workpath);
};