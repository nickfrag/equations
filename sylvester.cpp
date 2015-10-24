#include <iostream>
#include <stdio.h>
#include <string.h>
#include "sylvester.h"

#define SIZE 64

using namespace std;


Sylvester::Sylvester(Polynomial f1, Polynomial f2){

	int **a1, **a2;
	int x1, x2, y1, y2;
	int secret; // 0 --> x is secret :: 1 --> y is secret

	x1 = f1.getXdeg();
	y1 = f1.getYdeg();
	x2 = f2.getXdeg();
	y2 = f2.getYdeg();

	a1 = new int*[x1+1];
	for(int i=0; i<=x1; i++)
		a1[i] = new int[y1+1];

	a2 = new int*[x2+1];
	for(int i=0; i<=x2; i++)
		a2[i] = new int[y2+1];

	f1.getArray(a1);
	f2.getArray(a2);

	int xmax=0, ymax=0;

	xmax = x1;
	if(x2>xmax) xmax = x2;

	ymax = y1;
	if(y2>ymax) ymax = y2;

	if(ymax>xmax){
		array = new int**[y1+y2];
		for(int i=0; i<(y1+y2); i++){
			array[i] = new int*[y1+y2];
			for(int j=0; j<(y1+y2); j++)
				array[i][j] = new int[xmax+1];
		}
		secret = 0;
		fsize=xmax+1;
		msize = y1+y2;
	}
	else if(ymax<xmax){
		array = new int**[x1+x2];
		for(int i=0; i<(x1+x2); i++){
			array[i] = new int*[x1+x2];
			for(int j=0; j<(x1+x2); j++)
				array[i][j] = new int[ymax+1];
		}
		secret = 1;
		fsize=ymax+1;
		msize = x1+x2;
	}
	else{
		array = new int**[x1+x2];
		for(int i=0; i<(x1+x2); i++){
			array[i] = new int*[x1+x2];
			for(int j=0; j<(x1+x2); j++)
				array[i][j] = new int[ymax+1];
		}
		secret = 1;
		fsize=ymax+1;
		msize = x1+x2;
	}

	for(int i=0; i<msize; i++){
		for(int j=0; j<msize; j++){
			for(int k=0; k<fsize; k++){
				array[i][j][k] = 0;	
			}	
		}
	}

	//cout << secret << endl;

	if(secret==0){ // x is secret

		int l1=0, mn1=y1;
		int l2=0, mn2=y2;
		for(int i=0; i<msize; i++){
			if(i<y2){

				int m=y1;
					
				for(int j=l1; j<=mn1; j++){
					for(int k=0; k<=xmax; k++){
						if(k>x1) break;
						array[i][j][k] = a1[k][m];
					}
					m--;
					
				}
				m=y1;
				mn1++;
				l1++;
			} 
			else{
				int m=y2;
					
				for(int j=l2; j<=mn2; j++){
					for(int k=0; k<=xmax; k++){
						if(k>x2) break;
						array[i][j][k] = a2[k][m];
					}
					m--;
					
				}
				m=y2;
				l2++;
				mn2++;

			}
		}
			
	}

	else if(secret == 1){ // y is secret

		int l1=0, mn1=x1;
		int l2=0, mn2=x2;
		for(int i=0; i<msize; i++){
			if(i<x2){

				int m=x1;
					
				for(int j=l1; j<=mn1; j++){
					for(int k=0; k<=ymax; k++){
						if(k>y1) break;
						array[i][j][k] = a1[m][k];
					}
					m--;
					
				}
				m=x1;
				mn1++;
				l1++;
			} 
			else{
				int m=x2;
					
				for(int j=l2; j<=mn2; j++){
					for(int k=0; k<=ymax; k++){
						if(k>y2) break;
						array[i][j][k] = a2[m][k];
					}
					m--;
					
				}
				m=x2;
				l2++;
				mn2++;

			}
		}

	}


	for(int i=0; i<=x1; i++)
		delete[] a1[i];
	delete[] a1;

	for(int i=0; i<=x2; i++)
		delete[] a2[i];
	delete[] a2;
}

Sylvester::~Sylvester(){


	for(int i=0; i<msize; i++)
		for(int j=0; j<msize; j++)
			delete[] array[i][j];
	
	delete[] array;


}

int isZero(int matrix[], int size){

	for(int i=0; i<size; i++)
		if(matrix[i]!=0) return 0;

	return 1;
}

void printPol(int matrix[], int size){

	char output[SIZE];
	char str[16];
	
	strcpy(output, "");

	for(int i=0; i<size; i++){
		if(matrix[i]==1){
			if(i==0) strcat(output,"1");
			else if(i==1) strcat(output, "+y");
			else if(i>2){
				strcat(output,"+y^");
				sprintf(str, "%d", i);
				strcat(output, str);
				strcpy(str,"");
			}
		}
		else if(matrix[i]==-1){
			if(i==0) strcat(output,"-1");
			else if(i==1) strcat(output, "-y");
			else if(i>1){
				strcat(output,"-y^");
				sprintf(str, "%d", i);
				strcat(output, str);
				strcpy(str,"");
			}
		}
		else if(matrix[i]>1){
			sprintf(str, "%d", matrix[i]);
			if(i==0) strcat(output, str);
			else if(i==1){ 
				strcat(output, "+");
				strcat(output, str);
				strcat(output, "*y");
			}
			else if(i>1){
				strcat(output,"+");
				strcat(output, str);
				strcat(output, "*y^");
				sprintf(str, "%d", i);
				strcat(output, str);
			}
			strcpy(str, "");
		}
		else if(matrix[i]<-1){
			sprintf(str, "%d", matrix[i]);
			if(i==0) strcat(output, str);
			else if(i==1){ 
				strcat(output, str);
				strcat(output, "*y");
			}
			else if(i>1){
				strcat(output, str);
				strcat(output, "*y^");
				sprintf(str, "%d", i);
				strcat(output, str);
			}
			strcpy(str, "");
		}
	}

	if(output[0]=='+') output[0]=' ';

	printf("%10s", output);
}


void Sylvester::printSMatrix(){
	int size = fsize;
	cout << "==============================================================================" << endl;
	for(int i=0; i<msize; i++){
		for(int j=0; j<msize; j++){
			if(isZero(array[i][j], size))
				printf("%10d", 0);
			else
				printPol(array[i][j], size);
		}
		cout << endl;
	}
	cout << "==============================================================================" << "\n\n";
}


	
