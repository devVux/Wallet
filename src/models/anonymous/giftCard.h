#pragma once

#include "../anonymousCard.h"

class GiftCard: public AnonymousCard {

	public:

		explicit GiftCard(const string& title, const string& code, unsigned int value = 50);

		GiftCard* clone() const override { return new GiftCard(*this); }

		json toJSON() const override;
		friend void fromJSON(const json& j, GiftCard& card);
		
		void accept(CardsVisitorInterface& visitor) override { visitor.visit(*this); };

		void notifyAll() override;

		const CardType type() const { return CardType::Gift; }


	public:

		string code() { return mCode; }
		void setCode(const string& code);

		unsigned int value() { return mValue; }
		void setValue(unsigned int value);

	private:

		string mCode;
		unsigned int mValue;

};
