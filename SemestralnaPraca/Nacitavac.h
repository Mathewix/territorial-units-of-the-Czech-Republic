#pragma once
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Obec.h"
#include "Kraj.h"
#include "SOORP.h"
#include <string>
#include "CR.h"
#include <libds\amt\explicit_hierarchy.h>
#include <libds\amt\hierarchy.h>
#include <libds\adt\table.h>
#include <libds\adt\list.h>



using namespace ds::amt;
using namespace ds::adt;
using GBST = GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>*;
class Nacitavac
{
private:
	std::vector<UzemnyCelok*> obce;
	std::vector<UzemnyCelok*> kraje;
	std::vector<UzemnyCelok*> soorpy;
	GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>* tabulkaObec;
	GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>* tabulkaSOORP;
	GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>* tabulkaKraj;
	CR* stat = new CR();
	SOORP* xSorp = new SOORP("x", "x");
public:
	
	Nacitavac(std::string file);

	~Nacitavac();
	void nacitajDoHierarchie(MultiWayExplicitHierarchy<UzemnyCelok*>& hierarchia);
	void nacitajDoTabuliek();

	std::vector<UzemnyCelok*> getVector(std::string typCelku);
	GBST getTabulku(std::string typCelku);
	
};

