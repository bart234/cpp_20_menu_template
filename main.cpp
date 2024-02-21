#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <array>
#include <numeric>
#include <deque>
#include <cctype>
#include <list>
#include <forward_list>
#include <iterator> //required for user std::advance function
#include <cstring>
#include <memory>
#include <unistd.h>
#include "Lvl_0_Menu.h"



using namespace std;


namespace STL_List_challange
{
    /*
    Main task: (bigger then challange from cours)
    create mp3 player menu with stl::list
    menu should : 
        user selection        
            play my playlist 
                select track it to play from there
                play current song
                play next song
                play previous song
                during playing:
                    pause
                    play
                    stop
            Modify my playlist 
                remove track, 
                change order
            Add new track from my storage
                -display availible music,
                    -select track to add
                -display my current playlist 
                    -select place where to put new track
                        -before/after track number
                        -add upfront/on end               
                

    */
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

   class MusicObj
   {
    private:        
        std::string name;
        std::string artist;
        double length_in_sec;
        int tagId;
    public:
        MusicObj(std::string i_name, std::string i_artist, double i_length_in_sec):
                name{i_name},artist{i_artist},length_in_sec{i_length_in_sec}{};
        ~MusicObj()=default;  
        void setTagId(int id){this->tagId=id;};
        int getTagId(){return this->tagId;};
        const std::string &getName (){return this->name;};      
   };

   class Playlist
   {
    private:
        std::list<MusicObj> availibe_music{};
    public:
        Playlist(){};
        ~Playlist()=default;
        void addNewTrack(MusicObj &m1)
            {              
                availibe_music.push_back(m1);
            };
        void addNewTrack(std::string i_name, std::string i_artist, double i_length_in_sec)
            {              
                availibe_music.emplace_back(i_name,i_artist,i_length_in_sec);
            };

        void printAllTracks()
        {
            int i{1};
            for(auto &el: availibe_music)
            {
                el.setTagId(i);
                std::cout<<"#"<<el.getTagId()<< " " <<el.getName()<<std::endl;
                i++;
            };         
        }
   };
   
   class User
   {
    private:
        std::string name;
        int user_id;
        Playlist saved_playlist;
    public:
    User(std::string i_name,int i_user_id):name{i_name},user_id{i_user_id}{};
    ~User(){};
    void temp_create_user_playlist()
        {
            saved_playlist.addNewTrack("Paciorek","Delta",84);
            saved_playlist.addNewTrack("Kodak Kodak","Beta",21);
            saved_playlist.addNewTrack("Swan","Lake",54);
            saved_playlist.addNewTrack("Davy","Jones",34);
        }
    Playlist &getUserPlaylist(){return saved_playlist;};
    //Playlist *getUserPlaylist(){return &saved_playlist;};
    std::string getUserName() {return this->name;};
    int getUserId(){return this->user_id;};
    bool operator ==(const User&rhs) const{return this->user_id==rhs.user_id;};
    bool operator ==(const int user_id) const{return this->user_id==user_id;};

   };

   class Menu
   {
    private:
        std::shared_ptr<std::list<std::shared_ptr<User>>> user_list;
        std::shared_ptr<Playlist> general_music_storage;
        void print_users_as_a_list(){for(auto &el:*user_list){cout<<el->getUserId()<<" "<<el->getUserName()<<endl;}}
        bool quit_flag{false};
        std::shared_ptr<User> current_user{nullptr};


        bool is_user_already_set{false};
        
        User &get_currentuser(){return *this->current_user;};
        bool isSelectedUserIdExist(int user_id_to_find)
        {
            for(auto it = user_list->begin();it!=user_list->end(); it++)
            {
                if((*it)->getUserId() == user_id_to_find)
                {return true;}
            }
            return false;
            /*std::list<std::shared_ptr<User>>::iterator it = std::find(user_list->begin(),
                                                                        user_list->end(),
                                                                        user_id_to_find);
            if (it!= user_list->end()){
                return true;
            }else{
                return false;}*/
        }

        void setCurrentUser(int user_id_to_find)
        {                
            for(auto it = user_list->begin();it!=user_list->end(); it++)
            {
                cout<<(*it)->getUserName()<<endl;
            }
            /*
            std::list<std::shared_ptr<User>>::iterator it = std::find(user_list->begin(),
                                                                        user_list->end(),
                                                                        user_id_to_find);               
            current_user = std::make_shared<User>(*it);
            */
        }

    public:
        /*
        Menu(std::shared_ptr<std::list<std::shared_ptr<User>>> in_user_list):
            user_list{in_user_list}
            {}
        */
        
        Menu(std::shared_ptr<std::list<std::shared_ptr<User>>> in_user_list,
            std::shared_ptr<Playlist> in_general_music_storage):
            user_list{in_user_list},
            general_music_storage{in_general_music_storage}            
            {}
        
        ~Menu()=default;
        bool is_user_set(){return this->is_user_already_set;};
        void run_menu()
        {
            while(true)
            {
                menu_selectUserMenu();
                //if(this->quit_flag){break;}
                /*if(this->is_user_already_set)
                {

                }*/
                //if(this->quit_flag){break;}
            }
        }

        void menu_selectUserMenu()
        {
            cout<<"Hello"<<endl;
            cout<<"Select user from list below or create ne one"<<endl;
            while(this->current_user==nullptr)
            {   
                print_users_as_a_list();
                
                cout<<"Type user id:";
                std::string userIdRaw;   
                cin>>userIdRaw;

                if(is_number(userIdRaw))
                {
                    /*if(isSelectedUserIdExist(std::stoi(userIdRaw)))
                    {

                        cout<<"User exist test"<<endl;
                        setCurrentUser(std::stoi(userIdRaw));
                        try
                        {
                            cout<<"User " <<this->current_user->getUserName() << " selected"<<endl;
                            this->is_user_already_set=true;
                        }catch(std::exception &e)
                        {
                            cout<<"Error12: user not set"<<endl;
                            cout<<"Please type user id to load user settings or 'q' to exit"<<endl;
                        }
                        
                    }
                    else
                    {
                        cout<<"User doesnt exit. Please try again."<<endl;
                        cout<<"For quit please press q"<<endl;
                    };*/
                }
                else
                {   
                    if(userIdRaw=="q" or userIdRaw=="Q")
                    {
                        cout<<"Applicaton terminated."<<endl;
                        this->quit_flag=true;
                        break;               
                    }
                    else
                    {
                        cout<<"Please type user id to load user settings or 'q' to exit"<<endl;
                    }
                }
            }
        }

