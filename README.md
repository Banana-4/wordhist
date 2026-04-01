# Word Histogram program

## About
This is a simple UNIX-like utility program for outputing a histogram of word lengths.
The goal of this project is to demonstrate skills:
1. Making programs that can be composed.
2. Safe memory managment.
3. Data stream processing.
4. Iterative development cycle.

## Design
This program is based on the exercise from K&R word histogram.
The program is focused on doing one thing only converting the words in its input into a histogram of word lengths.

The program needs to:
1. Read and process a character stream input. Parse the input.
2. Store the words and theire lengths in memory.
3. Output a histogram of words lengths with the list of unique words in its input.

The program has three core parts, modules:
1. Input processing. Responsible for reading and parsing the character stream.
2. Memory managment. Responsible for safely and efficently storing the computated data.
3. Histogram output. Responsible for transforming words lengths into a histogram.

While designing this program I took inspiration from K&R principles and dr. Chuck.
Following those principles I designed the program using a iterative loop:
1. Define the responsibilities of the program.
2. Make it work.
3. Make it correct.
4. Simplify.
5. Analyze.
6. Do it again.

Constrains:
1. Handle inputs of unknow size.
2. Memory safe.
3. Process only unique words.
4. Time complexity O(n).
5. Memory complexity O(n).

The program is modular in design, made from composable parts. This is done to support the iterative development loop for ease of changes.

## Modules:
The design of modules reflect the way the data is used and process in the program.

### Memory:
Dynamic memory managment subsystem. This module is responsible for:
1. Providing dynamic memory data structures.
2. Safe dynamic memory usage.

This module handles the storage of parsed words and their lengths. The design of the data structures and their 
interfaces is based on how the data is used in the word histogram programm. The data structures support only 
the used operations by the program and nothing more. The data structurs in this module are designed to meet 
the constrains of the program.

Data Structures:
1. Dynamic Arrays.
2. Hash Map.

#### Dynamic Arrays
The dynamic arrays use the standart text book design. A struct to keep track of the allocated size, length and the pointer to the allocated memory block.
The starting size of the arrays is 8. The growth factor of the arrays is 2.
The arrays lazy grow when appending.

There are two implementaions of the Dynamic Arrays based on what data is stored:
1. Array - array for holding integers represnting word lengths.
2. StrArray - for storing character strings, words.

Both arrays support the following operations:
1. constructing - initiation of the arrays.
2. appending - adding a new element to the end of the array.
3. deleting - for safe freeing of all allocated dynamic memory. 

### Stream Processing:
2. Stream Processing - This module uses a simple defenition of a word to classifie the input chracters, a word is any char sequence that starts with a letter has only numbers letters and apostrophes and has no blanks.

### Histogram:
3. Output - This module takes the words and theire lengths, transforms lengths into a vertical histogram and outputs the list of words with their lengths.
