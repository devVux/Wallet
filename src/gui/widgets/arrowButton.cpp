#include "arrowButton.h"

#include "coloredIcon.h"
#include "../../utilities/parser.h"

ArrowButton::ArrowButton(const ArrowButton::Direction& direction, QWidget* parent): QPushButton(parent) {

	this->setObjectName("ArrowButton");
	this->setFixedSize(QSize(60, 60));
	this->setStyleSheet(QssParser::instance().loadStyle("arrowButton.qss"));

	switch (direction) {
		
		default:
		case Direction::Left:

			this->setIcon(ColoredIcon("leftArrow", Qt::white));
			break;

		case Direction::Right:

			this->setIcon(ColoredIcon("rightArrow", Qt::white));
			break;

	}

}
