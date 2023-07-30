#pragma once

#include "../../dependencies/json/single_include/nlohmann/json.hpp"

#include "../utilities/utils.h"
#include "../utilities/observer.h"

#include "cardsVisitorInterface.h"

using nlohmann::json;

// AnonymousCard is observed by all the classes which observe AnonymousCard
class CardInterface: public ObservedBy<Observer<CardInterface>> {

	public:

		virtual ~CardInterface() = default;

		virtual CardInterface* clone() const = 0;

		virtual json toJSON() const = 0;

		virtual bool isValid() const = 0;

		virtual void accept(CardsVisitorInterface& visitor) = 0;

		virtual CardType type() const = 0;

};
