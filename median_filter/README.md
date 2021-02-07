# medfilter

### Overview
medfilter implements a NxN median filter. The filter is meant to run on grayscale JPG images only. The filter
implementation is a bruteforce one in which the image borders are ignored. The algorithm was lifted from
the median filter [Wikipedia page](https://en.wikipedia.org/wiki/Median_filter#2D_median_filter_pseudo_code).

### Usage
To compile medfilter you will need to have installed libjpeg. libjpeg comes standard on most Linux distros.
However, if you are having trouble compiling on CentOS7, you can install libjpeg-turbo-devel and that
should resolve any issues related to the build:
```
[user@host medfilter] sudo yum install libjpeg-turbo-devel
```
To build the source run make.
```
[user@host medfilter] make
```
To run a 5x5 median filter on the sample image provided with this repo run the following command:
```
[user@host medfilter]./medfilter noise.jpg filtered.jpg
```
After running the above, your filtered image will appear in filtered.jpg. In general, medfilter expects
to arguments: an input image name and output image name. medfilter can also accept additional arguments
such as the grid dimension and an option to print timing statistics. run medfilter with the -h option
for more details.

### Documentation
If you're interested in viewing the Doxygen docs you can build them using the following command.
```
[user@host medfilter]doxygen doxygen_conf
```
After the build executes you can view the files in your browser.
```
[user@host medfilter]firefox docs/html/index.html
```
