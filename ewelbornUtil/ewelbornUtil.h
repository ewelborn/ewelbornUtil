/*
	Single .h and .c file that contains everything you'd need
	for your C project - hopefully!

	Version 0.1.0
	https://github.com/ewelborn/ewelbornUtil/

	Naming rules:
		All public functions, structs, and types, must be prefixed
		with "ewelborn_" in order to avoid polluting the namespace
		of whatever project uses this header.

		Private functions, structs, and types may be named whatever.

		Any function that operates directly on a datastructure,
		(such as dynamicArray) should be named as follows:
			ewelborn_dataStructure_method
		Ex.
			ewelborn_dynamicArray_insert
*/

#ifndef EWELBORN_UTIL // Start of header guard clause
#define EWELBORN_UTIL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

// *** DATASTRUCTURES

#define EWELBORN_DYNAMIC_ARRAY_STARTING_SIZE 8
#define EWELBORN_DYNAMIC_ARRAY_EXPANSION_CONSTANT 2
struct ewelborn_dynamicArray {
	// All the elements of a dynamic array are pointers, because we can be sure
	// that sizeof(void*) is consistent and known at compile time. Doing pointer
	// arithmetic with element sizes not known at compile time is difficult.
	void** array;
	int elements; // Number of elements in the array
	int maxElements; // Maximum number of elements given current array allocation
} typedef ewelborn_dynamicArray;

// Attempts to create a dynamic array. If the creation is successful, then
// the dynamic array will be returned - otherwise, it will return null.
ewelborn_dynamicArray* ewelborn_dynamicArray_initialize();

// Attempts to insert an element (given by a pointer) at the end of
// the dynamic array, which will be resized if the array isn't large enough.
// Returns true if the insertion is successful, returns false otherwise.
bool ewelborn_dynamicArray_push(ewelborn_dynamicArray* dynamicArray, void* element);

// This function will free all memory allocated to a given dynamicArray.
// WARNING! This will attempt to free all element pointers in the dynamicArray,
// if you want to keep your elements, then copy them to a safe place!
void ewelborn_dynamicArray_free(ewelborn_dynamicArray* dynamicArray);

// This function will iterate over every element in the given dynamic array
// and will call the given function on the element.
void ewelborn_dynamicArray_traverse(ewelborn_dynamicArray* dynamicArray, void(*f)(void*));

struct ewelborn_linkedList {
	void* element;
	struct ewelborn_linkedList* next;
} typedef ewelborn_linkedList;

// Attempts to create a linked list. If successful, the new list will be
// returned, otherwise, the function will return null.
ewelborn_linkedList* ewelborn_linkedList_initializeEmpty();

// This function will attempt to insert an element after the given linked list
// node. If there is already a linked list node after the current node, then
// it will be pushed up to make room. Returns true if successful, returns
// false otherwise.
bool ewelborn_linkedList_insert(ewelborn_linkedList* list, void* newElement);

// This function will attempt to insert an element at the end of the
// given linked list. Returns true if successful, returns false otherwise.
bool ewelborn_linkedList_pushToBack(ewelborn_linkedList* list, void* newElement);

// This function will iterate over every element in the given linked list
// and will call the given function on the element
void ewelborn_linkedList_traverse(ewelborn_linkedList* list, void(*f)(void*));

// This function will reverse a given linked list, and will
// return the new head of the list
ewelborn_linkedList* ewelborn_linkedList_reverse(ewelborn_linkedList* list);

// *** STRING MANIPULATION

// ewelborn_strings, or Estrings, are wrappers for Cstrings that provide
// some additional functionality.
//	1.	Estrings are backed by dynamic arrays, allowing them to
//			expand indefinitely.
//	2.	Estrings have their length available at all times, O(1) instead of O(n)
//  3.	Estrings are guaranteed to be null terminated so long as the
//			backing cstring is not directly manipulated.
//	4.	Estrings have functions that provide common string manipulation,
//			such as 
struct ewelborn_string {
	// This is a dynamic array, but we don't want to use the generic
	// ewelborn_dynamicArray implementation because that implementation
	// has pointer elements, which is way too much overhead compared to
	// char elements.
	char* cstring;
	int length; // Not including the null terminator
	int maxLength; // Including the null terminator
} typedef ewelborn_string;

// Attempts to insert a character at the end of the string while retaining
// the null terminator at the end and resizing the dynamic array if necessary.
// Returns true if push is successful, false otherwise.
bool ewelborn_string_pushChar(ewelborn_string* eString, char c);

// Returns the nth character in the estring, or \0 if n is greater than
// or equal to the estring's length, or less than 0.
char ewelborn_string_getChar(ewelborn_string* eString, int n);

// Attempts to create an empty estring, i.e. a string that only contains a
// null terminator character. Returns the estring if successful, returns
// null otherwise.
ewelborn_string* ewelborn_string_initializeEmpty();

// This function will attempt to append a given cstring to the end of
// a given estring. Returns true if successful, false otherwise. This
// function is *not* guaranteed to keep the estring unmodified if unsuccessful.
bool ewelborn_string_appendCString(ewelborn_string* estring, char* cstring);

// This function will attempt to append the appendString estring to the end of
// the given estring. Returns true if successful, false otherwise.
bool ewelborn_string_append(ewelborn_string* estring, ewelborn_string* appendString);

