#include "htmlEdit.h"

void HtmlEdit::openFile()
{
    filePath = QFileDialog::getOpenFileName(nullptr,
                                              "Open html",
                                              ":/",
                                              "html files (*.html)");

    QString fileDir;
    QString fileName;

    for(auto str : qAsConst(filePath))
    {
        if(str == "/")
            fileName = nullptr;
        else
            fileName += str;
    }

    int i = 0;
    for(auto str : qAsConst(filePath))
    {
        ++i;
        fileDir += str;
        if(i == filePath.length() - fileName.length()) break;
    }

    fileName = "edit_" + fileName;
    editFile = fileDir + fileName;

    QString data;
    QFile readfile(filePath);
    if (!readfile.open(QIODevice::ReadOnly)) qDebug() << "Error reading file main.html";
    QTextStream rstream(&readfile);
    data = rstream.readAll();
    readfile.close();

    textEdit->setPlainText(data);
    webView->setUrl(filePath);
}

void HtmlEdit::editText()
{

    QString data = textEdit->toPlainText();

    QFile file(editFile);
    if(file.open(QFile::WriteOnly))
    {
        QTextStream txtStr(&file);
        txtStr << data;
        file.close();
    }

    webView->setUrl(editFile);
}
