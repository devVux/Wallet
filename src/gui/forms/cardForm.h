#pragma once

#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QPushButton>

#include "../../models/cardInterface.h"

class CardForm: public QFrame {

	Q_OBJECT

	public:

		CardForm(QWidget* parent = nullptr);

		void addRow(QWidget* label, QWidget* field) { formLayout->addRow(label, field); }

		int rowCount() const { return formLayout->rowCount(); }
		QFormLayout* getFormLayout() const { return formLayout; }


	signals:

		void saveClicked();

	private:

		void loadUI();


	protected:
		
		QVBoxLayout* vLayout { new QVBoxLayout(this) };

		QFormLayout* formLayout { new QFormLayout };

		QPushButton* pSaveButton { new QPushButton("Save", this) };

};
