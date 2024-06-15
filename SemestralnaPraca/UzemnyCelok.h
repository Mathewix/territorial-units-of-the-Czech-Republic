#pragma once
#include <string>
#include <iostream>
class UzemnyCelok
{
protected:
	std::string nazov = "";
	std::string kod = "";
	std::string type = "";
public:
	UzemnyCelok(std::string pType, std::string pNazov) : type(pType), nazov(pNazov) {}
	virtual ~UzemnyCelok() {};
	virtual std::string getNazov()
	{
		return nazov;
	}
	virtual std::string getKod() {
		return kod;
	}
	virtual int getPoradie() { return 0; };
	virtual void vypis() = 0;
	std::string getType() {
		return type;
	};
	int getPocetSpoluhlasok();
};

