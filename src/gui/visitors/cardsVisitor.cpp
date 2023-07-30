#include "cardsVisitor.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QListWidget>

#include "../widgets/coloredIcon.h"

#include "../../utilities/parser.h"
		  
#include "../forms/cardForm.h"
		  
#include "../../models/anonymousCard.h"
#include "../../models/personalizedCard.h"
#include "../../models/anonymous/giftCard.h"
#include "../../models/personalized/paymentCard.h"
#include "../../models/personalized/fidelityCard.h"

static const float k = 1.3;

void CardsVisitor::visit(AnonymousCard& card) {
	pWidget = new QWidget();
	pWidget->setObjectName("Anonymous");
	pWidget->setMinimumSize(300 * k, 160 * k);
	pWidget->setStyleSheet(QssParser::instance().loadStyle("card.qss"));
	pWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	auto gridLayout = new QGridLayout(pWidget);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(k * 15, k * 15, k * 15, k * 15);

	auto titleLabel = new QLabel(QString::fromStdString(card.title()).toUpper(), pWidget);
	titleLabel->setObjectName("TitleLabel");
	gridLayout->addWidget(titleLabel, 0, 0, Qt::AlignTop);

}

void CardsVisitor::visit(PersonalizedCard& card) {
	CardsVisitor::visit(static_cast<AnonymousCard&>(card));
	pWidget->setObjectName("Personalized");

	auto gridLayout = static_cast<QGridLayout*>(pWidget->layout());
	
	auto expireLabel = new QLabel(QString("%1/%2").arg(card.expireDate().tm_mon + 1).arg(card.expireDate().tm_year % 100));
	expireLabel->setObjectName("ExpireLabel");

	auto ownerLabel = new QLabel(QString::fromStdString(card.owner()).toUpper());
	ownerLabel->setObjectName("OwnerLabel");

	gridLayout->addWidget(this->doubleWrap(Qt::Vertical, expireLabel, ownerLabel, pWidget), 2, 0);

}

