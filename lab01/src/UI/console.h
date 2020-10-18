#ifndef TREECONSOLE_H
#define TREECONSOLE_H

#include <QTextBrowser>
#include <QString>

class Console
{
private:
    QTextBrowser* _browser;
    QColor _techColor;
    QColor _textColor;
    QColor _errorColor;

    void _print(const QString& str, const QColor& color) const;
    void _printTime() const;


public:
    explicit Console(QTextBrowser* browser);
    explicit Console(QTextBrowser* browser, const QColor& techColor, const QColor& textColor, const QColor& errorColor);
    virtual ~Console();

    void newLine() const;
    void newPar() const;

    void print(const QString& str) const;
    void printTech(const QString& techMessage) const;
    void printError(const QString& errorMessage) const;

    void print(const QString& str, const QColor& color) const;

    QColor textColor() const;
    QColor techColor() const;
    QColor errorColor() const;

    void setTextColor(const QColor& textColor);
    void setTechColor(const QColor& techColor);
    void setErrorColor(const QColor& errorColor);
};

#endif // TREECONSOLE_H
