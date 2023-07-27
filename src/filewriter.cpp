#include "filewriter.h"

filewriter::filewriter(string path)
{
    if(test_exist(path))
    {
        puts("qtmaster ERROR:File exists.");
        exit(-1);
    }
    fout.open(path,ios::out);
    if(!fout.is_open())
    {
        puts("qtmaster ERROR:Can not create file!");
        exit(-1);
    }
}

filewriter::~filewriter()
{
    if(fout.is_open())
    fout.close();
}

void filewriter::write(string str)
{
    fout<<str;
}

bool filewriter::test_exist(string path)
{
    FILE* file = fopen(path.c_str(),"r");
    if(file)
    {
        fclose(file);
        return true;
    }
    return false;
}
