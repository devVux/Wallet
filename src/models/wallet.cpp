#include "wallet.h"

#include <fstream>
#include <QtCore/QDebug>
#include "../utilities/cardFactory.h"

Wallet::Wallet(): mSelectedIndex(0) {

}

Wallet::Wallet(const Wallet &other): ObservedBy(other), mCards(other.mCards) {

	for (size_t i = 0; i < other.mCards.size(); i++)	
		mCards[i] = other.mCards[i]->clone();

}

Wallet::~Wallet() {

    while (!mCards.empty()) {
		delete mCards.back();
		mCards.pop_back();
	}
}

json Wallet::toJSON() const {
    json j = json::array();

	for (const auto& card : mCards)
		j.push_back(card->toJSON());

	return j;
}

void fromJSON(const json& j, Wallet& wallet) {
	
	for (size_t i = 0; i < j.size(); i++) {
		CardInterface* card = CardFactory::createCard(j[i], static_cast<CardType>(j[i]["cardType"]));
		card->registerObserver(&wallet);
		wallet.mCards.push_back(card);
	}

}

void Wallet::notify(CardInterface&) {
	this->notifyAll();
}

void Wallet::notifyAll() {
	for (const auto observer : mObservers)
		observer->notify(*this);
}

void Wallet::addCard(CardInterface* card) {
	const auto iterator = std::find(mCards.begin(), mCards.end(), card);
	if (iterator == mCards.end()) {
		card->registerObserver(this);
		mCards.push_back(card);
		this->notifyAll();
	}
}

void Wallet::insertCard(int pos, CardInterface* card) {
	card->registerObserver(this);
	mCards.insert(mCards.begin() + pos, card);
	this->notifyAll();
}

void Wallet::removeCard(CardInterface* card) {
	if (isEmpty()) return;
	const auto iterator = std::find(mCards.begin(), mCards.end(), card);
	if (iterator != mCards.end()) {
		mCards.erase(iterator);
		this->prevCard();
	}
}

void Wallet::removeCardAt(int i) {
	if (isEmpty() || i < 0 || i >= mCards.size()) return;
	mCards.erase(mCards.begin() + i);
	this->prevCard();
}

void Wallet::promoteTo(CardInterface* card) {
	delete mCards[mSelectedIndex];
	card->registerObserver(this);
	mCards[mSelectedIndex] = card;
	this->notifyAll();
}

Wallet& Wallet::nextCard() {
	mSelectedIndex = std::min(static_cast<int>(mCards.size() - 1), mSelectedIndex + 1);
	this->notifyAll();
	return *this;
}

Wallet& Wallet::prevCard() {
	mSelectedIndex = std::max(0, mSelectedIndex - 1);
	this->notifyAll();
	return *this;
}
