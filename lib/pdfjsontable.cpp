#include "pdfjsontable.h"
#include <QPainter>
#include <QPrinter>

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
                QRect rect(0,0,style.value("width").toDouble(), style.value("height").toDouble());
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
                    painter->translate(style.value("width").toDouble(), 0);
                }
                else
                {
                    //img
                    QPixmap img("value");
                    painter->drawPixmap(0,0, img ) ;
                    painter->translate(style.value("width").toDouble(), 0);
                }
            }
        }
        painter->translate(0, style.value("height").toDouble());
    }

    painter->setFont(QFont("tahoma", 10));
    painter->translate(10, painter->viewport().height() );
    painter->setPen(QPen(QColor(0, 0, 0), 2));
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;

    painter->translate(0, headerHeight);
    painter->drawLine(0, 10, painter->viewport().width() , 10);
    painter->translate(0, 20);
}

bool PdfJsonTable::printTable(QPrinter *printer)
{
    if(!painter->begin(printer))
    {
        error = "painter->begin error.";
        return false;
    }

    preparePage();



    return true;
}

bool PdfJsonTable::print(QString outputPath, QString Creator, QString DocName)
{
    //Qt 5
    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Landscape);
    printer->setPaperSize(QPrinter::A3);
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
