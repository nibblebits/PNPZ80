Debug: ./bin/PNPZ80.dll

./bin/PNPZ80.dll: ./obj/PNPZ80.o ./obj/PNPZ80Hardware.o ./obj/PNPZ80Instance.o ./obj/PNPZ80Ram.o ./obj/PNPZ80Simulator.o
	g++ ./obj/PNPZ80.o ./obj/PNPZ80Hardware.o ./obj/PNPZ80Instance.o ./obj/PNPZ80Ram.o ./obj/PNPZ80Simulator.o -o ./bin/PNPZ80.dll -shared

./obj/PNPZ80.o:
	g++ -c -I./include -I./src ./src/PNPZ80.cpp -o ./obj/PNPZ80.o
./obj/PNPZ80Hardware.o:
	g++ -c -I./include -I./src ./src/PNPZ80Hardware.cpp -o ./obj/PNPZ80Hardware.o
./obj/PNPZ80Instance.o:
	g++ -c -I./include -I./src ./src/PNPZ80Instance.cpp -o ./obj/PNPZ80Instance.o
./obj/PNPZ80Ram.o:
	g++ -c -I./include -I./src ./src/PNPZ80Ram.cpp -o ./obj/PNPZ80Ram.o
./obj/PNPZ80Simulator.o:
	g++ -c -I./include -I./src ./src/PNPZ80Simulator.cpp -o ./obj/PNPZ80Simulator.o

cleanDebug:
	del ".\obj\PNPZ80.o"
	del ".\obj\PNPZ80Hardware.o"
	del ".\obj\PNPZ80Instance.o"
	del ".\obj\PNPZ80Ram.o"
	del ".\obj\PNPZ80Simulator.o"