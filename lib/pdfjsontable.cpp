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
                    QPixmap img(value);
                    double x,y;
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
                    QPixmap img(value);
                    double x, y;
                    x = style.value("width").toDouble();
                    y = style.value("height").toDouble();
                    painter->drawPixmap(x,y, img ) ;
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

bool PdfJsonTable::printCell(int row, int column, QJsonObject obj, double fullWidth)
{
    // write from left
    QString type = obj.value("type").toString();
    QString value = obj.value("value").toString();
    QJsonObject style = obj.value("style").toObject();

    double width = style.value("width").toDouble();
    double height = style.value("height").toDouble();
    QString fontFamily = style.value("font-family").toString();
    int fontSize = style.value("font-size").toInt();
    bool bold = style.value("bold").toBool();
    QString align = style.value("align").toString();
    int rowSpan = style.value("row-span").toInt();
    QString _color = style.value("color").toString();
    QString _backgroundColor = style.value("background-color").toString();

    if(rowSpan == -1) return true;
    if(rowSpan > 1)
          height = getRowSpanHeight(row, column);

    QColor color, backgroundColor;
    if(_color.isEmpty())
        color.setNamedColor("#000");
    else
        color.setNamedColor(_color);

    if(_backgroundColor.isEmpty())
        backgroundColor.setNamedColor("transparent");
    else
        backgroundColor.setNamedColor(_backgroundColor);

    QFont font(fontFamily);
    font.setPixelSize(fontSize);
    font.setBold(bold);

    height = (height == 0)? 50 : height;
    width = (width == 0)? fullWidth : width;

    painter->setPen(color);
    painter->setFont(font);
    QRect rect(0,0,width, height );
    painter->fillRect(rect, backgroundColor);

    if(type.compare("text", Qt::CaseInsensitive) == 0)
    {
        //text

        if(align.compare("center",Qt::CaseInsensitive) == 0)
            painter->drawText(rect, Qt::AlignVCenter | Qt::AlignHCenter , value);
        else if(align.compare("right",Qt::CaseInsensitive) == 0)
            painter->drawText(rect, Qt::AlignVCenter | Qt::AlignRight , value);
        else
            painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft , value);

        painter->translate(width, 0);
    }
    else
    {
        //img
        QPixmap img(value);
        int imgWidth = img.width();
        int imgHeight = img.height();
        if(imgWidth > width)
        {
            img.scaledToWidth(width - 10);
            imgWidth = img.width();
        }
        if(imgHeight > height)
        {
            img.scaledToHeight(height - 10);
            imgHeight = img.height();
        }
        double y = height/2 - imgHeight/2;
        if(align.compare("center",Qt::CaseInsensitive) == 0)
        {
            double x = width/2 - imgWidth/2;
            painter->drawPixmap(x,y, img ) ;
        }
        else if(align.compare("right",Qt::CaseInsensitive) == 0)
        {
            double x = width - imgWidth;
            painter->drawPixmap(x,y, img ) ;
        }
        else
        {
            painter->drawPixmap(0,y, img ) ;
        }

        painter->translate(width, 0);
    }

    return true;

}

double PdfJsonTable::getRowSpanHeight(int row, int column)
{
    double height = 0;
    QJsonArray array;
    QJsonObject obj;
    array = jsonTable[row].toArray();
    obj = array[column].toObject();
    obj = obj["style"].toObject();
    int rowSpan = obj["row-span"].toInt();
    if(rowSpan == -1) return 0;
    height = obj["height"].toDouble();
    if(rowSpan == 1) return height;
    if(rowSpan > 1)
    {
        for(int i = row+1; i < jsonTable.count(); i++)
        {
            array = jsonTable[i].toArray();
            obj = array[column].toObject();
            obj = obj["style"].toObject();
            rowSpan = obj["row-span"].toInt();
            if(rowSpan == -1)
                height += obj["height"].toDouble();
            else
                break;
        }

        return height;
    }
    else return 0;


    return height;
}

QString PdfJsonTable::lastError()
{
    return error;
}
