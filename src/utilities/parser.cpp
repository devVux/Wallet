#include "parser.h"

#include <QtCore/QDebug>

#include <fstream>

QString QssParser::loadStyle(const std::string& name) {

    std::ifstream styleFile(STYLES_PATH + name);
    string style;

    if (styleFile.is_open()) {
        string line;
        string property;

        while (std::getline(styleFile, line)) {

            size_t delimiterPos = line.find("@");
            size_t semicolonPos = line.find(";");

            if (delimiterPos != string::npos) {
                property = line.substr(delimiterPos + 1, semicolonPos - delimiterPos - 1);
                line.replace(delimiterPos, semicolonPos - delimiterPos, mProperties[property]);
            }

            style.append(line);

        }

        styleFile.close();

    }

    else

        qDebug() << QString::fromStdString("%1: file not found").arg(QString::fromStdString(name));

    return QString::fromStdString(style);

}

void fromJSON(const json& json, QssParser& parser) {
    parser.mProperties = json.get<map<string, string>>();
}
