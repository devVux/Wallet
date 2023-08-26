#include "mainFrame.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QShortcut>

#include <fstream>

#include "visitors/cardsVisitor.h"
#include "../gui/forms/cardForm.h"

#include "../utilities/parser.h"

#include "../models/personalized/paymentCard.h"
#include "../models/anonymous/giftCard.h"

MainFrame::MainFrame(QWidget* parent): QFrame(parent) {
	
	mWallet.registerObserver(pContentFrame);
	mWallet.registerObserver(this);
	this->loadWallet();
	this->setObjectName("MainFrame");
	this->loadUI();

}

void MainFrame::loadUI() {

	this->setStyleSheet(QssParser::instance().loadStyle("mainFrame.qss"));

	QObject::connect(pContentFrame, &ContentFrame::prevClicked, pContentFrame, [this]() {
		mWallet.prevCard();
	});
	QObject::connect(pContentFrame, &ContentFrame::nextClicked, pContentFrame, [this]() {
		mWallet.nextCard();
	});	
	QObject::connect(pContentFrame, &ContentFrame::addClicked, pContentFrame, [this]() {
		mWallet.insertCard(mWallet.index(), new AnonymousCard("Title"));
	});
	QObject::connect(pContentFrame, &ContentFrame::deleteClicked, pContentFrame, [this]() {
		mWallet.removeCardAt(mWallet.index());
	});
	QObject::connect(pContentFrame, &ContentFrame::promoteTo, pContentFrame, [this](CardInterface* from, CardInterface* to) {
		if (mWallet.isEmpty()) return;
		mWallet.promoteTo(to);
	});	

	pSplitter->addWidget(pContentFrame);
	pSplitter->addWidget(new CardForm(this));
	
	int contentSize = (2.0 / 3) * WIDTH;
	int formSize = WIDTH - contentSize;
	pSplitter->setSizes(QList<int> { contentSize, formSize });

	auto layout = new QVBoxLayout(this);
	layout->addWidget(pSplitter);

	mWallet.setIndex(0);

}

void MainFrame::saveWallet() {
	std::ofstream file(DATA_PATH + string("save.json"), std::ofstream::out);

	json j = mWallet.toJSON();

	file << j.dump(4);
	file.close();

	mAlreadySaved = true;

}

void MainFrame::loadWallet() {

	std::ifstream file(DATA_PATH + string("save.json"), std::ifstream::in);

	try {

		json j = json::parse(file);

		fromJSON(j, mWallet);

		file.close();

	} catch (const json::parse_error&) {
		QMessageBox msgBox;
		msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
		msgBox.setText("Unable to read save file");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}

	file.close();

}

void MainFrame::notify(Wallet&) {

	if (mWallet.isEmpty()) {

		auto form = new CardForm(this);
		QObject::connect(form, &CardForm::saveClicked, this, [this]() {
			this->saveWallet();
		});

		// We replace the form and delete the empty card form
		QWidget* old = pSplitter->replaceWidget(1, form);
		old->deleteLater();

	} else {

		CardInterface* card = mWallet.selectedCard();
		card->accept(mFormsVisitor);

		CardForm* form = mFormsVisitor.form();
		QObject::connect(form, &CardForm::saveClicked, this, [this]() {
			this->saveWallet();
		});
		
		// We replace the form and delete the first one
		QWidget* old = pSplitter->replaceWidget(1, form);
		old->deleteLater();
	
		form->setVisible(true);
		
	}

	mAlreadySaved = false;

}
