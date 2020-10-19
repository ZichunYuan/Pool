/*Zichun Yuan 
 *Code deals with allocating and freeing memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "structs.h"

/*Allocate a struct Ball in the linked list.*/
struct Ball* allocate_ball()
{
	static int count = 0;
	struct Ball *bp = (struct Ball*)malloc(sizeof(*bp));

	/*Deal with special cases*/
	if(bp == NULL) {
	if(TEXT)printf("Allocation failed. Function terminates.\n");
	return NULL;
	}
	count++;
	if(TEXT)printf("DIAGNOSTIC: %d balls allocated.\n", count);
	return bp;
}

/*Free the struct Ball if it is no longer needed.*/
void free_ball(void *data)
{
	static int count = 0;
	count++;
	if(TEXT)printf("DIAGNOSTIC: %d balls freed.\n", count);
	free(data);
}

