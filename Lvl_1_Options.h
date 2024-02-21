#pragma once
#include "OptionTemplate.h"

class Option_mm1_o1:public Option_MainMenu_Template
{   
    public:
        Option_mm1_o1(std::string i_description, int i_option_number):
                Option_MainMenu_Template(i_description,i_option_number)
                {};
        ~Option_mm1_o1(){};
    public:
        virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_main_queue)override
                {std::cout<<"Custom action at Option_mm1_o1 option"<<std::endl;}
};

class Option_mm1_o2:public Option_MainMenu_Template
{   
    public:
        Option_mm1_o2(std::string i_description, int i_option_number):
                Option_MainMenu_Template(i_description,i_option_number)
                {};
        ~Option_mm1_o2(){};
    public:
        virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_main_queue)override
                {std::cout<<"Custom action at Option_mm1_o2 option"<<std::endl;}
};