//Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#define NMAX 400

void set_up_vector(int v[NMAX], int N)
{
	for (int i = 0; i < N * N; ++i)
		v[i] = 0;
}

void afisare(int v[NMAX], int N)
{
	/*Daca un element in vectorul de frecventa este nul
	il putem folosi in joc, deci printam 1. In caz contrar,
	printam 0*/
	for (int i = 0; i < N * N; ++i)
		if (v[i] == 0)
			printf("1 ");
		else
			printf("0 ");
	printf("\n");
}

void verificare_pozitii_libere(int v_frecv[NMAX], int N)
{
	/*Desi vectorul de frecv ne arata ce nr nu sunt folosite,
	ne asiguram ca cele fololsite nu ocupa toate spatiile valide */
	int suma = 0;
	for (int i = 0; i < N * N; ++i)
		suma += v_frecv[i];
	/*Daca suma elementelor vectorului de freventa este egala cu N
	atunci linia/coloana/careul este plin, deci nu putem folosi nici un numar*/
	if (suma == (N * N))
		for (int i = 0; i < N * N; ++i)
			v_frecv[i] = 1;
}

void verificare_linie(int sudoku[NMAX][NMAX], int v_frecv[NMAX], int N, int x)
{
	for (int i = 0; i < N * N; ++i)
		if (sudoku[x][i] != 0)
			v_frecv[sudoku[x][i] - 1]++;
}

void verificare_coloana(int sudoku[NMAX][NMAX], int v_frecv[NMAX], int N, int y)
{
	for (int i = 0; i < N * N; ++i)
		if (sudoku[i][y] != 0)
			v_frecv[sudoku[i][y] - 1]++;
}

void vf_careu(int sudoku[NMAX][NMAX], int v_frecv[NMAX], int x, int y, int N)
{
	for (int i = x; i < (x + N); ++i)
		for (int j = y; j < (y + N); ++j)
			if (sudoku[i][j] != 0)
				v_frecv[sudoku[i][j] - 1]++;
}

int prima_coord_careu(int z, int N)
{
	int careu = 0, y = 0, x = 0;
	/*functia det prima coord a careului, parcurgand
	secvential fiecare careu*/
	while (careu != z) {
		if ((y + N) > (N * N - 1)) {
			x += N;
			y = 0;
			careu++;
		} else {
			y += N;
			careu++;
		}
	}
	return x;
}

int a_doua_coord_careu(int z, int N)
{
	int careu = 0, y = 0, x = 0;
	while (careu != z) {
		if ((y + N) > (N * N - 1)) {
			x += N;
			y = 0;
			careu++;
		} else {
			y += N;
			careu++;
		}
	}
	return y;
}

void operatie_1(int x, int sudoku[NMAX][NMAX], int N)
{
	int v_frecv[NMAX * NMAX];
	set_up_vector(v_frecv, N);
	verificare_linie(sudoku, v_frecv, N, x);
	afisare(v_frecv, N);
}

void operatie_2(int y, int sudoku[NMAX][NMAX], int N)
{
	int v_frecv[NMAX * NMAX];
	set_up_vector(v_frecv, N);
	verificare_coloana(sudoku, v_frecv, N, y);
	verificare_pozitii_libere(v_frecv, N);
	afisare(v_frecv, N);
}

void operatie_3(int z, int sudoku[NMAX][NMAX], int N)
{
	//localizam coord din coltul stanga-sus a celulei
	int x_careu = prima_coord_careu(z, N);
	int y_careu = a_doua_coord_careu(z, N);
	int v_frecv[NMAX * NMAX];
	set_up_vector(v_frecv, N);
	vf_careu(sudoku, v_frecv, x_careu, y_careu, N);
	verificare_pozitii_libere(v_frecv, N);
	afisare(v_frecv, N);
}

