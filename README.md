# Word Histogram program

## About
This is a UNIX-like utility program for outputing a histogram of words lengths.
The inspiration for the program comes from the K&R The C programing language book.

Example:

``` te
>> ./wordhist < hello_world.txt
 Histogram:
 _  _ 

 #  # 
 #  # 
 #  # 
 #  # 
 #  # 
 _  _ 


 Words List:
 Hello : 5
 World : 5

```

### How to run:
``` bash
make
./wordhist
```

### The goals of this project are:
1. Visualize the data as a histogram.
2. Process arbitrary input lengths.
3. Composable with other utility programs, example cat, grep...
4. Support for I/O redirections.

### Constrains:
1. The program will process the whole input or nothing.
2. Safely manage dynamic memory.
3. Use modular architecture.
4. Use only block memory, no linked lists, trees...
5. Time Complexity of O(n).
6. Space Complexity of O(n).

## Input:
The input is a stream of characters from stdin or redirected to it.

### Word Definition:
A word is any character sequence that starts with a letter that contains only letter, digits and '. 
There is no word boundry checks, its not check if a word is between two blank characters. 
Do to the lack of boundry checks any character sequence that matches the defintion is considered a word. 
Examples:
1. 11111hello### - hello is a word.
2. 1can't - can't is a word.
3. asdsdxzcvwedfdsf23123'23213 is a word.

## Design:
The design of the program reflects the way data is provided and process by the program.

The program was developed iteratively through multiple architectural stages:
1. Simple monolithic working version. Using static arrays.
2. Modular architecture. In this stage the program used dynamic arrays to handle memory management.
3. Unique words only stage. This stage added a hash map for efficent lookup of processed words.
4. Factory design pattern. In this stage the program was refactored and a string array builder optimization was applied for efficent word list building.
5. Error Codes. In this stage the API was improved to report back on errors that occured for ease of debuging.
6. User experience improvements - in this stage the program is made more user friendly.

This increamental development stragy resulted in building a robust and maintainable program.

Modules:
1. Memory - responsible for dynamic memory and string array building.
2. Input - handles input stream transformation to the words list.
3. Histogram - handles the transformation of words list into a histogram.
4. Main - cordinates the other modules.

### Memory module:
This module is designed with keeping in mind the program requirements. The data structures inside it are not general and provide only the functionality that the programs requires. There is no support for remove, pop... 
The program almost never removes data from data structures the only exception is the StrArray it removes the last inserted string if the appending of the index to the hash map fails.
With that in mind the program uses the following data structures:
1. Array - dynamic integer array.
2. Str - a string data structure, dynamic char array.
3. StrArray - dynamic array of Str.
4. StrArrayBuilder - a hash map, that has a sparse and dense storage. 

Module Invariants:
1. In case of allocation failure the whole program fails.
2. Dynamic arrays are owners of the memory.
3. StrArrayBuilder owns the memory while it is working. After the building of the array is done the ownership is transferd.

All data structures are constructed with the same size of 4 and grow by a factor of 2.
This choose is based on the input data. The stream can contain only a small amount of words and seting the start size to a bigger value would waste to much space.

Issue:
The separation of data and logic is not complete, the user of the memory module still needs to know how the data is stored to access it.   

#### Array:
This data structure holds data of type int. Its purpose is to provide bucktes for the string array builder hash map.
The growth of the Array is lazy handled, that is when the array is at full capacity and a new element is being inserted.
 The implementation of the Array is the text book implementation for a dynamic int array.

Owned Memory:
1. heap allocated static int array.
2. The Array pointer to it self.

Interface:
1. new_Array() - this function constructs a new Array and returns a pointer to it or NULL if the construction failed.
2. Error_Codes del_Array(Array *a) - this function is responsible for freeing the memory owned by the Array.
3. Error_Codes append_Array(Array *a, int i) - this function adds the passed int to the end of the Array and grows the Array if the capacity is at 100%. 

The error codes returned by the functions are:
1. NULL_ARGUMENT - when a null pointer is passed.
2. ALLOCATION_FAIL - when the append function can't allocate memory.

#### Str:
A dynamic char* array, a string. This data structure is the same as the Array the only difference comes from the fact that it stores null terminated characters.
The main difrence is in how the check is done for the capacity limit len + 1 == size, and the append method appends a '\0' at the end of the string, it inserts two new values to the end.

Owned Memory:
1. heap allocated static char *array.
2. The Str pointer to it self.

Interface:
1. new_Str() - this function constructs a new Str and returns a pointer to it or NULL if the construction failed.
2. Error_Codes del_Str(Str *a) - this function is responsible for freeing the memory owned by the Str.
3. Error_Codes append_Array(Str *a, char c) - this function adds the passed char to the end of the Str and grows the array if the len is one less then the size. 

The error codes returned by the functions are:
1. NULL_ARGUMENT - when a null pointer is passed.
2. ALLOCATION_FAIL - when the append function can't allocate memory.


#### StrArray:
This is a dynamic array of Str. Its purpose is to store the words as a list. It is the same dynamic array like the others the only difrence is that it stores Str.

Owned Memory:
1. heap allocated static Str** array.
2. The StrArray pointer to it self.

Interface:
1. new_StrArray() - this function constructs a new Str and returns a pointer to it or NULL if the construction failed.
2. Error_Codes del_StrArray(StrArray *a) - this function is responsible for freeing the memory owned by the Str.
3. Error_Codes append_StrArray(StrArray *a, Str *s) - this function adds the passed str to the end of the StrArray and grows the array if the len is one less then the size. 

The error codes returned by the functions are:
1. NULL_ARGUMENT - when a null pointer is passed.
2. ALLOCATION_FAIL - when the append function can't allocate memory.

#### StrArrayBuilder:
The StrArrayBuilder is the most complex data structure of the module. It handles the creation of unique words str array. 
To accomplish that it is implemented like a separate chaining colison resolution hash map that transfers ownership of its stored data. Unlike a regular hash map this data structure stores only keys, the key and the value are the same a word.
The inspiration for the design comes from the python dict implementation. The python dict has split data stores for memory efficency, ones is for hashing and the other holds key-value pairs.
Like the python dict the StrArrayBuilder has two data stores:
1. Array - a int sparse store that is used for hashing and holds indexes of the key in the StrArray.
2. StrArray - dense data storage that stores unique words, keys.

The reason for that is that the program needs a words list and building a word list from a hash map needs creation of another StrArray and apending to it the stored words.
The second reason is memory efficiency, instead of having a sparse array of StrArray there is only a sparse array of ints.

Owned Memory:
1. Array of Array** for hashing.
2. StrArray for storing words. 

Interface:
1. new_StrArrayBuilder() - constructor returns a pointer to StrArrayBuilder or NULL.
2. Error_Codes del_StrArrayBuilder(StrArrayBuilder *b) - destructor, frees the memory owned by the Str.
3. Error_Codes insert_StrArrayBuilder(StrArrayBuilder *b, Str *s) - this function adds the passed str to the end of the StrArray, by using a hash map to keep trakc of where the Str is inserted. 

The error codes returned by the functions are:
1. NULL_ARGUMENT - when a null pointer is passed.
2. ALLOCATION_FAIL - when the append function can't allocate memory.

### Fifth iteration - Error Codes:
Implemented error codes to preserve inforamtions for debuging.