        void showSelectUserMenu(std::list<User> &user_list)        
        {
            cout<<"Hello"<<endl;
            cout<<"Select User from list below or create ne one"<<endl;
            /*

            while(this->current_user==nullptr)
            {
                for(auto &el:user_list)
                    {
                        cout<<el.getUserId()<<" "<<el.getUserName()<<endl;
                    }
                cout<<"Type iser id:";
                std::string userIdRaw;   
                cin>>userIdRaw;

                if(is_number(userIdRaw))
                {
                    if(setCurrentUser(std::stoi(userIdRaw),user_list))
                    {
                        cout<<"User " <<this->current_user->getUserName() << " selected"<<endl;

                        this->is_user_already_set=true;
                    }
                    else
                    {
                        cout<<"User doesnt exit. Please try again."<<endl;
                        cout<<"For quit please press q"<<endl;
                    };
                }
                else
                {
                    if(userIdRaw=="q" or userIdRaw=="Q")
                    {
                        cout<<"Applicaton terminated."<<endl;
                        break;               
                    }
                    else
                    {
                        cout<<"Please type user id to load user settings or 'q' to exit"<<endl;
                    }
                }
            }*/
        }
        
        int show_specified_menu(int menu_number)
        {
            switch (menu_number)
            {
            case 1:
                { 
                    cout<<"menu option 1"<<endl;
                    auto aa = current_user->getUserPlaylist();
                    aa.printAllTracks();
                    break;
                }
            case 2:
                {//Play my playlist"<<endl;
                    cout<<"menu option 2"<<endl;
                    break;
                }
            case 3:
                {//Play my playlist"<<endl;
                    cout<<"menu option 3"<<endl;
                    break;
                }
            case 4:
                {//Play my playlist"<<endl;
                    cout<<"menu option 4"<<endl;
                    break;
                }
            case 5:
                {
                    cout<<"menu option 5"<<endl;
                    return 0;
                }
            }
        }

        int showUsersActions()
        {
            std::string rawOptionNumber;
            while(true)
            {
                cout<<"Hello "<< this->current_user->getUserName()<<endl;
                cout<<"1. Play my playlist"<<endl;
                cout<<"2. Modify my playlist (remove track, change order)"<<endl;
                cout<<"3. Add new track from my storage"<<endl;
                cout<<"4. Back to user selection"<<endl;
                cout<<"5. Quit"<<endl;
                cout<<"------------------------------------------------------"<<endl;
                cout<<"Select option number:";
                cin>>rawOptionNumber;
                if(is_number(rawOptionNumber))
                {
                    int temp_a = std::stoi(rawOptionNumber);
                    int inner_menu_result = show_specified_menu(temp_a);
                    //if user wan to quit app
                    if(inner_menu_result==0)
                    {
                        cout<<"Application terminate a1"<<endl;
                        break;
                    }

                }else
                {
                    if(rawOptionNumber=="q" || rawOptionNumber=="Q")
                    {
                        cout<<"Application terminate a0"<<endl;
                        break;
                    }
                }
            }
        }
   };

   class PlayMenu
   {
    private:
        MusicObj *track{nullptr};
    public:
        PlayMenu(MusicObj *i_track):track{i_track}{};
        ~PlayMenu()
        {
            track = nullptr; 
            delete track;
        }
            
   };

    class SubMenuPlayMyPlayList
    {
        private:
            Playlist *user_playlist{nullptr};
            Menu *main_menu{nullptr};
            int showCurrentUserPLayLIst()
                {
                    cout<<"--------Playlist-----------"<<endl;
                    user_playlist->printAllTracks();
                };
        public:
            SubMenuPlayMyPlayList(Playlist *i_user_playlist):
                            user_playlist{i_user_playlist}{};
            //SubMenuPlayMyPlayList(Playlist *i_user_playlist, Menu *i_main_menu):
             //                user_playlist{i_user_playlist},main_menu{i_main_menu}{};
            ~SubMenuPlayMyPlayList()
            {
                user_playlist = nullptr;
                delete user_playlist;
            };

            void ShowMenuPlayMyPlayList()
            {
                //IN PROGRESS
                int max_number_of_track = 0;
                max_number_of_track = showCurrentUserPLayLIst();
                cout<<"Press enter to start from track 1 or "<<endl;
                cout<<"put a number to start from that track"<<endl;
                std::string rawInput;
                cin>>rawInput;
                if(is_number(rawInput))
                {
                   // PlayMenu p(std:stoi(rawInput));
                   // p.play();
                }

            }


    };

    
    Playlist create_music_storage()
    {
        
        MusicObj m1{"Haba Haba","Abba",23};
        MusicObj m2{"Kodak Kodak","Beta",21};
        MusicObj m3{"Chulk Chulk","Gamma",34};
        /*
        std::list<MusicObj> availibe_music{};
        availibe_music.emplace_back("Haba Haba","Abba",23);
        availibe_music.emplace_back("Kodak Kodak","Beta",21);
        availibe_music.push_back(m3);
        */
        //for(auto &el:availibe_music){std::cout<<el.getName()<<std::endl;}

        Playlist a1;
        //we load availible playlist from source
        a1.addNewTrack(m1);
        a1.addNewTrack(m2);
        a1.addNewTrack(m3);
        a1.addNewTrack("Paciorek","Delta",84);
        a1.addNewTrack("Rolling","Stones",23);
        a1.addNewTrack("Swan","Lake",54);
        a1.addNewTrack("Davy","Jones",34);
        a1.addNewTrack("Black","Pearl",43);
        return a1;
    }


    void class_test1()
    {
        //music storage
        Playlist track_storage =create_music_storage();
        std::shared_ptr<Playlist> track_storage_ptr = std::make_shared<Playlist>(track_storage);        

        //shp pointer approach
        std::shared_ptr<std::list<std::shared_ptr<User>>>user_list_shr_ptr;
        std::shared_ptr<User> ala_2 = std::make_shared<User>("Ala_2",32);
        std::shared_ptr<User> becia_2 = std::make_shared<User>("Beta_2",32);
        user_list_shr_ptr->emplace_back(std::make_shared<User>("Ala_3",32));
        user_list_shr_ptr->push_back(ala_2);
        user_list_shr_ptr->push_back(becia_2);
        ala_2->temp_create_user_playlist();
        becia_2->temp_create_user_playlist();

        //shp list test
        user_list_shr_ptr->front()->getUserPlaylist().printAllTracks();

        Menu m_2(user_list_shr_ptr,track_storage_ptr);  
        m_2.run_menu();

        //old approach - there was a problem with user list
        {
            /*
            std::list<User> user_list;
            User ala("Ala",23);
            User becia("Beata",25);
            ala.temp_create_user_playlist();
            becia.temp_create_user_playlist();
            
            user_list.push_back(ala);
            user_list.push_back(becia);

            
            //test user playlist print
            auto a = ala.getUserPlaylist();
            a.printAllTracks();
            */
            //auto &a =user_list.front();
            //a.getUserPlaylist().printAllTracks();
        }
        
        /*Menu m(track_storage);
        m.showSelectUserMenu(user_list);
        if(m.is_user_set())
        {
            m.showUsersActions();
        }*/
            
        
    }

 








};

