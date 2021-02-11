# Dice Invaders

![Dice Invaders](https://github.com/ivan-guerra/misc/blob/master/dice_invaders/gameplay.PNG)

### Overview
Dice Invaders (DI) is a simplified version of the original Space Invaders game. DI uses the DiceInvadersLib provided by DiceLA to perform graphics related tasks (i.e., no external graphics libs are needed to build and run). 

### Usage
It is important to note that _DI can only be built and run on a Windows PC_. To build, you need [MinGW](https://sourceforge.net/projects/mingw-w64/) and [CMake](https://cmake.org/download/) version 3.10 or greater. Follow the commands below to build DI from source.
```
[user@host ~]$ git clone https://github.com/ivan-guerra/dice_invaders.git
[user@host ~]$ cd dice_invaders/
[user@host dice_invaders]$ mkdir build && cd build
[user@host build]$ cmake .. -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND"
[user@host build]$ mingw32-make && mingw32-make install
```
If the build was successful, you should see a `bin/` directory under `dice_invaders/`. The commands below show how to run DI.
```
[user@host build]$ cd ../bin
[user@host bin]$ invaders.exe
```
If you have [Doxygen](http://www.stack.nl/~dimitri/doxygen/) installed, you can build the project docs
using the following command.
```
[user@host super_word_search]$ doxygen doxygen_conf
```
Alternatively, you can view the prebuilt docs by opening docs/html/index.html
in your browser.

### License
This software is licensed under the MIT Open Source license (see LICENSE file).
