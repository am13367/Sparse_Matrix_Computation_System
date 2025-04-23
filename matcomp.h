//============================================================================
// Name         : DS Assignment#1
// Author       : Mai Oudah
// Version      : 1.0
// Date Created : 11-02-2023
// Date Modified: 19-02-2024
// Description  : Matrix Computation in C++ 
//============================================================================
#ifndef MATCOMP_H //include guards
#define MATCOMP_H
#include<fstream>
#include<string>
#include "linkedmatrix.h"
using namespace std;
//=======================================
class MatComp
{
	private:
		LinkedMatrix** matrix_list; //the imported and generated matrices will be stored in this array
		int matrix_count;
	public:
		MatComp();	//constructor pointers to matrices
		~MatComp();	//destructor to delete all matrices 
		void importMatrix(string filename); 
		void multi(char matrix_ID, int a);
		void add(char matrix1_ID, char matrix2_ID);
		void multi(char matrix1_ID, char matrix2_ID);
		void exportMat(char matrix1_ID, string filename);
		void display(char matrix_ID);
		void display2D(char matrix_ID);
		bool isValid(char matrix_ID);

	//add any other necessary code here
};
#endif
