
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <string>
#include<fcntl.h>
#include<sys/wait.h>
inline int appendStdout(std::string& input, std::string& target)
{
    std::stringstream ss(target);
    std::string filename;
    ss>>filename;

    int fd=open(filename.c_str(),O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd<0) return -1;
    write(fd,input.c_str(),input.size());
    write(fd,"/n",1);

    close(fd);
    std::cout<<input<<std::endl;
    return 1;
}
