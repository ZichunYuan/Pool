/* Zichun Yuan 
 * Table file that contains functions defining the balls' movements, including basic movement,
 * friction, and reflection.
 */

#include <stdio.h>
#include "structs.h"
#include "lib8ball.h"
#include "linkedlist.h"
#include "debug.h"
#include "dimensions.h"
#include <math.h>

/*Check to see if the ball is on or off table*/
int off_table (void *data)
{
	struct Ball *bp = data;
	/*return 1 if off table, 0 when not*/
	if(bp->x>LENGTH||bp->x<0) return 1;
	if(bp->y>WIDTH||bp->y<0) return 1;
	return 0;
}

/*Move the ball in x position.*/
static void xPos(struct Ball *bp)
{
	/*x = x + xV * dT*/
	bp->x = bp->x + bp->xV * bp->simPt->dT;
}

/*Move the ball in y position.*/
static void yPos(struct Ball *bp)
{
	bp->y = bp->y + bp->yV * bp->simPt->dT;
}

/*Determine if the ball is about to hit the left rail.*/
static int into_left_rail(struct Ball *bp)
{
	return (bp->x < RADIUS) && (bp->y <(WIDTH-C_POCKET)) && (bp->y>C_POCKET);
}

/*Reflect on the left rail.*/
static void reflect_left(struct Ball *bp)
{
	bp->xV = -bp->xV;
	/*Calculate the bounce back distance of the ball*/
	bp->x = (RADIUS - bp->x) + RADIUS;
	bp->xV *= 0.5;
	bp->yV *= 0.5;

}

/*Determine if the ball is about to hit the right rail.*/
static int into_right_rail(struct Ball *bp)
{
	return ((LENGTH-bp->x) < RADIUS)  && (bp->y <(WIDTH-C_POCKET)) && (bp->y>C_POCKET);
}

/*Reflect on the right rail.*/
static void reflect_right(struct Ball *bp)
{
	bp->xV = -bp->xV;
	/*Calculate the bounce back distance of the ball*/
	bp->x = LENGTH-((RADIUS - (LENGTH-bp->x)) + RADIUS);
	bp->xV *= 0.5;
	bp->yV *= 0.5;
}

/*Determine if the ball is about to hit the bottom rail.*/
static int into_bottom_rail(struct Ball *bp)
{
	return (bp->y < RADIUS) && (((C_POCKET < bp->x)&&(bp->x < S_POCKET_START)) || ((bp->x > S_POCKET_END)&&(bp->x < (LENGTH - C_POCKET))));
}

/*Reflect on the bottom rail.*/
static void reflect_bottom(struct Ball *bp)
{
	bp->yV = -bp->yV;
	/*Calculate the bounce back distance of the ball*/
	bp->y = (RADIUS - bp->y) + RADIUS;
	bp->xV *= 0.5;
	bp->yV *= 0.5;
}

/*Determine if the ball is about to hit the top rail.*/
static int into_top_rail(struct Ball *bp)
{
	return ((WIDTH-bp->y) < RADIUS) && (((C_POCKET < bp->x)&&(bp->x < S_POCKET_START)) || ((bp->x > S_POCKET_END)&&(bp->x < (LENGTH - C_POCKET))));
}

/*Reflect on the top rail.*/
static void reflect_top(struct Ball *bp)
{
	bp->yV = -bp->yV;
	/*Calculate the bounce back distance of the ball*/
	bp->y = WIDTH-((RADIUS - (WIDTH-bp->y)) + RADIUS);
	bp->xV *= 0.5;
	bp->yV *= 0.5;
}

/*Move the ball according to velocity.*/
static void move_ball(struct Ball *bp)
{
	xPos(bp);
	yPos(bp);
}

/*Reflect the ball if it hits a rail*/
static void reflect(struct Ball *bp)
{
	if(into_left_rail(bp)) reflect_left(bp);
	if(into_right_rail(bp)) reflect_right(bp);
	if(into_top_rail(bp)) reflect_top(bp);
	if(into_bottom_rail(bp)) reflect_bottom(bp);
}

/*Function implementing friction*/
static void friction(struct Ball *bp)
{
	double V, dV, percent;

	if(DEBUG)printf("dT is %f.\n", bp->simPt->dT);

	dV = MU_ROLLING * G_IPS2 * bp->simPt->dT;
 	V = sqrt(bp->xV * bp->xV + bp->yV * bp->yV);
	
	if(DEBUG)printf("Before, dV is %f, V is %f, xV is %f, yV is %f.\n", dV, V, bp->xV, bp->yV);

	if(dV > V){
		bp->xV = 0;
		bp->yV = 0;
	}else{
		percent = dV / V;
		/*percent remaining is (1-percent)*/
		bp->xV *= (1-percent);
		bp->yV *= (1-percent);
	}
	if(DEBUG)printf("Before, dV is %f, V is %f, xV is %f, yV is %f.\n", dV, V, bp->xV, bp->yV);
}

/*A function that combines all movement of a ball*/
void move(struct Ball *bp)
{
	move_ball(bp);
	reflect(bp);
	friction(bp);
}


