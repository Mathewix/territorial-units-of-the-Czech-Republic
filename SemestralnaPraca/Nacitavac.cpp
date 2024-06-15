#include "Nacitavac.h"

Nacitavac::Nacitavac(std::string file)
{
	
	std::ifstream ifile;
	std::string line;
	std::string nazovKraja = "";
	std::string nazovObce = "";
	std::string nazovSOORP = "";
	std::string kodKraja = "";
	std::string kodSOORP = "";
	std::string kodObce = "";
	std::string dummy = "";
	std::string poslednySOORP = "";
	std::string typObce = "";
	std::string pocetCastiObce = "";
	std::string pocetKatastrov = "";
	std::string rozloha = "";
	std::string populacia = "";
	std::string populacia14 = "";
	std::string populacia65 = "";
	std::string kanal = "";
	std::string voda = "";
	std::string plyn = "";
	std::string poradie = "";
	bool skip = false;
	std::istringstream stream;

	ifile.open(file);
	if (ifile.is_open()) {
		while (std::getline(ifile, line)) {
			if (line.substr(0, 2) == ";;") {
				line.erase(std::remove(line.begin(), line.end(), ';'), line.end());
				nazovKraja = line;
				skip = true;
			}

			if (skip) {
				stream.clear();
				std::getline(ifile, line);
				stream.str(line);
				
				std::getline(stream, kodKraja, ';');
				Kraj* kraj = new Kraj(nazovKraja, kodKraja);
				kraje.push_back(kraj);
				
				skip = false;
			}
			else {
				stream.clear();
				stream.str(line);
				
				std::getline(stream, dummy, ';');
			}
			std::getline(stream, kodSOORP, ';');
			std::getline(stream, nazovSOORP, ';');
			
			if (nazovSOORP != "x") {
				if (poslednySOORP != nazovSOORP) {

					SOORP* soorp = new SOORP(nazovSOORP, kodSOORP);
					soorpy.push_back(soorp);
					poslednySOORP = nazovSOORP;
				}
			}

			std::getline(stream, poradie, ';');
			
			std::getline(stream, nazovObce, ';');
			std::getline(stream, kodObce, ';');
			std::getline(stream, typObce, ';');
			std::getline(stream, dummy, ';');
			std::getline(stream, dummy, ';');
			std::getline(stream, rozloha, ';');
			std::getline(stream, populacia, ';');
			std::getline(stream, populacia14, ';');
			std::getline(stream, populacia65, ';');
			std::getline(stream, kanal, ';');
			std::getline(stream, voda, ';');
			std::getline(stream, plyn, ';');
			std::getline(stream, dummy, '\n');
			rozloha.erase(std::remove(rozloha.begin(), rozloha.end(), ' '), rozloha.end());
			populacia.erase(std::remove(populacia.begin(), populacia.end(), ' '), populacia.end());
			populacia14.erase(std::remove(populacia14.begin(), populacia14.end(), ' '), populacia14.end());
			populacia65.erase(std::remove(populacia65.begin(), populacia65.end(), ' '), populacia65.end());
			kanal = (kanal == "-" or kanal == "") ? "0" : kanal;
			voda = (voda == "-" or voda == "") ? "0" : voda;
			plyn = (plyn == "-" or plyn == "") ? "0" : plyn;
			Obec* obec = new Obec(nazovObce, kodObce, typObce, std::stoi(rozloha),
				std::stoi(populacia), std::stoi(populacia14), std::stoi(populacia65),
				std::stoi(kanal), std::stoi(voda), std::stoi(plyn), poradie);
			obce.push_back(obec);
		}
	}
	
	ifile.close();
}

Nacitavac::~Nacitavac()
{
	for (UzemnyCelok* kraj : kraje)
	{
		delete kraj;
	}
	for (UzemnyCelok* soorp : soorpy)
	{
		delete soorp;
	}
	for (UzemnyCelok* obec : obce)
	{	
		delete obec;
	}
	kraje.clear();
	soorpy.clear();
	obce.clear();

	auto start = tabulkaKraj->begin();
	while (start != tabulkaKraj->end()) {
		auto data = *start;
		delete data.data_;
		++start;
	}
	
	auto start1 = tabulkaSOORP->begin();
	while (start1 != tabulkaSOORP->end()) {
		auto data = *start1;
		delete data.data_;
		++start1;
	}
	
	auto start2 = tabulkaObec->begin();
	while (start2 != tabulkaObec->end()) {
		auto data = *start2;
		delete data.data_;
		++start2;
	}
	tabulkaKraj->clear();
	tabulkaSOORP->clear();
	tabulkaObec->clear();
	delete stat;
	delete xSorp;
	delete tabulkaKraj;
	delete tabulkaSOORP;
	delete tabulkaObec;
}

