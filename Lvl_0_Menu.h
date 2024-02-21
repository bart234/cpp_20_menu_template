#pragma once
#include "MenuTemplate.h"
#include "Lvl_0_Options.h"


class Menu_MainMenu:public MenuTemplate
{
    public:
        Menu_MainMenu():
                        MenuTemplate("Main Menu","Welcome in Play Me")
                        {
                            this->prepare_menu();
                        }
        ~Menu_MainMenu(){};
    private:
        void prepare_menu()
            {                    
                
                this->setAsMainMenu();
                //create option to that menu - already as unique ptr
                std::string t2a ="This is option 1 main menu";
                std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, 1}}; //text, number on the list
                std::unique_ptr<OptionTemplate> ptr_2 {new  Option_2 {"This is option nr 2", 2}};
                std::unique_ptr<OptionTemplate> ptr_3 {new  Option_3 {"This is option nr 3", 3}};
                
                //add unique ptr as a option to menu
                this->option_list[1]=std::move(ptr_1);
                this->option_list[2]=std::move(ptr_2);
                this->option_list[3]=std::move(ptr_3);

                //add back option
                if(!this->isItMainMenu())
                {
                    this->option_list[9]=this->prepare_back_option("'My previous menu'");
                }
                //add quit_app option
                this->option_list[0]=this->prepare_exit_option();                    
            }
    
};
   
