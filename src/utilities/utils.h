#pragma once

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

static const float WIDTH = 1280.0;
static const float HEIGHT = 720.0;



enum class PaymentType {
	Credit,
	Debit,
	Prepaid,
};

static const unordered_map<PaymentType, string> PaymentTypeMap = {
	{PaymentType::Credit, "Credit"},
	{PaymentType::Debit, "Debit"},
	{PaymentType::Prepaid, "Prepaid"}
};


enum class CardType {
	Anonymous,
	Personalized,
	Payment,
	Fidelity,
	Gift
};

