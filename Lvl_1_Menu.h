#pragma once
#include "MenuTemplate.h"
#include "Lvl_1_Options.h"


//add pre-declaration  of that menu at OptionTemplate.h
 
class Menu_at_mm_opt1:public MenuTemplate
{
    public:
        Menu_at_mm_opt1():MenuTemplate("Second Menu","Welcome in second menu")
                        {
                            this->prepare_menu();
                        }
        ~Menu_at_mm_opt1(){};
    private:
        void prepare_menu()
            {                    
                //this->setAsMainMenu();
                std::string t2a ="opt1 menu lvl1";
                std::unique_ptr<OptionTemplate> ptr_1 {new  Option_mm1_o1 {t2a, 1}};
                std::unique_ptr<OptionTemplate> ptr_2 {new  Option_mm1_o2 {"opt 2 menu lvl 1", 2}};
                
                //add unique ptr as a option to menu
                this->option_list[1]=std::move(ptr_1);
                this->option_list[2]=std::move(ptr_2);

                //add back option
                if(!this->isItMainMenu())
                {
                    this->option_list[9]=this->prepare_back_option("'My previous menu'");
                }
                //add quit_app option
                this->option_list[0]=this->prepare_exit_option();                    
            }        
};
// data moved because double import 