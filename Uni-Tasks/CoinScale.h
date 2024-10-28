#pragma once
#include <initializer_list>

class CoinTwoPanScale {
private:
	double genuineCoinWeight = -1;
	double fakeCoinWeight = -1;
	bool found = false;
public:
	CoinTwoPanScale(const std::initializer_list<double>& coinWeights);
	void addCoin(double weight);
	bool isFakeLighter() const;
};
