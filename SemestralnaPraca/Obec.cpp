#include "Obec.h"

Obec::Obec(std::string pNazov, std::string pKod, std::string pTypObce, 
	int pKatastral, int pocetO, int pocetO14, int pocetO65, int pKanalizacia, int pVodovod, int pPlynofikacia, std::string pPoradie) : UzemnyCelok("obec", pNazov)
{
	nazov = pNazov;
	kod = pKod;
	typObce = pTypObce;
	katastralnaVymera = pKatastral;
	pocetObyvatelov = pocetO;
	pocetObyvatelovDo14 = pocetO14;
	pocetObyvatelovOd65 = pocetO65;
	kanalizacia = pKanalizacia;
	vodovod = pVodovod;
	plynofikacia = pPlynofikacia;
	if (pPoradie == "x") {
		poradie = 0;
	}
	else {
		poradie = std::stoi(pPoradie);
	}
	
}

void Obec::vypis()
{
		std::cout << this->nazov + " " << this->kod << std::endl;
		std::cout << "Vymera: " << this->katastralnaVymera << std::endl;
		std::cout << "Pocet obyvatelov: " << this->pocetObyvatelov << " z toho do 14 rokov: " << this->pocetObyvatelovDo14 << " a od 65 rokov: " << this->pocetObyvatelovOd65 << std::endl;
		std::cout << "Kanalizacia: " << this->kanalizacia << " Vodovod: " << this->vodovod << " Plynofikacia: " << this->plynofikacia << std::endl;
}
