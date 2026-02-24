#include<stdio.h>
#include<stdlib.h>

struct Produs {
	int id; // int ocupa 4 octeti
	int stoc;
	char* denumire;  //char* ocupa 4 octeti daca avem arhitectura pe 36 de biti si 8 octeti la 64 de biti
	float pret; //float ocupa 4 octeti, double 8
	char categorie; //char ocupa 255, un byte (octet)
};

struct Produs initializare(int id, int stoc, char* denumire, float pret, char categorie) {
	struct Produs s;
	s.id = id;
	//initializare structura 
	s.stoc = stoc;
	s.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(s.denumire, denumire);
	//s.denumire = denumire;//daca nu alocam memoria manual, se aloca memoria din stiva, nu din heap si vor pointa amandoi catre acea adresa, se face atribuire de adrese
	s.pret = pret;
	s.categorie = categorie;
	return s;
}

void afisare(struct Produs s) {
	//afisarea tuturor atributelor.
	printf("\nId: %d\n", s.id);
	printf("Stoc: %d\n", s.stoc);
	printf("Denumire: %s\n", s.denumire);//se opreste la /0 -terminator de sir
	printf("Pret: %5.2f\n", s.pret);
	printf("Categorie: %c\n", s.categorie);

}

void modifica_Denumire(struct Produs* s, char* denumireNoua) {
	//modificarea unui atribut
	free(s->denumire);//se sterge memoria din locul vechi
	s->denumire = (char*)malloc(sizeof(char) * strlen(denumireNoua) + 1);//se aloca o noua zona de memorie
	strcpy(s->denumire, denumireNoua);//se copiaza de numirea noua in noua zona de memorie,,,, daca nu ransmit orin adresa, noua adresa de memorie se va sterge la incheierea functiei si va ramane adresa veche la denumire, care este stearsa, dei nu e bine prin valoare
}

void dezalocare(struct Produs* s) {
	//dezalocare campuri alocate dinamic dar si verificam
	if (s->denumire != NULL) {
		free(s->denumire);
		s->denumire = NULL;
	}
}

float CalcValTot(struct Produs p) {
	return p.pret * p.stoc;
}

int main() {
	struct Produs s;

	s = initializare(1, 20, "Telefon Smart", 2000, 'A'); //se pune cu '' ca sa nu se puna si sfarsitul de sir
	//telefon este salvat in stiva functiei main, iar cand se face initializarea se ia adresa de memorie din stiva

	afisare(s);
	modifica_Denumire(&s, "Mousse");
	afisare(s);
	printf("Valoarea Totala pentru %s este %5.2f RON", s.denumire, CalcValTot(s));

	dezalocare(&s);

	struct Produs* ps = &s;
	struct Produs* pp = malloc(sizeof(struct Produs));
	free(pp);
	//free(ps);

	/*char* c;
	printf("Un pointer ocupa %d", sizeof(c));
	am verificat dimensiunea unui char* */

	return 0;
}

//. - accesare
//* dereferentiere
//-> accesare+derefentiere