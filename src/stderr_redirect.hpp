
#include<unistd.h>
#include <sstream>
#include <string>
#include<fcntl.h>
#include<sys/wait.h>
inline int stderrRedirect(std::string& input, std::string& target)
{
    std::stringstream ss(target);
    std::string filename;
    ss>>filename;

    int fd=open(filename.c_str(),O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd<0) return -1;
    dup2(fd, STDERR_FILENO);
    close(fd);
    return 1;
}