void CardsVisitor::visit(PaymentCard& card) {

	pWidget = new QWidget;
	pWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	auto vLayout = new QVBoxLayout(pWidget);
	vLayout->setSpacing(20);

	// front card
	auto front = new QWidget(pWidget);
	qDebug() << static_cast<int>(card.paymentType());
	front->setObjectName(QString::fromStdString(PaymentTypeMap.at(card.paymentType())));
	front->setStyleSheet(QssParser::instance().loadStyle("card.qss"));
	front->setMinimumSize(300 * k, 160 * k);
	
	auto gridLayout = new QGridLayout(front);
	gridLayout->setContentsMargins(k * 15, k * 15, k * 15, k * 15);
	gridLayout->setSpacing(0);



	auto titleLabel = new QLabel(QString::fromStdString(card.title()).toUpper(), front);
	titleLabel->setObjectName("TitleLabel");

	auto circuitLabel = new QLabel(front);
	circuitLabel->setFixedSize(QSize(k * 40, k * 30));
	circuitLabel->setStyleSheet("background-color: #E0DDCF; border-radius:4px;");

	auto contactlessLabel = new QLabel(front);
	contactlessLabel->setFixedSize(QSize(k * 40, k * 40));
	contactlessLabel->setPixmap(ColoredIcon("contactless.png", Qt::white).pixmap(QSize(k * 40, k * 40)));

	QPixmap contactlessIcon = ColoredIcon("contactless.png", Qt::white).pixmap(QSize(k * 60, k * 40));
	contactlessIcon = contactlessIcon.scaled(QSize(k * 24, k * 24), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	contactlessLabel->setPixmap(contactlessIcon);


	auto typeLabel = new QLabel(front);
	typeLabel->setText(QString::fromStdString(PaymentTypeMap.at(card.paymentType())));

	auto ownerLabel = new QLabel(QString::fromStdString(card.owner()).toUpper());
	ownerLabel->setObjectName("OwnerLabel");


	gridLayout->addWidget(titleLabel, 0, 0, Qt::AlignTop);
	gridLayout->addWidget(this->doubleWrap(Qt::Horizontal, circuitLabel, contactlessLabel, front), 1, 0, Qt::AlignLeading);
	gridLayout->addWidget(this->doubleWrap(Qt::Vertical, typeLabel, ownerLabel, front), 2, 0, Qt::AlignBottom);





	// back card
	auto back = new QWidget(pWidget);
	back->setObjectName(QString::fromStdString(PaymentTypeMap.at(card.paymentType())));
	back->setStyleSheet(QssParser::instance().loadStyle("card.qss"));
	back->setMinimumSize(300 * k, 160 * k);

	auto gridLayout2 = new QGridLayout(back);
	gridLayout2->setContentsMargins(k * 15, k * 15, k * 15, k * 15);
	gridLayout2->setSpacing(0);


	auto titleLabel2 = new QLabel(QString::fromStdString(card.title()).toUpper(), front);
	titleLabel2->setObjectName("TitleLabel");

	// We display the card number divided in groups of 4 characters separated by space
	auto numberLabel = new QLabel(QString::fromStdString(card.number()).replace(QRegularExpression("(\\d{4})"), "\\1 "), back);
	numberLabel->setObjectName("NumberLabel");
	numberLabel->setAlignment(Qt::AlignCenter);
	numberLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	

	auto validThruLabel = new QLabel("Valid thru", back);
	auto expireLabel = new QLabel(back);
	expireLabel->setObjectName("ExpireLabel");
	expireLabel->setText(QString("%1/%2").arg(card.expireDate().tm_mon + 1).arg(card.expireDate().tm_year% 100));

	auto cvcLabel = new QLabel("CVC", back);
	cvcLabel->setAlignment(Qt::AlignRight);
	auto cvc = new QLabel(QString::fromStdString(card.cvc()), back);
	cvc->setObjectName("CvcLabel");
	cvc->setAlignment(Qt::AlignRight);


	gridLayout2->addWidget(titleLabel2, 0, 0);
	gridLayout2->addWidget(this->singleWrap(numberLabel), 1, 0);
	gridLayout2->addWidget(this->doubleWrap(Qt::Orientation::Vertical, validThruLabel, expireLabel, back), 2, 0, Qt::AlignLeading);
	gridLayout2->addWidget(this->doubleWrap(Qt::Orientation::Vertical, cvcLabel, cvc, back), 2, 0, Qt::AlignTrailing);


	vLayout->addWidget(front);
	vLayout->addWidget(back);

}

void CardsVisitor::visit(FidelityCard& card) {
	CardsVisitor::visit(static_cast<PersonalizedCard&>(card));
	pWidget->setObjectName("Fidelity");

	auto gridLayout = static_cast<QGridLayout*>(pWidget->layout());

	auto codeLabel = new QLabel(QString::fromStdString(card.code()), pWidget);
	codeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	codeLabel->setObjectName("NumberLabel");
	codeLabel->setAlignment(Qt::AlignCenter);
	
	auto companyLabel = new QLabel(QString::fromStdString(card.company()), pWidget);
	companyLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	companyLabel->setAlignment(Qt::AlignRight);

	gridLayout->addWidget(this->singleWrap(codeLabel, pWidget), 1, 0);
	gridLayout->addWidget(companyLabel, 2, 0, Qt::AlignTrailing);
	
}

void CardsVisitor::visit(GiftCard& card) {
	CardsVisitor::visit(static_cast<AnonymousCard&>(card));
	pWidget->setObjectName("Gift");

	auto gridLayout = static_cast<QGridLayout*>(pWidget->layout());

	auto codeLabel = new QLabel(QString::fromStdString(card.code()), pWidget);
	codeLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	codeLabel->setObjectName("NumberLabel");
	codeLabel->setAlignment(Qt::AlignCenter);

	auto valueLabel = new QLabel(pWidget);
	valueLabel->setText(QString::number(card.value()));
	valueLabel->setStyleSheet("font-size: 24px;");

	gridLayout->addWidget(this->singleWrap(codeLabel, pWidget), 1, 0);
	gridLayout->addWidget(valueLabel, 2, 0, Qt::AlignRight);

}

QWidget* CardsVisitor::singleWrap(QWidget* w, QWidget* parent) {
	
	auto wrap = new QWidget(parent);
	wrap->setContentsMargins(0, 0, 0, 0);
	wrap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	auto layout = new QVBoxLayout(wrap);
	layout->setSpacing(2);
	layout->setContentsMargins(0, 0, 0, 0);

	layout->addWidget(w);

	return wrap;

}

QWidget* CardsVisitor::doubleWrap(const Qt::Orientation& orientation, QWidget* w1, QWidget* w2, QWidget* parent) {
	
	auto wrap = new QWidget(parent);
	wrap->setContentsMargins(0, 0, 0, 0);
	wrap->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QLayout* layout;

	if (orientation == Qt::Orientation::Vertical)
		layout = new QVBoxLayout(wrap);
	else 
		layout = new QHBoxLayout(wrap);

	layout->setSpacing(2);
	layout->setContentsMargins(0, 0, 0, 0);

	layout->addWidget(w1);
	layout->addWidget(w2);

	return wrap;

}
