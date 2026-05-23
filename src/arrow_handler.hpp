
#include <fstream>
#include<unistd.h>
#include <cstdlib>
#include <sstream>
#include <string>
inline int arrowHandle(std::string& input, std::string& target)
{
    std::stringstream ss(target);
    std::string filename;
    ss>>filename;

    std::string filepath=std::getenv("PATH");
    std::stringstream sp(filepath);
    std::string curr;
    while(std::getline(sp,curr,':'))
    {
        curr=curr+filename;
        if(access(curr.c_str(),W_OK)!=0)
        {
            std::ofstream myFile;
           myFile.open(filename);
        }
            std::ofstream file(filename);
            file<<input;
            return 1;
    }
    return -1;
}
