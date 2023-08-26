#pragma once

#include <iomanip>
#include <string>
#include <ctime>

#include "anonymousCard.h"

class PersonalizedCard: public AnonymousCard {

	public:

		explicit PersonalizedCard(const string& title, const string& owner, time_t expireDate = std::time(0));
		
		PersonalizedCard* clone() const override { return new PersonalizedCard(*this); }

		json toJSON() const override;
		friend void fromJSON(const json& j, PersonalizedCard& card);

		bool isValid() const override;
	
		void accept(CardsVisitorInterface& visitor) override { visitor.visit(*this); };

		void notifyAll() override;

		CardType type() const { return CardType::Personalized; }


	public:
		
		string owner() const { return mOwner; }
		void setOwner(const string& owner);

		std::tm& expireDate() const { return *std::localtime(&mExpireDate); }
		void setExpireDate(time_t expireDate);
		

	private:

		string mOwner;
		time_t mExpireDate;

};