namespace STL_List_challange_simple_mode
{
  /*
  Main task: (bigger then challange from cours)
    create mp3 player menu with stl::list
    menu should : 
        user selection                                      <done>
            my playlists                                    <done>
                play my playlist                            <done>
                    play from first song                    <done>
                    play next song                          <done>
                    play previous song                      <done>
                    play again                              <done>
                    jump to song <n>                        <done>
                    back to previous menu                   <done>
                    close app                               <done>

                show my playlist                            <done>

                modify my playlist                          <done>
                    (select track and manipulate with it) 
                    move to position <n> -1                 <done>
                    move to position <n> +1                 <done>
                    remove from playlist                    <done>
                    back to previous menu                   <done>
                    close app                               <done>

            music storage
                show music storage 
                ( display all and makr what have on you  list and where)
                (select track and manipulate with it) 
                add to my playlist at begning
                add to my playlist at end
                after track number
                back to previous menu
                close app

*/


    class Playlist
    {
        private:
        std::list<std::string> basic_playlist;
        public:
        void loadAvailibleMusic();
        void printPlaylist(bool show_id);
        void printComparePlaylist(bool show_id,std::list<std::string> &userPls);
        std::string puttTrackIdReturnTrackName(int track_id);
        std::list<std::string> getPlayList(){return basic_playlist;};        
    };

    std::string Playlist::puttTrackIdReturnTrackName(int track_id)
    {
        int temp_id{0};
        for(auto &el:this->basic_playlist)
            {
                if(track_id==temp_id)
                    return el;
                temp_id++;
            }
        return "None";
    }


    void Playlist::printComparePlaylist(bool show_id,std::list<std::string> &userPls)
    {
        int temp_id{0};
        for(auto &el:this->basic_playlist)
        {                            
            std::list<std::string>::iterator it = std::find(userPls.begin(), userPls.end(),el);
            if(it!= userPls.end())
            {
                cout<<temp_id<< ". onpls  " <<el<<endl;                           
                temp_id++;
            }else
            {
                cout<<temp_id<< ".        " <<el<<endl;                           
                temp_id++;
            }
        }
    }

    void Playlist::printPlaylist(bool show_id=false)
    {
        if(show_id==false )
        {
            for(auto &el:this->basic_playlist)
                cout<<el<<endl;
        }
        else
        {   int temp_id{0};
            for(auto &el:this->basic_playlist)
                {                            
                    cout<<temp_id<< ".      " <<el<<endl;                           
                    temp_id++;
                }
        }
    };

    void Playlist::loadAvailibleMusic()
    {
        basic_playlist.push_back("Aquarius-09");
        basic_playlist.push_back("Pisces-02");
        basic_playlist.push_back("Aries-03");
        basic_playlist.push_back("Tourus-04");
        basic_playlist.push_back("Gemini-5");
        basic_playlist.push_back("Cancer-6");
        basic_playlist.push_back("Leo-7");
        basic_playlist.push_back("Virgo-8");
        basic_playlist.push_back("Libra-9");
        basic_playlist.push_back("Scorpius-10");
        basic_playlist.push_back("Sagittarius-11");
        basic_playlist.push_back("Capricornus-12");
        basic_playlist.push_back("One Kodak-Beta-21");
    }

    
    class User_simple
    {
        private:
            std::string name;
            int user_id;
            //Playlist saved_playlist;
            std::list<std::string> basic_playlist;
        public:
        
        User_simple(std::string i_name,int i_user_id):name{i_name},user_id{i_user_id}
        {
                basic_playlist.push_back("Zero-Delta-84");
                basic_playlist.push_back("One Kodak-Beta-21");
                basic_playlist.push_back("Two-Lake-54");
                basic_playlist.push_back("Tree-Jones-34");
        };
        ~User_simple(){};
        //operators - currently usefull, list just keep string, not a opj with diff elements
        //bool operator ==(const std)


        std::string getUserName() {return this->name;};
        int getUserId(){return this->user_id;};

        std::list<std::string> & user_playlist(){return this->basic_playlist;};
        void printUserPlaylist(bool show_id=false,int replace_id_by_arrow_at_track_number =-1)
            {
                if(show_id==false && replace_id_by_arrow_at_track_number == -1)
                {
                    for(auto &el:this->basic_playlist)
                        cout<<el<<endl;
                }
                else
                {   int temp_id{0};
                    for(auto &el:this->basic_playlist)
                        {
                            if(replace_id_by_arrow_at_track_number == -1)
                            {
                                cout<<temp_id<< ".      " <<el<<endl;
                            }
                            else
                            {   
                                if(temp_id==replace_id_by_arrow_at_track_number)
                                {
                                    cout<<"------>"<< " " <<el<<endl;
                                    
                                }
                                else
                                {
                                    cout<<temp_id<< ".      " <<el<<endl;
                                }                                
                            }
                            temp_id++;
                        }
                }
            };


    
    
        std::string getTrackIdReturnTrackName(int track_id)
            {
                int temp_id{0};
                for(auto &el:this->basic_playlist)
                    {
                        if(track_id==temp_id)
                            return el;
                        temp_id++;
                    }
                return "None";
            }
        

        /*void temp_create_user_playlist()
            {
                saved_playlist.addNewTrack("Paciorek","Delta",84);
                saved_playlist.addNewTrack("Kodak Kodak","Beta",21);
                saved_playlist.addNewTrack("Swan","Lake",54);
                saved_playlist.addNewTrack("Davy","Jones",34);
            }
        Playlist &getUserPlaylist(){return saved_playlist;};*/
    };

    void songPlaying(std::string songSong, int duration)
    {
        //#include <unistd.h>
        for ( int a = duration;a>0;--a)
        {
            cout<<a<<" " << songSong<<endl;
            sleep(1);
        }
    }

    
    std::string putTrackIdReturnTrackName(int track_id,std::list<std::string> &l)
    {
        //todo: redudance same function in user class
        int temp_id{0};
        for(auto &el:l)
            {
                if(track_id==temp_id)
                    return el;
                temp_id++;
            }
        return "none";
    }

