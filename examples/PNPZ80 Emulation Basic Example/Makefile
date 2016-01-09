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

linux: ./bin/PNPZ80EmuExample

./bin/PNPZ80EmuExample: ./obj/main.o ./obj/PNPZ80Audio.o
	cp "../../PNPZ80/bin/PNPZ80.so" "./PNPZ80.so"
	g++ ./obj/main.o ./obj/PNPZ80Audio.o ./PNPZ80.so -o ./bin/PNPZ80EmuExample
	mv "./PNPZ80.so" "./bin/PNPZ80.so"

cleanLinux:
	rm "./obj/main.o"
	rm "./obj/PNPZ80Audio.o"

