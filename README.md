# cpp

This is template for console menu.
It is a stack of menus, where current menu is on top, and each another menu is setting on top.

Menus and menu-options are inherinted from templates.
Manin idee behind it was to create easy console menu, where will be easy option to add new menu, and options,
and whole action behind that menu-option set in option.
I was tired to create loon in loop in loop, so I create stack. Previous menu will stay on stack to have option "back" as a default.
In main.cpp there is a lot of other code, which was created at first stage, of creation that template.
I dont want to remove it becasue i would like to see how it evolved.

What i use to create that:
+ meuns and options are on smart_pointers
+ there is also class polymorphism because stack it keep base class of Menus

How to use:
+  ...yea it require little cleaning to make it more simple, Ill do that in spare time, i ahve it on my list
