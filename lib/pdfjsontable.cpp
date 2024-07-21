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
                fontSize = style.value("font-size").toInt();
                font = style.value("font-family").toInt();
                if(width == 0)
                    width = paperWidth/(row.count());
                height = (height == 0)? 50 : height;

                QRect rect(0,0,width, height );
                QColor color(style.value("color").toString());
                painter->setPen(color);
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

    paperWidth = painter->viewport().width();
    paperHeight = painter->viewport().height();

    qDebug() << paperWidth << paperHeight;
    //1562
    //1562 1097

    preparePage();


    painter->end();

    return true;
}

bool PdfJsonTable::print(QString outputPath, QString Creator, QString DocName)
{
    //Qt 5
    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Landscape);
    printer->setPaperSize(QPrinter::A3);
/*
A0  841 x 1189 mm
A1  594 x 841 mm
A2  420 x 594 mm
A3  297 x 420 mm  1097    1562    ~ 3.7
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
    printer->setOutputFileName(outputPath);
    printer->setCreator(Creator);
    printer->setDocName(DocName);

    if(printTable(printer))
        return true;
    else
        return false;

    //Qt 6
//    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution);
//    printer->setPageOrientation(QPageLayout::Landscape);
//    printer->setPageSize(QPageSize::A3);
//    printer->setDocName(DocName);
//    printer->setCreator(Creator);
//    printer->setOutputFileName(outputPath);

//    if(printTable(printer))
//        return true;
//    else
//        return false;
}

QString PdfJsonTable::lastError()
{
    return error;
}
