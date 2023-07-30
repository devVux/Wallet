#include "cardForm.h"

#include <QtWidgets/QLabel>
#include <QtGui/QShortcut>

#include "../../utilities/parser.h"

CardForm::CardForm(QWidget* parent): QFrame(parent) {
	this->setObjectName("CardForm");
	this->loadUI();
}

void CardForm::loadUI() {

	this->setStyleSheet(QssParser::instance().loadStyle("cardForm.qss"));
	
	formLayout->setSpacing(40);

	pSaveButton->setObjectName("SaveButton");
	QObject::connect(pSaveButton, &QPushButton::clicked, this, [this]() {
		emit saveClicked();
	});
	QObject::connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this), &QShortcut::activated, this, [this]() {
		emit saveClicked();
	});
	
	auto hLayout = new QHBoxLayout;
	hLayout->addWidget(pSaveButton);

	vLayout->addLayout(formLayout);
	vLayout->addStretch();
	vLayout->addLayout(hLayout);

}
