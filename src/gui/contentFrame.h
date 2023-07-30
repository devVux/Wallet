#pragma once

#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

#include "../utilities/observer.h"

#include "visitors/cardsVisitor.h"
#include "../models/wallet.h"

class ContentFrame: public QFrame, public Observer<Wallet> {

	Q_OBJECT

	public:

		explicit ContentFrame(QWidget* parent = nullptr);

		void notify(Wallet& wallet) override;


	signals:

		void prevClicked();
		void nextClicked();
		void addClicked();
		void deleteClicked();
		void promoteTo(CardInterface* from, CardInterface* to);


	private:

		void loadUI();

		void buildMenu(QWidget* widget, CardInterface* card);

		
	private:

		QVBoxLayout* vLayout { new QVBoxLayout(this) };
		QGridLayout* gridLayout { new QGridLayout };

		QLabel* pCountLabel { new QLabel(this) };
		QWidget* pCard { new QWidget(this) };

		CardsVisitor mCardsVisitor;
};
