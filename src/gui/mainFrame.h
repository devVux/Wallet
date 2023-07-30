#pragma once

#include <QtWidgets/QSplitter>

#include "visitors/formsVisitor.h"
#include "visitors/cardsVisitor.h"

#include "contentFrame.h"

#include "../models/cardInterface.h"
#include "../models/wallet.h"

class MainFrame: public QFrame, public Observer<Wallet> {

	Q_OBJECT

	public:

		explicit MainFrame(QWidget* parent = nullptr);

		void notify(Wallet& wallet);

		void saveWallet();


	private:

		void loadUI();

		void loadWallet();

		QWidget* buildInstructionLabel() const;


	private:

		ContentFrame* pContentFrame { new ContentFrame(this) };

		QSplitter* pSplitter { new QSplitter(this) };

		FormsVisitor mFormsVisitor;
		CardsVisitor mCardsVisitor;

		Wallet mWallet;

};

