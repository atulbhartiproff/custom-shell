
#include <cstdlib>
#include <sstream>
#include <string>
#include<unistd.h>

inline int executeCom(std::string& command)
{
    std::string file;
    if(command[0]!='\'' && command[0]!='\"'){
    std::stringstream ss(command);
    ss>>file;
    }
    else {
        bool squo=false,dquo=false;
        if(command[0]=='\'') squo=true;
        else dquo=true;

        for(int i=1;i<command.size();i++)
        {
            if(command[i]=='\\') file+=command[i]+'\\';
            if(dquo)
            {
                if(command[i]=='\"') break;
                else file+=command[i];
            }
            else {
                if(command[i]=='\'') break;
                else file+=command[i];
            }
        }
    }
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
