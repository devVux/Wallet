#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>

#include "../../models/cardsVisitorInterface.h"

class CardsVisitor: public CardsVisitorInterface {

	public:

		void visit(AnonymousCard& card) override;
		void visit(PersonalizedCard& card) override;
		void visit(PaymentCard& card) override;
		void visit(FidelityCard& fidelity) override;
		void visit(GiftCard& fidelity) override;

		QWidget* widget() const { return pWidget; }

	private:

		QWidget* singleWrap(QWidget* w, QWidget* parent = nullptr);
		QWidget* doubleWrap(const Qt::Orientation& orientation, QWidget* w1, QWidget* w2, QWidget* parent = nullptr);


	private:

		QWidget* pWidget { nullptr };

};
