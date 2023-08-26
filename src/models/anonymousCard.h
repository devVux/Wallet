#pragma once

#include <string>

#include "cardInterface.h"
#include "../utilities/utils.h"

using std::string;

class AnonymousCard: public CardInterface {

	public:

		AnonymousCard(const string& title);
		
		AnonymousCard* clone() const override { return new AnonymousCard(*this); }

		json toJSON() const override;
		friend void fromJSON(const json& j, AnonymousCard& card);

		bool isValid() const override { return true; }

		void accept(CardsVisitorInterface& visitor) override { visitor.visit(*this); }

		void notifyAll() override;

		CardType type() const { return CardType::Anonymous; }


	public:

		string title() const { return mTitle; }
		void setTitle(const string& title);
		

	private:
		
		string mTitle;

};


