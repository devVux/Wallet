#pragma once

#include <QtCore/QString>

#include <string>
#include <map>

#include "../../dependencies/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;
using std::map;

class QssParser {

    private:

        QssParser() = default;


    public:

        // Returns a single, shared instance of the QssParser class. 
        static QssParser& instance() {
            static QssParser parser;
            return parser;
        }

        QssParser(const QssParser&) = delete;

        QssParser& operator=(QssParser&) = delete;


        // Loads and parses a QSS file.
        QString loadStyle(const string& file);

        // Loads parameters from JSON file.
        friend void fromJSON(const json& json, QssParser& parser);


    private:

        map<string, string> mProperties;

};
