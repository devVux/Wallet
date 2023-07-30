#include "anonymousCard.h"

AnonymousCard::AnonymousCard(const string& title): mTitle(title) {
	
}

json AnonymousCard::toJSON() const {
	return json {
		{"title", mTitle},
		{"cardType", CardType::Anonymous}
	};
}

void fromJSON(const json& j, AnonymousCard& card) {
	card.mTitle = j["title"];
}

void AnonymousCard::notifyAll() {
	for (const auto observer : mObservers)
		observer->notify(*this);
}

void AnonymousCard::setTitle(const string& title) { 
	if (!title.empty() && mTitle != title) {
		mTitle = title; 
		this->notifyAll(); 
	}
}
