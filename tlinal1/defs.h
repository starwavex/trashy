#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>

struct SVect {
	unsigned length;
	double* coords;
};


struct SVect* readVect(unsigned _length);
struct SVect* newVect(unsigned _length, double* _coords);
void delVect(struct SVect* _vect);
void printVect(struct SVect* _vect);
struct SVect* addVects(struct SVect* _v1, struct SVect* _v2);
struct SVect* sclVect(struct SVect* _vect, double _scalar);
double dotProd(struct SVect* _v1, struct SVect* _v2);
int calcPseudo(struct SVect* _v1, struct SVect* _v2, struct SVect* _func, double* _k1, double* _k2);
unsigned getDim(void);
struct SVect* sinVect(struct SVect* _vect); 
struct SVect* cnstVect(struct SVect* _vect); 
