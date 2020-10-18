#include "console.h"

#include <QDateTime>
#include <QScrollBar>

void Console::_print(const QString &str, const QColor &color) const
{
    QString text = "<span style=\"color:" + color.name() + "\">";
    text += str + "</span>";

    text.replace("<-", "&lt;-");
    text.replace("->", "-&gt;");
    text.replace("\n", "<br>");
    text.replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;");

    this->_browser->insertHtml(text);

    QScrollBar *sb = this->_browser->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void Console::_printTime() const
{
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");

    this->_print(time, this->_techColor);
}

Console::Console(QTextBrowser *browser)
    : _browser(browser), _techColor(QColor(4, 88, 133, 255)), _textColor(QColor(79, 79, 79, 255)), _errorColor(QColor(166, 35, 35, 255)) {}

Console::Console(QTextBrowser *browser, const QColor &techColor, const QColor &textColor, const QColor &errorColor)
    : _browser(browser), _techColor(techColor), _textColor(textColor), _errorColor(errorColor) {}

Console::~Console()
{
    delete this->_browser;
}

void Console::newLine() const
{
    if (this->_browser->toPlainText() == "")
        return;

    this->_print("<br>", QColor(0,0,0,0));
}

void Console::newPar() const
{
    this->newLine();
    this->newLine();
}

void Console::printTech(const QString &techMessage) const
{
    this->_printTime();

    this->_print("&nbsp;| " + techMessage, this->_techColor);
}

void Console::printError(const QString &errorMessage) const
{
    this->_print(errorMessage, this->_errorColor);
}

void Console::print(const QString &str) const
{
    this->_print(str, this->_textColor);
}

void Console::print(const QString &str, const QColor &color) const
{
    this->_print(str, color);
}

QColor Console::textColor() const
{
    return this->_textColor;
}

QColor Console::techColor() const
{
    return this->_techColor;
}

QColor Console::errorColor() const
{
    return this->_errorColor;
}

void Console::setTextColor(const QColor &textColor)
{
    this->_textColor = textColor;
}

void Console::setTechColor(const QColor &techColor)
{
    this->_techColor = techColor;
}

void Console::setErrorColor(const QColor &errorColor)
{
    this->_errorColor = errorColor;
}
