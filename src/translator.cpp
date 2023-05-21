#include "translator.h"

string translator::operator()(string str, string arg1, string arg2)
{
    string::size_type pos;
    while((pos = str.find("%1")) != string::npos)
    str.replace(pos,2,arg1);
    while((pos = str.find("%2")) != string::npos)
    str.replace(pos,2,arg2);
    return str;
}
