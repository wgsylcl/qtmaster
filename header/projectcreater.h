#pragma once
#include <bits/stdc++.h>
#include "filewriter.h"
#include <direct.h>
#include "translator.h"

using namespace std;
class projectcreater
{
    public:
    void create_dir(string path);
    void operator()(string projectname,string workpath);
};