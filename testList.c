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

/*Testing to traverse through a linkedlist.
  Pass the reference of the head pointer.
*/
void traverse(struct Ball *head)
{

	head = head->simPt->storagePt;
	if(DEBUG) printf("In traverse x value is %f\n",head->x);


}


void read_one(){
	/* et, dT, head pointer */
	double x, y, xV, yV;
	int num;
	struct Sim pooltable1 = { 0.0, 0.1, NULL};
	/* ball number, X, Y, VX, VY, sim pointer = {8, 50.0, 25.0, 20.0, 10.0, NULL}*/
	struct Ball xball1={1,1,1,1,1,NULL};
	struct Ball *bp1;

	/*Linked List content*/
	struct Sim pooltable2 = { 0.0, 0.1, NULL};
	struct Ball xball2={2,2,2,2,2.0,NULL};
	struct Ball *bp2;
	struct Ball *head;

	/*xball = {num,x,y,xV,yV,&pooltable};
	int scanVal = scanf("%d%lf%lf%lf%lf",&num,&x,&y,&xV,&yV);*/

	/*this doesn't work, why? xball = {0,12.5,12.5,12.0,5.0,NULL};*/
	bp1 = &xball1;
	bp1->simPt = &pooltable1;

	bp2 = &xball2;
	bp2->simPt = &pooltable2;

	bp1->simPt->storagePt = bp2; /*Passes the address, not the pointer.*/

	/*cant dereference void pointer ! 
	if(DEBUG) printf("x value is %f\n",bp1->simPt->storagePt->x);*/

	/*instead*/
	head = bp1;
	if(DEBUG) printf("Before x value is %f\n",head->x);

	/*here it works because I am assigning the head pointer value
	  directly. If I pass it to a function, I need to pass the referece*/
	head = head->simPt->storagePt; /*make head point to bp2.*/
	if(DEBUG) printf("After x value is %f\n",head->x);
	
	

}

int main()
{
	/*code from previous function.*/
	struct Sim pooltable1 = { 0.0, 0.1, NULL};
	/* ball number, X, Y, VX, VY, sim pointer = {8, 50.0, 25.0, 20.0, 10.0, NULL}*/
	struct Ball xball1={1,1,1,1,1,NULL};
	struct Ball *bp1;

	/*Linked List content*/
	struct Sim pooltable2 = { 0.0, 0.1, NULL};
	struct Ball xball2={2,2,2,2,2.0,NULL};
	struct Ball *bp2;
	struct Ball *head;

	/*xball = {num,x,y,xV,yV,&pooltable};
	int scanVal = scanf("%d%lf%lf%lf%lf",&num,&x,&y,&xV,&yV);*/

	/*this doesn't work, why? xball = {0,12.5,12.5,12.0,5.0,NULL};*/
	bp1 = &xball1;
	bp1->simPt = &pooltable1;

	bp2 = &xball2;
	bp2->simPt = &pooltable2;

	bp1->simPt->storagePt = bp2; 
	
	head = bp1;

	/*pass the address of the pointer, which result in a pointer to pointer to 	   struct Ball*/
	/* THIS IS THE RIGHT DEMO!
	traverse(&head);
	if(DEBUG) printf("In main x value is %f\n",head->x);*/

	/*Testing the wrong demo.*/
	traverse(head);
	if(DEBUG) printf("In main x value is %f\n",head->x);




	return 0;
}
