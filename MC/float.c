#include <stdio.h>
#include <math.h>

int binary_i(double n, int arr[]) {
	int i = 0;
	double tmp_i, tmp_f;
	while ((n != 0) && (i < 129)) {
		tmp_f = modf(n/2, &tmp_i);
		if (tmp_f == 0) arr[i] = 0;
		else arr[i] = 1;
		i++;
		n = tmp_i;
	}
	return i;
}

int binary_f(double f, int arr[]) {
	int i = 0;
	while ((f != 0) && (i < 151)) {
			f = f*2;
			if (f >= 1) {
				arr[i] = 1;
				f -= 1;
			}
			else arr[i] = 0;
			i++;
	}
	return i;
}

void binary_E(int n, int Flt[]) {
	int i;
	for (i = 23; i < 31; i++) {
		Flt[i] = n%2;
		n /= 2;
	}
	return;
}

void mk_zero(int Flt[]) {
	int i;
	for (i = 0; i < 31; i++) {
		Flt[i] = 0;
	}
	return;
}

void mk_inf(int Flt[]) {
	int i;
	for (i = 0; i < 31; i++) {
		if (i < 23) Flt[i] = 0;
		else Flt[i] = 1;
	}
	return;
}

void round_F(int remain, int last, int Flt[]) {
	if (last == 0) return;
	if ((remain == 1) && (Flt[0] == 0)) return;

	int i;
	for (i = 0; i < 23; i++)
		if (Flt[i] == 0) break;
		
	if (i == 23) return;

	for (i = 0; i < 23; i++) {
		if (Flt[i] == 0) {
			Flt[i] = 1;
			return;
		}
		Flt[i] = 0;
	}
	return;
}

void fill_F(int N_f[], int size_f, int start, int remain, int Flt[]) {
	int i = 22, j;
	for (j = start; j < size_f; j++) {
  	if (i < 0) {
    	round_F(remain, N_f[j], Flt);
      return;
    }
   	Flt[i] = N_f[j];
    i--;
  }
  for (j = i; j >= 0; j--)
  	Flt[j] = 0;
	return;
}

void fill_F2(int N_i[], int N_f[], int size_i, int size_f, int remain, int Flt[]) {
	int i = 22, j;
	for (j = size_i-2; j >= 0; j--) {
		if (i < 0) {
			round_F(remain, N_i[j], Flt);
		  return;
		}
		Flt[i] = N_i[j];
		i--;
	}
  for (j = 0; j < size_f; j++) {
  	if (i < 0) {
    	round_F(remain, N_f[j], Flt);
      return;
    }
    Flt[i] = N_f[j];
    i--;
  }
  for (j = i; j >= 0; j--)
  	Flt[j] = 0;
	return;
}

void mk_float(int sign, int N_i[], int N_f[], int size_i, int size_f, int Flt[]) {
	Flt[31] = sign;
	if (size_i >= 129) {
		mk_inf(Flt);
		return;
	}
	if ((size_i == 0) && (size_f == 0)) {
		mk_zero(Flt);
		return;
	}
	
	int remain;
	if (size_i == 0) {
		int k;
		for (k = 0; k < size_f; k++)
			if ((N_f[k] == 1) || (k > 125)) break;

		if (k < 126) {
			binary_E(126 - k, Flt);
			remain = size_f - k - 24;
			fill_F(N_f, size_f, k+1, remain, Flt);
		}
		else {
			binary_E(0, Flt);
			remain = size_f - 149;
			fill_F(N_f, size_f, 126, remain, Flt);
		}
	}
	else {
		binary_E(size_i + 126, Flt);
		remain = size_i + size_f - 24;
		fill_F2(N_i, N_f, size_i, size_f, remain, Flt);
	}
	return;
}

double mk_decimal(int Flt[]) {
	int i, E = 0, sign;
	double F = 0, two;
	if (Flt[31] == 0) sign = 1;
	else sign = -1;

	for (i = 30; i >= 23; i--) {
		E *= 2;
		E += Flt[i];
	}
	if (E == 0) {
		two = pow(2, -126);
		for (i = 22; i >= 0; i--) {
			two /= 2;
			F += two * Flt[i];
		}
		return F * sign;
	}
	if (E == 255) return INFINITY * sign;

	two = 1;
	for (i = 22; i >= 0; i--) {
		two /= 2;
		F += two * Flt[i];
	}
	F += 1;
	return sign * F * pow(2, E-127);
}

void print_array(int arr[]) {
	int i;
	for (i = 31; i >= 0; i--)
		printf("%d", arr[i]);
	printf("\n");
	return;
}

void main() {
	double N;
	int sign, N_i[129], N_f[151], size_i, size_f, Flt[32];

	printf("Enter a number: ");
	scanf("%lf", &N);

	if (N < 0) {
		sign = 1;
		N *= -1;
	}
	else sign = 0;

	double tmp_i, tmp_f;
	tmp_f = modf(N, &tmp_i);

	size_i = binary_i(tmp_i, N_i);
	size_f = binary_f(tmp_f, N_f);

 	mk_float(sign, N_i, N_f, size_i, size_f, Flt);

	print_array(Flt);
	printf("%lf\n", mk_decimal(Flt));

	return;
}
