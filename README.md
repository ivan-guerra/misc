# Super Word Search

### Overview
Super Word Search is a word search puzzle solver. Given an NxM character grid, a search mode, and a list of terms
to search, Super Word Search will compute the start and end points of each term that can be found
in the search grid. The application supports WRAP and NO WRAP modes. NO WRAP does not allow words
to wrap around the boundaries of the word grid whereas WRAP does.

### Input/Output Format
Super Word Search prompts the user for the path to a text file containing the character grid, search mode, and
list of key terms. An example input puzzle is shown below. Note, a single input file can have more than one puzzle
in sequence. Just be sure not to put any newlines between the puzzles.

```
4 3
ABC
DEF
GHI
JKL
WRAP
5
FED
CAB
AEIJBFG
LGEC
HIGH
```

Super Word Search outputs its results to stdout. For each search term that is found, you will see the 
start and end point coordinates of the word in the input character grid. If a term is not found, `NOT FOUND` is
output. Below is an example of the output for the puzzle above. Note, the order of the output corresponds to the
order of the search terms in the input.
```
--------------------------------
(1,2) (1,0)
(0,2) (0,1)
(0,0) (2,0)
(3,2) (0,2)
NOT FOUND
--------------------------------
```

### Usage
To compile, you need a **C++ compiler supporting C++14 features** and **CMake version 3.10 or higher**. Follow
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
