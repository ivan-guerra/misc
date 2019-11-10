# Super Word Search

### Overview
Super Word Search is a word search puzzle solver. Given an NxM character grid, a search mode, and a list of terms
to search, Super Word Search will compute the start and end points of each term that can be found
in the search grid. The application supports WRAP and NO WRAP modes. NO WRAP does not allow words
to wrap around the boundaries of the word grid whereas WRAP does.

### Usage
To compile, you need a **C++ compiler supporting C++14 features** and **CMake version 3.12 or higher**. Follow
the commands below to download and build the source.
```
[user@host ~]$ git clone https://github.com/ivan-guerra/super_word_search.git
[user@host ~]$ cd super_word_search/
[user@host super_word_search]$ mkdir build && cd build
[user@host build]$ cmake .. && make && make install
```
If the build was successful, you should see a bin/ directory under super_word_search/. The commands below
outline how to run the application as well as the unit tests.
```
[user@host build]$ cd ../bin
[user@host bin]$ ./wsearch
[user@host bin]$ ./wsearch_test
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
