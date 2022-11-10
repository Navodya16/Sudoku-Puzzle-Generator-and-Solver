#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//function to check if the number exists inside the box
//input parameters - arr(sudoku puzzle), row(row number), col(column number), n(number to be checked)
//output - boolean value of whether number is present in the box or not 
bool checkbox(int arr[][9], int row,int col,int n)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(arr[row+i][col+j]==n)
				return false;
		}
	}
	return true;
}

//function to check if the number exists in the row
//input parameters - arr(sudoku puzzle), row(row number), n(number to be checked)
//output - boolean value of whether number is present in the row or not 
bool checkrow(int arr[][9],int row,int n)
{
	for(int i=0;i<9;i++)
	{
		if(arr[row][i]==n)
			return false;
	}
	return true;
}

//function to check if the number exists in the column
//input parameters - arr(sudoku puzzle), col(column number), n(number to be checked)
//output - boolean value of whether number is present in the column or not 
bool checkcol(int arr[][9],int col,int n)
{
	for(int i=0;i<9;i++)
	{
		if(arr[i][col]==n)
			return false;
	}
	return true;
}

//this function will return true if the randomly generated number is safe to place. it will return true only if the above 3 functions are true
//input parameters - arr(sudoku puzzle), a(row number), b(column number), n(number to be checked)
//output - boolean value of whether number is safe to move or not 
bool safe(int arr[][9],int a, int b,int n)
{
	if(checkcol(arr,b,n) && checkrow(arr,a,n) && checkbox(arr,a-a%3,b-b%3,n))
		return true;
	else
		return false;
}

//function to fill other cells after filling diagonal boxes
//input parameters - arr(sudoku puzzle), i(row number), j(column number), n(number to be checked)
//output - fill other cells and return true if the array if fully filled
bool fillothercells(int arr[][9],int i, int j)
{
	if(i<8 && j>=9)
	{
		i=i+1;
		j=0;
	}
	
	if(i>=9 && j>=9)
		return true;
		
	if(i<3)
	{
		if(j<3)
			j=3;
	}
	
	else if(i<6)
	{
		if(j==int((i/3)*3))
			j=j+3;
	}
	
	else
	{
		if(j==6)
		{
			i=i+1;
			j=0;
			if(i>=9)
				return true;
		}
	}
	
	for(int number=1;number<=9;number++)
	{
		if(safe(arr,i, j,number))
		{
			arr[i][j]=number;
			if(fillothercells(arr,i, j+1))
				return true;
				
			arr[i][j]=0;
		}
	}
	
	return false;
}

//function to fill the diagonal box
//input parameters - arr(sudoku puzzle), r(row number), c(column number)
//output - fill the diagonal box with unique numbers
void fillD(int arr[][9],int r,int c)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			int s;
			s=rand()%9+1;
			if(checkbox(arr,r,c,s))
				arr[r+i][c+j]=s;
			else
				j=j-1;
			//cout<<s;
		}
	}
}

//function to fill the diagonal
void fillDiag(int arr[][9])
{
	for(int i=0;i<9;)
	{
		fillD(arr,i,i);
		i=i+3;
	}
}

//function to return the no of zeroes in a row
//input parameters - arr(sudoku puzzle), i(row number)
//output - count the no of zeroes in a given row and return
int checkNoofzeroesinarow(int arr[][9],int i)
{
	int cr=0;
	for(int x=0;x<9;x++)
	{
		if(arr[i][x]==0)
			cr++;
	}
	
	return cr;
}

//function to return the no of zeroes in a column
//input parameters - arr(sudoku puzzle), j(column number)
//output - count the no of zeroes in a given column and return
int checkNoofzeroesinacol(int arr[][9],int j)
{
	int cl=0;
	for(int x=0;x<9;x++)
	{
		if(arr[x][j]==0)
			cl++;
	}
	
	return cl;
}

//remove cells based on the user input
//input parameters - arr(sudoku puzzle), m(user input 2,3 or 4)
//output - select random cells in the array and assign it to 0 
void removecells(int arr[][9],int m)
{
	
	for(int i=0;i<9;i++)
	{
		int count=m;
		while(count!=0)
		{
			int d=rand()%9;
			int crr=checkNoofzeroesinarow(arr,i);
			int cll=checkNoofzeroesinacol(arr,d);
			if(crr<m && cll<m)
			{
				arr[i][d]=0;
				count--;
			}	
		}
	}
}

