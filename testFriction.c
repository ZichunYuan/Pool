/*Zichun Yuan 
 * A prototype testing motions of the ball.
 * First implemented friction to the ball, which slows the ball down.
 */

#include <stdio.h>
#include "structs.h"
#include "lib8ball.h"
#include "linkedlist.h"
#include "dimensions.h"
#include <math.h>
#define DEBUG 1

/*Take existing frame time and a velocity and computers the new frame time*/
void dTime(struct Ball *bp)
{
        /*Find the largest velocity, which corresponds to smallest dT*/
	double vLargest, xVel= bp->xV, yVel = bp->yV;
	double v = 0.5 * RADIUS / bp->simPt->dT;

	/*Deal with 0 and negative velocity*/	
	if(xVel<0) xVel = -xVel;
	if(yVel<0) yVel = -yVel;
		
	if(xVel > yVel) vLargest = xVel;
	else vLargest = yVel;
	
	/*if(DEBUG)printf("dTime: dT is %.3lf\n", odT);*/

	if(v>vLargest) bp->simPt->dT = 0.5*RADIUS/v; 
	else bp->simPt->dT = 0.5*RADIUS/vLargest;
}

/*Function implementing friction*/
void friction(struct Ball *bp)
{
	double V, dV, percent;
	/*compute dT which will be used by friction.*/
	dTime(bp);
	if(DEBUG)printf("dT is %f.\n", bp->simPt->dT);
	dV = MU_ROLLING * G_IPS2 * bp->simPt->dT;
 	V = sqrt(bp->xV * bp->xV + bp->yV * bp->yV);
	
	if(DEBUG)printf("Before, dV is %f, V is %f, xV is %f, yV is %f.\n", dV, V, bp->xV, bp->yV);

	if(dV > V){
		bp->xV = 0;
		bp->xV = 0;
	}else{
		percent = dV / V;
		/*percent remaining is (1-percent)*/
		bp->xV *= (1-percent);
		bp->yV *= (1-percent);
	}
	if(DEBUG)printf("After, dV is %f, V is %f, xV is %f, yV is %f.\n", dV, V, bp->xV, bp->yV);
}

void print_ball(struct Ball *bp)
{
	printf("Ball # %2d is at (%6.3f, %6.3f) moving (%9.4f, %10.4f)\n", bp->num, bp->x, bp->y, bp->xV, bp->yV);
}

int main()
{
	/*Test how to change the value of the members of structures.*/
	struct Sim pooltable = { 0.0, 0.1, NULL};
	struct Ball xball = {8, 12.5, 12.5, 12.0, 5.0, NULL};
	struct Ball *bp = &xball;

	xball.simPt = &pooltable; /*pointer to struct sim*/

	print_ball(bp);
	friction(bp);
	print_ball(bp);
	/*
	printf("Before dT is %f.\n",bp->dT);
	bp->dT = 0.2;
	printf("After dT is %f.\n",bp->dT);

	printf("Before time is %f.\n",bp->time);
	addTime(bp);
	printf("After time is %f.\n",bp->time);
	*/
	return 0;
}
