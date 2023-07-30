#pragma once

#include <vector>

#include "../../dependencies/json/single_include/nlohmann/json.hpp"

#include "../utilities/observer.h"

#include "cardInterface.h"

using std::vector;
using nlohmann::json;

class Wallet: public ObservedBy<Observer<Wallet>>, public Observer<CardInterface> {

	public:

		Wallet();
		Wallet(const Wallet& other);
		~Wallet();

		json toJSON() const;
		friend void fromJSON(const json& j, Wallet&);

		void notify(CardInterface& card);
		void notifyAll();

		void addCard(CardInterface* card);
		void insertCard(int pos, CardInterface* card);
		void removeCard(CardInterface* card);
		void removeCardAt(int index);
		void promoteTo(CardInterface* card);

		Wallet& nextCard();
		Wallet& prevCard();


	public:

		bool isEmpty() const { return mCards.empty(); }

		void setIndex(int index) { mSelectedIndex = index; this->notifyAll(); }
		int index() const { return mSelectedIndex; }

		vector<CardInterface*>& cards() { return mCards; }
		CardInterface* selectedCard() const { return mCards[mSelectedIndex]; }


	private:

		vector<CardInterface*> mCards;

		int mSelectedIndex;

};
