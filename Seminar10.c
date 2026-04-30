//Moduri de parcurgere graf: 
// ->preordine(radacina-stanga-dreapta RSD) 
// ->postordine (stanga-radacina-dreapta SRD)
// ->inordinde (SDR)


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
struct Nod {
	Masina info;
	struct Nod* stanga;
	struct Nod* dreapta;

};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	if (masina.id != -1)
	{
		printf("Id: %d\n", masina.id);
		printf("Nr. usi : %d\n", masina.nrUsi);
		printf("Pret: %.2f\n", masina.pret);
		printf("Model: %s\n", masina.model);
		printf("Nume sofer: %s\n", masina.numeSofer);
		printf("Serie: %c\n\n", masina.serie);
	}
	else printf("Masina nu exista!\n");
}


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina) {
		if ((*radacina)->info.id < masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua); // & si * pentru a dereferentia si a accesa adresa lui dreapta 
		}
		if ((*radacina)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua); 
		}
	}
	else {
		Nod* nou = malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		(*radacina) = nou;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	//setam primul nod pe null pentru ca intra direct pe else in functia de adaugare
	Nod* radacina = NULL;
	while (!feof(f)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore_preordine(Nod* radacina) {
	if (radacina)
	{
		afisareMasina(radacina->info);
		afisareMasiniDinArbore_preordine(radacina->stanga);
		afisareMasiniDinArbore_preordine(radacina->dreapta);
	}
}

void afisareMasiniDinArbore_inordine(Nod* radacina) {
	if (radacina) {
		afisareMasiniDinArbore_inordine(radacina->stanga);
		afisareMasina(radacina->info);
		afisareMasiniDinArbore_inordine(radacina->dreapta);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	if (*radacina) {
		dezalocareArboreDeMasini(&(*radacina)->stanga);
		dezalocareArboreDeMasini(&(*radacina)->dreapta);

		if ((*radacina)->info.numeSofer)
			free((*radacina)->info.numeSofer);
		if ((*radacina)->info.model)
			free((*radacina)->info.model);
		free(*radacina);
		*radacina = NULL;
	}

}

Masina getMasinaByID(Nod* radacina, int idCautat) {
	if (radacina) {
		if (radacina->info.id == idCautat) {
			Masina m = radacina->info;
			m.model = (char*)malloc(strlen(radacina->info.model) + 1);
			strcpy(m.model, radacina->info.model);
			m.numeSofer = malloc(strlen(radacina->info.numeSofer)+1);
			strcpy(m.numeSofer, radacina->info.numeSofer);
			return m;
		}
		if (radacina->info.id < idCautat) {
			Masina m = getMasinaByID(radacina->dreapta, idCautat);
			return m;
		}
		if (radacina->info.id > idCautat) {
			Masina m = getMasinaByID(radacina->stanga, idCautat);
			return m;
		}
		
	}
	else {
		Masina m;
		m.id = -1;
		return m;
	}
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina) {
		int stanga = determinaNumarNoduri(radacina->stanga);
		int dreapta = determinaNumarNoduri(radacina->dreapta);
		return stanga + dreapta + 1;
	}
	return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina) {
		int inaltimeSt = calculeazaInaltimeArbore(radacina->stanga);
		int inaltimeDr = calculeazaInaltimeArbore(radacina->dreapta);
		return max(inaltimeDr, inaltimeSt)+1;
	}
	return 0;
}

float calculeazaPretTotal(Nod* radacina) {

	if (radacina) {
		float stg = calculeazaPretTotal(radacina->stanga);
		float dr = calculeazaPretTotal(radacina->dreapta);
		return dr + stg + radacina->info.pret;
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
	if (radacina) {
		float suma = calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer)+calculeazaPretulMasinilorUnuiSofer(radacina->stanga,numeSofer);
		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
			return radacina->info.pret + suma;
		}
		else return suma;
		
	}
	else return 0;
}

int main() {
	Nod* radacina = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasiniDinArbore_inordine(radacina);

	
	afisareMasina(getMasinaByID(radacina, 5));
	//afisareMasina(getMasinaByID(radacina, 12));
	
	printf("Numarul de noduri din arbore este:%d\n", determinaNumarNoduri(radacina));
	printf("Inaltimea arborelui este:%d\n", calculeazaInaltimeArbore(radacina));
	printf("Pretul total al masinilor este:%5.2f\n", calculeazaPretTotal(radacina));
	printf("pretul masinilor lui gheorghe este de:%5.2f\n", calculeazaPretulMasinilorUnuiSofer(radacina, "Gheorghe"));
	printf("pretul masinilor lui Ionescu este de:%5.2f\n", calculeazaPretulMasinilorUnuiSofer(radacina, "Ionescu"));


	dezalocareArboreDeMasini(&radacina);
	printf("Arbore dupa dezalocare\n");
	afisareMasiniDinArbore_inordine(radacina);

	return 0;
}