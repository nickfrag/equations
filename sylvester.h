#include "polynomial.h"

class Sylvester{
	int msize, fsize; // msize το μέγεθος του πίνακα και fsize το μέγεθος της κάθε συνάρτησης
	int*** array;
	public:
		Sylvester(Polynomial f1, Polynomial f2);
		~Sylvester();
	};
