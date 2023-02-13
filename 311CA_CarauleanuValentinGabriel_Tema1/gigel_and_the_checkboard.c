//Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#define NMAX 1000

void final_pos(int x, int y, int n)
{
	printf("%d ", n - x);
	int cnt = 0;
	cnt = y / 26;
	/*daca catul impartirii lui y la 26 este nenul
	coordonatele vor fi de tipul 'AA', deci printam prima litera
	folosindu-ne de reprezentarea in cod ASCHII  a literelor*/
	if (cnt)
		printf("%c", 'A' + cnt - 1);
	//luam in consdierare ca tabla incepe numerotarea de la 0
	printf("%c\n", 'A' + y % 26);
}

int modif_white_square(int sah[NMAX][NMAX], int x, int y, int n)
{
	//functia se asigura ca raman in interiorul tablei de sah
	if (sah[x][y] > 0)
		y = (y + sah[x][y]) % n;
	else
		//ne asiguram ca operatorul '%' ne ofer un rezultat corect matematic
		y = ((y + sah[x][y]) % n + n) % n;
	return y;
}

int modif_black_square(int sah[NMAX][NMAX], int x, int y, int n)
{
	if (sah[x][y] > 0)
		x = (x + sah[x][y]) % n;
	else
		x = ((x + sah[x][y]) % n + n) % n;
	return x;
}

int main(void)
{
	int sah[NMAX][NMAX], n, x = 0, y = 0;
	unsigned long long distance = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			scanf("%d", &sah[i][j]);
	}

	while (sah[x][y]) {
		int aux1 = x, aux2 = y;

		if ((aux1 + aux2) % 2 == 0) {
			//patratul este alb
			y = modif_white_square(sah, x, y, n);
		} else {
			//patratul este negru
			x = modif_black_square(sah, x, y, n);
		}

		if (sah[aux1][aux2] > 0)
			distance += sah[aux1][aux2];
		else
			distance += (-1 * sah[aux1][aux2]);

		sah[aux1][aux2] = 0;
	}

	printf("%llu\n", distance);
	final_pos(x, y, n);

	return 0;
}
