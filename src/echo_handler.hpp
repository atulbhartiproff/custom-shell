

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
    for(int i=0;i<inp.size();i++)
    {
        // Space seperating two arguments which arent enclose in quotes
        // We will use every space outside quotes as the breaking point of words
        // Since consecutive quotes is append and space is the only place where we can completely change words
        if(inp[i]==' ' && !(squo || dquo))
        {
            if(arg.size()!=0) finalarg.push_back(arg);
            arg="";
        }
        // Backslash used outside any quotes
        // This would just add the next character into the argument
        else if(i!=inp.size()-1 && inp[i]=='\\' && !(squo || dquo))
        {
            arg+=inp[i+1];
            i++;
        }
        else {
            //If the single quotes is inside the double quote, just append
            if(dquo && inp[i]=='\'') arg+=inp[i];
            //if single quote outside, start the single quotes era
            else if(inp[i]=='\'') squo=!squo;
            //if double quote outside, start the double quotes era
            else if(inp[i]=='\"') dquo=!dquo;
            //If none of them, add literal to the arg
            else arg+=inp[i];
        }
    }
    //Add final word into vector
    if(arg.size()!=0) finalarg.push_back(arg);

    //No argument, direct return
    if(finalarg.size()==0) return 0;

    //Print rest
    else std::cout<<finalarg[0];
    for(int i=1;i<finalarg.size();i++) std::cout<<" "<<finalarg[i];
    std::cout<<std::endl;
    return 1;
}
