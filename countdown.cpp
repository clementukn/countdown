#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;


int fAdd(const int opr1, const int opr2) { 
	return opr1 + opr2; 
}

int fSub(const int opr1, const int opr2) { 
	return opr1 - opr2; 
}

int fMult(const int opr1, const int opr2) {	
	return opr1 * opr2; 
}

int fDiv(const int opr1, const int opr2) {
	if (opr2 != 0)
		return opr1 / opr2;
	else
		return 0;
}

typedef int (*Operator)(const int, const int);
Operator opr[] = {fAdd, fSub, fMult, fDiv};
char oprSigns[] = {'+', '-', '*', '/'};


string process(vector<int> cards, string sOpr, int nResult) {
	decltype(cards.begin()) itcd1, itcd2;
	for (itcd1 = cards.begin(); itcd1 != cards.end(); ++itcd1) {
		for (itcd2 = itcd1 + 1; itcd2 != cards.end(); ++itcd2) {
			for (int k = 0; k < sizeof(oprSigns); ++k) {
				int newcard = opr[k](*itcd1, *itcd2);
				if (newcard < 0) continue;

				vector<int> newCardSet(cards);
				// removes the 2 current cards and add the new one
				newCardSet.erase(find(newCardSet.begin(), newCardSet.end(), *itcd1));
				newCardSet.erase(find(newCardSet.begin(), newCardSet.end(), *itcd2));
				newCardSet.push_back(newcard);

				stringstream ss;
				ss << sOpr << *itcd1 << " " << oprSigns[k] << " " << *itcd2 << " = " << newcard << "\n";
				if (newcard == nResult) {
					return ss.str();
				}
				else if (newCardSet.size() > 1) {
					string sResult = process(newCardSet, ss.str(), nResult);
					if (sResult.empty())
						continue;
					else
						return sResult;
				}
			}
		}
	}
	return "";
}

int main(int argc, char *argv[]) {
	if (argc <= 2) {
		cout << "usage : program [c1 c2 ...] [result]\n";
		cout << "ex : program 10 15 5 7 3 578";
		return 1;
	}

	vector<int> cards;
	int nCards = argc - 2;

	transform(argv + 1, argv + nCards + 1, inserter(cards, cards.begin()), 
		[] (const char *s) { return atoi(s); });

	int nResult = atoi(argv[nCards + 1]);

	clock_t timerStart = clock();
	string sResult = process(cards, "", nResult);
	clock_t timerEnd = clock();
	double nExecutionTime = static_cast<double>(timerEnd - timerStart) / CLOCKS_PER_SEC;

	cout << sResult << endl;
	
	return 0;
}