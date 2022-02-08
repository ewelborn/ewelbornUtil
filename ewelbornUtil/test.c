#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "ewelbornUtil.h"

/*
	This is the driver file for testing ewelbornUtil.h

*/

void test_helloWorld()
{
	ewelborn_string* estring = ewelborn_string_initializeWithCString("Hello, world!");
	bool success = strcmp(ewelborn_string_getCString(estring),"Hello, world!") == 0;
	free(estring);
	assert(success == true);
}

int main(void)
{
	// Yes, I'm aware that it's ironic to use the tested material
	// inside the tester code.
	ewelborn_dynamicArray* tests = ewelborn_dynamicArray_initialize();

	// Add new tests here.
	ewelborn_dynamicArray_push(tests, &test_helloWorld);

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