#include "paymentCard.h"

PaymentCard::PaymentCard(const string& owner, const string& title, const string& number, const string& cvc, time_t expireDate, const PaymentType& type):
	PersonalizedCard(owner, title, expireDate), mNumber(number), mCvc(cvc), mType(type) {

}

json PaymentCard::toJSON() const {
	json j = PersonalizedCard::toJSON();
	j["cardType"] = CardType::Payment;
	j["number"] = mNumber;
	j["cvc"] = mCvc;
	j["paymentType"] = mType;
	return j;
}

void fromJSON(const json& j, PaymentCard& card) {
	fromJSON(j, static_cast<PersonalizedCard&>(card));
	card.mNumber = j.value("number", "Number");
	card.mCvc = j.value("cvc", "000");
	card.mType = j.value("paymentType", PaymentType::Debit);
}

void PaymentCard::notifyAll() {
	for (const auto observer : mObservers)
		observer->notify(*this);
}

void PaymentCard::setNumber(const string& number) {
	if (!number.empty() && mNumber != number) {
		mNumber = number;
		this->notifyAll();
	}
}

void PaymentCard::setCvc(const string& cvc) {
	if (!cvc.empty() && mCvc != cvc) {
		mCvc = cvc;
		this->notifyAll();
	}
}

void PaymentCard::setPaymentType(const PaymentType& type) {
	if (mType != type) {
		mType = type;
		this->notifyAll();
	}
}