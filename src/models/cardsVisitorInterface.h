#pragma once

class PersonalizedCard;
class AnonymousCard;
class PaymentCard;
class FidelityCard;
class GiftCard;

class CardsVisitorInterface {

	public:

		virtual ~CardsVisitorInterface() = default;

		virtual void visit(PersonalizedCard& card) = 0;
		virtual void visit(AnonymousCard& card) = 0;
		virtual void visit(PaymentCard& card) = 0;
		virtual void visit(FidelityCard& fidelity) = 0;
		virtual void visit(GiftCard& card) = 0;

};
