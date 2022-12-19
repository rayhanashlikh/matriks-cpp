// Rayhan Ashlikh Rosyada
// A11.2021.13398
// 43UG2

#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
#define N 3 

// Procedure untuk menampilkan matriks
template <class T>
void display(T A[50][50], int baris, int kolom)
{
	for (int i = 0; i < baris; i++)
	{
		cout << "| ";
		for (int j = 0; j < kolom; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << " |" << endl;
	}
	cout << endl;
}

// Procedure untuk menginput matriks
void input(int A[50][50], int baris, int kolom)
{
	for (int i = 0; i < baris; i++)
	{
		for (int j = 0; j < kolom; j++)
		{
			cout << "Input matriks baris ke-" << i + 1 << " kolom ke-" << j + 1 << " :";
			cin >> A[i][j];
		}
		cout << endl;
	}

	cout << "Matriks yang telah diinputkan adalah : " << endl;
	display(A, baris, kolom);
}

// Procedure untuk menjumlahkan dua matriks
void add(int A[50][50], int B[50][50], int C[50][50], int baris, int kolom)
{
	for (int i = 0; i < baris; i++)
	{
		for (int j = 0; j < kolom; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

// Procedure untuk mengalikan dua matriks
void multiply(int A[50][50], int B[50][50], int C[50][50], int baris1, int kolom2)
{
	for (int i = 0; i < baris1; i++)
	{
		for (int j = 0; j < kolom2; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < N; k++)
			{ 
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

// void transpose(int A[50][50], int transp[50][50], int baris, int kolom)
// {
// 	for (int i = 0; i < baris; i++)
// 	{
// 		for (int j = 0; j < kolom; j++)
// 		{
// 			transp[i][j] = A[j][i];
// 		}
// 	}
// }

// Procedure untuk mendapatkan kofator dari A[p][q] dalam temp[][]. dengan N adalah
// dimensi dari A[][]
void getCofactor(int A[50][50], int temp[50][50], int p, int q,
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
int determinan(int A[50][50], int n)
{
	int D = 0; // Inisialisasi hasil

	// Kasus dasar : jika matriks berisi satu elemen
	if (n == 1)
		return A[0][0];

	int temp[50][50]; // Untuk menyimpan kofaktor

	int sign = 1; // Untuk menyimpan penanda dari matriks yang akan diiterasi

	// Melakukan iterasi dari tiap elemen pada baris pertama
	for (int f = 0; f < n; f++)
	{
		// Mendapatkan kofaktor dari A[0][f]
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinan(temp, n - 1);

		// dilakukan iterasi untuk mengurangi variabel penanda
		sign = -sign;
	}

	return D;
}

/* Procedure untuk mendapatkan adjoin dari matriks A[50][50] 
yang disimpan pada adj[50][50].*/
void adjoin(int A[50][50], int adj[50][50], int n)
{
	if (n == 1)
	{
		adj[0][0] = 1;
		return;
	}

	// deklarasi variabel temp yang akan menyimpan kofaktor
	int sign = 1, temp[50][50];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// Mendapatkan kofaktor dari A[i][j]
			getCofactor(A, temp, i, j, n);

			// penanda dari adj[j][i] positif jika jumlah baris 
			// dan indeks dari kolom adalah genap
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Pergantian baris dan kolom untuk 
			// mendapatkan transpos dari kofaktor matriks
			adj[j][i] = (sign) * (determinan(temp, n - 1));
		}
	}
}

// Fungsi untuk menemukan invers dari matriks A[50][50].
// mengembalikan nilai false jika matriks singular
bool inverse(int A[50][50], float inverse[50][50], int baris, int kolom)
{
	// Mencari determinan dari A[][]
	int det = determinan(A, baris);
	// Kondisi jika determinan adalah 0
	if (det == 0)
	{
		cout << "Matriks Singular, tidak memiliki invers";
		return false;  
	}

	// Mencari adjoin
	int adj[50][50];
	adjoin(A, adj, baris);

	// Mencari inverse menggunakan rumus "inverse(A) =
	// adj(A)/det(A)"
	for (int i = 0; i < baris; i++)
		for (int j = 0; j < kolom; j++)
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
	A[50][50],
	B[50][50],
	C[50][50], adj[50][50], baris1, kolom1, baris2, kolom2, baris3, kolom3;
	float inv[50][50];
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
				cout << "Masukkan jumlah baris matriks A: ";
				cin >> baris1;
				cout << "Masukkan jumlah kolom matriks A: ";
				cin >> kolom1;
				cout << "Masukkan elemen matriks pertama: " << endl;
				input(A, baris1, kolom1);
				getch();

				cout << "Masukkan jumlah baris matriks B: ";
				cin >> baris2;
				cout << "Masukkan jumlah kolom matriks B: ";
				cin >> kolom2;
				cout << "\nMasukkan elemen matriks kedua: " << endl;
				input(B, baris2, kolom2);
				clear();
				break;

			case 2:
				system("cls");
				cout << "Matriks pertama: " << endl;
				display(A, baris1, kolom1);
				cout << "\nMatriks kedua: " << endl;
				display(B, baris2, kolom2);

				if (baris1 == baris2 && kolom1 == kolom2)
				{
					cout << "\nHasil penjumlahan: " << endl;
					add(A, B, C, baris1, kolom1);
					display(C, baris1, kolom1);
				}
				else
				{
					cout << "\nMatriks tidak dapat dijumlahkan" << endl;
				}
				clear();
				break;

			case 3:
				system("cls");
				cout << "Matriks pertama: " << endl;
				display(A, baris1, kolom1);
				cout << "\nMatriks kedua: " << endl;
				display(B, baris2, kolom2);

				if (kolom1 == baris2)
				{
					cout << "\nHasil perkalian: " << endl;
					multiply(A, B, C, baris1, kolom2);
					display(C, baris1, kolom2);
				}
				else
				{
					cout << "\nMatriks tidak dapat dikalikan" << endl;
				}
				clear();
				break;

			case 4:
				system("cls");
				cout << "Tentukan matriks A atau B yang ingin ditemukan determinannya: ";
				cin >> pilih;

				if (pilih == 'A')
				{
					if (baris1 != kolom1)
					{
						cout << "Matriks tidak dapat dihitung determinannya" << endl;
					}
					else
					{
						cout << "Determinan matriks A: " << endl;
						cout << determinan(A, baris1) << endl;
					}
				}
				else if (pilih == 'B')
				{
					if (baris2 != kolom2)
					{
						cout << "Matriks tidak dapat dihitung determinannya" << endl;
					}
					else
					{
						cout << "Determinan matriks B: " << endl;
						cout << determinan(B, baris2) << endl;
					}
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
					if (baris1 != kolom1)
					{
						cout << "Matriks A tidak dapat dihitung Adjoinnya" << endl;
					}
					else
					{
						cout << "Adjoin matriks A: " << endl;
						adjoin(A, adj, baris1);
						display(adj, baris1, kolom1);
					}
				}
				else if (pilih == 'B')
				{
					if (baris2 != kolom2)
					{
						cout << "Matriks B tidak dapat dihitung Adjoinnya" << endl;
					}
					else
					{
						cout << "Adjoin matriks B: " << endl;
						adjoin(B, adj, baris2);
						display(adj, baris2, kolom2);
					}
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
					if (baris1 != kolom1)
					{
						cout << "Matriks A tidak dapat dihitung Inversenya" << endl;
					}
					else
					{
						cout << "Inverse matriks A: " << endl;
						if (inverse(A, inv, baris1, kolom1)) {
							display(inv, baris1, kolom1);
						}
					}
				}
				else if (pilih == 'B')
				{
					if (baris2 != kolom2)
					{
						cout << "Matriks B tidak dapat dihitung Inversenya" << endl;
					}
					else
					{
						cout << "Inverse matriks B: " << endl;
						if (inverse(B, inv, baris2, kolom2)) {
							display(inv, baris2, kolom2);
						}
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
				display(A, baris1, kolom1);
				cout << "Matriks B: " << endl;
				display(B, baris2, kolom2);
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
