QT += core gui widgets

CONFIG += c++11

HEADERS += \
    src/utilities/parser.h \
    src/utilities/cardFactory.h \
    src/utilities/observer.h \
    src/models/cardInterface.h \
    src/models/anonymousCard.h \
    src/models/personalizedCard.h \
    src/models/personalized/paymentCard.h \
    src/models/personalized/fidelityCard.h \
    src/models/anonymous/giftCard.h \
    src/models/wallet.h \
    src/models/cardsVisitorInterface.h \
    src/gui/visitors/cardsVisitor.h \
    src/gui/visitors/formsVisitor.h \
    src/gui/widgets/coloredIcon.h \
    src/gui/widgets/arrowButton.h \
    src/gui/mainFrame.h \
    src/gui/contentFrame.h \
    src/gui/forms/cardForm.h

SOURCES += \
    main.cpp \
    src/utilities/parser.cpp \
    src/models/personalizedCard.cpp \
    src/models/anonymousCard.cpp \
    src/models/personalized/paymentCard.cpp \
    src/models/personalized/fidelityCard.cpp \
    src/models/anonymous/giftCard.cpp \
    src/models/wallet.cpp \
    src/gui/visitors/cardsVisitor.cpp \
    src/gui/visitors/formsVisitor.cpp \
    src/gui/widgets/coloredIcon.cpp \
    src/gui/widgets/arrowButton.cpp \
    src/gui/mainFrame.cpp \
    src/gui/contentFrame.cpp \
    src/gui/forms/cardForm.cpp

ù
DEFINES += PROJECT_PATH=\\\"$$PWD/\\\" \
           ICONS_PATH=\\\"$$PWD/assets/icons/\\\" \
           STYLES_PATH=\\\"$$PWD/assets/styles/\\\" \
           DATA_PATH=\\\"$$PWD/data/\\\"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
