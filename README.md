Heavily* inspired by Low Level Devel
https://www.youtube.com/watch?v=e87qKixKFME

Initial framework from https://github.com/rockytriton/LLD_gbemu

Important References:

https://gbdev.io/pandocs/

https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

https://archive.org/details/GameBoyProgManVer1.1/page/n85/mode/2up

https://github.com/rockytriton/LLD_gbemu/raw/main/docs/The%20Cycle-Accurate%20Game%20Boy%20Docs.pdf

https://github.com/rockytriton/LLD_gbemu/raw/main/docs/gbctr.pdf


Create a build directory, cd into it and run
cmake ..
make
gbemu/gbemu <rom path>