    bool swapElementsAtList(std::list<std::string> & string_list,
                                std::string el_to_switch_1,
                                std::string el_to_switch_2)
        {
            try
            {
                std::list<std::string>::iterator it = std::find(string_list.begin(),string_list.end(),el_to_switch_1);
                std::list<std::string>::iterator it2 = std::find(string_list.begin(),string_list.end(),el_to_switch_2);
                if(it==string_list.end() || it2==string_list.end())
                    return false;
                std::swap(*it,*it2);
                return true;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            
        }
    
    bool swapElementsAtList(std::list<std::string> & string_list,
                            unsigned int pos_of_el1,
                            unsigned int pos_of_el2)
    {
        try
        {
            int temp_offset;
            //idiot case                
            //
            //||
            unsigned int size_list =static_cast<unsigned int>(string_list.size());
            size_list -=1;
            if(pos_of_el1<0  ||pos_of_el2<0 || pos_of_el1==pos_of_el2||pos_of_el2> size_list||pos_of_el1> size_list)
                return false;
            
            if(pos_of_el1>pos_of_el2)
            {
                std::swap(pos_of_el1,pos_of_el2);
            }            
            std::list<std::string>::iterator it = std::find(string_list.begin(),string_list.end(),putTrackIdReturnTrackName(pos_of_el1,string_list)); 
            temp_offset = pos_of_el2-pos_of_el1;
            std::list<std::string>::iterator it2 =it;
            std::advance(it2,temp_offset);
            std::swap(*it,*it2);
            return true; 
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }        
    }

    std::vector<int> vector_int_from_cin_getline(bool remove_duplicates=false)
    {
        std::vector<int> ab;
        std::set<int> without_duplicates;
        std::string rawUserInput;
        std::getline(std::cin >> std::ws, rawUserInput);
                    
        std::istringstream iss{rawUserInput};
        std::string s;
        while(std::getline(iss,s,' '))
        {
            try
                {
                    if(remove_duplicates)
                    {without_duplicates.insert(std::stoi(s));}
                    else
                    {ab.push_back(std::stoi(s));};
                    
                }
            catch(const std::exception& e)
                {
                    cout << s<<" will be skipped"<<endl;
                }
        }
        if(remove_duplicates)
        {
            for(auto el:without_duplicates)
            {ab.push_back(el);}
        }

        return ab;
    }

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

    class App
    {
        private:
            bool flag_close_me{false};
            bool flag_isuser_selected{false};
            bool flag_already_logged{false};
            Playlist availible_music;
            
            std::shared_ptr<User_simple> current_user{nullptr};
            void menu_select_user();
            void menu_select_general_action();
            void menu_showUserPlaylist();
            void menu_editUserPlaylist();
            void menu_editUserPlaylist_trackMoveMenu(int &selectedTrackId);
            void menu_playMyPlaylist();
            void menu_showAvailibleTracks();
            void menu_add_track_from_storage_to_user_pls();

        public:
            App(){};
            ~App()=default;
            std::list<User_simple> container_user_list;
            void app_run();
            
    };

    void App::app_run()
    {
        //load users from source
        this->container_user_list.emplace_back("Aga",10);
        this->container_user_list.emplace_back("Beata",8);

        while(!flag_close_me)
        {
            //TODO:fix that ifs
            //0 0 not logged, not user selected
            if(!this->flag_isuser_selected && !this->flag_already_logged)
            {
                menu_select_user();
                if(flag_close_me)break;
            }
            
            // 1 1 logged and user selected
            if(this->flag_isuser_selected && this->flag_already_logged)
            {
                cout<<"User is already selected, do you want switch it?Y/N and q for close app"<<endl;
                std::string tempInput;
                cin>>tempInput;
                if(tempInput=="y"||tempInput=="Y")
                {
                    this->flag_isuser_selected=false;
                    this->flag_already_logged=false;
                    this->current_user=nullptr;
                }
                else if (tempInput=="q" || tempInput=="Q")
                {
                    this->flag_close_me=true;
                    this->flag_isuser_selected=false;
                    this->flag_already_logged=false;
                }
                else
                {
                    this->flag_already_logged=false;
                }
            }

            //1 0
            if(this->flag_isuser_selected and !this->flag_already_logged)
            {
                cout<<"Hello "<<this->current_user->getUserName()<< " select ation"<<endl;
                menu_select_general_action();
                this->flag_already_logged=true;
                if(flag_close_me)break;
            }
        }
    } 

    void App::menu_select_general_action()
    {
        bool quit_me{false};
        std::string rawUserInput;
        int userInput;
        while(!quit_me)
        {
            cout<<"--------------------------"<<endl;
            cout<<"   General menu    "<<endl;
            cout<<"1. Show my playlist"<<endl;
            cout<<"2. Edit my playlist"<<endl;
            cout<<"3. Play my playlist"<<endl;
            cout<<"4. Show availible tracks"<<endl;
            cout<<"9. Back to previous menu"<<endl;
            cout<<"0. To close app"<<endl;
            cout<<"Type here:";
            cin>>rawUserInput;
            userInput=rawInputHandler(rawUserInput);
            if(userInput==0 || userInput == 9|| userInput <0) 
                {
                    quit_me =true;
                    if(userInput==0)this->flag_close_me=true;
                }
            if(userInput==1)
            {
                menu_showUserPlaylist();
            }
            else if(userInput ==2)
            {
                menu_editUserPlaylist();
                if(flag_close_me)break;
            }
            else if(userInput ==3)
            {
                menu_playMyPlaylist();
                if(flag_close_me)break;
            }
            else if(userInput ==4)
            {
                menu_showAvailibleTracks();
                if(flag_close_me)break;
            }
        }
    }

    void App::menu_showAvailibleTracks()
    {
        bool quit_me{false};
        std::string rawUserInput;
        int userInput;
        int track_id = 0;
        availible_music.loadAvailibleMusic();

        while(!quit_me)
        {
            availible_music.printComparePlaylist(true,current_user->user_playlist());

            cout<<"--------------------------"<<endl;
            cout<<"   General menu    "<<endl;
            cout<<"1. Add to track/trackt to playlist "<<endl;
            cout<<"9. Back to previous menu"<<endl;
            cout<<"0. To close app"<<endl;
            cout<<"Type here:";
            cin>>rawUserInput;
            userInput=rawInputHandler(rawUserInput);

            if(userInput==0 || userInput == 9|| userInput <0) 
            {
                quit_me =true;
                if(userInput==0)this->flag_close_me=true;
            }
            if(userInput==1)
            {
                menu_add_track_from_storage_to_user_pls();     
                if(userInput==0)this->flag_close_me=true;
            }
        }
    }

    void App::menu_add_track_from_storage_to_user_pls()
    {
        cout<<endl;
        availible_music.printComparePlaylist(true,current_user->user_playlist());

        bool quit_me{false};
        std::string rawUserInput;
        int userInput;
        int track_id = 0;
        std::vector<int> vector_with_ids;
        //while(!quit_me)
        //{
        cout<<"--------------------------"<<endl;
        cout<<"Type tracks id with space between, to add them at the end of you playlist"<<endl;
        cout<<"Not corrected id will be skipped"<<endl;
        cout<<"Provide space or leave empty to back to previous menu"<<endl;
        cout<<"Type here:";
        while(true)
        {   
            vector_with_ids = vector_int_from_cin_getline(true);
            for(int &id: vector_with_ids)
            {
                std::string result_find {availible_music.puttTrackIdReturnTrackName(id)};
                if(result_find != "None")
                {
                    current_user->user_playlist().push_back(result_find);
                }
                else
                {
                    cout<<"Element "<<id<<" skipped"<<endl;
                }
            }
            break;

        }



        //}
    }

    void App::menu_playMyPlaylist()
    {   
        bool quit_me{false};
        std::string rawUserInput;
        int userInput;
        int track_id = 0;
        cout<<endl;
        while(!quit_me)
        {
            cout<< "---------------------------------------"<<endl;
            cout<<current_user->getUserName()<<" 's playlist"<<endl;

            current_user->printUserPlaylist(true,track_id);
            cout<<endl;
            songPlaying(current_user->getTrackIdReturnTrackName(track_id),4);
            cout<<endl;
            cout<<"Option: 1->next, 2->previous, 3-> again, 4->selected id, 9->Previous menu, 0->Quit app "<<endl;
            cout<<"Type here:";
            cin>>rawUserInput;
            userInput=rawInputHandler(rawUserInput);

            if(userInput==0 || userInput == 9|| userInput <0) 
                {
                    quit_me =true;
                    if(userInput==0)this->flag_close_me=true;
                }
            if(userInput==1)
            {
                //1->next,
                if(track_id==(current_user->user_playlist().size()-1))
                {
                    track_id = -1;
                }
                track_id++;
            }
            else if(userInput ==2)
            {
                //2->previous
                if(track_id==0)
                {
                    track_id = current_user->user_playlist().size();
                }
                track_id--;
            }
            else if(userInput ==3)
            {
                //3->again 
                //just nothing
            }
            else if(userInput ==4)
            {
                cout<<"Put id between 0 and "<<current_user->user_playlist().size()-1<<endl;
                std::string rawUserInput_select_id;
                cin>>rawUserInput_select_id;
                int userInput_select_id;        
                userInput_select_id=rawInputHandler(rawUserInput_select_id);
                //-1 - user not exist or you type something else to exit
                //-2 - you type q
                //>=0 - user id
                if(userInput_select_id<0|| userInput_select_id>current_user->user_playlist().size()-1)
                {
                    cout<<"Track doesnt exist, I will play again last one"<<endl;                    
                }
                else
                {
                    track_id=userInput_select_id;
                }


                //3->selected id
            }
        }

        

    }

    void App::menu_editUserPlaylist()
    {
        std::string rawUserInput;
        int userInput=rawInputHandler(rawUserInput);
        cout<<endl;
        cout<<"---------" <<current_user->getUserName()<< "'s playlist ----------"<<endl;
        current_user->printUserPlaylist(true);
        cout<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"First select track id, then chose action from next menu."<<endl;
        cin>>rawUserInput;
        userInput=rawInputHandler(rawUserInput);
        cout<<"----------------------------"<<endl;

        menu_editUserPlaylist_trackMoveMenu(userInput);
    }

    void App::menu_editUserPlaylist_trackMoveMenu(int &selectedTrackId)
    {
        bool quit_me{false};
        std::string rawUserInput;
        int userInput;
        while(!quit_me)
        {
            cout<<endl;
            cout<<"----------------------------"<<endl;
            cout<<"    Current  selected track:  " << selectedTrackId<<" : "<<current_user->getTrackIdReturnTrackName(selectedTrackId)<<endl;
            cout<<endl;
            cout<<"Chose your action:"<<endl;
            if(selectedTrackId != 0)
                cout<<"1. Move to position "<< selectedTrackId-1<<endl;
            if(selectedTrackId != current_user->user_playlist().size()-1)
                cout<<"2. Move to position "<< selectedTrackId+1<<endl;
            cout<<"3. Switch with other track"<<endl;
            cout<<"4. Remove from playlist"<<endl;
            cout<<"9. Back to previous menu"<<endl;
            cout<<"0. To close app"<<endl;
            cout<<"Type  here:";
            cin>>rawUserInput;
            userInput=rawInputHandler(rawUserInput);

            if(userInput==0)
            {   quit_me=true;
                flag_close_me=true;
                cout<<"Application going to close"<<endl;
                break;
            }
            else if (userInput==9)
            {
                quit_me=true;
            }
            else if (userInput==-1)
            {
                cout<<"Option doesnt exist,please try other option"<<endl;  
            }
            else
            {
                cout<<"------- Action made ----------"<<endl;
                switch(userInput)
                {
                    case 1:
                    {
                        //TODO? i dont need to override it because it is to string, and im looking for string
                        if(!swapElementsAtList(current_user->user_playlist(),selectedTrackId,selectedTrackId-1))
                            {
                                cout<<"Move failed"<<endl;
                            }   
                        selectedTrackId-=1;
                        break;
                    }
                    case 2:
                    {                        
                        if(!swapElementsAtList(current_user->user_playlist(),selectedTrackId,selectedTrackId+1))
                            {
                                cout<<"Move failed"<<endl;  
                            }                            
                        selectedTrackId+=1;
                        break;
                    }
                    case 3:
                    {
                        cout<<"3. Switch with other track"<<endl;
                        //get user input and check it
                        std::string raw_other_track_id;
                        cout<<"Put number of second track"<<endl;
                        cin>>raw_other_track_id;
                        int int_other_track_id = rawInputHandler(raw_other_track_id);
                        if(int_other_track_id<0)
                            {   
                                break;
                            }
                            else 
                            {
                                if(int_other_track_id<=current_user->user_playlist().size())
                                {
                                    if(!swapElementsAtList(current_user->user_playlist(),selectedTrackId,int_other_track_id));
                                    {cout<<"Move failed"<<endl;}
                                        
                                    selectedTrackId = int_other_track_id;
                                    break;
                                }
                                else
                                {
                                    cout<<"That track doesnt exist"<<endl;
                                }
                            }                        
                        break;
                    }
                    case 4:
                    {
                        //std::list<std::string>::iterator it = std::find(current_user->user_playlist().begin(),
                        //                                            current_user->user_playlist().end(),
                        //                                            current_user->getTrackIdReturnTrackName(selectedTrackId));
                        current_user->user_playlist().remove(current_user->getTrackIdReturnTrackName(selectedTrackId));
                        cout<<"Track removed"<<endl;
                        cout<<endl;
                        cout<<"---- after change -----"<<endl;
                        current_user->printUserPlaylist(true);
                        quit_me=true;
                        break;
                    }                        
                }
                cout<<endl;
                cout<<"---- after change -----"<<endl;
                current_user->printUserPlaylist(true);
                cout<<endl;
            }


        }
    }

    void App::menu_showUserPlaylist()
    {
        std::string rawUserInput;
        cout<<endl;
        cout<<"---------" <<current_user->getUserName()<< "'s playlist ----------"<<endl;
        current_user->printUserPlaylist();
        cout<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"Press enter key to back to previous menu"<<endl;
        cin>>rawUserInput;
        cout<<"----------------------------"<<endl;
    }

    void App::menu_select_user()
    {
        bool quit_me{false};
        std::string rawUserInput;
        int userInput;
        while(!quit_me)
        {
            if(!this->flag_isuser_selected)
            {
                cout<<"To select user typ his id, or type 'q' to exit"<<endl;
                for(auto it = this->container_user_list.begin();it!=this->container_user_list.end();++it)
                {   
                    cout<<"# "<<it->getUserId()<<"  "<<it->getUserName()<<endl;
                }

                cout<<"Type here:";
                cin>>rawUserInput;
                userInput=rawInputHandler(rawUserInput);
                
                if(userInput==-2)
                {   quit_me=true;
                    flag_close_me=true;
                    cout<<"Application going to close"<<endl;
                    break;
                }
                else if (userInput==-1)
                {
                    cout<<"user doesnt exist or you type something else to exit"<<endl;  
                }
                else
                {
                    //find user
                    for(auto &el: this->container_user_list)
                    {
                        //TODO: switch that to iterator ?
                        if(el.getUserId()==userInput)
                        {
                            this->current_user = std::make_shared<User_simple>(el);
                            this->flag_isuser_selected=true;   
                            quit_me=true;                                     
                            break;
                        }
                    }
                    if(!this->flag_isuser_selected)
                        cout<<"User doesnt exist"<<endl;                                        
                }                
            }   
        }
    }

    void test1()
    {
        App a;
        a.app_run();
    }
  
    namespace TestCases
    {
         void test8_f_vector_int_from_cin_getline()
        {            
            
            cout<<"Give me some numbers"<<endl;
            std::vector<int> a = vector_int_from_cin_getline();
            for(auto el:a)
            {cout<<el<<endl;}     
            
            cout<<"Give me some numbers ill remove duplicates"<<endl;
            std::vector<int> b = vector_int_from_cin_getline(true);
            for(auto el2:b)
            {cout<<el2<<endl;}    
            
        }

        
        void test7_f_waitForUserInput()
        {
            cout<<""<<endl;
            //waitForUserInput();
        }

        void test6_f_songPlaying()
        {
            songPlaying("abba",4);
        }
        
        void test4_f_putTrackIdReturnTrackName()
        {
            User_simple u("Ania",33);
            u.printUserPlaylist(true);
            cout<<putTrackIdReturnTrackName(2,u.user_playlist())<<endl;
        }
        void test2_f_swap()
        {
            User_simple u("Ania",22);
            u.printUserPlaylist();
            //auto list = u.user_playlist();
            cout<<"we switch it"<<endl;
            std::list<std::string>::iterator it = u.user_playlist().begin();
            //std::advance(it,1);
            std::list<std::string>::iterator it2 = u.user_playlist().begin();
            std::advance(it2,2);
            //it - begin 
            //it2 - 3th - swan lake
            std::swap(*it,*it2);
            cout<<endl;
            u.printUserPlaylist();
        }
        void test3_f_swapElementsAtList()
        {
            User_simple u("Ania",33);
            u.printUserPlaylist();
            cout<<swapElementsAtList(u.user_playlist(),"Kodak Kodak-Beta-21","Davy-Jones-34")<<endl;
            u.printUserPlaylist();
        }
        void test5_f_swapElementsAtList_by_track_id()
        {
            cout<<"---- test test5_f_swapElementsAtList_by_track_id -----"<<endl;
            std::vector<int> to_switch = {3,0};
            User_simple u("Ania",33);
            u.printUserPlaylist(true);
            std::string el1_before{putTrackIdReturnTrackName(to_switch[0],u.user_playlist())};
            std::string el2_before{putTrackIdReturnTrackName(to_switch[1],u.user_playlist())};
            std::string el1_after;
            std::string el2_after;
            //cout<<swapElementsAtList(u.user_playlist(),0,2)<<endl;
            cout<<swapElementsAtList(u.user_playlist(),to_switch[0],to_switch[1])<<endl;
            u.printUserPlaylist(true);
            cout<<"---------"<<endl;
            el1_after={putTrackIdReturnTrackName(to_switch[0],u.user_playlist())};
            el2_after={putTrackIdReturnTrackName(to_switch[1],u.user_playlist())};
            cout<<"moved: " <<to_switch[0]<<" "<<el1_before<<" --> "<<to_switch[1]<< " " <<el1_after<<endl;
            cout<<"moved: " <<to_switch[1]<<" "<<el2_before<<" --> "<<to_switch[0]<< " " <<el2_after<<endl;

        }
    }
}

namespace MenuClassesApproach
{
    

