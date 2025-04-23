#include <iostream>
#include <fstream>
#include <string>
#include "linkedmatrix.h"
#include "matcomp.h"
using namespace std;



MatComp::MatComp() //constructor class in matcomp where the count set to zero but the linkedmtrix list consist of 26 as an upper bound for alphabets
{
    matrix_count = 0;
    matrix_list = new LinkedMatrix*[26];
}

MatComp::~MatComp() //ddestructor class used to destroy temporarry pointers
{
    for (int z = 0; z < matrix_count; ++z) 
    {
        delete matrix_list[z];
    }
    delete[] matrix_list;
}


void MatComp::importMatrix(string filename)  //import function making use of unput output functions
{

	ifstream file;
	file.open(filename); //basic funcion to open the file

 	if (file.good()) //if no hiccups in filename, functioncarries on
 	{
	    LinkedMatrix* importmat;
	    importmat = new LinkedMatrix();
	    string iteration;
	    string val;
	    getline(file, iteration);
	    val = iteration.substr(iteration.find("=")+1); //this codeblock assists the findin g of rows columns an numnonzero elems from the text file using the getline and the stringline methods such as find
	    int numRows = stoi(val); 
	    getline(file, iteration);
	    val = iteration.substr(iteration.find("=")+1);
	    int numCols = stoi(val);
	    getline(file, iteration);
	    val = iteration.substr(iteration.find("=")+1);
	    int numNonZeroElements = stoi(val); //we set variables for clarity

	    importmat->create(numRows, numCols); //pointer initiallized earlerbut now created

	    for (int i = 0; i < numNonZeroElements; i++) 
	    {
	        getline(file, iteration);
	        size_t colval = iteration.find_first_of(','); //for loop and code block focuses on each actual position of nonzero elemetnts so it in=s the ocndition
	        size_t bracval= iteration.find_first_of(')');
       	    string val = iteration.substr(iteration.find("=")+1); //once again uses string dunctions whilst placing importance on comma and paranthesis positions
	        int row = stoi(iteration.substr(1, colval - 1));
	        int col = stoi(iteration.substr(colval + 1, bracval - colval - 1));
	        int value = stoi(val);

	        importmat->insertElement(row, col, value); //succesfullimport inserts
	    }

		matrix_list[matrix_count] = importmat;
		int alpha = matrix_count + 65;
	    cout << "Done! This is matrix '" << char(alpha) << "'." << endl; //clarity work to create a new matrix id and increment the maatrix count
		matrix_count++; 
	    file.close();
	}
	else
	{
  		cout << "Invalid input, import cancelled" << endl; //error if file not good
        file.close();
  		return;
	}
}


void MatComp::multi(char matrix_ID, int a) //function for mult constant
{
	LinkedMatrix *ConstMat;
	if (isalpha(matrix_ID))
	{
		int position= int(matrix_ID) - int('A');
		if (position>= 0 && position<=25) //initial set of checks to make sure input is precise and within boundaries
		{
			ConstMat = matrix_list[position];
			if (ConstMat!=NULL)
			{
				for (int i=0; i<ConstMat->numRows;i++) //loops to find each value to multily with matrix with scalar
				{
					for(int j=0;j<ConstMat->numCols;j++)
					{
						int scalarval;
						if (a==0)
						{
							ConstMat->removeElement(i,j);//if a==0 matrix is lost so used remove element

						}
						scalarval = ConstMat->getValue(i,j); //variable to get value and then we insert into back to matrix id A
						if (scalarval!=0)
						{
							ConstMat->insertElement(i,j,scalarval*a);
						}

					}
				}
				cout<<"Done!"<<endl;
			}
			else
			{
				cout<<"There is no matrix with that matrix_ID"<<endl; //error outputs focusing on mishaps in input
			}
		}
		else
		{
			cout<<"matrix_ID needs to be a capital letter"<<endl;
		}
	}
	else
	{
		cout<<"matrix_ID needs to be a letter"<<endl;
	}

}


