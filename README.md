# PNPZ80

PNPZ80 stands for Plug N Play Z80. PNPZ80 is a library that will allow you to create emulators that simulate the Z80 processor simply. Using PNPZ80 you can add your own virtual hardware that you have created.

The best way to describe PNPZ80 is that its like someone giving you a Z80 Processor and possibly some built in virtual hardware that you need to build the system you want and then leaving you to do the programming. Any hardware that is not in the core you can make yourself.

Feel free to contribute to the project, at the moment the important part is finishing the Z80 simulator.

#Compiling notes:
To compile on windows use "mingw32-make windows" to compile on linux use "make linux". Be sure to firstly clean the project by using "mingw32-make cleanWindows" or "make cleanLinux" depending on your operating system.

If your compiling on linux make sure g++ is installed before compiling:

sudo apt-get update

sudo apt-get install g++

If your on Windows you should download Mingw and set your "PATH" variable in your environment variables to include the folder of the mingw "bin" directory.


At the moment any changes made by the code holder will not be recognised when building the project. You will first have to clean the project as described above. This shouldn't be an issue and hopefully the "Makefile" issues will be solved soon.
