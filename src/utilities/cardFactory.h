#pragma once

#include <functional>
#include <unordered_map>
#include <memory>
#include <ctime>

#include "utils.h"

#include "../models/anonymousCard.h"
#include "../models/personalizedCard.h"
#include "../models/anonymous/giftCard.h"
#include "../models/personalized/paymentCard.h"
#include "../models/personalized/fidelityCard.h"

using std::function;
using std::unordered_map;

class CardFactory {

    public:

        static CardInterface* createCard(const json& j, const CardType& cardType) {

			AnonymousCard* card;

			switch (cardType) {

				default:
				case CardType::Anonymous:
					card = new AnonymousCard("Title");
					fromJSON(j, *card);
					break;

				case CardType::Personalized:
					card = new PersonalizedCard("Title", "Owner");
					fromJSON(j, static_cast<PersonalizedCard&>(*card));
					break;

				case CardType::Gift:
					card = new GiftCard("Title", "Code");
					fromJSON(j, static_cast<GiftCard&>(*card));
					break;

				case CardType::Payment:
					card = new PaymentCard("Title", "Owner", "Number", "000");
					fromJSON(j, static_cast<PaymentCard&>(*card));
					break;

				case CardType::Fidelity:
					card = new FidelityCard("Title", "Owner", "Company", "Code");
					fromJSON(j, static_cast<FidelityCard&>(*card));
					break;

			}

			return card;

        }

		static CardInterface* promoteTo(const CardInterface* /*from*/, const CardType& to) {
			return createCard(from->toJSON(), to);
		}

};

