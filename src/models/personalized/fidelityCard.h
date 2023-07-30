#pragma once

#include "../personalizedCard.h"

class FidelityCard: public PersonalizedCard {

	public:

		explicit FidelityCard(const string& title, const string& owner, const string& company, const string& code, time_t expireDate = std::time(0));
		
		FidelityCard* clone() const override { return new FidelityCard(*this); }

		json toJSON() const override;
		friend void fromJSON(const json& j, FidelityCard& card);

		void accept(CardsVisitorInterface& visitor) override { visitor.visit(*this); }

		void notifyAll() override;

		const CardType type() const { return CardType::Fidelity; }


	public:

		string company() const { return mCompany; }
		void setCompany(const string& company);

		string code() const { return mCode; }
		void setCode(const string& code);

	private:

		string mCompany;
		string mCode;

};