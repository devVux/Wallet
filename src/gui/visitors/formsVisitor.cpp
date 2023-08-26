#include "formsVisitor.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtCore/QDate>
#include <QtGui/QRegularExpressionValidator>

#include "../../models/anonymousCard.h"
#include "../../models/personalizedCard.h"
#include "../../models/anonymous/giftCard.h"
#include "../../models/personalized/paymentCard.h"
#include "../../models/personalized/fidelityCard.h"
#include "../forms/cardForm.h"

void FormsVisitor::visit(AnonymousCard& card) {
	pForm = new CardForm;
	pForm->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

	auto titleLabel = new QLabel("Title", pForm);
	auto titleInput = new QLineEdit(titleLabel);
	titleInput->setText(QString::fromStdString(card.title()));
	QObject::connect(pForm, &CardForm::saveClicked, [&, titleInput]() {
		card.setTitle(titleInput->text().toStdString());
	});

	pForm->addRow(titleLabel, titleInput);

}

void FormsVisitor::visit(PersonalizedCard& card) {
	FormsVisitor::visit(static_cast<AnonymousCard&>(card));

	auto ownerLabel = new QLabel("Owner", pForm);
	auto ownerInput = new QLineEdit(ownerLabel);
	ownerInput->setText(QString::fromStdString(card.owner()));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, ownerInput]() {
		card.setOwner(ownerInput->text().toStdString());
	});

	auto expireDateLabel = new QLabel("Expire date", pForm);
	auto expireDateInput = new QDateEdit(expireDateLabel);
	expireDateInput->setDisplayFormat("MM.yyyy");
	expireDateInput->setDate(QDate(card.expireDate().tm_year + 1900, card.expireDate().tm_mon + 1, card.expireDate().tm_mday));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, expireDateInput]() {
		card.setExpireDate(expireDateInput->dateTime().toSecsSinceEpoch());
	});

	pForm->addRow(ownerLabel, ownerInput);
	pForm->addRow(expireDateLabel, expireDateInput);

}

void FormsVisitor::visit(PaymentCard& card) {
	FormsVisitor::visit(static_cast<PersonalizedCard&>(card));

	auto numberLabel = new QLabel("Number", pForm);
	auto numberInput = new QLineEdit(numberLabel);
	numberInput->setText(QString::fromStdString(card.number()));
	numberInput->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{16}")));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, numberInput]() {
		card.setNumber(numberInput->text().toStdString());
	});
	
	auto cvcLabel = new QLabel("CVC", pForm);
	auto cvcInput = new QLineEdit(cvcLabel);
	cvcInput->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{3}")));
	cvcInput->setText(QString::fromStdString(card.cvc()));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, cvcInput]() {
		card.setCvc(cvcInput->text().toStdString());
	});

	auto typeLabel = new QLabel("Type", pForm);
	auto typeBox = new QComboBox(pForm);

	typeBox->addItem(QString::fromStdString("Credit"));
	typeBox->addItem(QString::fromStdString("Debit"));
	typeBox->addItem(QString::fromStdString("Prepaid"));

	typeBox->setCurrentIndex(static_cast<int>(card.paymentType()));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [this, &card, typeBox]() {
		card.setPaymentType(static_cast<PaymentType>(typeBox->currentIndex()));
	});

	pForm->addRow(numberLabel, numberInput);
	pForm->addRow(cvcLabel, cvcInput);
	pForm->addRow(typeLabel, typeBox);

}

void FormsVisitor::visit(FidelityCard& card) {
	FormsVisitor::visit(static_cast<PersonalizedCard&>(card));

	auto companyLabel = new QLabel("Company", pForm);
	auto companyInput = new QLineEdit(companyLabel);
	companyInput->setText(QString::fromStdString(card.company()));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, companyInput]() {
		card.setCompany(companyInput->text().toStdString());
	});

	auto codeLabel = new QLabel("Code", pForm);
	auto codeInput = new QLineEdit(codeLabel);
	codeInput->setText(QString::fromStdString(card.code()));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, codeInput]() {
		card.setCode(codeInput->text().toStdString());
	});

	pForm->addRow(companyLabel, companyInput);
	pForm->addRow(codeLabel, codeInput);

}

void FormsVisitor::visit(GiftCard& card) {
	FormsVisitor::visit(static_cast<AnonymousCard&>(card));

	auto codeLabel = new QLabel("Code", pForm);
	auto codeInput = new QLineEdit(codeLabel);
	codeInput->setText(QString::fromStdString(card.code()));
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, codeInput]() {
		card.setCode(codeInput->text().toStdString());
	});
	
	auto valueLabel = new QLabel("Value", pForm);
	auto valueInput = new QSpinBox(valueLabel);
	valueInput->setValue(card.value());
	QObject::connect(pForm, &CardForm::saveClicked, pForm, [&card, valueInput]() {
		card.setValue(valueInput->value());
	});

	pForm->addRow(codeLabel, codeInput);
	pForm->addRow(valueLabel, valueInput);

}
