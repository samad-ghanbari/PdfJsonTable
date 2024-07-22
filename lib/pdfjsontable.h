#ifndef PDFJSONTABLE_H
#define PDFJSONTABLE_H

#include <QObject>
#include <QPen>
#include <QFont>
#include <QPageSize>
#include <QPrinter>

class QPrinter;
class QPainter;

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

/*
A0  841 x 1189 mm
A1  594 x 841 mm
A2  420 x 594 mm
A3  297 x 420 mm
A4  210 x 297 mm
A5  148 x 210 mm
A6  105 x 148 mm
A7  74 x 105 mm
A8  52 x 74 mm
A9  37 x 52 mm

B0  1030 x 1456 mm
B1  728 x 1030 mm
B2  515 x 728 mm
B3  364 x 515 mm
B4  257 x 364 mm
B5  182 x 257 mm
B6  128 x 182 mm
B7  91 x 128 mm
B8  64 x 91 mm
B9  45 x 64 mm
B10 32 x 45 mm

Letter 216 x 279 mm

*/

class PdfJsonTable : public QObject
{
    Q_OBJECT
public:
    explicit PdfJsonTable(QJsonArray &header, QJsonArray &table, QObject *parent = nullptr);

    void preparePage();

#if QT_VERSION > 0x051210
    bool print(QString outputPath, QString Creator, QString DocName, QPageSize::PageSizeId pageSize, qreal pageMarginLeft=4, qreal pageMarginTop=2, qreal pageMarginRight=4, qreal pageMarginBottom=1.5);
#else
    bool print(QString outputPath, QString Creator, QString DocName, QPrinter::PageSize pageSize, qreal pageMarginLeft=4, qreal pageMarginTop=2, qreal pageMarginRight=4, qreal pageMarginBottom=1.5);
#endif
    bool printTable(QPrinter *printer);
    bool printCell(int row, int column, QJsonObject obj, double fullWidth);
    double getRowSpanHeight(int row, int column);
    QString lastError();

private:
    QJsonArray &jsonHeader, &jsonTable;
    QPainter *painter;
    QPen pen; // for table borders

    bool newPageFlag;
    int pageNumber;

    QString error;

    //paper size
    double paperWidth, paperHeight;

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
