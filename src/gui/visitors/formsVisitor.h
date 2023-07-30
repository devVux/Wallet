#pragma once

#include <QtWidgets/QWidget>

#include "../../models/cardsVisitorInterface.h"

#include "../forms/cardForm.h"

class FormsVisitor: public CardsVisitorInterface {

	public:

		void visit(AnonymousCard& card) override;
		void visit(PersonalizedCard& card) override;
		void visit(PaymentCard& card) override;
		void visit(FidelityCard& card) override;
		void visit(GiftCard& card) override;

		CardForm* form() const { return pForm; }

	private:

		CardForm* pForm;

};
