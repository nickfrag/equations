#include "SylvesterPoly.h"
#include <iostream>
#include <iomanip>

using namespace std;

SylvesterPoly::SylvesterPoly(Sylvester* matrix) {
	sdeg=matrix->getFsize();
	msize=matrix->getMsize();
	array= new int**[sdeg];
	for(int i=0;i<sdeg;i++){
		array[i]= new int*[msize];
		for(int j=0;j<msize;j++){
			array[i][j]=new int[msize];
			for(int k=0;k<msize;k++){
				array[i][j][k]=matrix->getMatrix()[j][k][i];
			}
		}
	}

}

SylvesterPoly::~SylvesterPoly() {

}

void SylvesterPoly::printSPoly(){
	int middle = msize/2+msize%2-1;
	cout << "==============================================================================";
	for(int j=0;j<msize;j++){
		cout << endl;
		if(j==middle){
			cout<<"S(y) =";
		}
		else
			cout << "      ";
		for(int i=0;i<sdeg;i++){
			for(int k=0;k<msize;k++){
				cout<< setw(3) << right <<array[i][j][k];
			}
			if(j==middle){
				cout<<" * y^"<<i;
			}
			else
				cout << "      ";
		}

	}
	cout << endl << "==============================================================================" << endl;
}
