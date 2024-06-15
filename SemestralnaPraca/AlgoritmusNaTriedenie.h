#pragma once
#include "UzemnyCelok.h"
#include <vector>
#include <functional>

//otypovanie lambdovej funkcie lebo je to fujble a tak som si to nazval jednoduchsie :) Alias
template<typename L>
using TriediacaLambda = std::function<bool(std::string, L)>;

class AlgoritmusNaTriedenie
{
public:
	template<typename T, typename I>
	std::vector<T> algoritmus(std::string str, I begin, I end, TriediacaLambda<T> lambda) {
		std::vector<T> filtered;
		I it = begin;
		while (it != end) {
			if (lambda(str, *it)) {
				filtered.push_back(*it);
			}
			++it;
			
		}
		return filtered;
	}

};