//print the sudoku array
//input parameters - arr(sudoku puzzle)
//output - print the array
void print(int arr[][9])
{
	for (int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(j==3 || j==6)
				cout<<" ";
			cout<<arr[i][j]<<" ";
		}
		if(i==2 || i==5)
			cout<<endl;
		cout<<endl;
	}
}

//find the positions of zeroes in the array
//input parameters - arr(sudoku puzzle), &row(row number), &col(column number)
//output - find the position of zero and assign it to row and column
bool findzero(int arr[][9], int &row, int &col)
{
	for(row=0;row<9;row++)
	{
		for(col=0;col<9;col++)
		{
			if(arr[row][col]==0)
			{
				//*x=i;
				//*y=j;
				return true;
			}
		}
	}
	return false;
}

//function to check whether the number can assigned to the given position
//input parameters - arr(sudoku puzzle), row(row number), col(column number), num(number to be assigned)
//output - return true if the number can be assigned to the given position
bool isvalid(int arr[][9],int row,int col,int num )
{
	if( checkrow(arr,row,num) && checkcol(arr,col,num) && checkbox(arr, row-row%3,col-col%3,num))
		return true;
	else
		return false;
}


//solve the puzzle step by step and in each step, the puzzle will be printed and the position of the filled cell will be indicated with * sign
//assigned value also be printed
//input parameters - arr(sudoku puzzle)
//output - return true if the puzzle is solved
bool solve(int arr[][9])
{
	int row;
	int col;
	if(!findzero(arr,row,col))
		return true;
	for(int N=1;N<=9;N++)
	{
		if(isvalid(arr,row,col,N))
		{
			arr[row][col]=N;
			for (int i=0;i<9;i++) //print the cell by indicating it with * sign
			{
				for(int j=0;j<9;j++)
				{
					if(j==3 || j==6)
						cout<<" ";
					if(i==row && j==col)
						cout<<"*"<<arr[i][j]<<" ";
					else
						cout<<arr[i][j]<<"  ";
				}
				if(i==2 || i==5)
					cout<<endl;
				cout<<endl;
			}
			//print(arr);
			cout<<"the position of ("<<row <<","<<col<<") was filled with the value "<<N<<endl<<endl;
			if(solve(arr))
				return true;
			arr[row][col]=0; //if cannot solve, this will backtrack agin to the previous step by assigning zero
		}
	}
	return false;
}


int main()
{
	/*
	generation part
	
	1. first an array with 9 rows and 9 cols will be created and the elemnts are initially assigned with 0
	2. second, the diagonal boxes will be filled with unique random numbers, then it is easy to fill other cells
	3. when fill the diagonal box, each cell in the diagonal box should check other elements and fill unique numbers only
	4. after that other cells will be filled if the number is not present in row, column or box
	5. finally random positions will be assigned 0 based on the user input
	*/
	
	/*
	solver part
	
	1. first it will check whether the number is present in row or column or box
	2. then it will check in the array for positions assigned as zero
	3. third it will solve the puzzle if its a valid place
	4. if cannot solve, it will go to previous step by assigning zero to the current position
	*/
	
	//initilize the array with 0
	int array[9][9];
	for (int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			array[i][j]=0;
		}
	}
	
	fillDiag(array); //fill diagonal boxes
	
	fillothercells(array,0,3); //fill other cells in the array
	cout<<"generated array before removing cells : "<<endl<<endl;
	print(array); //print the generated array
	
	cout<<endl<<endl<<"enter the no of columns and rows you want to remove (you can insert 2,3 or 4 based on the level of the game.)\n";
	cout<<"\t\t easy\t - 2\n";
	cout<<"\t\t medium\t - 3\n";
	cout<<"\t\t hard\t - 4\n";
	cout<<"\n\t\tenter the value :";
	int nu;
	while(!(nu>=2 && nu<=4))
	{
		cin>>nu;
		cout<<"\t\tinvalid range. enter the number again :";
	}
	
	removecells(array,nu); //remove the user entered no of cells from both rows and columns
	cout<<endl<<endl<<"after removing cells in the array :"<<endl<<endl;
	print(array); //print array after removing cells
	cout<<endl<<endl;
	
	cout<<"-----------------------solving part------------------------------\n\n ";
	cout<<"enter y/Y if you want to solve the puzzle or n/N to exit : ";
	char letter;
	cin>>letter;
	if(letter=='y' || letter=='Y')
		solve(array);
	else if(letter=='n' || letter=='N')
		exit(0);
	else
		cout<<"invalid user input";
	//print(array);
	
	return 0;
}

