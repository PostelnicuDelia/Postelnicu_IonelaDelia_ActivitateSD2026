//#include<stdio.h>
//#include<string.h>
//
//struct Student {
//	int id;
//	char* nume;
//	float medie;
//};
//
//typedef struct Student Student;
//
//struct Nod {
//	Student informatii;
//	struct Nod* next;
//};
//
//typedef struct Nod Nod;
//
//Student cititreStudentFisier(FILE* fisier) {
//	char buffer[20];
//	char separator = "',\n";
//	fgets(buffer, 19, fisier);
//
//	Student s;
//	
//	s.id = atoi(strtok(buffer, separator));
//	char* aux = strtok(NULL, separator);
//		s.nume = (char*)malloc(strlen(aux)+1);
//		strcpy(s.nume, aux);
//	s.medie = atof(strtok(NULL, separator));
//
//	return s;
//}
//
//void afisareStudent(Student s) {
//	printf("Id: %d\n", s.id);
//	printf("Nume: %s\n", s.nume);
//	printf("Media: %5.2\n", s.medie);
//	printf("\n");
//}
//
//void afisareListaStudenti(Nod* cap) {
//	while (cap != NULL) {
//		afisareStudent(cap->informatii);
//		cap = cap->next;
//	}
//}
//
//void adaugaStudInListaFinal(Nod** cap, Student studNou) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->informatii = studNou;
//	nou->next = NULL;
//
//	if (*cap == NULL) {
//		*cap = nou;
//	}
//	else {
//		Nod* aux = (*cap);
//		while (aux->next) {
//			aux = aux->next;
//		}
//		aux->next = nou;
//	}
//}
//
//int main() {
//	Nod* cap = adaugaStudInListaFinal
//
//
//	return 0;
//}