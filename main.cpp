// Rayhan Ashlikh Rosyada
// A11.2021.13398
// 43UG2

#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
#define N 3

// Procedure untuk menampilkan matriks
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
	cout << endl;
}

// Procedure untuk menginput matriks
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

	cout << "Matriks yang telah diinputkan adalah : " << endl;
	display(A);
}

// Procedure untuk menjumlahkan dua matriks
void add(int A[N][N], int B[N][N], int C[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

// Procedure untuk mengalikan dua matriks
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

// Procedure untuk mendapatkan kofator dari A[p][q] dalam temp[][]. dengan N adalah
// dimensi dari A[][]
void getCofactor(int A[N][N], int temp[N][N], int p, int q,
				 int n)
{
	int i = 0, j = 0;

	// Looping dari tiap elemen pada matriks
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			// Melakukan copy dari tiap elemen yang bukan pada baris p dan kolom q
			if (row != p && col != q)
			{
				temp[i][j++] = A[row][col];

				// Baris telah terisi, maka naikkan indeks baris dan
				// lakukan reset kolom index
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

/* Fungsi rekursif untuk menemukan determinan dari matriks,
dimana n merupakan dimensi dari A[][] */
int determinant(int A[N][N], int n)
{
	int D = 0; // Inisialisasi hasil

	// Kasus dasar : jika matriks berisi satu elemen
	if (n == 1)
		return A[0][0];

	int temp[N][N]; // Untuk menyimpan kofaktor

	int sign = 1; // Untuk menyimpan penanda dari matriks yang akan diiterasi

	// Melakukan iterasi dari tiap elemen pada baris pertama
	for (int f = 0; f < n; f++)
	{
		// Mendapatkan kofaktor dari A[0][f]
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);

		// dilakukan iterasi untuk mengurangi variabel penanda
		sign = -sign;
	}

	return D;
}

/* Procedure untuk mendapatkan adjoin dari matriks A[N][N] 
yang disimpan pada adj[N][N].*/
void adjoint(int A[N][N], int adj[N][N])
{
	if (N == 1)
	{
		adj[0][0] = 1;
		return;
	}

	// deklarasi variabel temp yang akan menyimpan kofaktor
	int sign = 1, temp[N][N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// Mendapatkan kofaktor dari A[i][j]
			getCofactor(A, temp, i, j, N);

			// penanda dari adj[j][i] positif jika jumlah baris 
			// dan indeks dari kolom adalah genap
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Pergantian baris dan kolom untuk 
			// mendapatkan transpos dari kofaktor matriks
			adj[j][i] = (sign) * (determinant(temp, N - 1));
		}
	}
}

// Fungsi untuk menemukan invers dari matriks A[N][N].
// mengembalikan nilai false jika matriks singular
bool inverse(int A[N][N], float inverse[N][N])
{
	// Mencari determinan dari A[][]
	int det = determinant(A, N);
	// Kondisi jika determinan adalah 0
	if (det == 0)
	{
		cout << "Matriks Singular, tidak memiliki invers";
		return false;
	}

	// Mencari adjoin
	int adj[N][N];
	adjoint(A, adj);

	// Mencari inverse menggunakan rumus "inverse(A) =
	// adj(A)/det(A)"
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			inverse[i][j] = adj[i][j] / float(det);

	return true;
}

// Fungsi untuk melakukan getch agar program yang dijalankan tidak langsung keluar
void clear()
{
	cout << "\nPress anything to continue...";
	getch();
}

int main()
{
	int option, 
	A[N][N] = {
		-11, 2, 3,
		4, 5, 6,
		7, 21, 9
	}, 
	B[N][N] = {
		10, 11, 12,
		13, 14, 15,
		16, 17, 18
	}, 
	C[N][N], adj[N][N];
	float inv[N][N];
	char pilih;

	do
	{
		system("cls");
		cout << "OPERASI MATRIKS" << endl;
		cout << "1. Input matriks" << endl;
		cout << "2. Jumlahkan matriks" << endl;
		cout << "3. Kalikan matriks" << endl;
		cout << "4. Determinan matriks" << endl;
		cout << "5. Adjoin matriks" << endl;
		cout << "6. Invers matriks" << endl;
		cout << "7. Lihat matriks" << endl;
		cout << "0. Keluar" << endl;

		cout << "\nMasukkan pilihan anda: ";
		cin >> option;

		switch(option)
		{
			case 1:
				system("cls");
				cout << "Masukkan elemen matriks pertama: " << endl;
				input(A);
				cout << "\nMasukkan elemen matriks kedua: " << endl;
				input(B);
				clear();
				break;

			case 2:
				system("cls");
				cout << "Matriks pertama: " << endl;
				display(A);
				cout << "\nMatriks kedua: " << endl;
				display(B);

				cout << "\nHasil penjumlahan: " << endl;
				add(A, B, C);
				display(C);
				clear();
				break;

			case 3:
				system("cls");
				cout << "Matriks pertama: " << endl;
				display(A);
				cout << "\nMatriks kedua: " << endl;
				display(B);

				cout << "\nHasil perkalian: " << endl;
				multiply(A, B, C);
				display(C);
				clear();
				break;

			case 4:
				system("cls");
				cout << "Tentukan matriks A atau B yang ingin ditemukan determinannya: ";
				cin >> pilih;

				if (pilih == 'A')
				{
					cout << "Determinan matriks A: " << endl;
					cout << determinant(A, N) << endl;
				}
				else if (pilih == 'B')
				{
					cout << "Determinan matriks B: " << endl;
					cout << determinant(B, N) << endl;
				}
				else
				{
					cout << "Pilihan tidak tersedia" << endl;
				}
				clear();
				break;

			case 5:
				system("cls");
				cout << "Tentukan matriks A atau B yang ingin ditemukan Adjoin nya: ";
				cin >> pilih;

				if (pilih == 'A')
				{
					cout << "Adjoin matriks A: " << endl;
					adjoint(A, adj);
					display(adj);
				}
				else if (pilih == 'B')
				{
					cout << "Adjoin matriks B: " << endl;
					adjoint(B, adj);
					display(adj);
				}
				else
				{
					cout << "Pilihan tidak tersedia" << endl;
				}
				clear();
				break;

			case 6:
				system("cls");
				cout << "Tentukan matriks A atau B yang ingin ditemukan Inverse nya: ";
				cin >> pilih;

				if (pilih == 'A')
				{
					cout << "Inverse matriks A: " << endl;
					if (inverse(A, inv)) {
						display(inv);
					}
				}
				else if (pilih == 'B')
				{
					cout << "Inverse matriks B: " << endl;
					if (inverse(B, inv)) {
						display(inv);
					}
				}
				else
				{
					cout << "Pilihan tidak tersedia" << endl;
				}
				clear();
				break;

			case 7:
				system("cls");
				cout << "Matriks A: " << endl;
				display(A);
				cout << "Matriks B: " << endl;
				display(B);
				clear();
				break;
			
			case 0:
				break;

			default:
				cout << "Pilihan tidak tersedia" << endl;
				clear();
				break;
		}
	} while (option != 0);

	return 0;
}
