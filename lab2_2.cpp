//============================================================================
// Name         : Lab2_2
// Author       : Tianze Li
// Version      : 1.0
// Date Created : 30/01/25
// Date Modified: 01/02/25
// Description  : A C++ Program that add, subtracts and multiplies dynamically
//                created matrices
//============================================================================
//starter_code_begins
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

//function declaration
int** add(int** matrix1, int** matrix2, int rows, int cols);								//Adds two matrices and returns the resulting matrix.
void cleanup(int** matrix, int rows);														//Frees the dynamically allocated memory of a matrix.
int** subtract(int** matrix1, int** matrix2, int rows, int cols);							//Subtracts one matrix from another and returns the resulting matrix.
int** multiply(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2);	//Multiplies two matrices and returns the resulting matrix.
void fill(int** matrix, int rows, int cols);												//Fills a matrix random values (0-20 both inclusive).
void display(int** matrix, int rows, int cols);												//Displays the contents of a matrix.		
int main()
{
	int **matrix1=NULL;
	int **matrix2=NULL;
	int rows1, cols1, rows2, cols2;
	int **ans1=NULL, **ans2=NULL, **ans3=NULL;

	cout<<"Enter the number of rows for first Matrix :";
	cin>>rows1;
	cout<<"Enter the number of columns for first Matrix :";
	cin>>cols1;
	cout<<"Enter the number of rows for second Matrix :";
	cin>>rows2;
	cout<<"Enter the number of columns for second Matrix :";
	cin>>cols2;

	// Create dynamic 2D arrays
	matrix1 = new int*[rows1];
	for(int i=0; i<rows1; i++)
		matrix1[i] = new int[cols1];
	matrix2 = new int*[rows2];
	for(int i=0; i<rows2; i++)
		matrix2[i] = new int[cols2];

	srand(time(0));
	fill(matrix1,rows1,cols1);		//fill both matrices with random values (int the range of 0-20)
	srand(time(0) + 100);
	fill(matrix2,rows2,cols2);
	cout<<"Matrix1 :"<<endl;
	display(matrix1, rows1, cols1);
	cout<<"Matrix2 :"<<endl;
	display(matrix2, rows2, cols2);
	
	if(rows1 == rows2 && cols1 == cols2)		//Perform addition only if both matrices have same dimensions
	{
		ans1 = add(matrix1, matrix2, rows1, cols1);
		cout<<"Matrix1 + Matrix2 :"<<endl;
		display(ans1,rows1, cols1);
		cleanup(ans1,rows1);

		ans2 = subtract(matrix1, matrix2, rows1, cols1);
		cout<<"Matrix1 - Matrix2 :"<<endl;
		display(ans2,rows1, cols1);
		cleanup(ans2,rows2);
	}

	if(cols1 == rows2)							//Perform multiplication if columns of first matrix are rows to the columns of second matrix
	{
		ans3 = multiply(matrix1,matrix2,rows1, cols1, rows2, cols2);
		cout<<"Matrix1 * Matrix2 :"<<endl;
		display(ans3,rows1,cols2);
		cleanup(ans3,rows1);
	}

	//Perform necessary cleanup (delete dynamically created memory)
	cleanup(matrix1,rows1);
	cleanup(matrix2,rows2);
	return 0;
}
//==============================================================
//starter_code_ends
/**
 * @brief Adds two matrices and returns the resulting matrix.
 * 
 * @param matrix1 First input matrix.
 * @param matrix2 Second input matrix.
 * @param rows Number of rows in both matrices.
 * @param cols Number of columns in both matrices.
 * @return int** Pointer to the newly allocated matrix containing the sum.
 */
int** add(int** matrix1, int** matrix2, int rows, int cols)
{
	//dynamically intiallise a new matrix called result
	int** result = new int*[rows];
    for (int i = 0; i < rows; i++)
        result[i] = new int[cols];

	//use two for loops to go through every element in matrix 1 and 2 and add them up
	//Then put the result back in the result matrix and return result matrix
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = matrix1[i][j] + matrix2[i][j];

    return result;
}
//==============================================================
/**
 * @brief Frees the dynamically allocated memory of a matrix.
 * 
 * @param matrix Pointer to the matrix.
 * @param rows Number of rows in the matrix.
 */
void cleanup(int** matrix, int rows)
{
	//use a for loop to delete all the rows in the matrix and then delete the matrix
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}
//===============================================================
/**
 * @brief Subtracts one matrix from another and returns the resulting matrix.
 * 
 * @param matrix1 First input matrix.
 * @param matrix2 Second input matrix.
 * @param rows Number of rows in both matrices.
 * @param cols Number of columns in both matrices.
 * @return int** Pointer to the newly allocated matrix containing the difference.
 */
int** subtract(int** matrix1, int** matrix2, int rows, int cols)
{
	//dynamically intiallise a new matrix called result
	int **result = new int*[rows];
	for (int i = 0; i < rows; i++)
		result[i] = new int[cols];

	//use two for loops to go through every element in matrix 1 and 2 and subtract them
	//Then put the result back in the result matrix and return result matrix
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < rows; j++)
			result[i][j] = matrix1[i][j] - matrix2[i][j];
	
	return result;
}
//==============================================================
/**
 * @brief Multiplies two matrices and returns the resulting matrix.
 * 
 * @param matrix1 First input matrix.
 * @param matrix2 Second input matrix.
 * @param rows1 Number of rows in the first matrix.
 * @param cols1 Number of columns in the first matrix (must match rows2).
 * @param rows2 Number of rows in the second matrix (must match cols1).
 * @param cols2 Number of columns in the second matrix.
 * @return int** Pointer to the newly allocated matrix containing the product.
 */
int** multiply(int** matrix1, int** matrix2, int rows1, int cols1, int rows2,int cols2)
{
	//checks if the matrix dimention is avaliable for multiplication of matrix
	if (cols1 != rows2)
		return NULL;
	
	//dynamically intiallise a new matrix called result
	int** result = new int*[rows1];
    for (int i = 0; i < rows1; i++){
        result[i] = new int[cols2];
	}
	//use three for loops to go through every row of matrix 1 and every column of matrix 2 and 
	// do the dot product to get the result matrix
	//Then put the result back in the result matrix and return result matrix
	for (int i = 0; i < rows1; i++){
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0; // resets all element in result matrix
            for (int k = 0; k < cols1; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j]; // dot product
        }
	}
    return result;
	
}
//===============================================================
/**
 * @brief Fills a matrix random values (0-20 both inclusive).
 * 
 * @param matrix Pointer to the matrix.
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 */
void fill(int** matrix, int rows, int cols)
{	
	//use two for loops to go through every element and assigns a randome number in each element
	for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand() % 21;
}
//===============================================================
/**
 * @brief Displays the contents of a matrix (see screenshot in the pdf docment).
 * 
 * @param matrix Pointer to the matrix.
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 */
void display(int** matrix, int rows, int cols)
{
	//use two for loops to go through every element and outputs all element of matrix
	for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(8) << right << matrix[i][j];
        }
        cout << endl;
    }
	cout << endl;
}