void Nacitavac::nacitajDoHierarchie(MultiWayExplicitHierarchy<UzemnyCelok*>& hierarchia)
{
	MultiWayExplicitHierarchyBlock<UzemnyCelok*>& root = hierarchia.emplaceRoot();
	//hierarchia.changeRoot(&root);
	root.data_ = stat;
	auto test = hierarchia.accessRoot();

	//std::cout << &root << std::endl;
	//std::cout << test;
	int counter = 0;
	int pomocnaI = 0;
	int pomocnaJ = 1;
	//kraje
	for (UzemnyCelok* u : this->kraje) {
		MultiWayExplicitHierarchyBlock<UzemnyCelok*>& syn = hierarchia.emplaceSon(root, counter);
		syn.data_ = u;
		//std::cout << syn.data_->getKod() + "\n";
		//Hlavne mesto
		if (counter == 0) {
			
 			MultiWayExplicitHierarchyBlock<UzemnyCelok*>& vnuk = hierarchia.emplaceSon(syn, 0);
			vnuk.data_ = xSorp;
			MultiWayExplicitHierarchyBlock<UzemnyCelok*>& pravnuk = hierarchia.emplaceSon(vnuk, 0);
			pravnuk.data_ = this->obce[0];
			counter++;
		}
		else {
			//soorp
			for (int i = pomocnaI; i < this->soorpy.size(); i++) {
				MultiWayExplicitHierarchyBlock<UzemnyCelok*>& vnuk = hierarchia.emplaceSon(syn, i - pomocnaI);
				vnuk.data_ = this->soorpy[i];
				//std::cout << vnuk.data_->getKod() + "\n";
				//obce
				for (int j = pomocnaJ; j < this->obce.size(); j++) {

					if (j + 1 < this->obce.size()) {
						
						if (obce[j]->getPoradie() + 1 == obce[j+1]->getPoradie()) {

							MultiWayExplicitHierarchyBlock<UzemnyCelok*>& pravnuk = hierarchia.emplaceSon(vnuk, j - pomocnaJ);
							pravnuk.data_ = this->obce[j];
							//std::cout << pravnuk.data_->getKod() + "\n";
						}
						else {
							MultiWayExplicitHierarchyBlock<UzemnyCelok*>& pravnuk = hierarchia.emplaceSon(vnuk, j - pomocnaJ);
							pravnuk.data_ = this->obce[j];
							//std::cout << pravnuk.data_->getKod() + "\n";
							pomocnaJ = j + 1;
							break;
						}
					}
					else {
						MultiWayExplicitHierarchyBlock<UzemnyCelok*>& pravnuk = hierarchia.emplaceSon(vnuk, j-pomocnaJ);
						pravnuk.data_ = this->obce[j];
						//std::cout << pravnuk.data_->getKod() + "\n";
					}
				}
				// koniec obce
				if (i + 1 < this->soorpy.size()) {
					int kod1 = std::stoi(this->soorpy[i + 1]->getKod());
					int kod2 = std::stoi(this->soorpy[i]->getKod());
					if (kod1 - kod2 != 1) {
						pomocnaI = i + 1;
						break;
					}
				}
			}
			counter++;
		}
		
	}
}

void Nacitavac::nacitajDoTabuliek()
{
	this->tabulkaKraj = new GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>();
	this->tabulkaSOORP = new GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>();
	this->tabulkaObec = new GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>();

	for (UzemnyCelok* u : this->kraje) {
		if (!this->tabulkaKraj->contains(u->getNazov())) {
			auto list = new ImplicitList<UzemnyCelok*>();
			list->insertLast(u);
			this->tabulkaKraj->insert(u->getNazov(), list);
		}
		else {
			auto list = this->tabulkaKraj->find(u->getNazov());
			list->insertLast(u);
		}
	}
	for (UzemnyCelok* u : this->soorpy) {
		if (!this->tabulkaSOORP->contains(u->getNazov())) {
			auto list = new ImplicitList<UzemnyCelok*>();
			list->insertLast(u);
			this->tabulkaSOORP->insert(u->getNazov(), list);
		}
		else {
			auto list = this->tabulkaSOORP->find(u->getNazov());
			list->insertLast(u);
		}
	}

	for (UzemnyCelok* u : this->obce) {
		if (!this->tabulkaObec->contains(u->getNazov())) {
			auto list = new ImplicitList<UzemnyCelok*>();
			list->insertLast(u);
			this->tabulkaObec->insert(u->getNazov(), list);
		}
		else {
			auto list = this->tabulkaObec->find(u->getNazov());
			list->insertLast(u);
		}
	}
}

std::vector<UzemnyCelok*> Nacitavac::getVector(std::string typCelku)
{
	if (typCelku == "1" || typCelku == "kraj") {
		return this->kraje;
	} else if (typCelku == "2" || typCelku == "soorp") {
		return this->soorpy;
	} else if (typCelku == "3" || typCelku == "obec") {
		return this->obce;
	}
	return std::vector<UzemnyCelok*>();
}

GBST Nacitavac::getTabulku(std::string typCelku)
{
	if (typCelku == "0") {
		return this->tabulkaKraj;
	} else if (typCelku == "1") {
		return this->tabulkaSOORP;
	} else if (typCelku == "2") {
		return this->tabulkaObec;
	}
	return GBST();
}
