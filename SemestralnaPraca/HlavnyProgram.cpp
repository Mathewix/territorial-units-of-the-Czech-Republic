#include "HlavnyProgram.h"

HlavnyProgram::HlavnyProgram(std::string fileName) : nacitavac(fileName) 
{
	this->nacitavac.nacitajDoHierarchie(this->hierarchia);
	this->nacitavac.nacitajDoTabuliek();
	this->initializeLambdaFunctions();
	
}

void HlavnyProgram::uroven1()
{
	while (true) {
		std::cout << "Èo ideme filtrova? (kraj = 1, soorp = 2, obec = 3, koniec (ukonèenie programu))\n";
		std::cin >> this->vstup;
		std::vector<UzemnyCelok*> uzemneCelky;

		uzemneCelky = this->nacitavac.getVector(this->vstup);
		if (uzemneCelky.empty()) {
			break;
		}
		std::cout << "Zadajte string, pod¾a ktorého chcete filtrova\n";
		std::cin >> this->filter;
		std::cout << "String má by na zaèiatku (start = 1) alebo sa má v názve iba nachádza? (contains = 2)\n";
		std::cin >> this->vstup;
		if (this->vstup == "1" || this->vstup == "start") {

			this->vyhovujuce = algoritmusT.algoritmus(this->filter, uzemneCelky.begin(), uzemneCelky.end(), this->startsWith);
		}
		else if (this->vstup == "2" || this->vstup == "contains") {
			this->vyhovujuce = algoritmusT.algoritmus(this->filter, uzemneCelky.begin(), uzemneCelky.end(), this->containsStr);
		}
		for (auto uc : vyhovujuce) {
			std::cout << uc->getNazov() + " " + uc->getKod() + "\n";
		}
	}
}

void HlavnyProgram::urovenTwoAndFour()
{
	auto aktualnyVrchol = hierarchia.accessRoot();
	while (true) {
		MultiWayExplicitHierarchy<UzemnyCelok*>::PreOrderHierarchyIterator poi_b(&this->hierarchia, aktualnyVrchol);
		MultiWayExplicitHierarchy<UzemnyCelok*>::PreOrderHierarchyIterator poi_e(&this->hierarchia, nullptr);
		std::cout << "Nachadzas sa na: '" << aktualnyVrchol->data_->getType() + "' " << aktualnyVrchol->data_->getNazov() << "\nchces sa niekam posunut? dole = 0, hore = 1, vyhladavat = 2 \n";
		std::cin >> this->vstup;
		if (this->vstup == "0" || this->vstup == "dole") {
			if (aktualnyVrchol->data_->getType() != "obec") {
				std::string poradie = "";
				std::cout << "Na ktoru nizsiu jednotku v poradi sa posunieme? Tu su synovia:\n";
				
				for (int i = 0; i < aktualnyVrchol->sons_->size(); i++) {
					std::cout << i << ". ";
					aktualnyVrchol->sons_->access(i)->data_->data_->vypis();
				}
				std::cin >> poradie;
				if (std::stoi(poradie) < aktualnyVrchol->sons_->size()) {
					aktualnyVrchol = this->hierarchia.accessSon(*aktualnyVrchol, std::stoi(poradie));
				}
				else {
					std::cout << aktualnyVrchol->data_->getNazov() + " neobsahuje tolko uzemnych jednotiek\n";
				}
			}
			else {
				std::cout << "Z obce sa uz nizsie neda ist.\n";
			}
		}
		else if (this->vstup == "1" || this->vstup == "hore") {
			if (aktualnyVrchol->data_->getType() != "stat") {
				aktualnyVrchol = this->hierarchia.accessParent(*aktualnyVrchol);
			}
			else {
				std::cout << "Zo statu sa uz vyssie neda ist.\n";
			}
		}
		else if (this->vstup == "2" || this->vstup == "vyhladavat") {
			std::cout << "Ako ideme filtrovat? 0 = string na zaciatku, 1 = nazov obsahuje string, 2 = uzemne celky, zvoleneho typu\n";
			std::cin >> this->vstup;
			if (this->vstup == "0") {
				std::cout << "Napis string, ktorim sa bude filtrovat\n";
				std::cin >> this->filter;
				this->vyhovujuce = this->algoritmusT.algoritmus<UzemnyCelok*, MultiWayExplicitHierarchy<UzemnyCelok*>::PreOrderHierarchyIterator>(this->filter, poi_b, poi_e, this->startsWith);
			}
			else if (this->vstup == "1") {
				std::cout << "Napis string, ktorim sa bude filtrovat\n";
				std::cin >> this->filter;
				this->vyhovujuce = this->algoritmusT.algoritmus<UzemnyCelok*, MultiWayExplicitHierarchy<UzemnyCelok*>::PreOrderHierarchyIterator>(this->filter, poi_b, poi_e, this->containsStr);
			}
			else if (this->vstup == "2") {
				std::cout << "Aky typ? 0 = kraj, 1 = soorp, 2 = obec\n";
				std::cin >> this->filter;
				if (this->filter == "0" || this->filter == "kraj") {
					this->filter = "kraj";
				}
				else if (this->filter == "1" || this->filter == "soorp") {
					this->filter = "soorp";
				}
				else if (this->filter == "2" || this->filter == "obec") {
					this->filter = "obec";
				}
				this->vyhovujuce = this->algoritmusT.algoritmus<UzemnyCelok*, MultiWayExplicitHierarchy<UzemnyCelok*>::PreOrderHierarchyIterator>(this->filter, poi_b, poi_e, this->isSameType);
			}
			else {
				break;
			}
			if (uroven != "4") {
				for (UzemnyCelok* uc : this->vyhovujuce) {
					uc->vypis();
				}
			}
			else {
				std::cout << "Ako zoradi uzemne celky? 0 = abecedne, 1 = pocet spoluhlasok\n";
				std::cin >> this->vstup;
				if (this->vstup == "0") {
					this->is = this->sorter.algoritmus<UzemnyCelok*>(this->vyhovujuce, this->abecednePorovnanie);
				}
				else if (this->vstup == "1") {
					this->is = this->sorter.algoritmus<UzemnyCelok*>(this->vyhovujuce, this->pocetSpoluhlasok);
				}
				else {
					break;
				}
				auto start = this->is->begin();
				while (start != this->is->end()) {
					(*start)->vypis();
					++start;
				}
			}

			//std::cout << is.accessFirst()->data_->getNazov() << " " << is.accessLast()->data_->getNazov() << "\n";


			std::cout << "Chcete pokraèova?\n";
			std::cin >> this->vstup;
			this->vyhovujuce.clear();
			if (vstup == "nie") {
				break;
			}
		}
		else {
			break;
		}
	}
	if (is) {
		is->clear();
		delete is;
	}
}

