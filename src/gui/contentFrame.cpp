#include "contentFrame.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>

#include "../utilities/parser.h"
#include "widgets/arrowButton.h"

#include <fstream>
#include "../utilities/cardFactory.h"

ContentFrame::ContentFrame(QWidget* parent): QFrame(parent) {

	this->setObjectName("ContentFrame");
	this->loadUI();

}

void ContentFrame::notify(Wallet& wallet) {

	if (wallet.isEmpty()) {
		pCountLabel->setText("Wallet is empty! Start by adding some cards!");

		float k = 1.3;
		auto emptyCard = new QLabel(this);
		emptyCard->setPixmap(QPixmap((ICONS_PATH + string("emptyCard.png")).data())
			.scaled(300 * k, 100 * k, Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));

		QWidget* old = gridLayout->replaceWidget(pCard, emptyCard)->widget();
		old->deleteLater();

		pCard = emptyCard;

	} else {
		
		pCountLabel->setText(QString("Showing %1 of %2").arg(wallet.index() + 1).arg(wallet.cards().size()));

		CardInterface* card = wallet.selectedCard();
		card->accept(mCardsVisitor);

		this->buildMenu(mCardsVisitor.widget(), card);

		QWidget* old = gridLayout->replaceWidget(pCard, mCardsVisitor.widget())->widget();
		old->deleteLater();

		pCard = mCardsVisitor.widget();

	}

}

void ContentFrame::loadUI() {

	auto prevButton = new ArrowButton(ArrowButton::Left, this);
	auto nextButton = new ArrowButton(ArrowButton::Right, this);

	QObject::connect(prevButton, &QPushButton::clicked, this, [this]() {
		emit prevClicked();
	});
	QObject::connect(nextButton, &QPushButton::clicked, this, [this]() {
		emit nextClicked();
	});


	pCountLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	pCountLabel->setStyleSheet("color: black;");

	auto delButton = new QPushButton("Delete");
	delButton->setObjectName("DeleteButton");
	delButton->setFixedSize(90, 50);
	QObject::connect(delButton, &QPushButton::clicked, this, [this]() {
		emit deleteClicked();
	});

	auto addButton = new QPushButton("Add");
	addButton->setObjectName("AddButton");
	addButton->setFixedSize(90, 50);
	QObject::connect(addButton, &QPushButton::clicked, this, [this]() {
		emit addClicked();
	});


	auto wrap = new QWidget();
	auto wrapLayout = new QHBoxLayout(wrap);
	wrapLayout->addWidget(delButton);
	wrapLayout->addWidget(addButton);

	gridLayout->addWidget(prevButton,	1, 0, 2, 1, Qt::AlignLeft);
	gridLayout->addWidget(nextButton,	1, 2, 2, 1, Qt::AlignRight);
	gridLayout->addWidget(pCard,		1, 1, 2, 1, Qt::AlignCenter);
	gridLayout->addWidget(wrap,			2, 1, 1, 1, Qt::AlignHCenter | Qt::AlignBottom);

	vLayout->setSpacing(0);
	vLayout->addWidget(pCountLabel);
	vLayout->addLayout(gridLayout);

}

void ContentFrame::buildMenu(QWidget* widget, CardInterface* card) {

	auto menu = new QMenu(widget);
	
	auto promoteMenu = new QMenu("Promote to");

	auto anonymousAction = new QAction("Anonymous Card");
	QObject::connect(anonymousAction, &QAction::triggered, widget, [this, card, widget]() {
		if (card->type() != CardType::Anonymous)
			emit promoteTo(card, CardFactory::promoteTo(card, CardType::Anonymous));
	});
	
	auto personalizedAction = new QAction("Personalized Card");
	QObject::connect(personalizedAction, &QAction::triggered, widget, [this, card, widget]() {
		if (card->type() != CardType::Personalized)
			emit promoteTo(card, CardFactory::promoteTo(card, CardType::Personalized));
	});
	
	auto paymentAction = new QAction("Payment Card");
	QObject::connect(paymentAction, &QAction::triggered, widget, [this, card, widget]() {
		if (card->type() != CardType::Payment)
			emit promoteTo(card, CardFactory::promoteTo(card, CardType::Payment));
	});
	
	auto fideltyAction = new QAction("Fidelty Card");
	QObject::connect(fideltyAction, &QAction::triggered, widget, [this, card, widget]() {
		if (card->type() != CardType::Fidelity)
			emit promoteTo(card, CardFactory::promoteTo(card, CardType::Fidelity));
	});

	auto giftAction = new QAction("Gift Card");
	QObject::connect(giftAction, &QAction::triggered, widget, [this, card, widget]() {
		if (card->type() != CardType::Gift)
			emit promoteTo(card, CardFactory::promoteTo(card, CardType::Gift));
	});

	promoteMenu->addAction(giftAction);
	promoteMenu->addAction(anonymousAction);
	promoteMenu->addAction(personalizedAction);
	promoteMenu->addAction(paymentAction);
	promoteMenu->addAction(fideltyAction);
	promoteMenu->addAction(giftAction);

	menu->addMenu(promoteMenu);
	QObject::connect(widget, &QPushButton::customContextMenuRequested, [this, menu, widget](const QPoint& p) {
		menu->exec(widget->mapToGlobal(p));
	});

}
