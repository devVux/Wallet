
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMessageBox>

#include <iostream>
#include <fstream>

#include "src/gui/mainFrame.h"
#include "src/utilities/parser.h"

void loadStyleSheetProperties() {
    std::ifstream file(STYLES_PATH + string("properties.json"), std::ifstream::in);

    try {

        json j = json::parse(file);
        fromJSON(j, QssParser::instance());

    } catch (const json::parse_error&) {
        QMessageBox msgBox;
        msgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        msgBox.setText("Unable to read style properties file");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    file.close();
}

int main(int argc, char* argv[]) {

    loadStyleSheetProperties();
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QString::fromStdString(ICONS_PATH + string("wallet.png"))));

    QMainWindow q;
    q.setStyleSheet(QssParser::instance().loadStyle("mainWindow.qss"));
    q.resize(WIDTH, HEIGHT);

    q.setCentralWidget(new MainFrame);
    q.show();

    return app.exec();

}

