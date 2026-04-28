#ifndef HTMLEDIT_H
#define HTMLEDIT_H

#include <QApplication>
#include <QMainWindow>
#include <QWebEngineView>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

class HtmlEdit : public QMainWindow
{
    Q_OBJECT

public:
    QTextEdit *textEdit = nullptr;
    QPushButton *openButton = nullptr;
    QHBoxLayout *webPage = nullptr;
    QWebEngineView *webView = new QWebEngineView;

    HtmlEdit(QWidget *parent = nullptr)  : QMainWindow(parent) {}

    void openFile();
    void editText();

public slots:
    void Open() { openFile(); };
    void Edit() { editText(); };

private:
    QString filePath;
    QString editFile;
};
#endif // HTMLEDIT_H