// Attempts to create an estring with a given cstring value. If the user
// wants to initialize an estring with another estring, they should look
// at ewelborn_string_clone() instead. Returns the estring if successful,
// returns null otherwise.
ewelborn_string* ewelborn_string_initializeWithCString(char* cstring);

// As of writing, estrings are backed with dynamic arrays, but this
// may not always be true. This function is guaranteed to return a
// character array (cstring) that represents the given estring,
// regardless of the estring's implementation.
// TODO: Look at memory management on this
char* ewelborn_string_getCString(ewelborn_string* eString);

// This function will free all memory allocated to a given estring.
void ewelborn_string_free(ewelborn_string* eString);

// Given a pre-existing estring, this function will create a new
// estring that is identical to the given estring. This is useful
// for performing string manipulation, as you may wish to keep an
// unedited copy of the string. Returns an estring if successful,
// returns null otherwise.
ewelborn_string* ewelborn_string_clone(ewelborn_string* estring);

// This function will move each character in the estring n places
// to the left, with the leftmost n characters being erased. The
// length will be reduced by n. If n <= 0 then this function
// will do nothing.
/*void ewelborn_string_shiftLeft(ewelborn_string* estring, int n)
{
	// "fifo\0"
	// If n is <= 0, then no shifting is necessary. Otherwise,
	// shift the entire string to the left.
	if (n <= 0) { return; }
	if (n > estring->length)
	for (int i = n; i < estring->length + 1; i++) {
		estring->cstring[i - n] = estring->cstring[i];
	}
}*/

// TODO: Implement shiftRight function that pads whitespace to the left

// This function will delete the first n characters of the estring.
// If n <= 0 then this function will do nothing. If n is greater than
// the estring's length, then n will be truncated to the estring's length.
void ewelborn_string_deleteLeft(ewelborn_string* estring, int n);

// This function will delete the last n characters of the estring.
// If n <= 0 then this function will do nothing. If n is greater than
// the estring's length, then n will be truncated to the estring's length.
void ewelborn_string_deleteRight(ewelborn_string* estring, int n);

// This function will remove all whitespace ' ' and tabs '\t' that
// precede the estring.
void ewelborn_string_trimLeft(ewelborn_string* estring);

// This function will remove all whitespace ' ' and tabs '\t' that
// follow the estring.
void ewelborn_string_trimRight(ewelborn_string* estring);

// This function will remove all whitespace ' ' and tabs '\t' that
// precede and follow the estring.
void ewelborn_string_trim(ewelborn_string* estring);

// This function will attempt to find a given char in a given estring,
// it will return the char's position in the string if successful, or
// -1 if the char does not exist in the string. If offset is greater than 0,
// then the function will only search the string starting from offset.
//
// The returned character index is relative to the estring, not the offset,
// i.e. findChar("hi world",'w',0) and findChar("hi world",'w',2) will both
// return 3.
int ewelborn_string_findChar(ewelborn_string* estring, char c, int offset);

// This function will slice a given estring so that only the characters
// within the start and end (not inclusive) boundaries are left remaining.
// Ex. slice("Hello, world!",2,4) will modify the estring to be "ll"
void ewelborn_string_slice(ewelborn_string* estring, int start, int end);

// This function will split a given estring on a certain character, and
// return a dynamic array of all the estrings that arise from the result
// of the split, or null if the function is unsuccessful. Ex.
//	estring1 is equivalent to "Hi. hello. how are you?"
//	ewelborn_string_split(estring1, '.') will return the dynamic array:
//	{"Hi", " hello", " how are you?"}
ewelborn_dynamicArray* ewelborn_string_split(ewelborn_string* estring, char c);

// This function will delete the nth character in the estring. If n is
// greater than or equal to the estring's length, or n is less than 0,
// then nothing will happen.
void ewelborn_string_deleteChar(ewelborn_string* estring, int n);

// If the nth character in the estring is equal to c, then the nth character
// will be deleted, and the string will be moved and resized to fill the gap
// if necessary. If the nth character is *not* equal to c, then nothing happens.
// The function returns true if the nth character is consumed, false otherwise.
// The function returns false if n is greater than or equal to the estring's length,
// or less than 0.
bool ewelborn_string_consumeChar(ewelborn_string* eString, char c, int n);

// This function is an implementation of sprintf for estrings. Given an estring
// filled with printf format modifiers and a variable list of arguments, this
// function will generate the result that printf would give for the same
// arguments, but will store it back into the estring instead. Example:
//	ewelborn_string_snprintf(estring1{"Name: %s, Age: %d"},"Ethan",21)
// estring1 will now be "Name: Ethan, Age: 21". This function returns true
// if successful, false otherwise.
bool ewelborn_string_sprintf(ewelborn_string* estring, ...);

// *** FILE MANIPULATION

// This function will attempt to open the file at the given file path and
// read it. If successful, the function will return a dynamic array of
// estring pointers that are the individual lines in the file. Otherwise,
// the function will return null.
ewelborn_dynamicArray* ewelborn_readLinesFromFile(ewelborn_string* filePath);

// This function will attempt to open the file at the given file path and
// write the content string to it. If the file has not been created, then
// this function will create it. This function returns true if the write
// is successful, false otherwise.
bool ewelborn_writeStringToFile(ewelborn_string* filePath, ewelborn_string* content);

#endif // End of header guard clause