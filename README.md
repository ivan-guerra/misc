# Nearest Neighbors 3D

### Overview
Nearest Neighbors 3D (NN3D) is a program for finding the nearest neighbors of a set of points within 3D space
given a search radius. NN3D uses a static, balanced 3-D Tree to perform spatial searches on large sets of
points.

### Input/Output Format
NN3D prompts for two key inputs: the path to a text file containing the set of points and a double precision
search radius. The format of the text file is shown below
```
num_points
x y z
x y z
. . .
x y z
```
At the top of the file is the number of points to load. Each subsequent line contains a 3D point represented by 3 double
precision values seperated by whitespace.

NN3D outputs its results to the console. For each point that was ingested, it will output the results of the search as
```
point_id:[num_neighbors | neighbor_id(s)]
```
Note that point IDs range from 1 to n where the first point has ID 1, second point ID 2, etc. Example input and output are given below.

Suppose we want to find all neighbors within a radius of 1.0 for all the points in the following input file.
```
3
0 0 0
0 0 1
0.5 0.5 0.5
```
NN3D would compute NNs for each point within a 1.0 radius and print the following to stdout:
```
------------- Start Search Results -------------
1:[ 2 | 2 3 ]
2:[ 2 | 3 1 ]
3:[ 2 | 2 1 ]
------------- End Search Results --------------
```

### Usage
To compile, you need a **C++ compiler supporting C++14 features** and **CMake version 3.10 or higher**. Follow
the commands below to download and build the source.
```
[host ~]$ git clone https://github.com/ivan-guerra/nearest_neighbors_3d.git
[host ~]$ cd nearest_neighbors_3d
[host nearest_neighbors_3d]$ mkdir build && cd build
[host build]$ cmake .. && make && make install
```
If the build was successful, you should see a bin/ directory under nearest_neighbors_3d/. The commands below
outline how to run the application as well as the unit tests.
```
[host build]$ cd ../bin
[host bin]$ ./nearest_neighbors
[host bin]$ ./nearest_neighbors_test
```
If you have [Doxygen](http://www.stack.nl/~dimitri/doxygen/) installed, you can build the project docs
using the following command.
```
[host nearest_neighbors_3d]$ doxygen doxygen_conf
```
Alternatively, you can view the prebuilt docs by opening docs/html/index.html
in your browser.

### License
This software is licensed under the MIT Open Source license (see LICENSE file).
