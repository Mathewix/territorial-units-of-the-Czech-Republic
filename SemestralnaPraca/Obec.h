#pragma once
#include <string>
#include "UzemnyCelok.h"
class Obec :
	public UzemnyCelok
{
private:
	std::string nazov{};
	std::string kod{};
	std::string typObce{};
	int katastralnaVymera = 0;
	int pocetObyvatelov = 0;
	int pocetObyvatelovDo14 = 0;
	int pocetObyvatelovOd65 = 0;
	int kanalizacia = 0;
	int vodovod = 0;
	int plynofikacia = 0;
	int poradie = 0;
public:
	Obec(std::string pNazov, std::string pKod, std::string pTypObce,
		int pKatastral, int pocetO, int pocetO14, int pocetO65,
		int pKanalizacia, int pVodovod, int pPlynofikacia, std::string pPoradie);

	~Obec() override {};
	std::string getNazov() override {
		return nazov;
	}
	std::string getKod() override {
		return kod;
	}
	int getPoradie() override {
		return poradie;
	}
	void vypis() override;
};

