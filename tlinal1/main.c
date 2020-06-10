#include "defs.h"

int main(void) {
	unsigned N;
	struct SVect *v1, *v2, *func1, *func2;

	printf("Enter vector space dimension: ");
	N = getDim();

	printf("Enter x values: ");
	v1 = readVect(N);

	printf("Enter y values: ");
	v2 = readVect(N);

	//printf("Enter func values: ");
	func1 = cnstVect(v1);
	func2 = sinVect(v1);
	
	double k1 = 0., k2 = 0.;
	if (calcPseudo(func1, func2, v2, &k1, &k2)) {
		return -1;
	}
	printf("Coefficients: k1 = %lf   k2 = %lf\n", k1, k2);
	struct SVect *sfunc = addVects(sclVect(func1, k1), sclVect(func2,k2));
	printf("Pseudo = "); printVect(sfunc);
	struct SVect *squad = addVects(v2, sclVect(sfunc, -1.));
	printf("Quadratic offset  = %lf\n", dotProd(squad, squad)); 
	delVect(v1); delVect(v2); delVect(func1); delVect(func2);
	delVect(sfunc); delVect(squad);
	return 0;
}
