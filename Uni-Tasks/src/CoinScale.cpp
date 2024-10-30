#include <iostream>
#include "CoinScale.h"

CoinTwoPanScale::CoinTwoPanScale(const std::initializer_list<double>& coinWeights) {
	for (double weight : coinWeights) {
		addCoin(weight);
		if (found && genuineCoinWeight != weight) {
			fakeCoinWeight = weight;
			break;
		}
	}
}

void CoinTwoPanScale::addCoin(double weight) {
	if (!found) {
		if (genuineCoinWeight == weight && genuineCoinWeight > -1) {
			found = true;
		}
		else if (fakeCoinWeight == weight && fakeCoinWeight > -1) {
			std::swap(fakeCoinWeight, genuineCoinWeight);
			found = true;
		}
		else if (fakeCoinWeight != weight && fakeCoinWeight > -1) genuineCoinWeight = weight;
		else if (fakeCoinWeight == -1) fakeCoinWeight = weight;
	}
}

bool CoinTwoPanScale::isFakeLighter() const {
	if (!found) throw std::runtime_error("no fake found");
	return genuineCoinWeight > fakeCoinWeight;
}
