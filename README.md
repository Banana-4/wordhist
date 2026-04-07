# Word Histogram program

## About
This is a simple UNIX-like utility program for outputing a histogram of words lengths from input stream.
The inspiration for the program comes from the K&R exercise word histogram.

### The goals of this project are:
1. Iterative program building. 
2. Working safely with memory.
3. Designing program architecture.
4. API Design.
5. Practicing data structures and algorithms.
6. Clean documentation of code.

## Word Definition:
A word is any character sequence that starts with a letter that contains only letter, digits and '. 
There is no word boundry checks, its not check if a word is between two blank characters. 

Do to the lack of boundry checks any character sequence that matches the defintion is considered a word. 
Examples:
1. 11111hello### - hello is a word
2. 1can't - is a word.
3. asdsdxzcvwedfdsf23123'23213 is a word.

## Design:
The program was developed iteratively through multiple architectural stages:

``` text
static arrays and input processing -> dynamic memory -> hash map for removing duplicate words -> string array builder for collecting words from input 

```

The goal of the design process was to develope a compossible program architecture.
The program is made from modules:
1. Memory - responsible for dynamic memory and string array building.
2. Input - handles parsing input and storing words.
3. Histogram - handles the creation and output of the histogram.
4. Main - cordinates the other modules and owns the built StrArray.

Note:
The StrArrayBuilder should be semantically a separate module it builds a unique words str array, but internaly it performs data storage, memory management using dynamic arrays and uses a hashing algorithm. Because interanly it handles data storage I place it inside the memory module. 

## Enginers Log:

### First iteration - static memory
In the first iteration the goal is to have a simple working version of the program. The data is stored in static arrays and the whole program is one monolithic main function.
In this version I verified my initial idea of how the program whould work, what are the individual steps needed to transform input stream into a words length histogram.
From this first version the pipeline is:
1. Allocate and initilaze static memory to hold the program data.
2. Process input
3. Output histogram

### Second iteration - dynamic memory and module separation
The first iteration showed me how should the program needs to be organized.
The modules are:
1. Memory.
2. Input. 
3. Histogram.
In this iteration i broke the program into individual modules and implemented dynamic arrays.

### Third iteration - hash map and unique words.
After getting a basic random size input processing program it was time to handle the problem of processing only unique words from the input.
The solution was to use a lookup table, hash map. This iteration showed me that doing iterative design and breaking into modules is very powerfull, it allowed me to do minimal changes and reuse code to implement a new functionalty.
The program now handles:
1. arbitrary amount of data from input.
2. unique words.

### Forth iteration - StrArrayBuilder

From the third iteration I was left with a lot of duplicate data stored, word lengths where both in the strings and in the dynamic integer array. Strings where stored both in a string array and the hash map.
Memory ownership was spread across diffrent data structures. The API design needed improvements.
There where no precisely defined invariants.
The first and obvious solution was to remove the dynamic array that stored word lengths.

The second thing I did is define the invariants:
1. There are no duplicate words in the StrArray.
2. StrArrayBuilder owns the StrArray while the input is processing.
3. Strings are owned by the StrArray.
4. If the input stream cant be processed the program stops and reprots a error.

The third solution was to implement a string array builder that would build a unique words array and than transfer the array ownership to the main function. For that purpose i decided to reuse the hash map using ideas from the python dictonary implementation.
The python dict uses two arrays:
1. key-value array.
2. Hash array that stores the index of the key in the key-value pair at the hashed position of the key.

This give me the idea to use a hash map inside the string builder that uses words as the keys and indexes into the StrArray as the values.
Doing this cleanly allowed the StrArrayBuilder to maintain unique words and build a StrArray effectivly.

