# K-means image segmentation
Implementation of k-means image segmentation in C.

### How to Use
Dependencies: `png.h`

Clone: `git clone https://github.com/inventshah/Kmeans-C.git`

Compile: `./build.sh`

Run: `./bin/main [source filename] [output filename] [K-value] [max generations]`

Default max generations is 100.

### Examples

source | 2 | 3 | 4 | 5
:-----:|:-:|:-:|:-:|:-:
![source](images/source.png) | ![2](images/k2.png) | ![3](images/k3.png) | ![4](images/k4.png) | ![5](images/k5.png)

### Built With
* C