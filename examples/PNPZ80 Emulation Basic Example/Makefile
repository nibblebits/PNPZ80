windows: ./bin/PNPZ80EmuExample.exe

./bin/PNPZ80EmuExample.exe: ./obj/main.o ./obj/PNPZ80Audio.o
	copy "..\..\PNPZ80\bin\PNPZ80.dll" ".\bin\PNPZ80.dll"
	g++ ./obj/main.o ./obj/PNPZ80Audio.o ./bin/PNPZ80.dll -o ./bin/PNPZ80EmuExample.exe

./obj/main.o:
	g++ -c -I../../PNPZ80/include -I./include -I./src ./src/main.cpp -o ./obj/main.o
./obj/PNPZ80Audio.o:
	g++ -c -I../../PNPZ80/include -I./include -I./src ./src/PNPZ80Audio.cpp -o ./obj/PNPZ80Audio.o

cleanWindows:
	del ".\obj\main.o"
	del ".\obj\PNPZ80Audio.o"