void HlavnyProgram::uroven3(GBST kraje, GBST soorpy, GBST obce)
{

	GeneralBinarySearchTree<std::string, ImplicitList<UzemnyCelok*>*, TableItem<std::string, ImplicitList<UzemnyCelok*>*>>* tabulkaSDatami = nullptr;
	std::string vstup = "";
	while (true) {
		std::cout << "Co chceme prehladat? (kraje = 0, soorpy = 1, obce = 2)\n";
		std::cin >> vstup;
		if (vstup == "0") {
			tabulkaSDatami = kraje;
		}
		else if (vstup == "1") {
			tabulkaSDatami = soorpy;
		}
		else if (vstup == "2") {
			tabulkaSDatami = obce;
		}
		else {
			break;
		}
		std::cout << "Zadaj nazov, ktory ma mat tvoj hladany Uzemny Celok\n";
		std::cin.ignore();
		std::getline(std::cin, vstup);
		if (tabulkaSDatami->contains(vstup)) {
			auto list = tabulkaSDatami->find(vstup);
			if (list) {
				for (int i = 0; i < list->size(); i++) {
					list->access(i)->vypis();
				}
			}
			else {
				std::cout << "Zaznam nebol najdeny.\n";
			}
		}
		else {
			std::cout << "Nazov sa nenachadza v tabulke.\n";
		}

	}
}

void HlavnyProgram::initializeLambdaFunctions()
{
	startsWith = [](std::string filter, UzemnyCelok* uzemnyCelok) {
		int dlzka = filter.length();
		return uzemnyCelok->getNazov().compare(0, dlzka, filter) == 0;
		};
	containsStr = [](std::string filter, UzemnyCelok* uzemnyCelok) {
		return uzemnyCelok->getNazov().find(filter) != std::string::npos;
		};
	isSameType = [&](std::string level, UzemnyCelok* uzemnyCelok) {
		return uzemnyCelok->getType() == level;
		};

	abecednePorovnanie = [](UzemnyCelok* uc1, UzemnyCelok* uc2) {
		std::string ceskaAbeceda = "AÁáBCÈèDÏïEÉéÌìFGHIÍíJKLMNòOóPQRØøSŠšTUÚúùVWXYÝýZŽž";
		std::string nazov1 = uc1->getNazov();
		std::string nazov2 = uc2->getNazov();
		int len = (nazov1.size() < nazov2.size()) ? nazov1.size() : nazov2.size();
		for (int i = 0; i < len; ++i) {
			char c1 = std::toupper(nazov1[i]);
			char c2 = std::toupper(nazov2[i]);


			int index1 = ceskaAbeceda.find(c1);
			int index2 = ceskaAbeceda.find(c2);

			if (index1 == std::string::npos || index2 == std::string::npos) {
				if (c1 != c2) {
					return c1 < c2;
				}
			}
			else {
				if (index1 != index2) {
					return index1 < index2;
				}
			}
		}
		return nazov1.size() < nazov2.size();
		};
	pocetSpoluhlasok = [](UzemnyCelok* uc1, UzemnyCelok* uc2) {
		return uc1->getPocetSpoluhlasok() < uc2->getPocetSpoluhlasok();
		};
}
void HlavnyProgram::program() {
	std::string zaver = "";
	while (true) {
		std::cout << "Ktoru funkciu ideme testovat? 1,2,3,4\n";
		std::cin >> this->uroven;
		if (this->uroven == "1") {
			this->uroven1();
			std::cout << "Koncime program alebo skusime ine urovne? (napis 'ine' pre pokracovanie)\n";
			std::cin >> zaver;
			if (zaver != "ine") {
				break;
			}
		}
		else if (this->uroven == "2" || this->uroven == "4") {
			this->urovenTwoAndFour();
			std::cout << "Koncime program alebo skusime ine urovne? (napis 'ine' pre pokracovanie)\n";
			std::cin >> zaver;
			if (zaver != "ine") {
				break;
			}
		}
		else if (this->uroven == "3") {
			this->uroven3(this->nacitavac.getTabulku("0"), this->nacitavac.getTabulku("1"), this->nacitavac.getTabulku("2"));
			std::cout << "Koncime program alebo skusime ine urovne? (napis 'ine' pre pokracovanie)\n";
			std::cin >> zaver;
			if (zaver != "ine") {
				break;
			}
		}
		else {
			std::cout << ":)";
			break;
		}
	}
	
}
