#include "linkedmatrix.h"
#include "iostream"
#include "iomanip"
using namespace std;


LinkedMatrix::LinkedMatrix() //constructor 
{
	rowArray = NULL; //initially set the arrays to nul representing an emptymatrix
	colArray = NULL;
	numNonZeroElements = 0; //set private elements tonull as well
	numCols = 0;
	numRows = 0;
}

void LinkedMatrix::create(int numRows, int numCols)//thhe creat function that intiailizes the object in linkedmatrix
{
	this->numCols = numCols;
	this->numRows = numRows; //initiallizes numrows andcols whilst also dynamically creating a matrix using a rowarray and colarray which represent a list of pointers
	rowArray= new Node*[numRows];
	colArray= new Node*[numCols];
	for(int i=0; i<numCols; i++) //++i
		colArray[i] = NULL;
	for(int i=0; i<numRows; i++)
		rowArray[i] = NULL;
}

void LinkedMatrix::insertElement(int Row_Indx, int Col_Indx, int value) //the inserelement here uses pointers that traverse the rows and colums, and a pointer that focuses on the value
{
	Node *newptr;
	newptr = new Node(Row_Indx,Col_Indx,value); //all the defined pointers are present
	Node *travrow;
	Node *travcol;
	travrow = rowArray[Row_Indx];
	travcol = colArray[Col_Indx];

	if (value!=0) //inital check that prevent zero values
	{
		if (Row_Indx>=0 && Row_Indx<numRows) //another set of checks to make sure the rowindx and colindx that are inputed are within the correct range
		{
			if (Col_Indx>=0 && Col_Indx<numCols)
			{
				Node *valuecolcheck; //a new node being created tht checks colvalue
				valuecolcheck = rowArray[Row_Indx];
				while (valuecolcheck!=NULL) //while loop focuse on if the valuecolcheck which is pointe to the rowarray is null, it integrates the value it hols onto the esignated colindx
				{
					if (valuecolcheck->column == Col_Indx)
					{
						valuecolcheck->value = value;
						return;
					}
					valuecolcheck=valuecolcheck->next; //traverses to the right
				}

				if (travcol==NULL || travcol->row > Row_Indx)  //a condition that checks if pointer is out of bounds
				{
		            newptr->down = travcol;
		            colArray[Col_Indx] = newptr;//if thats the casenewptr is first element in column 
		        } 
		        else 
		        {
		        	while (travcol->down!=NULL && travcol->down->row < Row_Indx) //a loop that checks if pointer is within bounds
		        	{
		                travcol = travcol->down;
		            }
		            newptr->down = travcol->down;//pointers traverse the loop and swith palces once they reach the spot
		            travcol->down = newptr;
		        }



				if (travrow==NULL || travrow->column > Col_Indx) //this block represents the same idea but in the rows instead, so pointers swap an move an travers to the right
				{
		            newptr->next = travrow;
		            rowArray[Row_Indx] = newptr;
		        } 
		        else 
		        {
		        	while (travrow->next!=NULL && travrow->next->column < Col_Indx) 
		        	{
		                travrow = travrow->next;
		            }
		            newptr->next = travrow->next;
		            travrow->next = newptr;
		        }






		        numNonZeroElements = numNonZeroElements+1; //num of values within the matrix not zero increase

			}
			else
			{
				cout<<"Column index inputted is not within range"<<endl;
			}
		}
		else
		{
			cout<<"Row index inputted is not within range"<<endl; //set of outputs when error found
		}
	}
	else
	{
		cout<<"Value has to be non-zero to be inserted"<<endl;

	}

}

