#include "Red.h"

Red:: ~Red() {
	while (poc) {
		Elem*stari = poc;
		poc = poc->sled;
		delete stari;
	}
	poc = posl = nullptr;

	/*Klasican destruktor za listu koji koriscenjem pokazivaca stari krene od prvog elementa reda i dok prvi postoji tj. dok nije dosao
	  do kraja, brise element po element. */
}

Red& Red::dodaj(Node* node) {
	Elem* novi = new Elem(node);

	if (posl == nullptr) poc = novi;
	else
		posl->sled = novi;

	posl = novi;

	/* Po definiciji reda, element se u red dodaje na njegov kraj, pa stoga, ukoliko je red prazan, prvi i posl ce pokazivati na taj element,
	   a ukoliko nije, posl->sled ukazuje na novi, dodati element, pa prebacimo posl na taj novi, jer je on sada poslednji u redu.*/

	return*this;
}

Node* Red::obrisi() {
	if (poc == nullptr) {
		cout << "Nema elemenata u redu!" << endl;
		return nullptr;
	}

	Elem*stari = poc;
	Node* tek = poc->pok;

	poc = poc->sled;
	if (poc == nullptr) posl = nullptr;
	delete stari;

	/* Klasicno brisanje iz nekog reda, uz proveru da, ukoliko je red prazan tj. prvi==nullptr, onda vratimo nullptr, a ukoliko
	neki element postoji u redu, mi zapamtimo ono na sta on pokazuje i to vratimo kao povratnu vrednost, jer cemo onda raditi nesto s njim. */

	return tek;
}
