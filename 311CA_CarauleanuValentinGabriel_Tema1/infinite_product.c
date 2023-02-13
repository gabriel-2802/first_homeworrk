//Carauleanu Valentin Gabriel 311CA
#include <stdio.h>
#include <math.h>

long long transf_b8_b10(long long n)
{
	//functia trece 'n' din baza 8 in baza 10
	long long new_nr = 0;
	int p = 0;
	while (n) {
		new_nr += n % 10 * pow(8, p);
		n /= 10;
		p++;
	}
	return new_nr;
}

int main(void)
{
	long long n, ps = 0, ai, bi, a_max2 = -1,
	b_max2 = -1, a_max1 = -1, b_max1 = -1;
	/*variabilele _max2 vor memora al doilea maxim, iar
	variabilele _max1 vor memora primul maxim*/
	double n_a  = 0, n_b = 0;
	scanf("%lli", &n);

	while (n) {
		scanf("%lli%lli", &ai, &bi);
		ai = transf_b8_b10(ai);
		bi = transf_b8_b10(bi);

		ps += (ai * bi);

		if (ai > a_max2 && ai < a_max1) {
			a_max2 = ai;
		} else if (ai > a_max1) {
			a_max2 = a_max1;
			a_max1 = ai;
		}
		if (bi > b_max2 && bi < b_max1) {
			b_max2 = bi;
		} else if (bi > b_max1) {
			b_max2 = b_max1;
			b_max1 = bi;
		}

		n_a += (double)(ai * ai);
		n_b += (double)(bi * bi);

		n--;
	}
	n_a = sqrt(n_a);
	n_b = sqrt(n_b);

	printf("%lli\n%lli %lli\n%.7lf %.7lf\n", ps, a_max2, b_max2, n_a, n_b);
	return 0;
}