    class OptionTemplate
    {
            std::string option_description;
            int option_numer;
        public:
            //MenuTemplate &parent_menu_instance;
        public:
            virtual void print_me(){std::cout<<"#"<<option_numer<<".  "<<option_description<<std::endl;};
            virtual void doMyAction()=0;
            public:
            OptionTemplate(std::string i_description, int i_option_number):
                           option_description{i_description},option_numer{i_option_number}
                            {};
            ~OptionTemplate(){};
    };

    class Option_MainMenu_Template: public OptionTemplate
    {
        public:
            Option_MainMenu_Template(std::string i_description, int i_option_number):
                            OptionTemplate(i_description,i_option_number)
                            {};
            ~Option_MainMenu_Template(){};
        public: 
            //virtual void doMyAction()=0;
    };

    class Option_1:public Option_MainMenu_Template
    {   
        public:
            Option_1(std::string i_description, int i_option_number):
                    Option_MainMenu_Template(i_description,i_option_number)
                    {};
            ~Option_1(){};
        public:
            virtual void doMyAction()override
                    {std::cout<<"Custom action at option nr 1 menu 0"<<std::endl;}
    };
    
    class Option_2:public Option_MainMenu_Template
    {   
        public:
            Option_2(std::string i_description, int i_option_number):
                    Option_MainMenu_Template(i_description,i_option_number)
                    {};
            ~Option_2(){};
        public:
            virtual void doMyAction()override
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
            virtual void doMyAction()override
                    {std::cout<<"Custom action at option nr 3 menu 0"<<std::endl;}
    };

