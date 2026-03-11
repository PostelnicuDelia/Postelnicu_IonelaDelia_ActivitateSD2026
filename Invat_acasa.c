#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraStudent {
	int id;
	int nrCredite;
	float medie;
	char* nume;
	char* specializare;
	unsigned char serie;
};

typedef struct StructuraStudent Student;

void afisareStudent(Student s) {
	printf("Id:%d\n", s.id);
	printf("Nume:%s\n", s.nume);
	printf("nrCredite:%d\n ", s.nrCredite);
	printf("medie:%5.2f \n", s.medie);
	printf("Specializare:%s \n", s.specializare);
	printf("Serie:%c \n", s.serie);
	printf(" \n");
}

void afisareVectorStudenti(Student* studenti, int nrStudenti) {
	for (int i = 0;i < nrStudenti;i++)
		afisareStudent(studenti[i]);
}

void adaugaStudent(Student** studenti, int* nrStudenti, Student s) {
	Student* temp = (Student*)malloc(sizeof(Student) * ((*nrStudenti)+1));
	for (int i = 0;i < *nrStudenti;i++) {
		temp[i] = (*studenti)[i];
	}

	temp[*nrStudenti] = s;
	(*nrStudenti)++;

	free(*studenti);
	(*studenti) = temp;

}

Student citireStudFisier(FILE* fisier) {
	Student s;
	char buffer[50];
	fgets(buffer, 50, fisier);

	char delimitator[3] = ",\n";
	s.id = atoi(strtok(buffer, delimitator));
	s.nrCredite= atoi(strtok(NULL, delimitator)); 
	s.medie = atof(strtok(NULL, delimitator));

	char* aux = strtok(NULL, delimitator);
	s.nume = (char*)malloc(sizeof(char) * (strlen(aux)+ 1));
	strcpy(s.nume, aux);

	aux = strtok(NULL, delimitator);
	s.specializare = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(s.specializare, aux);

	s.serie = strtok(NULL, delimitator)[0];

	return s;
}

Student* citireVEctorStudenti(const char* numeFisier, int* nrStudenti) {
	FILE* fisier;
	fisier = fopen(numeFisier, "r");

	Student* stud = NULL;
	(*nrStudenti) = 0;
	while (!feof(fisier)) {
		adaugaStudent(&stud, nrStudenti,citireStudFisier(fisier));
	}

	fclose(fisier);
	return stud;

}

void citireVectorStudentiFaraReturnare(const char* numeFisier, int* nrStudenti, Student** Studenti) {
	FILE* fisier;
	fisier = fopen(numeFisier, "r");

	(*nrStudenti) = 0;
	while(!feof(fisier)){
		adaugaStudent(Studenti, nrStudenti, citireStudFisier(fisier));
}
	fclose(fisier);

}

void dezalocare(Student** studenti, int* nrStudenti) {
	for (int i = 0;i < *nrStudenti;i++) {
		free((*studenti)[i].nume);
		free((*studenti)[i].specializare);
	}

	free(*studenti);
	*studenti = NULL;
	*nrStudenti = 0;
}

void main() {
	Student* stud=NULL;
	int nrstudenti = 0;

	stud = citireVEctorStudenti("studenti.txt", &nrstudenti);
	afisareVectorStudenti(stud, nrstudenti);

}