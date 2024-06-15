#include "UzemnyCelok.h"

int UzemnyCelok::getPocetSpoluhlasok()
{
	int result = 0;
	std::string ceskeSpoluhlasky = "BCÈèDÏïFGHJKLMNòPQRØøSŠšTVWXZ";

	for (int i = 0; i < nazov.size(); ++i) {
		char c1 = std::toupper(nazov[i]);
		int index1 = ceskeSpoluhlasky.find(c1);

		if (index1 != std::string::npos) {
			result++;
		}
	}
	return result;
}