void MatComp::add(char matrix1_ID, char matrix2_ID) //function about addition
{
	int Apos;
	int Bpos;
	int Bmatvalue;
	int Amatvalue;
	Apos = int(matrix1_ID)-int('A');
	Bpos = int(matrix2_ID)-int('A'); //initial variables and pointers created
	LinkedMatrix *Aaddmat;
	LinkedMatrix *Baddmat;
	Aaddmat = matrix_list[Apos];
	Baddmat = matrix_list[Bpos];


	if (Apos>= 0 && Apos<=25)
	{
		if (Bpos>= 0 && Bpos<=25)
		{
			if (Aaddmat)
			{
				if (Baddmat)
				{
					if (Aaddmat->numRows == Baddmat->numRows) //after many boundary checks we focus on the matrices only to be ade if they have the same dimensions
					{
						if (Aaddmat->numCols == Baddmat->numCols)
						{
							for (int i = 0;i<Baddmat->numRows;i++)
							{
								for (int j = 0;j<Baddmat-> numCols; j++)
								{
									Amatvalue = Aaddmat->getValue(i,j);
									Bmatvalue = Baddmat->getValue(i,j);
									int addition = Amatvalue+Bmatvalue; //similar ot previous function we get value through varibales an insert back into the matrixid 1 pr matrix A usiallya s an example

									if (addition!= 0)
									{
										Aaddmat->insertElement(i,j,addition);
									}
									else
									{
										Aaddmat->removeElement(i,j); //removes vale if 0 found
									}

								}

							}
							cout<<"Done!"<<endl;
							return;
						}
						else
						{
							cout<<"Columns not the same, cant add"<<endl;
						}
					}
					else
					{
						cout<<"rows not the same, cant add"<<endl;
					}
				}
				else
				{
					cout<<"There is no matrix in the list with matrix2_ID"<<endl; //error results and checks
				}
			}
			else
			{
				cout<<"There is no matrix in the list with matrix1_ID"<<endl;

			}
			
		}
		else
		{
			cout<<"inavlid input for matrix2_id"<<endl;
		}
	}
	else
	{
		cout<<"inavlid input for matrix1_id"<<endl;
	}


}