void LinkedMatrix::removeElement(int Row_Indx, int Col_Indx) //function to remove elements
{
	Node *travrow;
	Node *travcol;
	Node *oldrow;
	Node *oldcol;
	travrow = rowArray[Row_Indx];//variable identified
	travcol = colArray[Col_Indx];
	oldcol = NULL;
	oldrow = NULL;


	if (Row_Indx>=0 && Row_Indx<numRows)
	{
		if (Col_Indx>=0 && Col_Indx<numCols)
		{
	        while (travrow!=NULL &&  Col_Indx!=travrow->column)  //after passing initial boundry checks , we traverse to find the required row and column
	        {
            	oldrow = travrow;
            	travrow = travrow->next;
        	}

        	while (travcol!=NULL && travcol->row != Row_Indx) 
        	{
           		oldcol = travcol;
            	travcol = travcol->down; //this is down in the rows and cols
        	}


            if (travrow!=NULL && travcol!=NULL)  //if both thr row and col pointers definitel point to something
            {
	            if (oldcol!=NULL) 
	            {
	                oldcol->down = travcol->down;
	            } 
	            else 
	            {
	                colArray[Col_Indx] = travcol->down; //this codeblock allows for ponters to swap so that value to be deleted can be binded to an olptr and get deleted
	            }            	
            	if (oldrow!=NULL) 
            	{
                	oldrow->next = travrow->next;
                }
	            else 
	            {
	                rowArray[Row_Indx] = travrow->next;
	            }

	            delete travrow;
	            numNonZeroElements--; //nonzero elems decrease
	        }
		}
		else
		{
			cout<<"Column index inputted is not within range"<<endl;
		}
	}
	else
	{
		cout<<"Row index inputted is not within range"<<endl; //error outputs
	}	
}



int LinkedMatrix::getValue(int Row_Indx, int Col_Indx) const //function to get element
{
	Node *travcol;
	travcol = colArray[Col_Indx];

	if (Row_Indx>=0 && Row_Indx<numRows)
	{
		if (Col_Indx>=0 && Col_Indx<numCols) //nitially identify pointers and make boundary conditions
		{

			if (travcol==NULL) //this justshows whether the element doesnt exist  if null
			{
					return 0;
			}
			else
			{
	        	while (travcol!=NULL) 
	        	{
	           		if (travcol->row != Row_Indx) //else we traverse until we find the value
	           		{
	           			travcol = travcol->down;
	           		}
	           		else
	           		{
	           			return travcol->value;
	           		}

	        	}
	        }
	        return 0;
	    }
		else
		{
			cout<<"Column index inputted is not within range"<<endl; //error output
			return 0;
		}
	}
	else
	{
		cout<<"Row index inputted is not within range"<<endl;
		return 0;
	}
}


LinkedMatrix::~LinkedMatrix() //destructor function
{
	for (int i=0;i<numCols;i++)
	{
		Node *destructcol;
		destructcol = colArray[i]; //used to destroy the temporary pointers including the list of pointers or rowarray and colarray
		Node *tempcol;
		while(destructcol)
		{
			tempcol = destructcol;
			destructcol = destructcol->down;
			delete tempcol;
		}
	}
	delete [] colArray; delete [] rowArray;
}


void LinkedMatrix::display() const //simple display function to reperesent assignment rubrics
{
    cout << "NumRows= " << numRows << "         " << "NumColumns= " << numCols << "       " << "NumNonZeroElements= " << numNonZeroElements << endl;
    for (int colind = 0; colind < numCols; colind++) 
    {
        for (int rowind = 0; rowind < numRows; rowind++)  //we move through the collumns and assign base n cols
        {
            int val = getValue(rowind, colind);
            if (val != 0) 
            {
                cout << "(" << rowind << "," << colind << ")=" << val << endl;
            }
        }
    }
}
void LinkedMatrix::display2D() const //very similar implementation, but we make it look actually like a amtrix using setw
{
    cout << "NumRows= " << numRows << "         " << "NumColumns= " << numCols << "       " << "NumNonZeroElements= " << numNonZeroElements << endl;

    for (int di = 0; di < numRows; di++)
    {
        for (int dj = 0; dj < numCols; dj++) //these loops are also used to traverse through arrayns
        {
            cout << setw(10) << getValue(di,dj); 
        }
        cout <<endl; 
    }
}

























