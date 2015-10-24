#include "polynomial.h"

class Sylvester{
	int msize, fsize;
	int*** array;
	public:
		Sylvester(Polynomial f1, Polynomial f2);
		~Sylvester();
		void printSMatrix();
	};
