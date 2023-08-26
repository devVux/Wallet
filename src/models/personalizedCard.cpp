#include "personalizedCard.h"

PersonalizedCard::PersonalizedCard( const string& title, const string& owner,time_t expireDate): 
	AnonymousCard(title), mOwner(owner), mExpireDate(expireDate) {

}

json PersonalizedCard::toJSON() const {
	json j = AnonymousCard::toJSON();
	j["owner"] = mOwner;
	j["expireDate"] = mExpireDate;
	j["cardType"] = CardType::Personalized;
	return j;
}

void fromJSON(const json& j, PersonalizedCard& card) {
	fromJSON(j, static_cast<AnonymousCard&>(card));
	card.mOwner = j.value("owner", "Owner");
	card.mExpireDate = j.value("expireDate", std::time(0));
}

bool PersonalizedCard::isValid() const {
	auto t = std::time(nullptr);
	auto todayDate = *std::localtime(&t);
	auto expDate = this->expireDate();
	return todayDate.tm_year <= expDate.tm_year && 
			todayDate.tm_mon <= expDate.tm_mon && 
			todayDate.tm_mday <= expDate.tm_mday;
}

void PersonalizedCard::notifyAll() {
	for (const auto observer : mObservers)
		observer->notify(*this);
}

void PersonalizedCard::setOwner(const string& owner) {
	if (!owner.empty() && mOwner != owner) {
		mOwner = owner;
		this->notifyAll();
	}
}

void PersonalizedCard::setExpireDate(time_t expireDate) {
	if (mExpireDate != expireDate) {
		mExpireDate = expireDate;
		this->notifyAll();
	}
}