#pragma once
#include "Nacitavac.h"
#include "AlgoritmusNaTriedenie.h"
#include "Sortovac.h"
#include <iterator>

class HlavnyProgram
{
private:
	Nacitavac nacitavac;
	AlgoritmusNaTriedenie algoritmusT;
	Sortovac sorter;
	MultiWayExplicitHierarchy<UzemnyCelok*> hierarchia;
	ImplicitSequence<UzemnyCelok*>* is{};
	std::string vstup = "";
	std::string filter = "";
	std::string uroven = "";
	std::vector<UzemnyCelok*> vyhovujuce;
	TriediacaLambda<UzemnyCelok*> startsWith;
	TriediacaLambda<UzemnyCelok*> containsStr;
	TriediacaLambda<UzemnyCelok*> isSameType;
	SortovaciaLambda<UzemnyCelok*> abecednePorovnanie;
	SortovaciaLambda<UzemnyCelok*> pocetSpoluhlasok;
public:
	HlavnyProgram(std::string fileName);
	void initializeLambdaFunctions();
	void uroven1();
	void urovenTwoAndFour();
	void uroven3(GBST kraje, GBST soorpy, GBST obce);
	void program();
};

