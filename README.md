# Word Histogram program

## About
This is a UNIX-like utility program for outputing a histogram of words lengths.
The inspiration for the program comes from the K&R The C programing language book.

Example:

``` bash
>> ./wordhist.sh  hello_world.txt
 Histogram:
  #  #
  #  #
  #  #
  #  #
  #  #
  _  _
 
  H  W
  e  o
  l  r
  l  l
  o  d

```

## Requirements:
In order to use the program the following is required: 
1. gcc
2. make
3. bash

## How to run:
``` bash
make
./wordhist.sh file
```
