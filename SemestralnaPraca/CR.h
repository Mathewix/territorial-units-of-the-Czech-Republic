#pragma once
#include "UzemnyCelok.h"
class CR :
    public UzemnyCelok
{

public:
	CR() : UzemnyCelok("stat", "�esk� Republika") {
		nazov = "�esk� Republika";
		kod = "x";
	}
	~CR() override {}
	void vypis() override {
		std::cout << nazov + " " << kod + "\n";
	}
};


