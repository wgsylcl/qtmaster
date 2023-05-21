#pragma once
#include <bits/stdc++.h>
using namespace std;
class filewriter
{
    public:
    filewriter(string path);
    ~filewriter();
    void write(string str);
    bool test_exist(string path);
    private:
    ofstream fout;
};