    class MenuTemplate
    {   
        protected:
            std::string menu_name;
            std::string menu_header;
            std::string previous_menu_tag;            
            bool is_a_main_menu;
        public:
            std::map<int, std::unique_ptr<OptionTemplate>> option_list;
        public:
            std::map<std::string, std::shared_ptr<MenuTemplate>> &menu_collection;
        public:
            MenuTemplate(std::map<std::string, std::shared_ptr<MenuTemplate>> &i_menu_collection,
                            std::string i_menu_name,std::string i_m_header):
                        menu_collection{i_menu_collection},menu_name{i_menu_name},menu_header{i_m_header},is_a_main_menu{false}
                        {}
            ~MenuTemplate(){};
            virtual void show_menu()
                {
                    this->print_header();
                    this->print_options();                   

                };
            virtual void selected_option_response(int selected_option){};
            virtual void prepare_back_option(){};
            virtual void prepare_exit_option(){};
            virtual void print_options()
                {
                    for (auto el=  option_list.begin();el!=option_list.end();el++)
                    {
                        el->second->print_me();
                    }
                };
            virtual void print_header(){std::cout<<this->menu_header<<std::endl;};
            virtual void setAsMainMenu(){is_a_main_menu=true;};
            virtual bool isItMainMenu(){return is_a_main_menu;};
            virtual std::string getMenuName(){return this->menu_name;};
            virtual std::string getUserInput(std::string input_description)
                {
                    std::string tempRawInput;
                    cout<<input_description<<endl;
                    cin>>tempRawInput;
                    return tempRawInput;
                }
    };

