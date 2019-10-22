#include "Red.h"

int Stablo::ID = 0;

Stablo::~Stablo() {

	Red lvl;
	Node*tek = prvi;
	lvl.dodaj(tek);                                   // U red se ubaci cvor

	while (lvl.getpoc() != nullptr) {                 // Dok ne dodjemo do kraja reda ( dok ne bude prazan )
		tek = lvl.obrisi();                           // Skinemo jedan cvor sa reda

		for (int i = 0; i < 5; i++)                   // Pogledamo sve njegove sinove
			if (tek->pok[i]!= nullptr)                // Ukoliko nisu nullptr
				lvl.dodaj(tek->pok[i]);               // Dodamo ih u red da cekaju svoje brisanje
			
		tek->otac = nullptr;                          // Oca od tekuceg cvor stavimo na nullptr
		delete tek;                                   // Obrisemo tekuci cvor
	}

	prvi = nullptr;
}

int Stablo::pobednik(int**a, int igrac, Node*tek) {       //pobednik metodi se salje matrica i broj sa pozicije koja je novoubacena, a vraca pobednika

	if (igrac == 0) return 0;


	/* PROVERA ZA DIJAGONALU DOLE LEVO - GORE DESNO */
	for (int j = 0; j < 3; j++) {
		for (int i = 2; i < 5; i++) {
			if (a[i][j] == igrac && a[i - 1][j + 1] == igrac && a[i - 2][j + 2] == igrac)
				return igrac;
		}
	}

	/* PROVERA ZA DIJAGONALU DOLE DESNO - GORE LEVO */
	for (int j = 2; j < 5; j++) {
		for (int i = 2; i < 5; i++) {
			if (a[i][j] == igrac && a[i - 1][j - 1] == igrac && a[i - 2][j - 2] == igrac)
				return igrac;
		}
	}

	/* PROVERA ZA VRSTU LEVO - DESNO */
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 3; i++) {
			if (a[i][j] == igrac && a[i][j + 1] == igrac && a[i][j + 2] == igrac)
				return igrac;
		}
	}
	/* PROVERA ZA KOLONU GORE - DOLE */
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 3; i++) {
			if (a[i][j] == igrac && a[i + 1][j] == igrac && a[i + 2][j] == igrac)
				return igrac;
		}
	}

	/* ZA JOS NIJE KRAJ SITUACIJE */

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == 0 && tek->napotezu == -1) return -2; // AKO JOS NIJE KRAJ PARTIJE I IGRA -1, VRATI -2
			if (a[i][j] == 0 && tek->napotezu == 1) return 2; // AKO JOS NIJE KRAJ PARTIJE I IGRA 1, VRATI 2
		}
    }

	return 0; /* AKO NISTA PRETHODNO NE VRATI INDIKATOR POBEDE, VRATICEMO INDIKATOR KRAJA PARTIJE NERESENIM ISHODOM */
}

Stablo& Stablo::odradi() {

	if (prvi == nullptr) exit(1);

	Red lvl;
	Node*tek = prvi;
	lvl.dodaj(tek);
	while (lvl.getpoc() != nullptr) {
		
		tek = lvl.obrisi();

		for (int i = 0; i < 5; i++) {

			if (tek->pobednik == 2 || tek->pobednik==-2) {                   // Ako jos nemamo pobednika, radimo sledecu obradu

				int**pom;                                                    // Napravimo pomocnu matricu

				pom = new int*[5];                                           // Prekopiramo matricu iz oca cvora
				for (int j = 0; j < 5; j++) {
					pom[j] = new int[5];
					for (int k = 0; k < 5; k++)
						pom[j][k] = tek->mat[j][k];
				}

				int winner = 0;                                               // Odredimo pobednika ( u nekom od sledecih koraka )

				if (pom[0][i] == 0) {                                         // Ako se u datu kolonu moze ubaciti kuglica

					pom = ubaci(pom, i, winner,tek->napotezu,tek);            // Ubacimo kuglicu na dato mesto

					int q = 0;                                                // Prebacimo da sledeci potez igra odgovarajuci igrac
					if (tek->napotezu == -1) q = 1;
					if (tek->napotezu == 1) q = -1;

					tek->pok[i] = new Node(pom, tek, winner,q);               // Nakacimo sina na tekuci cvor
					lvl.dodaj(tek->pok[i]);                                   // Ubacimo ga u red

				}                                                             // Ako ne moze prelazimo na sledeceg sina tekuceg cvora

			}

		}

	}
	return*this;
}

int** Stablo::ubaci(int ** a, int k, int& winner, int igrac, Node*tek) {

	int lucky = 8;

	for (int i = 4; i >= 0; i--) {               // Prodjemo kroz kolonu k odozdo na vise i trazimo slobodno mesto za nasu kuglicu
		if (a[i][k] == 0) {                      // Cim pronadjemo prvo mesto koje je 0, izadjemo iz petlje, jer smo nasli odgovarajuce mesto 
			lucky = i;                           // Pritom, samo zapamtimo indeks te vrste u koju treba upisati igraca koji je na potezu 
			break;
		}
	}

	int**pomm = a;

	pomm[lucky][k] = igrac;                     // Ubacimo igraca koji igra na pronadjenu poziciju

	int help = pomm[lucky][k];                  // Uzmemo njega, jer ce se u njegovoj manje vise neposrednoj blizini desiti promena

	winner = pobednik(pomm, help,tek);          // Odredimo pobednika ( ono sto je napisano kao kasnije ) i vratimo ga po referenci

	return pomm;
}

