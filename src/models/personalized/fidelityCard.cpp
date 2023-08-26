#include "fidelityCard.h"

FidelityCard::FidelityCard(const string& title, const string& owner, const string& company, const string& code, time_t expireDate):
	PersonalizedCard(title, owner, expireDate), mCompany(company), mCode(code) {
	
}

json FidelityCard::toJSON() const {
	json j = PersonalizedCard::toJSON();
	j["company"] = mCompany;
	j["code"] = mCode;
	j["cardType"] = CardType::Fidelity;
	return j;
}

void fromJSON(const json& j, FidelityCard& card) {
	fromJSON(j, static_cast<PersonalizedCard&>(card));
	card.mCode = j.value("code", "Code");
	card.mCompany = j.value("company", "Company");
}

void FidelityCard::notifyAll() {
	for (const auto observer : mObservers)
		observer->notify(*this);
}

void FidelityCard::setCompany(const string& company) {
	if (!company.empty() && mCompany != company) {
		mCompany = company;
		this->notifyAll();
	}
}

void FidelityCard::setCode(const string& code) {
	if (!code.empty() && mCode != code) {
		mCode = code;
		this->notifyAll();
	}
}
