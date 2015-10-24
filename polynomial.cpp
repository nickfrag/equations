#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "polynomial.h"

#define MSize 20

using namespace std;

typedef struct{
	int num;
	int x;
	int y;
	}Mononyms;

// Construct a polynomial
Polynomial::Polynomial(){
	xdeg=0;
	ydeg=0;
}

// Initialize a random polynomial
void Polynomial::initialize(int degree){
	int dx, dy;

	srand(time(NULL));

	dx = (rand()%(degree-1))+1;
	dy = degree - dx;

	xdeg = dx;
	ydeg = dy;

	array = new int*[dx+1];
	for(int i=0; i<=dx; i++){
		array[i] = new int[dy+1];
	}

	int i=dx, j=dy;
	
	array[i][j] = (rand()%19)-9;
	if(array[i][j] == 0) array[i][j]++;

	for(i=0; i<dx; i++)
		for(j=0; j<dy; j++)
			array[i][j] = (rand()%19)-9;

}

// Initialize a polynomial given by the user
void Polynomial::initialize(int degree, char* function){
	int count=1; //counter of mononyms

	if((*function) == '-') count-=1;

	for(int i=0; i<strlen(function); i++)
		if((*(function+i) == '+')||(*(function+i) == '-')) count++;

	//Seperate polynomial to mononyms
	char mono[count][MSize];
	Mononyms mns[count]; 

	int i=0, j=0, l=0;
	if((*function) == '-'){
		mono[j][l]='-';
		l++;
		i++;
	}
	
	while(*(function+i)!='\0'){
		if((*(function+i)!='+')&&(*(function+i)!='-')){
			mono[j][l]=*(function+i);
			l++;
		}
		else{
			mono[j][l]='\0';
			j++;
			l=0;
			mono[j][l]=*(function+i);
			l++;
		}
		i++;
	}

	mono[j][l]='\0';
	
	i=0;
	l=0;
	int e=0, xmax=0, ymax=0;
	char synt[5], xexp[2], yexp[2];

	strcpy(synt,"");
	strcpy(xexp," ");
	strcpy(yexp," ");
	
	//Initialize the Mononyms
	for(int j=0; j<count; j++){
		while(mono[j][i]!='\0'){
			if((mono[j][i]=='*'||mono[j][i]=='x'||mono[j][i]=='y')&&(e==0)){
				synt[l]='\0';
				e=1;
				l=0;
			}
			if(e!=1){
				synt[l]=mono[j][i];
				l++;
			}
			else{
				if(mono[j][i]=='x'){
					if(mono[j][i+1]=='^'){
						xexp[0]=mono[j][i+2];
						xexp[1]='\0';
						i+=3;
						continue;
					}
					else{
						xexp[0]='1';
						xexp[1]='\0';
						i++;
						continue;
					}
				}
				else if(mono[j][i]=='y'){
					if(mono[j][i+1]=='^'){
						yexp[0]=mono[j][i+2];
						yexp[1]='\0';
						i+=3;
						continue;
					}
					else{
						yexp[0]='1';
						yexp[1]='\0';
						i++;
						continue;
					}
				}
			}
			i++;
		}
		if(mono[j][i]=='\0'){
			if((synt[0]=='-')&&(synt[1]=='\0')) mns[j].num = -1; 
			else if((synt[0]=='+')&&(synt[1]=='\0')) mns[j].num = 1; 
			else mns[j].num = atoi(synt);


			if(strcmp(xexp," ")==0) mns[j].x=0; 
			else mns[j].x = atoi(xexp);

			if(strcmp(yexp," ")==0) mns[j].y=0; 
			else mns[j].y = atoi(yexp);			
			 
			if(xmax<mns[j].x) xmax = mns[j].x;
			if(ymax<mns[j].y) ymax = mns[j].y;
			l=0;
			e=0;
			i=0;

			strcpy(synt,"");
			strcpy(xexp,"  ");
			strcpy(yexp," ");
		}
	}

	/*for(int j=0; j<count; j++){
		cout << j << " " << mns[j].num << " " << mns[j].x << " " << mns[j].y << endl;
	}*/

	xdeg = xmax;
	ydeg = ymax;

	//Iniatialize the array

	array = new int*[xdeg+1];
	for(int i=0; i<=xdeg; i++){
		array[i] = new int[ydeg+1];
	}

	for(int j=0; j<count; j++){
		array[mns[j].x][mns[j].y] = mns[j].num;
	}
}

// Destructor
Polynomial::~Polynomial(){

	for(int i=0; i<xdeg+1; i++)
		delete[] array[i];
	delete[] array;

}


void Polynomial::printArray(){
	for(int i=0; i<xdeg+1; i++){
		for(int j=0; j<ydeg+1; j++)
			printf("%3d", array[i][j]);
		cout << endl;
	}
}

void Polynomial::getArray(int** target){

	for(int i=0; i<=xdeg; i++)
		for(int j=0; j<=ydeg; j++)
			target[i][j] = array[i][j];
}		

int Polynomial::getXdeg(){
	return xdeg;
}

int Polynomial::getYdeg(){
	return ydeg;
}
		
	