int Stablo::koigra(int **m) const {

	int k = 0, br1 = 0, br2 = 0, h=0;

	//Prebrojimo elemente u ulaznoj matrici kako bismo znali koji igrac igra sledeci.

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (m[i][j] == 1) br1++;
			if (m[i][j] == -1) br2++;
		}                                                            // PRETPOSTAVKA ZADATKA: Matrica se smatra da je ispravna, pa se ne mora proveravati da li neki igrac igra vise
	                                                                 // od jednog puta ( ako je br1 = br2+2 ) ili pak vise od toga ( br1 > br2 +1 ) sto pokriva sve i analogno za 
	                                                                 // obrnutu situaciju tj. drugog igraca.

	if (br1 > br2) k = -1;                                           // Ako u pocetnoj matrici ima vise 1, nego -1, igra -1.
	if (br2 > br1) k = 1;                                            // Ako u pocetnoj matrici ima vise -1, nego 1, igra 1.
	if (br2 == br1) {                                                // Ako ih ima jednako dozvolicemo korisniku da unese neki broj, pa cemo random selekcijom odabrati ko ce da igra
		cout << "Unesite neki pozitivan broj, po zelji: " << endl;
		cin >> h;

		if (h < 0) exit(1);

		if (h % 2 == 1) k = -1;                                      // Ako korisnik unese neparan broj, mi cemo mu odrediti -1,
		else k = 1;                                                  // dok, ako unese paran broj, dodelicemo mu 1.
	}

	return k;
}


void Stablo::ispis() const {

	if (!prvi) return;

	Red lvl;
	Node*tek = prvi;
	Node*smece = new Node();

	lvl.dodaj(prvi);
	lvl.dodaj(smece);

	while (lvl.getpoc() != nullptr) {

		tek = lvl.obrisi();

		if (tek != smece) {

				cout << "Na potezu je ";
				if (tek->napotezu == -1) cout << "plavi(-1)" << endl;
				else if (tek->napotezu == 1) cout << "crveni(1)" << endl;
             
			cout << endl;
			cout << tek->id << endl;

			cout << endl;

			for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++) {
					cout << tek->mat[i][j] << " ";

				if (i == 2 && j == 4) {

					if (tek->pobednik == -1) cout << "     (" << -tek->pobednik << ")";
					else if (tek->pobednik == 1) cout << "     (" << -tek->pobednik << ")";
					else cout << "     (" << tek->pobednik << ")";
					
			    }

					if (j == 4 && i != 4) cout << endl;
			}

			cout << endl;
			cout << endl;

			for (int i = 0; i < 5; i++)
				if (tek->pok[i] != nullptr)
					lvl.dodaj(tek->pok[i]);
		}

		else {

			cout << endl;
			cout << endl;
			cout << endl;

			if (lvl.getpoc() != nullptr)                                     // Ista fora sa smecem kao pomocnikom iz prvog zadatka
				lvl.dodaj(smece);
		}

	}

	delete smece;
	smece = nullptr;
}



bool Stablo::list(Node*tek) const{

	for (int i = 0; i < 5; i++)
		if (tek->pok[i] != nullptr) return false;                          // Ukoliko je neko od dece datog cvora razlicito od nullptr, taj cvor nije list.
	    return true;                                                       // Ukoliko su sva nullptr, on je list!
}



Stablo& Stablo::stabloigara(Node* prvi) {
	Red lvl;
	Node* tek = prvi;
	lvl.dodaj(tek);

	while (lvl.getpoc() != nullptr) {

		tek = lvl.obrisi();

		if (list(tek) == true) {

			int kraj = tek->pobednik;                                   // Zapamtimo pobednika iz lista ( koji mora biti -1/0/1 jer je zavrsno stanje )
			Node* oce = tek->otac;                                      // Vracamo se unazad pokazivacima na oca

			while (oce != nullptr) {                                    // Dok pokazivac na oca ne bude nullptr ( jedino kod cvora )

																		// Odradimo minimaks metodu:

				if (oce->napotezu == -1)                                // Ako je trenutno na potezu -1
					if (kraj < oce->pobednik) {                         // A krajnje stanje iz lista je manje od njega
						oce->pobednik = kraj;                           // Mi mu dodelimo to stanje, jer je to najbolje moguce stanje za njega
					}

				if (oce->napotezu == 1)                                 // Ako je trenutno na potezu 1
					if (kraj > oce->pobednik) {                         // A krajnje stanje iz lista je vece od njega
						oce->pobednik = kraj;                           // Mi mu dodelimo to stanje, jer je to najbolje moguce stanje za njega
					}

				oce = oce->otac;                                        // Idemo unazad dalje
			}
		}

		for (int i = 0; i < 5; i++)                                     // Ako dati cvor nije list 
			if (tek->pok[i] != nullptr)                                 // Svakog njegovog sina koji nije nullptr
				lvl.dodaj(tek->pok[i]);                                 // Ubacimo u red
	}
	return*this;
}