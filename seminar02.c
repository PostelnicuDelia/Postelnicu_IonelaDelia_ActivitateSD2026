////[] = deplasare + dereferentiere
//// -> = dereferentiere + accesare
//
////vector = colectie de elem de acelasi tip care ocupa o zona de mem contigua si pe care putem folosi indexarea pt ca avem acces direct
//
//
//#include<stdio.h>
//#include<malloc.h>
//
//struct Biblioteca {
//	int id;
//	int nrCarti;
//	char* nume;
//	float suprafata;
//	char sector;
//};
//struct Biblioteca initializare(int id, int nrcarti, char* nume, float suprafata, char sector) {
//	struct Biblioteca s;
//	//initializare structura 
//	s.id = id;
//	s.nrCarti = nrcarti;
//	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//	strcpy(s.nume, nume);
//	s.suprafata = suprafata;
//	s.sector = sector;
//
//	return s;
//}
//
//
//
//void afisare(struct Biblioteca s) {
//	//afisarea tuturor atributelor
//	printf("Id: %d, Numarul de carti: %d, Nume: %s, Suprafata: %5.2f, Sector: %d\n", s.id, s.nrCarti, s.nume, s.suprafata, s.sector);
//
//}
//
//void afisareVectorB(struct Biblioteca* vector, int nrElemente) {
//	//afisarea elementelor din vector apeland functia afisare
//	for (int i = 0;i < nrElemente;i++) {
//		afisare(vector[i]);
//
//	}
//}
//
//struct Biblioteca copiazaBiblioteca(struct Biblioteca sursa) {
//	return initializare(sursa.id, sursa.nrCarti, sursa.nume, sursa.suprafata, sursa.sector);
//}
//
//struct Biblioteca* copiazaPrimeleNElemente(struct Biblioteca* vector, int nrElemente, int nrElementeCopiate) {
//	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
//	struct Biblioteca* vectorNou = NULL;
//	if (nrElementeCopiate > nrElemente) {
//		nrElementeCopiate = nrElemente;
//	}
//
//	vectorNou = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * nrElementeCopiate);
//	for (int i = 0;i < nrElementeCopiate;i++) {
//		vectorNou[i] = copiazaBiblioteca(vector[i]);
//	}
//
//	return vectorNou;
//}
//
//void dezalocare(struct Biblioteca** vector, int* nrElemente) {
//	//dezalocam elementele din vector si vectorul
//	for (int i = 0;i < (*nrElemente); i++) {
//		free((*vector)[i].nume); //dereferentiere(*) + indexare([]) + accesare(.)
//	}
//	free((*vector));
//	*vector = NULL;
//	*nrElemente = 0;
//}
//
//void copiazaBibliCuSuprafMaxima(struct Biblioteca* vector, char nrElemente, float suprafataMinima, struct Biblioteca** vectorNou, int* dimensiune) {
//	//parametrul prag poate fi modificat in functie de 
//	// tipul atributului ales pentru a indeplini o conditie
//	//este creat un nou vector cu elementele care indeplinesc acea conditie
//
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].suprafata > suprafataMinima)
//			(*dimensiune)++;
//	}
//
//	(*vectorNou) = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * (*dimensiune));
//	int contor = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].suprafata > suprafataMinima)
//		{
//			(*vectorNou)[contor++] = copiazaBiblioteca(vector[i]);
//		}
//
//	}
//}
//
//struct Biblioteca getPrimulElementConditionat(struct Biblioteca* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Biblioteca s;
//	s.id = 1;
//
//	return s;
//}
//
//
//int main() {
//	struct Biblioteca b1;
//	b1 = initializare(1, 542, "Nationala", 500.5, 3);
//	afisare(b1);
//
//	int nrBiblioteci = 5;
//
//	struct Biblioteca* vectorB = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * nrBiblioteci);
//	vectorB[0] = b1; //shallow copy
//	vectorB[1] = initializare(2, 11, "ASE", 234.6, 1);
//	vectorB[2] = initializare(3, 32, "Slavici", 874.5, 3);
//	vectorB[3] = initializare(4, 34, "Creanga", 102.3, 4);
//	vectorB[4] = initializare(5, 567, "Sadoveanu", 784, 2);
//
//	printf("\nElementele din vector:\n");
//	afisareVectorB(vectorB, nrBiblioteci);
//
//	int nrCopiate = 3;
//	struct Biblioteca* copie = copiazaPrimeleNElemente(vectorB, nrBiblioteci, nrCopiate);
//	printf("\nElementele vectorului cu primele %d elem copiate\n", nrCopiate);
//	afisareVectorB(copie, nrCopiate);
//
//	dezalocare(&copie, &nrCopiate);
//
//	struct Biblioteca* vectorBiblioteciSuprafataMare=NULL;
//	int nrBiblioteciSuprafataMare=0;
//
//	printf("\nBibliotecile cu suprafata cea mai mare:\n");
//	copiazaBibliCuSuprafMaxima(vectorB, nrBiblioteci, 100, &vectorBiblioteciSuprafataMare, &nrBiblioteciSuprafataMare);
//	afisareVectorB(vectorBiblioteciSuprafataMare, nrBiblioteciSuprafataMare);
//
//	printf("\nDezalocare vector cu suprafata mare:\n");
//	dezalocare(&vectorBiblioteciSuprafataMare, &nrBiblioteciSuprafataMare);
//	printf("Dezalocare vector initial:\n");
//	dezalocare(&vectorB, &nrBiblioteci);
//
//
//	return 0;
//}