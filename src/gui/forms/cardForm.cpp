#include "CardForm.h"

#include <QtWidgets/QLabel>
#include <QtGui/QShortCut>

#include "../../utilities/parser.h"

CardForm::CardForm(QWidget* parent) {
	this->setObjectName("CardForm");
	this->loadUI();
}

void CardForm::loadUI() {

	this->setStyleSheet(QssParser::instance().loadStyle("CardForm.qss"));
	
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