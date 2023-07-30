#pragma once

#include "../personalizedCard.h"

class PaymentCard: public PersonalizedCard {

	public:

		explicit PaymentCard(const string& title, const string& owner, const string& number, const string& cvc, time_t expireDate = std::time(0), const PaymentType& type = PaymentType::Debit);
		
		PaymentCard* clone() const override { return new PaymentCard(*this); }

		json toJSON() const override;
		friend void fromJSON(const json& j, PaymentCard& card);

		void accept(CardsVisitorInterface& visitor) override { visitor.visit(*this); };

		void notifyAll() override;

		CardType type() const { return CardType::Payment; }

	public:

		string number() const { return mNumber; }
		void setNumber(const string& number);

		string cvc() const { return mCvc; }
		void setCvc(const string& cvc);

		PaymentType paymentType() const { return mType; }
		void setPaymentType(const PaymentType& type);

	private:

		string mNumber;
		string mCvc;
		PaymentType mType;

};
