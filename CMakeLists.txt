cmake_minimum_required(VERSION 3.1.3)

project("Carte")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(HEADERS

    "src/utilities/parser.h"

    "src/utilities/cardFactory.h"
    "src/utilities/observer.h"
    "src/utilities/memento.h"

    "src/models/abstractCard.h"
    "src/models/personalizedCard.h"
    "src/models/anonymousCard.h"
    "src/models/personalized/paymentCard.h"
    "src/models/personalized/fidelityCard.h"
    "src/models/anonymous/giftCard.h"
    "src/models/wallet.h"
    
    "src/models/visitorInterface.h"
    "src/gui/visitors/cardsVisitor.h"
    "src/gui/visitors/formsVisitor.h"

    "src/gui/widgets/coloredIcon.h"
    "src/gui/widgets/arrowButton.h"

    "src/gui/mainFrame.h"
    "src/gui/contentFrame.h"
    "src/gui/forms/cardForm.h"

)


set(SOURCES
    "main.cpp"

    "src/utilities/parser.cpp"

    "src/models/personalizedCard.cpp"
    "src/models/anonymousCard.cpp"
    "src/models/personalized/paymentCard.cpp"
    "src/models/personalized/fidelityCard.cpp"
    "src/models/anonymous/giftCard.cpp"
    "src/models/wallet.cpp"
    
    "src/gui/visitors/cardsVisitor.cpp"
    "src/gui/visitors/formsVisitor.cpp"

    "src/gui/widgets/coloredIcon.cpp"
    "src/gui/widgets/arrowButton.cpp"

    "src/gui/mainFrame.cpp"
    "src/gui/contentFrame.cpp"
    "src/gui/forms/cardForm.cpp"

)

qt6_wrap_cpp(MOC_FILES
    
    "src/gui/mainFrame.h"

)

add_library("dependencies")

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES} ${MOC_FILES} )

target_link_libraries(${CMAKE_PROJECT_NAME} Qt6::Core Qt6::Widgets)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE PROJECT_PATH="${CMAKE_SOURCE_DIR}/"
                                                         ICONS_PATH="${CMAKE_SOURCE_DIR}/assets/icons/"
                                                         STYLES_PATH="${CMAKE_SOURCE_DIR}/assets/styles/"
                                                         DATA_PATH="${CMAKE_SOURCE_DIR}/data/"
)

