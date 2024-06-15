#pragma once
#include <string>
#include "UzemnyCelok.h"
class SOORP :
	public UzemnyCelok
{
public:
	SOORP(std::string pNazov, std::string pKod) : UzemnyCelok("soorp", pNazov) {
		nazov = pNazov;
		kod = pKod;
	}
	~SOORP() override {}
	
	void vypis() override {
		std::cout << nazov + " " << kod + "\n";
	}

};

