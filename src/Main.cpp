#include "Stablo.h"

int main() {

	bool kraj = true;

	Stablo s;
	
	int **m = nullptr;

	while (kraj) {

		cout << "Vase opcije su sledece:" << endl;

		cout << "1. Unosenje matrice trenutnog stanja:" << endl;
		cout << "2. Formiranje stabla:" << endl;
		cout << "3. Ispisivanje stabla:" << endl;
		cout << "4. Zavrsetak programa!" << endl;

		cout << "Vas izbor?" << endl;

		int izbor;
		cin >> izbor;

		switch (izbor) {

		 case 1:

			cout << "Unesite elemente matrice:" << endl;
			cout << "Plavi= -1, a crveni=1" << endl;

			m = new int*[5];
			for (int i = 0; i < 5; i++) {
				m[i] = new int[5];
				for (int j = 0; j < 5; j++)
					cin >> m[i][j];
			}
			// Matrica se smatra ispravnom i nema potrebe za vrsenjem provera poput onih da li je unet neispravan broj kuglica, da li data matrica
			// vec ima pobednika i slicno.

			break;

		 case 2:

			s.dodaj(m);

			s.odradi();

			s.stabloigara(s.getprvi());

			cout << endl;
			cout << "Preporucujem da sledeci izbor bude 3!" << endl;
			cout << endl;

			break;

		 case 3:

			s.ispis();

			break;

		 case 4:

			cout << "Hasta la Vista!" << endl;
			cout << endl;
			kraj = false;
			break;

		}
	}

	system("pause");
	return 0;
}