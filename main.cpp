#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "sylvester.h"

#define SIZE 128

using namespace std;

int main(int argc, char* argv[]){

	FILE* fd;
	int d1, d2;
	char func1[SIZE];
	char func2[SIZE];
	char buf[SIZE];

	Polynomial f1;
	Polynomial f2;
	if(argc>2){
		if(strcmp(argv[1],"-read")==0){
			if(strcmp(argv[2],"-i")==0 && argc==8){
				if((fd = fopen(argv[3], "r"))==NULL){
					perror("fopen");
					return 1;
				}

				if(strcmp(argv[4],"-d1")==0 && strcmp(argv[6],"-d2")==0){
					d1 = atoi(argv[5]);
					d2 = atoi(argv[7]);
					int i=1;
					while(fgets(buf, sizeof(buf), fd) != NULL){
						buf[strlen(buf)-1] = '\0';
						if(i==1){
							//Polynomial f1(d1, buf);
							f1.initialize(d1, buf);
						}
						else if(i==2){
							//Polynomial f2(d2, buf);
							f2.initialize(d2, buf);
						}
						else break;
						i++;
					}
				}
				else return 1;

			}
			else if(strcmp(argv[2],"-console")==0 && argc==3){
				cout << "Give 1st polynomial: ";
				cin >> func1;
				cout << "Give 1st polynomial degree: ";
				cin >> d1;

				//Polynomial f1(d1, func1);
				f1.initialize(d1, func1);

				cout << "Give 2nd polynomial: ";
				cin >> func2;
				cout << "Give 2nd polynomial degree: ";
				cin >> d2;

				//Polynomial f2(d2, func2);
				f2.initialize(d2, func2);
			}
			else return 1;

		}
		else if(strcmp(argv[1],"-generate")==0 && argc==6){
			if(strcmp(argv[2],"-d1")==0 && strcmp(argv[4],"-d2")==0){

				d1 = atoi(argv[3]);
				//Polynomial f1(d1);
				f1.initialize(d1);

				d2 = atoi(argv[5]);
				//Polynomial f2(d2);
				f2.initialize(d2);
			}
			else return 1;

		}
		else return 1;
	}
	else return 1;

	f1.printfunc();

	cout << endl;

	f2.printfunc();
	Sylvester s(f1, f2);

	return 0;
}
