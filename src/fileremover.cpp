#include "fileremover.h"

bool fileremover::test_exist(string path)
{
    FILE* file = fopen(path.c_str(),"r");
    if(file)
    {
        fclose(file);
        return true;
    }
    return false;
}

fileremover::fileremover()
{
}

fileremover::~fileremover()
{
}

int fileremover::operator()(string path)
{
    if(!test_exist(path))
    {
        puts("qtmaster ERROR:The file is not exist!");
        exit(-1);
    }
    return remove(path.c_str());
}