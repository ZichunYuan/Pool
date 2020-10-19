/*Zichun Yuan 
 * A prototype testing motions of the ball.
 * First implemented reflection of the ball, which bounces on the rails.
 */

#include <stdio.h>
#include "structs.h"
#include "lib8ball.h"
#include "linkedlist.h"
#include "dimensions.h"
#include <math.h>
#define DEBUG 1

/*Determine if the ball is about to hit the left rail.*/
int into_left_rail(struct Ball *bp)
{
	return (bp->x < RADIUS) && (bp->y <(WIDTH-C_POCKET)) && (bp->y>C_POCKET);
}

/*Reflect on the left rail.*/
void reflect_left(struct Ball *bp)
{
	bp->xV = -bp->xV;
	/*Calculate the bounce back distance of the ball*/
	bp->x = (RADIUS - bp->x) + RADIUS;
	bp->xV *= 0.5;
	bp->yV *= 0.5;

}

/*Determine if the ball is about to hit the right rail.*/
int into_right_rail(struct Ball *bp)
{
	return ((LENGTH-bp->x) < RADIUS)  && (bp->y <(WIDTH-C_POCKET)) && (bp->y>C_POCKET);
}

/*Reflect on the right rail.*/
void reflect_right(struct Ball *bp)
{
	bp->xV = -bp->xV;
	/*Calculate the bounce back distance of the ball*/
	bp->x = LENGTH-((RADIUS - (LENGTH-bp->x)) + RADIUS);
	bp->xV *= 0.5;
	bp->yV *= 0.5;
if(DEBUG)printf("Got here!\n");
}

/*Determine if the ball is about to hit the bottom rail.*/
int into_bottom_rail(struct Ball *bp)
{
	return (bp->y < RADIUS) && (((C_POCKET < bp->x)&&(bp->x < S_POCKET_START)) || ((bp->x > S_POCKET_END)&&(bp->x < (LENGTH - C_POCKET))));
}

/*Reflect on the bottom rail.*/
void reflect_bottom(struct Ball *bp)
{
	bp->yV = -bp->yV;
	/*Calculate the bounce back distance of the ball*/
	bp->y = (RADIUS - bp->y) + RADIUS;
	bp->xV *= 0.5;
	bp->yV *= 0.5;
}

/*Determine if the ball is about to hit the top rail.*/
int into_top_rail(struct Ball *bp)
{
	return ((WIDTH-bp->y) < RADIUS) && (((C_POCKET < bp->x)&&(bp->x < S_POCKET_START)) || ((bp->x > S_POCKET_END)&&(bp->x < (LENGTH - C_POCKET))));
}

/*Reflect on the top rail.*/
void reflect_top(struct Ball *bp)
{
	bp->yV = -bp->yV;
	/*Calculate the bounce back distance of the ball*/
	bp->y = WIDTH-((RADIUS - (WIDTH-bp->y)) + RADIUS);
	bp->xV *= 0.5;
	bp->yV *= 0.5;
	

}

void print_ball(struct Ball *bp)
{
	printf("Ball # %2d is at (%6.3f, %6.3f) moving (%9.4f, %10.4f)\n", bp->num, bp->x, bp->y, bp->xV, bp->yV);
}


int main()
{
	struct Ball xball = {10,99,46,-5,0,NULL};
	struct Ball *bp = &xball;
	print_ball(bp);

	if(into_left_rail(bp)) reflect_left(bp);
	if(into_right_rail(bp)) reflect_right(bp);
	if(into_top_rail(bp)) reflect_top(bp);
	if(into_bottom_rail(bp)) reflect_bottom(bp);
	print_ball(bp);

	return 0;
}
