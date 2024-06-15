#pragma once
#include <libds/adt/sorts.h>
#include <libds/amt/implicit_sequence.h>
#include "UzemnyCelok.h"

template<typename L>
using SortovaciaLambda = std::function<bool(L, L)>;

using namespace ds::adt;
using namespace ds::amt;
class Sortovac
{
public:
	template<typename T>
	ImplicitSequence<T>* algoritmus(std::vector<UzemnyCelok*> vektor, SortovaciaLambda<T> lambda) {
		ImplicitSequence<T>* is = new ImplicitSequence<T>();
		for (T celok : vektor) {
			is->insertLast().data_ = celok;
		}
		
		QuickSort<T> sorter = QuickSort<T>();
		
		sorter.sort(*is, lambda);
		auto start = is->begin();
		while (start != is->end()) {
			auto nazov = (*start)->getNazov();
			++start;
		}
		return is;
	}
	
};

