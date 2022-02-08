#include "ewelbornUtil.h"

ewelborn_dynamicArray* ewelborn_dynamicArray_initialize()
{
	ewelborn_dynamicArray* dynamicArray = malloc(sizeof(ewelborn_dynamicArray));
	if (dynamicArray == NULL) { return NULL; }
	dynamicArray->elements = 0;
	dynamicArray->maxElements = EWELBORN_DYNAMIC_ARRAY_STARTING_SIZE;
	dynamicArray->array = malloc(sizeof(void*) * dynamicArray->maxElements);
	if (dynamicArray->array == NULL) {
		free(dynamicArray);
		return NULL;
	}
	return dynamicArray;
}

bool ewelborn_dynamicArray_push(ewelborn_dynamicArray* dynamicArray, void* element)
{
	if (dynamicArray->elements >= dynamicArray->maxElements) {
		dynamicArray->maxElements *= EWELBORN_DYNAMIC_ARRAY_EXPANSION_CONSTANT;
		void** newArray = realloc(dynamicArray->array, sizeof(void*) * dynamicArray->maxElements);
		if (newArray == NULL) { return false; }
		dynamicArray->array = newArray;
	}

	dynamicArray->array[dynamicArray->elements++] = element;
	return true;
}

void ewelborn_dynamicArray_free(ewelborn_dynamicArray* dynamicArray)
{
	for (int i = 0; i < dynamicArray->elements; i++) {
		free(dynamicArray->array[i]);
	}
	free(dynamicArray->array);
	free(dynamicArray);
}

ewelborn_linkedList* ewelborn_linkedList_initializeEmpty()
{
	ewelborn_linkedList* list = malloc(sizeof(ewelborn_linkedList));
	if (list == NULL) { return NULL; }
	list->element = NULL;
	list->next = NULL;
	return list;
}

bool ewelborn_linkedList_insert(ewelborn_linkedList* list, void* newElement)
{
	ewelborn_linkedList* newList = ewelborn_linkedList_initializeEmpty();
	if (newList == NULL) { return false; }
	newList->element = newElement;

	if (list->next == NULL) {
		list->next = newList;
	}
	else {
		newList->next = list->next;
		list->next = newList;
	}

	return true;
}

bool ewelborn_linkedList_pushToBack(ewelborn_linkedList* list, void* newElement)
{
	while (list->next) { list = list->next; }
	ewelborn_linkedList_insert(list, newElement);
}

void ewelborn_linkedList_traverse(ewelborn_linkedList* list, void(*f)(void*))
{
	while (true) {
		f(list->element);
		if (list->next) {
			list = list->next;
		}
		else {
			break;
		}
	}
}

ewelborn_linkedList* ewelborn_linkedList_reverse(ewelborn_linkedList* list)
{
	ewelborn_linkedList* previousList = NULL;
	while (true) {
		//printf("v. %s\n", list->element);
		ewelborn_linkedList* nextList = NULL;
		if (list->next != NULL) {
			nextList = list->next;
		}
		if (previousList == NULL) {
			// We were the head of the list.. now we're the tail
			list->next = NULL;
		}
		else {
			list->next = previousList;
		}
		previousList = list;
		if (nextList != NULL) {
			list = nextList;
		}
		else {
			//printf("ret. %s\n", list->element);
			return list;
		}
	}
}

bool ewelborn_string_pushChar(ewelborn_string* eString, char c)
{
	// Add 1 to length to include null terminator
	if (eString->length + 1 >= eString->maxLength) {
		eString->maxLength *= EWELBORN_DYNAMIC_ARRAY_EXPANSION_CONSTANT;
		char* newString = realloc(eString->cstring, sizeof(char) * eString->maxLength);
		if (newString == NULL) { return false; }
		eString->cstring = newString;
	}

	eString->cstring[eString->length++] = c;
	eString->cstring[eString->length] = '\0';
	return true;
}

ewelborn_string* ewelborn_string_initializeEmpty()
{
	ewelborn_string* eString = malloc(sizeof(ewelborn_string));
	if (eString == NULL) { return NULL; }
	eString->length = 0;
	eString->maxLength = EWELBORN_DYNAMIC_ARRAY_STARTING_SIZE;
	eString->cstring = malloc(sizeof(char) * eString->maxLength);
	if (eString->cstring == NULL) {
		free(eString);
		return NULL;
	}
	eString->cstring[0] = '\0';
	return eString;
}

bool ewelborn_string_appendCString(ewelborn_string* estring, char* cstring)
{
	// TODO: Replace with a function that can calculate all of the
	// memory requirements at once, instead of using pushChar that may
	// resize the dynamic array multiple times during the for loop.
	for (int i = 0; cstring[i] != '\0'; i++) {
		if (ewelborn_string_pushChar(estring, cstring[i]) == false) { return false; }
	}

	return true;
}

