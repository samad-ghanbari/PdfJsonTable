#include "pdfjsontable.h"
#include <QPainter>
#include <QPrinter>
#include <QDebug>

PdfJsonTable::PdfJsonTable(QJsonArray &header, QJsonArray &table, QObject *parent)
    : QObject{parent}, jsonHeader(header), jsonTable(table), painter(new QPainter())
{
    pageNumber = 1;
    error = "";
}

void PdfJsonTable::preparePage()
{
    painter->resetTransform();

    QJsonArray row;
    QJsonObject obj, style;
    QString type,value;
    int headerHeight = 0;

    for(int i=0; i < jsonHeader.count(); i++)
    {
        row = jsonHeader[i].toArray();

        for(int j=0; j < row.count(); j++)
        {
            headerHeight += row[j].toObject().value("style").toObject().value("height").toDouble();

            if(row.count() == 1)
            {
                // write in center
                obj = row[j].toObject();

                type = obj.value("type").toString();
                value = obj.value("value").toString();
                style = obj.value("style").toObject();
                QRect rect(0,0,painter->viewport().width(), style.value("height").toDouble());
                QColor color(style.value("color").toString());
                painter->setPen(color);
                if(!style.value("background-color").toString().isNull())
                {
                    QColor bg(style.value("background-color").toString());
                    painter->fillRect(rect, bg);
                }

                if(type.compare("text", Qt::CaseInsensitive) == 0)
                {
                    //text
                    painter->drawText(rect, Qt::AlignVCenter | Qt::AlignHCenter , value);
                    painter->translate(0, style.value("height").toDouble());
                }
                else
                {
                    //img
                    QPixmap img("value");
                    int x,y;
                    x = painter->viewport().width()/2 - style.value("width").toDouble()/2;
                    y = style.value("height").toDouble();
                    painter->drawPixmap(x, y, img ) ;
                }
            }
            else
            {
                // write from left
                obj = row[j].toObject();

                type = obj.value("type").toString();
                value = obj.value("value").toString();
                style = obj.value("style").toObject();
                width = style.value("width").toDouble();
                height = style.value("height").toDouble();
                font.setFamily(style.value("font-family").toString());
                font.setPixelSize(style.value("font-size").toInt());
                font.setBold(style.value("bold").toBool());

                if(width == 0)
                    width = paperWidth/(row.count());
                height = (height == 0)? 50 : height;

                QRect rect(0,0,width, height );
                QColor color(style.value("color").toString());
                painter->setPen(color);
                painter->setFont(font);
                QBrush brush(Qt::red);
                painter->setBrush(brush);
                if(!style.value("background-color").toString().isNull())
                {
                    QColor bg(style.value("background-color").toString());
                    painter->fillRect(rect, bg);
                }

                if(type.compare("text", Qt::CaseInsensitive) == 0)
                {
                    //text
                    painter->drawText(rect, Qt::AlignVCenter | Qt::AlignHCenter , value);
                    painter->translate(width, 0);
                }
                else
                {
                    //img
                    QPixmap img("value");
                    painter->drawPixmap(0,0, img ) ;
                    painter->translate(width, 0);
                }
            }
        }
        painter->translate(0, height);
    }

    painter->setFont(QFont("tahoma", 10));
    painter->translate(10, painter->viewport().height() );
    painter->setPen(QPen(QColor(0, 0, 0), 2));
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;

    painter->translate(0, headerHeight);
    painter->drawLine(0, 10, paperWidth , 10);
    painter->translate(0, 20);
}

bool PdfJsonTable::printTable(QPrinter *printer)
{
    if(!painter->begin(printer))
    {
        error = "painter->begin error.";
        return false;
    }

    //painter->setViewport(0,0,1584,1123);
    paperWidth = painter->viewport().width();
    paperHeight = painter->viewport().height();
    // A3 11.7 in x 16.5 in
    // dpi 96 standard
    // 11.7 * 96 = 1123.2
    // 16.5 * 96 = 1584 >> 1588 1123
    // default padding left right 11
    // default padding top bottom 13.1
    preparePage();



    painter->end();

    return true;
}

#if QT_VERSION > 0x051210
bool PdfJsonTable::print(QString outputPath, QString Creator, QString DocName, QPageSize::PageSizeId  pageSize, qreal pageMarginLeft, qreal pageMarginTop, qreal pageMarginRight, qreal pageMarginBottom)
{
    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution); //dpi  96

    //Qt 6
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setPageSize(pageSize);
    printer->setDocName(DocName);
    printer->setCreator(Creator);
    printer->setOutputFileName(outputPath);
    QMarginsF margins(pageMarginLeft/96,pageMarginTop/96,pageMarginRight/96, pageMarginBottom/96);
    printer->setPageMargins(margins, QPageLayout::Inch );
    // A3 : 1580 1119

    if(printTable(printer))
        return true;
    else
        return false;
}
#else
bool PdfJsonTable::print(QString outputPath, QString Creator, QString DocName,  QPrinter::PageSize  pageSize, qreal pageMarginLeft, qreal pageMarginTop, qreal pageMarginRight, qreal pageMarginBottom)
    {
    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution); //dpi  96
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Landscape);
    printer->setPaperSize(pageSize);
    printer->setPageMargins(pageMarginLeft/96,pageMarginTop/96,pageMarginRight/96, pageMarginBottom/96, QPrinter::Inch );
    // A3 : 1580 1119
    printer->setOutputFileName(outputPath);
    printer->setCreator(Creator);
    printer->setDocName(DocName);

    if(printTable(printer))
        return true;
    else
        return false;
}
#endif


QString PdfJsonTable::lastError()
{
    return error;
}
