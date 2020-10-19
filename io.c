/*Zichun Yuan*/
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "structs.h"
#include "linkedlist.h"
#include "memo.h"

/*Comparison Function for insert that sorts the list in num order.*/
static int num_order(void *data1, void *data2)
{
	/*Even though it is a void pointer, we know that it points to struct Ball*/
	struct Ball *bp1 = data1;
	struct Ball *bp2 = data2;
	return bp1->num < bp2->num;
}

/*Helper function for read_one that puts the data into a ball.*/
static void put_value(struct Ball *bp, int num, double x, double y, double xV, double yV)
{
	bp->num = num;
	bp->x = x;
	bp->y= y;
	bp->xV = xV;
	bp->yV = yV;
}

/*Reading data from the file and stores them in struct Ball, then turn them into a linked list.*/
static int read_one(struct Sim *pooltable)
{
	struct Ball *bp;
	int num;
	double x, y, xV, yV;
	/*Assign variables their values.*/
	int scanValue = scanf("%d %lf %lf %lf %lf",&num,&x,&y,&xV,&yV);
	
	if(scanValue== 5){
		bp = allocate_ball(pooltable);
		put_value(bp,num,x,y,xV,yV);
		bp->simPt = pooltable;
		/*if insert fails*/
		if(!insert(&pooltable->storagePt, bp, num_order, TEXT)){
			free(bp);			
			/*error message~!~*/
			if(TEXT) printf("ERROR: insert FAILED! Nodes failed to allocate.\n");
		}
	}
	return scanValue;
}
/*Reads every ball from a file into a linked list.*/
void read_balls(struct Sim *pooltable)
{
	int scanValue = read_one(pooltable);
	while(scanValue == 5) scanValue = read_one(pooltable);

	printf("read_one: scanf returns %d\n", scanValue);
}
