//Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#define ALPHA 26

int cmmdc(int a, int b)
{
	if (a == b)
		return a;
	else if (a > b)
		return cmmdc(a - b, b);
	else
		return cmmdc(a, b - a);
}

int conditie_lit_distincte(int v_frecv[ALPHA])
{
	/*functia returneaza 1, daca am cel putin 2 litere
	distincte citite si 0 in caz contrar*/
	int nr_litere_distincte = 0;
	for (int i = 0; i < ALPHA; ++i) {
		if (v_frecv[i])
			nr_litere_distincte++;
		if (nr_litere_distincte >= 2)
			return 1;
	}
	return 0;
}

int alert(int v_frecv[ALPHA], char v_lit[ALPHA])
{
	/*functia retunreaza 1 daca alerta este valida si
	printeaza litera dominanta alaturi de raportul cerut*/
	int nr_lit_total = 0;
	for (int i = 0; i < ALPHA; ++i)
		nr_lit_total += v_frecv[i];

	for (int i = 0; i < ALPHA; ++i)
		if (1.0 * v_frecv[i] >= 1.0 * nr_lit_total / 2) {
			int d = cmmdc(v_frecv[i], nr_lit_total);
			printf("%c %d/%d\n", v_lit[i], v_frecv[i] / d, nr_lit_total / d);
			return 1;
		}
	return 0;
}

void frecventa_lit(int v_frecv[ALPHA], char v_lit[ALPHA], char litera)
{
	for (int i = 0; i < ALPHA; ++i)
		if (litera == v_lit[i])
			v_frecv[i]++;
}

void nr_aparitii(char L, int v_frecv[ALPHA], char v_lit[ALPHA])
{
	for (int i = 0; i < ALPHA; ++i)
		if (v_lit[i] == L)
			printf("%c %d\n", v_lit[i], v_frecv[i]);
}

void primele_k(int k, int v_frecv[ALPHA], char v_lit[ALPHA])
{
	int v_aux[ALPHA];
	for (int i = 0; i < ALPHA; ++i)
		v_aux[i] = v_frecv[i];
	//copiem vect de frecv in v_aux pt a puteaa modifica aparitiile literelor
	while (k) {
		int max = -1, poz_max = -1;
		for (int i = 0; i < ALPHA; ++i)
			if (v_aux[i] > max) {
				max = v_aux[i];
				poz_max = i;
			}
		if (k > 1) {
			printf("%c ", v_lit[poz_max]);
			v_aux[poz_max] = -1;
		} else {
			//checker-ul temei nu accepta ' ' dupa ultimul output
			printf("%c", v_lit[poz_max]);
			v_aux[poz_max] = -1;
		}
		k--;
	}
	printf("\n");
}

void stergere_aparitii(char L, int v_frecv[ALPHA], char v_lit[ALPHA])
{
	for (int i = 0; i < ALPHA; ++i)
		if (L == v_lit[i]) {
			v_frecv[i] = 0;
			return;
		}
}

int main(void)
{
	char litera;
	/*lit_citite va memora nr de litere citite in vederea declansarii
	unei alerte valide */
	int v_frecv[ALPHA], last_alert = 0, lit_citite = 0;
	for (int i = 0; i < ALPHA; ++i)
		v_frecv[i] = 0;
	char v_lit[ALPHA] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
	'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z'};

	while (1) {
		scanf("%c", &litera);
		if ((litera >= 'A' && litera <= 'Z') && (litera != 'Q') &&
			(litera != 'T') && (litera != 'E'))
			break;

		if (litera >= 'a' && litera <= 'z') {
			frecventa_lit(v_frecv, v_lit, litera);
			lit_citite++;
			last_alert++;
			if (conditie_lit_distincte(v_frecv) && last_alert >= 5 &&
				lit_citite >= 5)
				if (alert(v_frecv, v_lit))
					last_alert = 0;
		}

		if (litera == 'Q') {
			char L;
			//ne asiguram ca L evita caracterul '\n' si ' '
			while (1) {
				scanf("%c", &L);
				if (L >= 'a' && L <= 'z')
					break;
			}
			nr_aparitii(L, v_frecv, v_lit);
		}

		if (litera == 'T') {
			int k;
			scanf("%d", &k);
			primele_k(k, v_frecv, v_lit);
		}

		if (litera == 'E') {
			char L;
			while (1) {
				scanf("%c", &L);
				if (L >= 'a' && L <= 'z')
					break;
			}
			stergere_aparitii(L, v_frecv, v_lit);
		}
	}
	return 0;
}
