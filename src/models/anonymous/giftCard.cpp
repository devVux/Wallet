#include "giftCard.h"

GiftCard::GiftCard(const string& title, const string& code, unsigned int value): 
    AnonymousCard(title), mCode(code), mValue(value) {

}

json GiftCard::toJSON() const {
    json j = AnonymousCard::toJSON();
    j["code"] = mCode;
    j["value"] = mValue;
    j["cardType"] = CardType::Gift;
    return j;
}

void fromJSON(const json& j, GiftCard& card) {
    fromJSON(j, static_cast<AnonymousCard&>(card));
    card.mCode = j.value("code", "Code");
    card.mValue = j.value("value", 50);
}

void GiftCard::notifyAll() {
    for (const auto observer : mObservers)
        observer->notify(*this);
}

void GiftCard::setCode(const string& code) {
    if (!code.empty() && mCode != code) {
        mCode = code;
        this->notifyAll();
    }
}

void GiftCard::setValue(unsigned int value) {
    if (mValue != value) {
        mValue = value;
        this->notifyAll();
    }
}