    class Menu_MainMenu:public MenuTemplate
    {
        public:
            Menu_MainMenu(std::map<std::string, std::shared_ptr<MenuTemplate>> &i_menu_collection,
                            std::string i_menu_name,std::string i_m_header):
                            MenuTemplate(i_menu_collection,i_menu_name,i_m_header)
                            {}
            ~Menu_MainMenu(){};
        public:
    };

    class Menu_mm_option1:public MenuTemplate
    {
        public:
            Menu_mm_option1(std::map<std::string, std::shared_ptr<MenuTemplate>> &i_menu_collection,
                                std::string i_menu_name,std::string i_m_header):
                            MenuTemplate(i_menu_collection,i_menu_name,i_m_header)
                            {}
            ~Menu_mm_option1(){};
        public:
    };

    class Option_mm_1_0:public Option_MainMenu_Template
    {   
        public:
            Option_mm_1_0(std::string i_description, int i_option_number):
                    Option_MainMenu_Template(i_description,i_option_number)
                    {};
            ~Option_mm_1_0(){};
        public:
            virtual void doMyAction()override
                    {std::cout<<"Custom action at option nr 3 menu 0"<<std::endl;}
    };

    void test_7_two_menus_and_switch_between_second_try()
    {        
        //MenuTemplate going to change , next namespace is prepared

        //option DoAction need access to menu_collection to be able to launch menu with some name
        //menu_collection added to menu instance as ref in constructor,so we cant create menu without menu collection 
            //menutemplate cannot be wrap on unique ptr because i cant put that adress in options as a parent
            //ill switch it to shared_ptr

        // main_menu by default is going to add to that quene
        // while loop  taking 1th element form top and it start show menu
        // menu should print: header, menu customed options, 9-back(if it is last element - skip),0-close app


        std::map<std::string, std::shared_ptr<MenuTemplate>> menu_collection;

        //create menu - make a unique ptr and initialize constructor
        std::shared_ptr<MenuTemplate> main_menu {new Menu_MainMenu{menu_collection,"Main Menu","Welcome in Play Me"}}; 


        //create option to that menu - already as unique ptr
        std::string t2a ="This is option 1 main menu";
        std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, 1}};
        std::unique_ptr<OptionTemplate> ptr_2 {new  Option_2 {"This is option nr 2", 2}};
        std::unique_ptr<OptionTemplate> ptr_3 {new  Option_3 {"This is option nr 3", 3}};
        
        //add unique ptr as a option to menu
        main_menu->option_list[1]=std::move(ptr_1);
        main_menu->option_list[2]=std::move(ptr_2);
        main_menu->option_list[3]=std::move(ptr_3);       
        
        //add menu to coll
        menu_collection.insert(std::pair(main_menu->getMenuName(),std::move(main_menu)));

        //another menu
        std::unique_ptr<MenuTemplate> menu_option_1{new Menu_mm_option1{menu_collection,"MM option1","Welcome at option 1 from mm"}};

        //one option
        std::unique_ptr<OptionTemplate> ptr_o_mm_1_o_0{new Option_mm_1_0{"This is my main option from menu 1_1",1}};
        menu_option_1->option_list[1] = std::move(ptr_o_mm_1_o_0);

        //add menu to coll
        menu_collection[menu_option_1->getMenuName()]=std::move(menu_option_1);

