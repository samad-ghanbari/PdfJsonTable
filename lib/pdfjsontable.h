#ifndef PDFJSONTABLE_H
#define PDFJSONTABLE_H

#include <QObject>
#include <QPen>
#include <QFont>

class QPrinter;
class QPainter;

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class PdfJsonTable : public QObject
{
    Q_OBJECT
public:
    explicit PdfJsonTable(QJsonArray &header, QJsonArray &table, QObject *parent = nullptr);

    void preparePage();
    bool printTable(QPrinter *printer);
    bool print(QString outputPath, QString Creator, QString DocName);
    QString lastError();

private:
    QJsonArray &jsonHeader, &jsonTable;
    QPainter *painter;
    QPen pen; // for table borders

    bool newPageFlag;
    int pageNumber;

    QString error;


    // cell margins
    int topMargin;
    int bottomMargin;
    int leftMargin;
    int rightMargin;
    // margins for table
    int topBlank;
    int bottomBlank;
    int leftBlank;
    int rightBlank;
};

#endif // PDFJSONTABLE_H
