#pragma once
#include <string>
#include "UzemnyCelok.h"

class Kraj :
	public UzemnyCelok
{
public:
	Kraj(std::string pNazov, std::string pKod) : UzemnyCelok("kraj", pNazov) {
		nazov = pNazov;
		kod = pKod;
	}
	~Kraj() override {}
	
	void vypis() override {
		std::cout << nazov + " " << kod + "\n";
	}
};

