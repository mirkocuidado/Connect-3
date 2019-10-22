#pragma once

#include<iostream>
using namespace std;

class Stablo {
	static int ID;
public:

	struct Node {
		int** mat;
		Node**pok;
		Node* otac;
		int pobednik;
		int napotezu;
		int id = ++ID;

		Node(int** m, Node* parent, int pobeda, int igra) {

			mat = new int*[5];
			for (int i = 0; i < 5; i++) {
				mat[i] = new int[5];
				for (int j = 0; j < 5; j++)
					mat[i][j] = m[i][j];
			}

			pok = new Node*[5];
			for (int i = 0; i < 5; i++)
				pok[i] = nullptr;

			otac = parent;
			pobednik = pobeda;
			napotezu = igra;
		}

		Node() {
			mat = new int*[5];
			for (int i = 0; i < 5; i++) {
				mat[i] = new int[5];
				for (int j = 0; j < 5; j++)
					mat[i][j] = 0;
			}

			pok = new Node*[5];
			for (int i = 0; i < 5; i++)
				pok[i] = nullptr;

			otac = nullptr;
			pobednik = 0;
		}

		~Node() {
			for (int i = 0; i < 5; i++)
				delete mat[i];
			delete[] mat;

			otac = nullptr;
			pobednik = 0;
		}

	};

	Stablo() {                                              // konstruktor bazican
		prvi = nullptr;
	}

	Stablo& dodaj (int**m) {                                   
		int prvii = koigra(m);

		int p;

		if (prvii == -1) p = 2;
		if (prvii == 1) p = -2;

		Node*novi = new Node(m, nullptr, p, prvii);
		prvi = novi;
		return *this;
	}

	~Stablo();

	int pobednik(int**mat, int igrac, Node*tek);

	int** ubaci(int** mat, int k, int& winner, int igrac, Node* tek);

	Stablo& odradi();

	Node* getprvi() const {
		return prvi;
	}

	void ispis() const;

	int koigra(int **m) const;

	Stablo& stabloigara(Node*prvi);

	bool list(Node*tek) const;

private:
	Node* prvi;
};

