#include "coloredIcon.h"

#include <QtGui/QPixmap>
#include <QtGui/QPainter>

ColoredIcon::ColoredIcon(const string& path): QIcon(QPixmap((ICONS_PATH + path).data())) {

}

ColoredIcon::ColoredIcon(const string& path, const QColor& c): QIcon(QPixmap((ICONS_PATH + path).data())) {
    this->setColor(c);
}

void ColoredIcon::setColor(const QColor& c) {
    QPixmap pix = this->pixmap(24, 24);
    QPainter painter(&pix);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pix.rect(), c);
    this->addPixmap(pix);
}
