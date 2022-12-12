// C++ program to find adjoint and inverse of a matrix
#include <bits/stdc++.h>
using namespace std;
#define N 3

void input(int A[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> A[i][j];
		}
		cout << endl;
	}
}

void multiply(int A[N][N], int B[N][N], int C[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < N; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// Function to get cofactor of A[p][q] in temp[][]. n is
// current dimension of A[][]
void getCofactor(int A[N][N], int temp[N][N], int p, int q,
				 int n)
{
	int i = 0, j = 0;

	// Looping for each element of the matrix
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			// Copying into temporary matrix only those
			// element which are not in given row and
			// column
			if (row != p && col != q)
			{
				temp[i][j++] = A[row][col];

				// Row is filled, so increase row index and
				// reset col index
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

/* Recursive function for finding determinant of matrix.
n is current dimension of A[][]. */
int determinant(int A[N][N], int n)
{
	int D = 0; // Initialize result

	// Base case : if matrix contains single element
	if (n == 1)
		return A[0][0];

	int temp[N][N]; // To store cofactors

	int sign = 1; // To store sign multiplier

	// Iterate for each element of first row
	for (int f = 0; f < n; f++)
	{
		// Getting Cofactor of A[0][f]
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);

		// terms are to be added with alternate sign
		sign = -sign;
	}

	return D;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(int A[N][N], int adj[N][N])
{
	if (N == 1)
	{
		adj[0][0] = 1;
		return;
	}

	// temp is used to store cofactors of A[][]
	int sign = 1, temp[N][N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// Get cofactor of A[i][j]
			getCofactor(A, temp, i, j, N);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj[j][i] = (sign) * (determinant(temp, N - 1));
		}
	}
}

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(int A[N][N], float inverse[N][N])
{
	// Find determinant of A[][]
	int det = determinant(A, N);
	if (det == 0)
	{
		cout << "Singular matrix, can't find its inverse";
		return false;
	}

	// Find adjoint
	int adj[N][N];
	adjoint(A, adj);

	// Find Inverse using formula "inverse(A) =
	// adj(A)/det(A)"
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			inverse[i][j] = adj[i][j] / float(det);

	return true;
}

template <class T>
void display(T A[N][N])
{
	for (int i = 0; i < N; i++)
	{
		cout << "| ";
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << " |" << endl;
	}
}

int main()
{
	int A[N][N] = {11, 2, 3,
				   4, 5, 6,
				   7, 21, 9};

	int B[N][N]
	= { 10, 11, 12,
		13, 14, 15,
		16, 17, 18 };

	int C[N][N];
	int adj[N][N]; // To store adjoint of A[][]
	int cof[N][N]; // To store cofactor of A[][]

	float inv[N][N]; // To store inverse of A[][]

	cout << "Enter the elements of first matrix: " << endl;
	input(A);
	cout << "Enter the elements of second matrix: " << endl;
	input(B);

	cout << "Input matrix is :\n";
	display(A);
	cout << "\n";
	display(B);

	cout << "\nMultiplication between two matrices: " << endl;
	multiply(A, B, C);
	display(C);

	cout << "\nDeterminant: \n";
	cout << determinant(A, N) << endl;

	cout << "\nThe Adjoint is :\n";
	adjoint(A, adj);
	display(adj);

	cout << "\nThe Inverse is :\n";
	if (inverse(A, inv))
		display(inv);

	return 0;
}
