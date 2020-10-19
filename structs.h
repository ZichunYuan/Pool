/*Zichun Yuan*/
#define MU_ROLLING 0.01
#define G_IPS2 386.08858267716
struct Sim {double time; double dT;void *storagePt;};
struct Ball {int num; double x; double y; double xV; double yV; struct Sim *simPt;};
