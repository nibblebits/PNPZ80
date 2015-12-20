# PNPZ80

PNPZ80 stands for Plug N Play Z80. This Z80 emulator will be like no other. Once complete you will very easily be able to create your own Z80
system on the emulator. See the example code for an example. It goes something like

// The code below would have made your z80 system capable of using audio, you can very easily program your own Z80 hardware as well
z80_system.attachHardware(new PNPZ80AudioHardware());

Feel free to contribute to the project, at the moment the important part is finishing the Z80 simulator.

Compiling notes:
If you are using Codeblocks to compile the PNPZ80 then be sure to change the libaries in the build options to include the header files and libaries at the correct directories.
