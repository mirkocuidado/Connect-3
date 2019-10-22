#pragma once

#include "Stablo.h"

using Node = Stablo::Node;

class Red
{

public:

	struct Elem {
		Node* pok;
		Elem*sled;

		Elem(Node* p) {
			pok = p;
			sled = nullptr;
		}
	};

	Red() {
		poc = nullptr;
		posl = nullptr;
	}

	~Red();

	Red& dodaj(Node* node);

	Node* obrisi();

	Elem* getpoc() const {
		return poc;
	}

private:
	Elem* poc, *posl;

};

