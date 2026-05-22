
#include <cstdlib>
#include <sstream>
#include <string>
#include<unistd.h>

inline int executeCom(std::string& command)
{
    std::stringstream ss(command);
    std::string file;
    ss>>file;

    std::string path_env= std::getenv("PATH");

    std::stringstream sp(path_env);
    std::string currPath;
    while(std::getline(sp,currPath,':'))
    {
        currPath=currPath+"/"+file;
        if(access(currPath.c_str(), X_OK)==0)
        {
            std::system(command.c_str());
            return 1;
        }
    }
    return -1;
}
