#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "ewelbornUtil.h"

/*
	This is the driver file for testing ewelbornUtil.h

*/

// Does a simple "Hello, world!" work with estrings?
void test_helloWorld()
{
	ewelborn_string* estring = ewelborn_string_initializeWithCString("Hello, world!");
	bool success = strcmp(ewelborn_string_getCString(estring),"Hello, world!") == 0;
	free(estring);
	assert(success == true);
}

// Does the queue work if we do some generic pushing and popping?
void test_queue_genericTest()
{
	ewelborn_queue* queue = ewelborn_queue_initialize(10,false);
	bool success = true;

	int a = 5;
	int b = 6;
	int c = 12;
	int d = -2;

	ewelborn_queue_push(queue, &a);
	ewelborn_queue_push(queue, &b);
	ewelborn_queue_push(queue, &c);

	success = success && *((int*)ewelborn_queue_pop(queue)) == a;
	success = success && *((int*)ewelborn_queue_pop(queue)) == b;
	success = success && *((int*)ewelborn_queue_pop(queue)) == c;

	free(queue);
	assert(success == true);
}

int main(void)
{
	// Yes, I'm aware that it's ironic to use the tested material
	// inside the testing code.
	ewelborn_dynamicArray* tests = ewelborn_dynamicArray_initialize();

	// Add new tests here.
	ewelborn_dynamicArray_push(tests, &test_helloWorld);
	ewelborn_dynamicArray_push(tests, &test_queue_genericTest);

	printf("Running tests..\n");

	// Run each test one by one. All tests should use assert to force
	// a hard crash and write an error to the output.
	for (int i = 0; i < tests->elements; i++) {
		// Convert the void pointer to a function pointer of type
		// void functionName(void) and execute
		((void(*)(void)) tests->array[i])();
	}
	
	printf("All tests ran successfully.\n");
}