#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	printf("ID:%d \n, Usi:%d\n, pret:%5.2f\n, Model:%s\n, Sofer:%s\n, Serie:%c\n\n", 
		masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0;i < nrMasini;i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	Masina* temp = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));

	for (int i = 0;i < *nrMasini;i++) {
		temp[i] = (*masini)[i]; //* la masini pt ca trebuie sa dereferentiem si apoi sa accessam
		//se face shallow copy pentru model si nume Sofer
	}

	temp[*nrMasini] = masinaNoua; //atribuim lui temp 
	free(*masini);

	(*masini) = temp; //inlocuim adresa din stiva main cu adresam lui temp din stiva functiei
	(*nrMasini)++;
}

Masina citireMasinaFisier(FILE* file) { //FILE* = string catre fisier
	Masina m;
	char buffer[50]; //val din paranteze trebuie sa fie mai mare decat maximul fiecarei linii din txt
	fgets(buffer, 49, file); //49=nr maxim de caractere;

	char varDelimitator[3] = ",\n";
	
	m.id = atoi(strtok(buffer, varDelimitator));
	m.nrUsi = atoi(strtok(NULL, varDelimitator));
	m.pret = atof(strtok(NULL, varDelimitator));

	char* aux = strtok(NULL, varDelimitator);
	m.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.model, aux);

	aux = strtok(NULL, varDelimitator);
	m.numeSofer = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.numeSofer, aux);

	m.serie = strtok(NULL, varDelimitator)[0];
	return m;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file;
	file = fopen(numeFisier, "r");
	Masina* masini = NULL; //nu stim inca cate masini avem
	(*nrMasiniCitite) = 0;
	while (!feof(file)) {
		Masina m = citireMasinaFisier(file);
		adaugaMasinaInVector(&masini, nrMasiniCitite, m);
	}

	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0;i < (*nrMasini);i++) {
		//dereferentiere + deplasare + dereferentiere + accesare 
		//                          []
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}

	free(*vector);
	(*vector) = NULL;
	(*nrMasini) = 0;
}

int main() {
	Masina* masini = NULL;
	int nrMasini = 0;

	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);

	printf("Am dezalocat\n");
	dezalocareVectorMasini(&masini, &nrMasini);
	return 0;
}