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
Dynamic memory management subsystem. 

Responsibilities:
1. Providing dynamic memory data structures for storing processed words from a input stream.
2. Safe dynamic memory usage.

This module solves the problem of storing arbitrary amounts of processed data from a input stream.
The solution uses dynamic arrays and hash maps.

The design of the module takes into account how the programm process the data and tries to meet those requirments. 

Program data requirements:
1. Arbitary amount of character stream data from stdin or redirect to stdin from other sources.
2. Storage of words, strings, of various sizes.
3. Storage of the lengths of the words as ints, the number of words is not know before the stream is processed.
4. The program process only unique words.
4. Ideal space complexity O(n)
5. Ideal time complexity O(n).

The data structures support only the operations needed by the program. The data structurs in this module are designed to meet the constrains of the program.

Data Structures:
1. Dynamic Arrays:
- Array for storing integers. 
- Str for storing char *.
- StrArray for storing Str.

2. Hash Map - data structure used for building the StrArray from processed input.

The starting size of all data structures is 4 and the growth factor is 2. That is done to make the data structures uniform and to provide a good time and space complexity.

#### Dynamic Arrays
The dynamic arrays use the standard text book design. 
A struct that keeps track of the allocated size, and used slots,length and holds the pointer to the allocated memory block.

The arrays lazy grow when appending.

There are three implementaions of the Dynamic Arrays based on what data is stored:
1. Array - array for holding integers represnting word lengths.
2. Str - for storing character strings, words.
3. StrArray - a array of Str. This data strucure owns the Strs.

The implementations are very similiar, the only difference is how Str handles appending it needs to handle appending the terminator of strings '\0'.

The data stored in the array is never removed and after the input is processed the arrays never change.

All arrays support the following operations:
1. constructing - initialization and allocation of the array struct.
2. appending - adding a new element to the end of the array.
3. deletion - for safe freeing of all allocated dynamic memory. 

#### Hash Map:
The hash map is responsible for building a unique words StrArray.
The keys and values in this problem are the same a Str. In that way the hash map is like the python set.

The hash map design is inspired by the implementation of the python dict but unlike the dict the hash map uses separate chaining collision resolution method. 

The hash map uses sparse and dense memory stores. 
The sparse store is idxs, the Array data structure that is used for the hashing. The idxs stores the indexes to the keys in the StrArray.
The dense memory store is the StrArray. This data structure is used to store the keys.

The hash algorithm is AI generated and is djb2 by Daniel J. Bernstein.

Supported operations:
1. Construction - allocation and initialization of the hash map struct.
2. insert - adding a new key to the hash map.
3. has - checking if the map contains a key.
4. deletion - free only the memory used by the hashmap struct, it does not owns the memory of Str.
5. grow - grows the hash map to keep the load factor low.

##### Operations:

###### __grow_HashMap(HashMap *m):
This operation is responsible for growing the hash map when the load factor exceeds the load limit.
The operation is desigend to be exception safe, the hash map is mutated only if there are no errors.

The operation changes:
1. idxs - grows the indexs array and rehashes the keys.
2. size - doubles the size.

The cleanup code is grouped in the labeled block for reducing code duplication and giving better structure.

### Stream Processing:
2. Stream Processing - This module uses a simple defenition of a word to classifie the input chracters, a word is any char sequence that starts with a letter has only numbers letters and apostrophes and has no blanks.

### Histogram:
3. Output - This module takes the words and theire lengths, transforms lengths into a vertical histogram and outputs the list of words with their lengths.
