#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

class ArrowButton: public QPushButton {
	
	public:

		enum Direction { Left, Right };


	public:

		ArrowButton(const ArrowButton::Direction& direction = Direction::Left, QWidget* parent = nullptr);



};
