#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H
#include <iostream>
#include <stack>
#include <memory>
#include <map>


namespace GeneralFuncitons
{
    bool is_number(const std::string &rawElement)
    {
        try{
            std::stoi(rawElement);
            }
        catch(std::exception &e)
            {
                return false;
            }
        return true;
    }

    int rawInputHandler(std::string inputFromConsole)
    {
        //-1 - user not exist or you type something else to exit
        //-2 - you type q
        //>=0 - user id
        if(is_number(inputFromConsole))
        {   
            return std::stoi(inputFromConsole);
        }
        else
        {
            //it is not number
            if(inputFromConsole =="q" || inputFromConsole=="Q"|| inputFromConsole=="exit")
            {
                return -2;
            }
            else
            {
                return -1;
            }
        }
        
    }
}

#endif