void MatComp::multi(char matrix1_ID, char matrix2_ID)
{
	int Apos;
	int Bpos;
	int Multvalue;
	Apos = int(matrix1_ID)-int('A'); //function for multiplication betweenmatrices create by initialy creating pointers an variables.
	Bpos = int(matrix2_ID)-int('A');
	LinkedMatrix *Amultmat;
	LinkedMatrix *Bmultmat;
	LinkedMatrix *FinalMat;
	Amultmat = matrix_list[Apos];
	Bmultmat = matrix_list[Bpos];
	FinalMat = new LinkedMatrix();
	FinalMat->create(Amultmat->numRows,Bmultmat->numCols);
	char FinalMatID = 'A' + matrix_count; //finalmatrix as we implement it into a new matrix

	if (Apos>= 0 && Apos<=25)
	{
		if (Bpos>= 0 && Bpos<=25)
		{
			if (Amultmat)
			{
				if (Bmultmat)
				{
					if (Amultmat->numCols == Bmultmat->numRows) //once again many conditions are followed to make sure inut is not awry and within the boundaries
					{
						for (int i=0;i<Amultmat->numRows;i++)
						{
							for (int j=0;j<Bmultmat-> numCols; j++)
							{
								Multvalue=0;
								for (int m=0;m<Amultmat->numCols;m++)
								{
									Multvalue= Multvalue + Amultmat->getValue(i,m)*Bmultmat->getValue(m,j); //this time instead of the other two previousfunctions we traverse a for loop thrice in orer to get ht emultiplication perfect
									if (Multvalue!=0)
									{
										FinalMat->insertElement(i,j,Multvalue);
									}
									else
									{
										FinalMat->removeElement(i,j); //wee inserrt the value found into a new matrix and remove values as well if a 0 is found
									}

								}
							}
						}
						matrix_list[matrix_count++] = FinalMat;
						FinalMat->display();
						cout<<"Done! This is matrix "<<FinalMatID<<endl; //interesting code that increments matrix count number while also displaying the final matrix

					}
					else
					{
						cout<<"Matrix dimensions do not match for multiplication"<<endl;
					}
				}
				else
				{
					cout<<"There is no matrix in the list with matrix2_ID"<<endl;
				}
			}
			else
			{
				cout<<"There is no matrix in the list with matrix1_ID"<<endl; //specific error statements absed on mishandle input
			}
		}
		else
		{
			cout<<"No matrix with this ID exists in the system!"<<endl;
		}
	}
	else
	{
		cout<<"o matrix with this ID exists in the system!"<<endl;
	}


}

 
void MatComp::exportMat(char matrix1_ID, string filename) //function to export matrix info into a txt file
{
	LinkedMatrix *ConstMat;
	int position= int(matrix1_ID) - int('A'); //makes use of fout pointers and variables
	ConstMat = matrix_list[position];
	int ConstMatvalue;

	ofstream fout(filename); //output stream
	if (fout.is_open()) //opens file 
	{
		fout<<"Rows="<<ConstMat->numRows<<endl; //simple design to print out statements with values
		fout<<"Columns="<<ConstMat->numCols<<endl;
		fout<<"Non-ZeroElements="<<ConstMat->numNonZeroElements<<endl;

		for (int i=0; i< ConstMat->numCols;i++)
		{
			for (int j=0; j< ConstMat->numRows;j++) //loop used to make sure to go first through colums then rows so that it matches ass rubrics.
			{
				ConstMatvalue = ConstMat->getValue(i,j);
				if (ConstMatvalue != 0)
				{
					fout<<"("<<j<<","<<i<<")="<<ConstMatvalue<<endl; //specifically esigne to match assingment
				}
			}
		}
		fout.close();
	}
	cout<<"Done"<<endl;
}




void MatComp::display(char matrix_ID)  //display function that builds upon the one in the linkedmatrix class
{
	int position= int(matrix_ID) - int('A');
	if (position >= 0 && position < matrix_count)
	{
		LinkedMatrix *ConstMat; //once againwe go through conitions an boundary checks so that we can make sure matrix is present so we can then call display function forom linkedmatrix
		ConstMat=matrix_list[position];
		if(ConstMat!=NULL)
		{
			ConstMat->display();
		}
		else
		{
			cout<<"No matrix with this ID exists in the system!"<<endl;
		}
	}
	else
	{
		cout<<"No matrix with this ID exists in the system!"<<endl; //specific error outputs if mishandled output
	}
}

void MatComp::display2D(char matrix_ID) //display2d inspired by linkedmatrix function
{
	int position= int(matrix_ID) - int('A');
	if (position >= 0 && position < matrix_count)
	{
		LinkedMatrix *ConstMat;
		ConstMat=matrix_list[position];
		if(ConstMat!=NULL)
		{
			ConstMat->display2D(); //same design as display function in checksfor matrix
		}
		else
		{
			cout<<"No matrix with this ID exists in the system!"<<endl;
		} //error statements
	}
	else
	{
		cout<<"No matrix with this ID exists in the system!"<<endl;
	}
}

bool MatComp::isValid(char matrix_ID) //final function for a function that holds error checks
{
	LinkedMatrix *ConstMat;
	int position= int(matrix_ID) - int('A');
	if (position >= 0 && position < matrix_count) //had little experience in this case and initially preferred to write error in each function
	{
		ConstMat=matrix_list[position]; //but this function still proves useful for quizk error checks
		if(ConstMat!=NULL)
		{
			return true;
		}
	}
	return false;
}




