#include "defs.h"

struct SVect* newVect(unsigned _length, double* _coords) {
	if (!_coords || _length == 0) {
		return NULL;
	}
	struct SVect* vect = (struct SVect*)malloc(sizeof(struct SVect));
	if (!vect) {
		return NULL;
	}
	vect->coords = (double*)malloc(_length * sizeof(double));
	if (!(vect->coords)) {
		free(vect);
		return NULL;
	}
	vect->length = _length;
	for (unsigned i = 0; i < _length; ++i) {
		(vect->coords)[i] = _coords[i];
	}
	return vect;
}

void delVect(struct SVect* _vect) {
	if (!_vect || !(_vect->coords)) {
		return;
	}
	free(_vect->coords);
	free(_vect);
	return;
}

void printVect(struct SVect* _vect) {
	if (!_vect || !(_vect->coords)) {
		return;
	}
	//fprintf(stdout, "Vector = ( ");
	for (unsigned i = 0; i < _vect->length; ++i) {
		fprintf(stdout, "%lf ", (_vect->coords)[i]);
	}
	fprintf(stdout,"\n");
	return;
}

struct SVect* addVects(struct SVect* _v1, struct SVect* _v2) {
	if (!_v1 || !_v2) return NULL;
	if (_v1->length != _v2->length) return NULL;
	struct SVect* sum = newVect(_v1->length, _v1->coords);
	if (!sum) return NULL;
	for (unsigned i = 0; i < _v1->length; ++i) {
		(sum->coords)[i] += (_v2->coords)[i];
	}
	return sum;
}

struct SVect* sclVect(struct SVect* _vect, double _scalar) {
	if (!_vect) return NULL;
	struct SVect* scl = newVect(_vect->length, _vect->coords);
	if (!scl) return NULL;
	for (unsigned i = 0; i < _vect->length; ++i) {
		(scl->coords)[i] *= _scalar;
	}
	return scl;
}

double dotProd(struct SVect* _v1, struct SVect* _v2) {
	double dotprod = 0.;
	for (unsigned i = 0; i < _v1->length; ++i) {
		dotprod += (_v1->coords)[i] * (_v2->coords)[i];
	}
	return dotprod;
}

int calcPseudo(struct SVect* _v1, struct SVect* _v2, struct SVect* _func, double* _k1, double* _k2) {
	double a1, a2, b1, b2, c1, c2, detm;
	a1 = dotProd(_v1,_v1); a2 = dotProd(_v1,_v2); c1 = dotProd(_func,_v1);
	b1 = dotProd(_v2,_v1); b2 = dotProd(_v2,_v2); c2 = dotProd(_func,_v2);
	detm = a1 * b2 - a2 * b1;
	if (fabs(detm) < DBL_MIN) {
		return -1;
	}
	*_k1 = (c1 * b2 - c2 * a2)/detm;
	*_k2 = (a1 * c2 - c1 * b1)/detm;
	return 0;
}

struct SVect* readVect(unsigned _length) {
	if (_length == 0) return NULL;
	double* coords = (double*)malloc(_length * sizeof(double));
	if (!coords) return NULL;
	for (unsigned i = 0; i < _length; ++i) {
		if (fscanf(stdin, "%lf", coords+i) != 1) {
			free(coords);
			return NULL;
		}
	}
	struct SVect* vect = newVect(_length, coords);
	free(coords);
	return vect;
}

unsigned getDim(void) {
	unsigned N = 0;
	fscanf(stdin, "%u", &N);
	return N;
}

struct SVect* sinVect(struct SVect* _vect) {
	struct SVect* vect = newVect(_vect->length, _vect->coords);
	if (!vect) return NULL;
	for (unsigned i = 0; i < _vect->length; ++i) {
		(vect->coords)[i] = sin((_vect->coords)[i]);
	}
	return vect;
}

struct SVect* cnstVect(struct SVect* _vect) {
	struct SVect* vect = newVect(_vect->length, _vect->coords);
	if (!vect) return NULL;
	for (unsigned i = 0; i < _vect->length; ++i) {
		(vect->coords)[i] = 1.;
	}
	return vect;
}




