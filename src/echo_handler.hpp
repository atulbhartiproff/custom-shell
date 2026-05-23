

#include <iostream>
#include <string>
#include <vector>

inline int echoHandle(std::string& line)
{
    std::string inp=line.substr(5,line.size());
    bool squo=false,dquo=false;
    //Boolean flags for single quote is open
    // or
    //double quotes is opened
    std::string arg="";
    std::vector<std::string> finalarg;
    for(int i=0;i<line.size();i++)
    {
        // Space seperating two arguments which arent enclose in quotes
        if(inp[i]==' ' && !(squo || dquo))
        {
            if(arg.size()!=0) finalarg.push_back(arg);
            arg="";
        }
        // Backslash used outside any quotes
        else if(inp[i]=='\\' && !(squo || dquo))
        {
            arg+=inp[i+1];
            i++;
        }
        else {
            if(dquo && inp[i]=='\'') arg+=inp[i];
            else if(inp[i]=='\'') squo=!squo;
            else if(inp[i]=='\"') dquo=!dquo;
            else arg+=inp[i];
        }
    }

    if(finalarg.size()==0) return 0;
    else std::cout<<finalarg[0];
    for(int i=1;i<finalarg.size();i++) std::cout<<" "<<finalarg[i];
    return 1;
}
