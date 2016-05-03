# uavdetect
## Table of Contents
[System Requirements](#requirements)  

[Training the filter](#train)

[Build](#build)  

[Run](#run) 


<a name="requirements"/>
### System Requirements
* Opencv
* Gimp  
```
$ sudo apt-get install gimp-plugin-registry
```

<a name="train"/>
### Training the filter
1)Get more images of the uav.<br />
2)Here we have all the images in uav_more directory.<br />
3) Created a batch process in gimp to convert the original images to grayscale and to resize them to 40 x 40 pixels.<br />
4) Took the grayscale images and applied the following transformations:upside-down, blur 3.0 , brightness +0.5 ,  brightness -0.5 , contrast +0.5, contrast -0.5 .<br />
5) create the info file
```
$ cd uavdetect
$ find ./uav_more -iname "*.jpg" > positives.txt
$ sed -i 's/.jpg/.jpg 1 0 0 40 40/' positives_grey.txt
```
6)	create the info file for negative images.
```
$ find ./sample1_neg -iname "*.jpg" > negatives.txt
```
7) create the vector file
```
$ opencv_createsamples -info positives_grey.txt -num 1200 -w 40 -h 40 -vec training.vec
```
8) train the filter
```
$ mkdir data
$ opencv_traincascade -data data -vec training.vec -bg negatives.txt -numPos 200 -numNeg 200 -numStages 10 -nsplits 2 -w 40 -h 40 -featureType HAAR -minhitrate 0.999 -maxfalsealarm 0.5
$ cp data/cascade.xml .
```


<a name="build"/>
### Build

```
$ make
```
<a name="run"/>
### Run
```
$ ./flightdetector samples/<img_name>
```
