#pragma once
#include <bits/stdc++.h>
using namespace std;
class fileremover
{
    public:
    bool test_exist(string path);
    fileremover();
    ~fileremover();
    int operator()(string path);
};