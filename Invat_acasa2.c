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