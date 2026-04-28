#include "htmlEdit.h"
#include "./ui_htmlEdit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HtmlEdit w(nullptr);
    Ui::HtmlEdit ui;
    ui.setupUi(&w);
    w.textEdit = ui.textEdit;
    w.openButton = ui.openButton;
    w.webPage = ui.webPage;
    w.webPage->addWidget(w.webView);
    w.resize(640, 480);
    w.show();
    return a.exec();
}
