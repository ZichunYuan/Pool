/*Zichun Yuan 
 * A prototype testing structures.
 * Later adding motion into it. Testing motion as well.
 */

#include <stdio.h>
#include "structs.h"
#include "lib8ball.h"
#include "linkedlist.h"
#include "dimensions.h"
#include <math.h>
#define DEBUG 1

void print_ball(struct Ball *bp)
{
	printf("Ball # %2d is at (%6.3f, %6.3f) moving (%9.4f, %10.4f)\n", bp->num, bp->x, bp->y, bp->xV, bp->yV);
}

int main()
{
	double y;
	/* et, dT, head pointer */
	struct Sim pooltable = { 0.0, 0.1, NULL};

	/* ball number, X, Y, VX, VY, sim pointer */
	struct Ball xball = {8, 95.0, 25.0, 100.0, 0.0, NULL};
	struct Ball *bp = &xball;

	xball.simPt = &pooltable; /*pointer to struct sim*/
	
	/*compute dT which will be used by friction.*/
	/*dTime(bp);*/


	printf("dT is %f\n.",bp->simPt->dT);

	print_ball(bp);

	return 0;

}
