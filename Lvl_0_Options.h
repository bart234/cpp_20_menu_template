#pragma once
#include "OptionTemplate.h"
#include "Lvl_1_Menu.h"


class Option_1:public Option_MainMenu_Template
    {   
        public:
            Option_1(std::string i_description, int i_option_number):
                    Option_MainMenu_Template(i_description,i_option_number)
                    {};
            ~Option_1(){};
        public:
            virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)override
                    {
                        //expected action - preapare menu behind option 1
                        //push it at fron of queue
                        
                        std::cout<<"Custom action at option nr 1 menu 0"<<std::endl;
                         
                        std::shared_ptr<MenuTemplate> main_menu2 {new Menu_at_mm_opt1{}}; //include that menu as file
                        i_stack_of_menus.push(main_menu2);
                        //i_stack_of_menus.top()->show_menu();
                        
                        //selected_option=i_stack_of_menus.front()->manageUserInput();
                        //i_stack_of_menus.front()->launch_selected_option(selected_option,i_stack_of_menus);
                        //i_stack_of_menus.push(std::move(main_menu2));
                        
                        std::cout<<"new menu pushed as a 1th one"<<std::endl;

                    }
    };
    
    class Option_2:public Option_MainMenu_Template
    {   
        public:
            Option_2(std::string i_description, int i_option_number):
                    Option_MainMenu_Template(i_description,i_option_number)
                    {};
            ~Option_2(){};
        public:
            virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)override
                    {std::cout<<"Custom action at option nr 2 menu 0"<<std::endl;}
    };
    
    class Option_3:public Option_MainMenu_Template
    {   
        public:
            Option_3(std::string i_description, int i_option_number):
                    Option_MainMenu_Template(i_description,i_option_number)
                    {};
            ~Option_3(){};
        public:
            virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)override
                    {std::cout<<"Custom action at option nr 3 menu 0"<<std::endl;}
    };
