#ifndef OPTIONTEMPLATE_H
#define OPTIONTEMPLATE_H
#include "GeneralFunctions.h"


    //pre-declaration
    class MenuTemplate;
    class Menu_MainMenu;
    class Menu_at_mm_opt1;
    
    
    class OptionTemplate
    {                    
        public:
            //std::queue<std::shared_ptr<MenuTemplate>> &main_queue;
        private:
            std::string option_description;
            int option_numer;   
        public:
            virtual void print_me(){std::cout<<"#"<<option_numer<<".  "<<option_description<<std::endl;};
            virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)=0;
            public:
            OptionTemplate(std::string i_description, int i_option_number):
                            option_description{i_description},option_numer{i_option_number}
                            {};
            ~OptionTemplate(){};
            virtual void setNewDescription(std::string new_description){this->option_description=new_description;};
    };

    class Option_MainMenu_Template: public OptionTemplate
    {
        public:
            Option_MainMenu_Template(std::string i_description, int i_option_number):
                            OptionTemplate(i_description,i_option_number)
                            {};
            ~Option_MainMenu_Template(){};
    };
    
    class Option_ToPreviousMenu:public OptionTemplate
    {   
        std::string previus_menu_name;
        public:
            Option_ToPreviousMenu(std::string i_previous_menu_name):
                    OptionTemplate("",9),previus_menu_name{i_previous_menu_name}
                    {
                        std::string temp {"Back to " + std::string{i_previous_menu_name} + " menu."};
                        this->setNewDescription(temp);
                    };
            ~Option_ToPreviousMenu(){};
        public:
            virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)override
                    {std::cout<<"Back to previous menu."<<std::endl;}
    };

    class Option_ExitApp:public OptionTemplate
    {   
        std::string previus_menu_name;
        public:
            Option_ExitApp():
                        OptionTemplate("Quit",0){};
            ~Option_ExitApp(){};
        public:
            virtual void doMyAction(std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)override
                    {std::cout<<"It should close all."<<std::endl;}
    };
    

#endif