ewelborn_string* ewelborn_string_initializeWithCString(char* cstring)
{
	ewelborn_string* estring = ewelborn_string_initializeEmpty();
	if (estring == NULL) { return NULL; }

	if (ewelborn_string_appendCString(estring, cstring) == false) { return NULL; }

	return estring;
}

char* ewelborn_string_getCString(ewelborn_string* eString)
{
	return eString->cstring;
}

void ewelborn_string_free(ewelborn_string* eString) {
	free(eString->cstring);
	free(eString);
}

ewelborn_string* ewelborn_string_clone(ewelborn_string* estring)
{
	ewelborn_string* clonedString = malloc(sizeof(ewelborn_string));
	if (clonedString == NULL) { return NULL; }
	clonedString->length = estring->length;
	clonedString->maxLength = estring->maxLength;
	clonedString->cstring = malloc(sizeof(char) * clonedString->maxLength);
	if (clonedString->cstring == NULL) {
		free(clonedString);
		return NULL;
	}

	// Copy the cstring from given estring
	memcpy(clonedString->cstring, estring->cstring, estring->length + 1);

	return clonedString;
}

void ewelborn_string_deleteLeft(ewelborn_string* estring, int n)
{
	if (n <= 0) { return; }
	if (n > estring->length) { n = estring->length; }
	for (int i = 0; i < estring->length; i++) {
		estring->cstring[i] = (i + n) >= (estring->length) ? '\0' : estring->cstring[i + n];
	}
}

void ewelborn_string_deleteRight(ewelborn_string* estring, int n)
{
	if (n <= 0) { return; }
	if (n > estring->length) { n = estring->length; }
	// We don't actually need to delete anything, we can simply reduce
	// the length of the estring and add the null terminator in.
	estring->length -= n;
	estring->cstring[estring->length] = '\0';
}

void ewelborn_string_trimLeft(ewelborn_string* estring)
{
	int shiftLeftBy = 0;

	// Start from the beginning of the string, and keep counting until
	// we encounter a character that isn't ' ' or '\t'. No other end condition
	// necessary: if the entire string is filled with whitespaces or tabs, then
	// the null terminator at the end will stop the loop.
	for (; estring->cstring[shiftLeftBy] == ' ' || estring->cstring[shiftLeftBy] == '\t'; shiftLeftBy++) {}

	ewelborn_string_deleteLeft(estring, shiftLeftBy);
}

void ewelborn_string_trimRight(ewelborn_string* estring)
{
	int shiftRightBy = 0;

	// Start from the end of the string, and keep counting until
	// we encounter a character that isn't ' ' or '\t', or when
	// shiftRightBy is equal to the length of the entire string,
	// i.e. the string is composed entirely of whitespaces or tabs.
	for (;
		estring->length - 1 - shiftRightBy == -1 ||
		estring->cstring[estring->length - 1 - shiftRightBy] == ' ' ||
		estring->cstring[estring->length - 1 - shiftRightBy] == '\t';
		shiftRightBy++) {
	}

	ewelborn_string_deleteRight(estring, shiftRightBy);
}

void ewelborn_string_trim(ewelborn_string* estring)
{
	ewelborn_string_trimLeft(estring);
	ewelborn_string_trimRight(estring);
}

int ewelborn_string_findChar(ewelborn_string* estring, char c, int offset)
{
	if (offset < 0 || offset >= estring->length) { return -1; }

	for (int i = offset; i < estring->length; i++) {
		if (estring->cstring[i] == c) { return i; }
	}

	return -1;
}

void ewelborn_string_slice(ewelborn_string* estring, int start, int end)
{
	ewelborn_string_deleteRight(estring, estring->length - end);
	ewelborn_string_deleteLeft(estring, start);
}

ewelborn_dynamicArray* ewelborn_string_split(ewelborn_string* estring, char c)
{
	ewelborn_dynamicArray* results = ewelborn_dynamicArray_initialize();
	if (results == NULL) { return NULL; }

	// Keep attempting to find the character in the estring. If we find
	// the character, then slice the estring from offset to i (not inclusive)
	// and store the slice in the array. If we do not find the character,
	// then take whatever's left of the string and store it in the array.
	int offset = 0;
	while (true) {
		int i = ewelborn_string_findChar(estring, c, offset);
		if (i >= 0) {
			ewelborn_string* slice = ewelborn_string_clone(estring);
			ewelborn_string_slice(slice, offset, i);
			ewelborn_dynamicArray_push(results, slice);
			//printf("slice slice [%d,%d): %s\n", offset, i, ewelborn_string_getCString(slice));
			offset = i + 1;
		}
		else {
			break;
		}
	}
	ewelborn_string* finalSlice = ewelborn_string_clone(estring);
	ewelborn_string_deleteLeft(finalSlice, offset);
	ewelborn_dynamicArray_push(results, finalSlice);
	//printf("final slice: %s\n", ewelborn_string_getCString(finalSlice));

	return results;
}
