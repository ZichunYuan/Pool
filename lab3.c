/*Zichun Yuan*/
#include <stdio.h>
#include <math.h>
#include "lib8ball.h"
#include "linkedlist.h"
#include "debug.h"
#include "structs.h"
#include "dimensions.h"
#include "table.h"
#include "memo.h"
#include "io.h"

/*Function that always return true;*/
int always_true(void *data)
{
	return 1;
}

/*Compute the frame time of all balls on the table.*/
double dT(void *data)
{
	/*Find the largest velocity, which corresponds to smallest dT*/
	struct Ball *bp = data;	
	double vLargest, xVel= bp->xV, yVel = bp->yV;
	double v = 0.5 * RADIUS / bp->simPt->dT;
	
	/*Deal with 0 and negative velocity*/	
	if(xVel<0) xVel = -xVel;
	if(yVel<0) yVel = -yVel;
		
	if(xVel > yVel) vLargest = xVel;
	else vLargest = yVel;

	if(v>vLargest) return 0.5*RADIUS/v; 
	else return 0.5*RADIUS/vLargest;
}
/*Print the data of the ball.*/
void print(void *data)
{
	struct Ball *bp = data;
	/*Print the message.*/
	if(!off_table(data)) printf("Ball # %2d is at (%6.3f, %6.3f) moving (%9.4f, %10.4f)\n", bp->num, bp->x, bp->y, bp->xV, bp->yV);
	
}

/*A function that checks if the ball on the table is still moving.*/
int still_moving(void *data)
{
	/*return 1 if still moving, 0 otherwise.*/
	struct Ball *bp = data;
	if(bp->xV!=0 || bp->yV!=0) return 1; /*still moving*/
	return 0;
}

/*Move the ball, applying friction and reflection to it.*/
void action(void *data)
{
	struct Ball *bp = data;
	move(bp);
}

/*Disposal the ball and free the memory allocated earlier.*/
void disposal (void *data)
{
	free_ball(data);
}

/*Helper function of updating the ball's movement.*/
void updating(struct Sim *headPt)
{
	deleteSome(&headPt->storagePt, off_table, disposal, TEXT);
	headPt->time+=headPt->dT;
	iterate(headPt->storagePt, action);
}

/*Helper function that prints message and delete all the balls that don't move at the end.*/
void ending(struct Sim *headPt)
{
	/*If there are non-moving balls on the table, print them*/
	if(headPt->storagePt!=NULL){
	printf("\nAt time %7.4f: \n", headPt->time);
	iterate(headPt->storagePt, print);
	}
	printf("\n"); /*print a black line*/
	printf("Simulation ends at sim elapsed time of %7.4f seconds.\n", headPt->time);
	deleteSome(&headPt->storagePt,always_true, disposal,TEXT);
}

/*text output*/
void text(struct Sim *headPt)
{
	while(headPt->storagePt!=NULL && some(headPt->storagePt,still_moving)){
	/*printing*/
	printf("\nAt time %7.4f: \n", headPt->time);
	iterate(headPt->storagePt, print);
	/*updating*/
	updating(headPt);
	}
	ending(headPt);
}

/*Helper function for graphic that display the ball on the table.*/
void draw_a_ball(void *data)
{
	struct Ball *bp = data;
	if(!off_table(data))eb_ball(bp->num,bp->x,bp->y);
}

/*graphic output*/
void graphic(struct Sim *headPt)
{
	while(headPt->storagePt!=NULL && some(headPt->storagePt,still_moving))
	{	
		eb_clear();
		iterate(headPt->storagePt, draw_a_ball); /*Put every ball on the table*/
		eb_refresh();
		millisleep((int)(headPt->dT * 1000)); /*have it wait so that we can see.*/
		updating(headPt); /*Update every ball with its action.*/
	}
	deleteSome(&headPt->storagePt,always_true, disposal,TEXT);
	millisleep(2000); /*Stop for 2 seconds.*/
}

/*Helper function that keeps the main short and concise. It displays the info of the balls either in text or graphic.*/
void run(struct Sim *headPt)
{
	if(TEXT) text(headPt);
	if(GRAPHICS && eb_initialize(DEBUG)){
		graphic(headPt);
		eb_teardown(); /*return to normal.*/
	}
}

/*main function for lab3 that implements all funcionality of a pool*/
int main()
{
	double timeBegin, realTime; /*declaring variables*/

	struct Sim head = {0,0.1,NULL};
	struct Sim *headPt = &head;

	read_balls(headPt);

	headPt->dT=least(headPt->storagePt, dT);

	timeBegin = now();
	run(headPt);
	realTime = now() - timeBegin; /*Measure the performance of my code.*/
	printf("Total run time is %f seconds.\n",realTime);
	return 0;
}
