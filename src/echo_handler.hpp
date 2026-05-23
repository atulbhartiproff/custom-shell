

#include <iostream>
#include <sstream>
#include <string>

inline int echoHandle(std::string& line)
{
    //Simple echo with no quotes in it
    if (line.find("\'") == std::string::npos && line.find("\"") == std::string::npos) {
      std::string word;
      std::stringstream ss(line);
      ss>>word;
      while (ss >> word) {
        std::cout << word << " ";
      }
      std::cout << std::endl;
    }
    //echo with single quotes in it
    else if(line.find("\"") != std::string::npos){
        std::string inp=line.substr(5,line.size());
        std::string word="";
        std::string finalword="";
        bool openQuo=false;
        for(int i=0;i<inp.size();i++)
        {
            if(inp[i]!='\"')
            {
                if(openQuo)
                    word=word+""+inp[i];
                else
                {
                    if(inp[i]==' ' && word.size()!=0)
                    {
                        finalword=finalword+" "+word;
                        word="";
                    }
                    else if(inp[i]==' ')
                    {
                        continue;
                    }
                    else
                    {
                        word=word+""+inp[i];
                    }
                }
            }
            else {
                  if(inp[i+1]=='\"')
                  {
                      i+=1;
                      continue;
                  }
                  else {
                      if(openQuo)
                      {
                          openQuo=false;
                          if(finalword.size()==0) finalword=word;
                          else finalword=finalword+" "+word;
                          word="";
                      }
                      else
                      {
                          openQuo=true;
                          word="";
                      }
                  }
            }
        }
        if(word.size()!=0) finalword=finalword+" "+word;
        std::cout<<finalword<<std::endl;
    }
    else{
        std::string inp=line.substr(5,line.size());
        std::string word="";
        std::string finalword="";
        bool openQuo=false;
        for(int i=0;i<inp.size();i++)
        {
            if(inp[i]!='\'')
            {
                if(openQuo)
                    word=word+""+inp[i];
                else
                {
                    if(inp[i]==' ' && word.size()!=0)
                    {
                        finalword=finalword+" "+word;
                        word="";
                    }
                    else if(inp[i]==' ')
                    {
                        continue;
                    }
                    else
                    {
                        word=word+""+inp[i];
                    }
                }
            }
            else {
                  if(inp[i+1]=='\'')
                  {
                      i+=1;
                      continue;
                  }
                  else {
                      if(openQuo)
                      {
                          openQuo=false;
                          if(finalword.size()==0) finalword=word;
                          else finalword=finalword+" "+word;
                          word="";
                      }
                      else
                      {
                          openQuo=true;
                          word="";
                      }
                  }
            }
        }
        if(word.size()!=0) finalword=finalword+" "+word;
        std::cout<<finalword<<std::endl;
  }
    return 1;
}
