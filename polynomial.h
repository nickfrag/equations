class Polynomial{
	int xdeg;
	int ydeg;
	int** array;
	public:
		Polynomial();
		void initialize(int degree);
		void initialize(int degree, char* function);
		~Polynomial();
		void printArray();
		void getArray(int** target);
		int getXdeg();
		int getYdeg();
	};
