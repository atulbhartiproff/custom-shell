
#include <cstdlib>
#include <iostream>
#include <sstream>
#include<string>
#include <unistd.h>

inline int typeCom(std::string& command)
{

    std::stringstream ss(command);
    std::string file;
    ss>>file; ss>>file;

    std::string pathnames= std::getenv("PATH");
    std::stringstream sp(pathnames);
    std::string currPath;
    while(std::getline(sp,currPath,':'))
    {
        currPath=currPath+"/"+file;
        if(access(currPath.c_str(), X_OK)==0)
        {
            std::cout<<file<<" is "<<currPath<<std::endl;
            return 0;
        }
    }
    return -1;
}
