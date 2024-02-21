#include "OptionTemplate.h"
#ifndef OMENUTEMPLATE_H
#define OMENUTEMPLATE_H

class MenuTemplate
{   
    public:
        //std::map<std::string, std::shared_ptr<MenuTemplate>> &menu_collection;
        //std::queue<std::shared_ptr<MenuTemplate>> &main_queue;
    protected:
        std::string menu_name;
        std::string menu_header;
        std::string previous_menu_tag;            
        bool is_a_main_menu;
    public:
        std::map<int, std::unique_ptr<OptionTemplate>> option_list;

    public:
        MenuTemplate(
                    std::string i_menu_name,std::string i_m_header):
                    menu_name{i_menu_name},menu_header{i_m_header},is_a_main_menu{false}
                    {}
        ~MenuTemplate(){};

        virtual void prepare_menu()=0; 
        virtual void launch_selected_option(int option,std::stack<std::shared_ptr<MenuTemplate>> &i_stack_of_menus)
            {
                this->option_list[option]->doMyAction(i_stack_of_menus);
            } 
        virtual void show_menu()
            {                    
                this->print_header();
                this->print_options(); 
            };
        virtual int manageUserInput()
        {
            std::pair<int,bool> userMenuInput{999,false};

            while(!userMenuInput.second)
            {
                userMenuInput = getUserMenuInput();
                if(!userMenuInput.second)
                    {std::cout<<"Please provide correct value"<<std::endl;}
            }
            return userMenuInput.first;     
        }
        
        private:
            virtual std::string getUserInput(std::string input_description)
            {
                std::string tempRawInput;
                std::cout<<input_description<<std::endl;
                std::cin>>tempRawInput;
                return tempRawInput;
            }
            virtual void print_options()
            {
                for (auto el=  option_list.begin();el!=option_list.end();el++)
                {   
                    if(!el->first==0)
                    {el->second->print_me();};
                }
                option_list.at(0)->print_me();
            };
            virtual void print_header(){std::cout<<this->menu_header<<std::endl;};
            virtual std::pair<int,bool> getUserMenuInput()
                {
                    bool is_correct_input;
                    std::string userInput = getUserInput("Select option:");
                    bool temp1{GeneralFuncitons::is_number(userInput)};
                    if(temp1)
                    {
                        //input is a number
                        if(this->option_list.find(std::stoi(userInput))!=this->option_list.end())
                        {//exist on map list
                            is_correct_input=true;
                        }
                        else
                        {
                            is_correct_input=false;
                        }
                    }
                    else
                    {is_correct_input=false;}

                    if(is_correct_input)
                    {return std::pair<int,bool>{std::stoi(userInput),is_correct_input};}
                    else
                    {return std::pair<int,bool>{-999,is_correct_input};}

                };
        protected:
            virtual void setAsMainMenu(){is_a_main_menu=true;};
            virtual bool isItMainMenu(){return is_a_main_menu;};
            virtual std::string getMenuName(){return this->menu_name;};
            virtual std::unique_ptr<OptionTemplate> prepare_back_option(std::string previous_menu_name)
            {
                std::unique_ptr<OptionTemplate> ptr_2 {new  Option_ToPreviousMenu{previous_menu_name}};
                return ptr_2;
            };
            virtual std::unique_ptr<OptionTemplate> prepare_exit_option()
                {
                    std::unique_ptr<OptionTemplate>exit_ptr{new Option_ExitApp()};
                    return exit_ptr;
                };
        //std::pair<int,bool> convertUserInputIntoValue(std::string convertUserInputIntoValue);
};

// class Menu_MainMenu:public MenuTemplate
// {
//     public:
//         Menu_MainMenu():
//                         MenuTemplate("Main Menu","Welcome in Play Me")
//                         {
//                             this->prepare_menu();
//                         }
//         ~Menu_MainMenu(){};
//     private:
//         void prepare_menu()
//             {                    
                
//                 this->setAsMainMenu();
//                 //create option to that menu - already as unique ptr
//                 std::string t2a ="This is option 1 main menu";
//                 std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, 1}};
//                 std::unique_ptr<OptionTemplate> ptr_2 {new  Option_2 {"This is option nr 2", 2}};
//                 //std::unique_ptr<OptionTemplate> ptr_3 {new  Option_3 {"This is option nr 3", 3}};
                
//                 //add unique ptr as a option to menu
//                 this->option_list[1]=std::move(ptr_1);
//                 this->option_list[2]=std::move(ptr_2);
//                 //this->option_list[3]=std::move(ptr_3);

//                 //add back option
//                 if(!this->isItMainMenu())
//                 {
//                     this->option_list[9]=this->prepare_back_option("'My previous menu'");
//                 }
//                 //add quit_app option
//                     this->option_list[0]=this->prepare_exit_option();                    
//             }
    
// };
    
#endif