        //print element from collction
        //TODO: add catch if there is no element like that
        menu_collection["Main Menu"]->show_menu();
             
    }

    void test_7_two_menus_and_switch_between()
    {        
        //try failed - builed in wrong direction
        /*
        //option DoAction need access to menu_collection to be able to launch menu with some name
        //menu_collection added to menu instance as ref in constructor,so we cant create menu without menu collection 
            //menutemplate cannot be wrap on unique ptr because i cant put that adress in options as a parent
            //ill switch it to shared_ptr

        std::queue<MenuTemplate> main_queue;
        // main_menu by default is going to add to that quene
        // while loop  taking 1th element form top and it start show menu
        // menu should print: header, menu customed options, 9-back(if it is last element - skip),0-close app


        std::map<std::string, std::shared_ptr<MenuTemplate>> menu_collection;

        //create menu - make a unique ptr and initialize constructor
        std::shared_ptr<MenuTemplate> main_menu {new Menu_MainMenu{menu_collection,"Main Menu","Welcome in Play Me"}}; 


        //create option to that menu - already as unique ptr
        std::string t2a ="This is option 1 main menu";
        std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, 1}};
        std::unique_ptr<OptionTemplate> ptr_2 {new  Option_2 {"This is option nr 2", 2}};
        std::unique_ptr<OptionTemplate> ptr_3 {new  Option_3 {"This is option nr 3", 3}};
        
        //add unique ptr as a option to menu
        main_menu->option_list[1]=std::move(ptr_1);
        main_menu->option_list[2]=std::move(ptr_2);
        main_menu->option_list[3]=std::move(ptr_3);       
        
        //add menu to coll
        menu_collection.insert(std::pair(main_menu->getMenuName(),std::move(main_menu)));

        //another menu
        std::unique_ptr<MenuTemplate> menu_option_1{new Menu_mm_option1{menu_collection,"MM option1","Welcome at option 1 from mm"}};

        //one option
        std::unique_ptr<OptionTemplate> ptr_o_mm_1_o_0{new Option_mm_1_0{"This is my main option from menu 1_1",1}};
        menu_option_1->option_list[1] = std::move(ptr_o_mm_1_o_0);

        //add menu to coll
        menu_collection[menu_option_1->getMenuName()]=std::move(menu_option_1);

        //print element from collction
        //TODO: add catch if there is no element like that
        menu_collection["Main Menu"]->show_menu();
        */        
    }
    
    void test_6_test_menu_class_with_two_menus()
    {   /* const was modified     
        std::map<std::string, std::unique_ptr<MenuTemplate>> menu_collection;

        //create menu - make a unique ptr and initialize constructor
        std::unique_ptr<MenuTemplate> main_menu {new Menu_MainMenu{"Main Menu","Welcome in Play Me"}}; 

        //create option to that menu - already as unique ptr
        std::string t2a ="This is option 1 main menu";
        std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, 1}};
        std::unique_ptr<OptionTemplate> ptr_2 {new  Option_2 {"This is option nr 2", 2}};
        std::unique_ptr<OptionTemplate> ptr_3 {new  Option_3 {"This is option nr 3", 3}};
        
        //add unique ptr as a option to menu
        main_menu->option_list[1]=std::move(ptr_1);
        main_menu->option_list[2]=std::move(ptr_2);
        main_menu->option_list[3]=std::move(ptr_3);       
        
        //add menu to coll
        menu_collection[main_menu->getMenuName()]=std::move(main_menu);

        //another menu
        std::unique_ptr<MenuTemplate> menu_option_1{new Menu_mm_option1{"MM option1","Welcome at option 1 from mm"}};

        //one option
        std::unique_ptr<OptionTemplate> ptr_o_mm_1_o_0{new Option_mm_1_0{"This is my main option from menu 1_1",1}};
        menu_option_1->option_list[1] = std::move(ptr_o_mm_1_o_0);

        //add menu to coll
        menu_collection[menu_option_1->getMenuName()]=std::move(menu_option_1);

        //print element from collction
        //TODO: add catch if there is no element like that
        menu_collection["Main Menu"]->show_menu();
        */        
    }
    
    void test_5_collection_of_options()
    {         
        //wrong test to do wrong thing
        std::string t2a ="This is option 1 main menu";
        std::map<int, std::unique_ptr<OptionTemplate>> menu_maps2;
        std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, 1}};
        std::unique_ptr<OptionTemplate> ptr_2 {new  Option_2 {"This is option nr 2", 2}};
        std::unique_ptr<OptionTemplate> ptr_3 {new  Option_3 {"This is option nr 3", 3}};

        menu_maps2[1]= std::move(ptr_1);
        menu_maps2[2]= std::move(ptr_2);
        menu_maps2[3]= std::move(ptr_3);

        for (auto el=  menu_maps2.begin();el!=menu_maps2.end();el++)
        {            
            el->second->print_me();
        }

    }

    void test_4_option_collection_shp_ptr()
    {         
        //wrong test to do wrong thing
        int t1a =1;
        std::string t2a ="This is option 1 main menu";
        std::map<std::string, std::unique_ptr<OptionTemplate>> menu_maps2;


        std::unique_ptr<OptionTemplate> ptr_1 {new  Option_1 {t2a, t1a}};

        menu_maps2["test1"]= std::move(ptr_1);
        menu_maps2["test1"]->print_me();
        menu_maps2["test1"]->doMyAction();


    }

    void test_3_option_collection()
    { 
        std::map<std::string, OptionTemplate*> menu_maps;
        int t1 =1;
        std::string t2 ="This is option 1 main menu";
        std::cout<<"class tests"<<std::endl;
        Option_1 o1_m1(t2, t1);
        menu_maps["mainMenu"]= &o1_m1;
        menu_maps["mainMenu"]->print_me();
        menu_maps["mainMenu"]->doMyAction();        

    }

    void test_2_just_option_classes()
    {
        //std::map<std::string, std::unique_ptr<OptionTemplate>> menu_maps;
        int t1 =1;
        std::string t2 ="This is option 1 main menu";
        std::cout<<"class tests"<<std::endl;
        Option_1 o1_m1(t2, t1);
        o1_m1.print_me();
        o1_m1.doMyAction();        
        Option_2 o2_m1("This is option 1 main menu", 2);
        o2_m1.print_me();
        o2_m1.doMyAction();        

    }

    void test_1_just_option_classes()
    {
        int t1 =1;
        std::string t2 ="This is option 1 main menu";
        std::cout<<"class tests"<<std::endl;
        Option_1 o1_m1(t2, t1);
        o1_m1.print_me();
        o1_m1.doMyAction();
    }
    
}

namespace MenuClassesApproach_2
{
    //pre-declaration    
    void test_8_add_queue_modif_menu_cls()
    {        
        //my main quene
        std::stack<std::shared_ptr<MenuTemplate>> stack_of_menus;

        //we add ad start main menu
        std::shared_ptr<MenuTemplate> main_menu_lvl0 {new Menu_MainMenu{}}; 
        stack_of_menus.push(main_menu_lvl0);

        // main_menu by default is going to add to that quene
        int selected_option;
        
        while (true)
        {   
            stack_of_menus.top()->show_menu();        
            selected_option=stack_of_menus.top()->manageUserInput();            
            stack_of_menus.top()->launch_selected_option(selected_option,stack_of_menus);
            if (selected_option == 0) {break;}
            if (selected_option == 9) {stack_of_menus.pop();}
        }

        // while loop  taking 1th element form top and it start show menu
        // menu should print: header, menu customed options, 9-back(if it is last element - skip),0-close app
        
        //another menu
        //std::unique_ptr<MenuTemplate> menu_option_1 {new Menu_at_mm_opt1{}};

        //one option
        //std::unique_ptr<OptionTemplate> ptr_o_mm_1_o_0{new Option_mm_1_0{"This is my main option from menu 1_1",1}};
        //menu_option_1->option_list[1] = std::move(ptr_o_mm_1_o_0);

        //add menu to coll
        //menu_collection[menu_option_1->getMenuName()]=std::move(menu_option_1);

        //print element from collction
        //TODO: add catch if there is no element like that
        
        //menu_collection["Main Menu"]->show_menu();
        
             
    }

    void test_9_is_number_test()
    {
        std::cout<<GeneralFuncitons::is_number("324")<<std::endl;
        std::cout<<GeneralFuncitons::is_number("sdf")<<std::endl;
    }
}

int main()
{
    //MenuClassesApproach::test_1_just_option_classes();
    //MenuClassesApproach::test_2_just_option_classes();
    //MenuClassesApproach::test_3_option_collection();
    //MenuClassesApproach::test_4_option_collection_shp_ptr();
    //MenuClassesApproach::test_5_collection_of_options();
    //MenuClassesApproach::test_6_test_menu_class_with_two_menus();
    //MenuClassesApproach::test_7_two_menus_and_switch_between_second_try();

    //MenuClassesApproach_2::test_9_is_number_test();
    MenuClassesApproach_2::test_8_add_queue_modif_menu_cls();
    
    //todo: check how to avoid adding pre-declaration at optionTemplate

    //STL_List_challange_simple_mode::test1();
    

}