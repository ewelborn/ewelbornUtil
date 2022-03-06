# ewelbornUtil
This is my attempt at implementing some higher level data structures in C. I wrote this header file specifically for my Advanced Algorithms course, but I'll likely use it in the rest of my C projects from now on.

The Github repo is a visual studio project that will be expanded on in the future for the purposes of testing the header file.

**Warning: this project is still very much a work-in-progress, and the interface provided by ewelbornUtil.h is likely to change. I'm also really bad at Git.**

## Features

- **ewelborn_string**: mutable string object backed by a dynamic array and comes with several string manipulation functions to make input processing less of a nightmare.
- **ewelborn_dynamicArray**: generic dynamic array in C that can be appended to without having to worry about resizing.
- **ewelborn_linkedList**: **WIP**
- **ewelborn_queue**: generic FIFO queue with simple push and pop operations, backed by a circular buffer.
- **ewelborn_priorityQueue**: priority queue backed by a dynamic heap, can be flagged to work either as a min or max priority queue.

## Install

This header file is (or should be) compatible with any standard C compiler, but it has been developed and tested to work on the Microsoft Visual C++ compiler running on the latest version. 
To use the most recent version of the header file in your code, 
[download the .h file here](https://github.com/ewelborn/ewelbornUtil/blob/3cb436b383ba7b3d79fbd972892c85be10d1b7b8/ewelbornUtil/ewelbornUtil.h), and 
[download the .c file here](https://github.com/ewelborn/ewelbornUtil/blob/3cb436b383ba7b3d79fbd972892c85be10d1b7b8/ewelbornUtil/ewelbornUtil.c), and add them directly to your project folder. In the future, stable releases will be available separately for download.

## Thanks for stopping by!
If you want to know more about me and what I do, feel free to [visit my website](https://www.ethanwelborncs.com/). You can also visit the [project page](https://www.ethanwelborncs.com/ewelborn/article/ewelbornutil/) directly.
