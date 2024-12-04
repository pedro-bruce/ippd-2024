#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct data{
	FILE *f;
	int n;
	double t_medio;
};

bool tem_seq = false;
int res_esperado;

void calculaMedia(struct data *d)
{
	int res;
	double t;
	d->n = 0;

	while(fread(&res, sizeof(int), 1, d->f)){
		if (tem_seq && res != res_esperado)
			printf("Res esperado: %d - Res encontrado: %d\n", res_esperado, res);

		fread(&t, sizeof(double), 1, d->f);
		d->t_medio += t;
		d->n++;
	}

	d->t_medio /= d->n;

	if (!tem_seq)	//Só entra nesse if caso tenha o resultado da versão sequencial
		res_esperado = res;
}

int main (int argc, char *argv[])
{
	if (strlen(argv[1]) != strlen(argv[2]))
		printf("Alerta. As amostras têm intervalos diferentes\n");
	else
		//o +3 é pra pular as 3 primeiras letras
		if (strcmp(argv[1]+3, argv[2]+3)){
			printf("Alerta. As amostras têm intervalos diferentes\n");
		}

	struct data seq;
	struct data par;

	seq.f = fopen(argv[1], "rb");
	par.f = fopen(argv[2], "rb");
	
	if (!seq.f)
		printf("Sem amostras da versão sequencial\n");
	else{
		calculaMedia(&seq);
		tem_seq = true;

		printf("\nSequencial:\n");
		printf("Nº de amostras: %d\n", seq.n);
		printf("Media: %f ms\n", seq.t_medio);

		fclose(seq.f);
	}

	if (!par.f)
		printf("Sem amostras da versão paralelizada\n");
	else{
		calculaMedia(&par);
		printf("\nParalelizada:\n");
		printf("Nº de amostras: %d\n", par.n);
		printf("Media: %f ms\n", par.t_medio);
		fclose(par.f);
	}
	

	if (!seq.f && !par.f)
		return 1;
	else if (seq.f && par.f)
		printf("\nSpeedup alcançado na versão paralelizada: %f\n", seq.t_medio/par.t_medio);

	return 0;
}
