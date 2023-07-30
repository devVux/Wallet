#pragma once

#include <QtGui/QIcon>
#include <QtGui/QColor>

#include <string>

using std::string;

class ColoredIcon : public QIcon {

    public:

    // Constructs a ColoredIcon object with the specified path
    ColoredIcon(const string& path);

    // Constructs a ColoredIcon object with the specified name and color
    ColoredIcon(const string& path, const QColor& color);


    void setColor(const QColor& color);

};
