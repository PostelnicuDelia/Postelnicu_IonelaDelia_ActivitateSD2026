#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char* titlu;
	int nrPagini;
	float pret;
};

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Nod {
	Nod* next;
	Carte info;
};

Carte initializare(int id, const char* denumire, int nrPagini, float pret) {
	Carte c;
	c.id = id;
	c.pret = pret;
	c.nrPagini = nrPagini;

	c.titlu = malloc(strlen(denumire) + 1);
	strcpy(c.titlu, denumire);

	return c;
}

void afisareCarte(Carte c) {
	printf("Id %d\n", c.id);
	printf("Denumire %s\n", c.titlu);
	printf("Pret %5.2f\n", c.pret);
	printf("Numar Pagini %d\n", c.nrPagini);
}

void pushStack(Nod** prim, Carte c) {
	Nod* nodNou = malloc(sizeof(Nod));
	nodNou->info = c;
	nodNou->next = (*prim);
	(*prim) = nodNou;
}

Carte popStack(Nod** prim) {
	Carte c;
	if (*prim) {
		c = (*prim)->info;
		Nod* aux = (*prim);
		(*prim) = (*prim)->next;
		free(aux);
	}
	else {
		c.id = -1;
	}
	return c;

}

Carte getCarteByID(Nod** prim, int idDat) {
	Nod* auxStiva = NULL;
	Carte rezultat;
	Carte aux;

	while (*prim && (*prim)->info.id != idDat) {
		pushStack(&auxStiva, popStack(prim));
	}
	if (*prim) {
		aux = popStack(prim);
		rezultat = aux;
		rezultat.titlu = malloc(strlen(aux.titlu) + 1);
		strcpy(rezultat.titlu, aux.titlu);
		pushStack(prim, aux);
	}
	else {
		rezultat.id = -1;
		rezultat.titlu = NULL;
		rezultat.nrPagini = -1;
		rezultat.pret = -1;
	}
	while (auxStiva) {
		pushStack(prim, popStack(&auxStiva));
	}
	return rezultat;
}

Nod* splitStiva(Nod** p, int pragPagini) {
	Nod* stivaSubtire = NULL;
	Nod* aux = NULL;
	while (*p) {
		if ((*p)->info.nrPagini < pragPagini)
			pushStack(&stivaSubtire, popStack(p));
		else {
			pushStack(&aux, popStack(p));
		}
	}

	while (aux) {
		pushStack(p, popStack(&aux));
	}
	return stivaSubtire;

}

void dezalocare(Nod** cap) {
	while (*cap) {
		Carte c = popStack(cap);
		free(c.titlu);
	}
}

int main() {
	Carte c1 = initializare(1, "Ion", 120, 14.5);
	Carte c2 = initializare(2, "Enigma", 543, 15.2);
	Carte c3 = initializare(3, "Moara", 200, 23);
	Carte c4 = initializare(4, "Harap-alb", 80, 8.03);
	Carte c5 = initializare(5, "Morometii", 451, 18.03);
	Carte c6 = initializare(6, "XYZ", 784, 80);

	Nod* stiva = NULL;
	pushStack(&stiva, c1);
	pushStack(&stiva, c2);
	pushStack(&stiva, c3);
	pushStack(&stiva, c4);
	pushStack(&stiva, c5);
	pushStack(&stiva, c6);

	afisareCarte(popStack(&stiva));

	Nod* stivaSubtire = splitStiva(&stiva, 201);
	while (stivaSubtire) {
		Carte c = popStack(&stivaSubtire);
		afisareCarte(c);
		free(c.titlu);

	}

	Carte cautata = getCarteByID(&stiva, 3);
	afisareCarte(cautata);
	free(cautata.titlu);
	cautata = getCarteByID(&stiva, 2);
	afisareCarte(cautata);
	free(cautata.titlu);

	dezalocare(&stiva);


	return 0;
}