void operatie_4(int x, int y, int sudoku[NMAX][NMAX], int N)
{
	if (sudoku[x][y]) {
		for (int i = 0; i < N * N; ++i)
			printf("0 ");
		printf("\n");
		return;
	}
	int v_frecv[NMAX];
	set_up_vector(v_frecv, N);
	verificare_linie(sudoku, v_frecv, N, x);
	verificare_coloana(sudoku, v_frecv, N, y);

	int careu = x / N * N + y / N; // var 'careu' este careul actual
	int x_careu = prima_coord_careu(careu, N);
	int y_careu = a_doua_coord_careu(careu, N);
	vf_careu(sudoku, v_frecv, x_careu, y_careu, N);

	afisare(v_frecv, N);
}

void operatie_5(int x, int y, int c, int sudoku[NMAX][NMAX])
{
	if (sudoku[x][y] == 0)
		sudoku[x][y] = c;
}

void operatie_6(int sudoku[NMAX][NMAX], int N)
{
	//incepem prin a verifica daca jocul mai este valid
	int celula_libera = 0, v_frecv[NMAX];

	//verificam liniile pentre dubluri, dar si pentru o pozitie libera
	for (int i = 0; i < N * N; ++i) {
		set_up_vector(v_frecv, N);
		verificare_linie(sudoku, v_frecv, N, i);
		for (int k = 0; k < N * N; ++k) {
			if (v_frecv[k] == 0)
				celula_libera = 1;
			if (v_frecv[k] > 1) {
				//daca gasim o dublura iesim din functie
				printf("1\n");
				return;
			}
		}
	}

	//verificam coloanele pentru dubluri, dar si pentru o pozitie libera
	for (int i = 0; i < N * N; ++i) {
		set_up_vector(v_frecv, N);
		verificare_coloana(sudoku, v_frecv, N, i);
		for (int k = 0; k < N * N; ++k) {
			if (v_frecv[k] == 0)
				celula_libera = 1;
			if (v_frecv[k] > 1) {
				printf("1\n");
				return;
			}
		}
	}

	//verificam careele pentru dubluri, dar si pentru o pozitie libera
	for (int i = 0; i < N * N; ++i) {
		set_up_vector(v_frecv, N);
		int x_careu = prima_coord_careu(i, N);
		int y_careu = a_doua_coord_careu(i, N);
		vf_careu(sudoku, v_frecv, x_careu, y_careu, N);
		for (int k = 0; k < N * N; ++k) {
			if (v_frecv[k] == 0)
				celula_libera = 1;
			if (v_frecv[k] > 1) {
				printf("1\n");
				return;
			}
		}
	}

	/* daca ajungem aici fara sa iesim din functie, jocul este valid
	si testam sa vedem daca jocul mai poate fi completat */
	if (celula_libera) {
		printf("0\n");
		return;
	}

	/*In acest punct jocul nu este invalid si este completat,
	Prin urmare, jocul este castigat */
	printf("2\n");
}

int main(void)
{
	int N, M, sudoku[NMAX][NMAX];
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N * N; ++i)
		for (int j = 0; j < N * N; ++j)
			scanf("%d", &sudoku[i][j]);

	int operatie, x, y, z, c;

	while (M) {
		scanf("%d", &operatie);
		switch (operatie) {
		case 1:
			scanf("%d", &x);
			operatie_1(x - 1, sudoku, N);
			break;
		case 2:
			scanf("%d", &y);
			operatie_2(y - 1, sudoku, N);
			break;
		case 3:
			scanf("%d", &z);
			operatie_3(z - 1, sudoku, N);
			break;
		case 4:
			scanf("%d%d", &x, &y);
			operatie_4(x - 1, y - 1, sudoku, N);
			break;
		case 5:
			scanf("%d%d%d", &x, &y, &c);
			operatie_5(x - 1, y - 1, c, sudoku);
			break;
		case 6:
			operatie_6(sudoku, N);
			break;
		}
		M--;
	}

	return 0;
}
