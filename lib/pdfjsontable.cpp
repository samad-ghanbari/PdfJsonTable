#include "pdfjsontable.h"
#include <QPainter>
#include <QPrinter>
#include <QDebug>

PdfJsonTable::PdfJsonTable(QString outputPath, QString Creator, QString DocName, QString _pageSize, QString orientation, qreal pageMarginLeft, qreal pageMarginTop, qreal pageMarginRight, qreal pageMarginBottom, QObject *parent)
    : QObject{parent}, painter(new QPainter()), printer(new QPrinter(QPrinter::ScreenResolution))
{
    pageNumber = 1;
    error = "";
    // screanResolution dpi 96
    // A3 11.7 in x 16.5 in
    // dpi 96 standard
    // 11.7 * 96 = 1123.2
    // 16.5 * 96 = 1584 >> 1588 1123
    // default padding left right 11
    // default padding top bottom 13.1

    QMarginsF margins(pageMarginLeft/96,pageMarginTop/96,pageMarginRight/96, pageMarginBottom/96);
    printer->setDocName(DocName);
    printer->setCreator(Creator);
    printer->setOutputFileName(outputPath);

#if QT_VERSION > 0x051210
    QMap<QString, QPageSize::PageSizeId> PAGE_SIZE_ID = {
        {"A0", QPageSize::A0}, {"A1", QPageSize::A1}, {"A2", QPageSize::A2}, {"A3", QPageSize::A3}, {"A4", QPageSize::A4}, {"A5", QPageSize::A5}, {"A6", QPageSize::A6}, {"A7", QPageSize::A7}, {"A8", QPageSize::A8}, {"A9", QPageSize::A9}, {"A10", QPageSize::A10},
        {"B0", QPageSize::B0}, {"B1", QPageSize::B1}, {"B2", QPageSize::B2}, {"B3", QPageSize::B3}, {"B4", QPageSize::B4}, {"B5", QPageSize::B5}, {"B6", QPageSize::B6}, {"B7", QPageSize::B7}, {"B8", QPageSize::B8}, {"B9", QPageSize::B9}, {"B10", QPageSize::B10}
    };
    QMap<QString, QPageLayout::Orientation> ORIENTATION ={ {"landscape", QPageLayout::Landscape}, {"portrait", QPageLayout::Portrait} };

    printer->setPageOrientation(ORIENTATION.value(orientation));

    printer->setPageSize(PAGE_SIZE_ID.value(_pageSize));

    printer->setPageMargins(margins, QPageLayout::Inch );
    // A3 : 1580 1119

#else
    QMap<QString, QPrinter::PaperSize> PAGE_SIZE_ID = {
        {"A0", QPrinter::A0}, {"A1", QPrinter::A1}, {"A2", QPrinter::A2}, {"A3", QPrinter::A3}, {"A4", QPrinter::A4}, {"A5", QPrinter::A5}, {"A6", QPrinter::A6}, {"A7", QPrinter::A7}, {"A8", QPrinter::A8}, {"A9", QPrinter::A9}, {"A10", QPrinter::A10},
        {"B0", QPrinter::B0}, {"B1", QPrinter::B1}, {"B2", QPrinter::B2}, {"B3", QPrinter::B3}, {"B4", QPrinter::B4}, {"B5", QPrinter::B5}, {"B6", QPrinter::B6}, {"B7", QPrinter::B7}, {"B8", QPrinter::B8}, {"B9", QPrinter::B9}, {"B10", QPrinter::B10}
    };
    QMap<QString, QPrinter::Orientation> ORIENTATION ={ {"landscape", QPrinter::Landscape}, {"portrait", QPrinter::Portrait} };

    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(ORIENTATION.value(orientation));
    printer->setPaperSize(PAGE_SIZE_ID.value(_pageSize));
    printer->setPageMargins(pageMarginLeft/96,pageMarginTop/96,pageMarginRight/96, pageMarginBottom/96, QPrinter::Inch );
    // A3 : 1580 1119

#endif

    if(!painter->begin(printer))
    {
        error = "painter->begin error.";
    }
    else
    {
        paperWidth = painter->viewport().width();
        paperHeight = painter->viewport().height();
    }
}

void PdfJsonTable::setHeader(QJsonArray *header)
{
    jsonHeader = *header;
}

void PdfJsonTable::setTable(QJsonArray *table)
{
    jsonTable = *table;
}

int PdfJsonTable::getViewPortWidth()
{
    return painter->viewport().width();
}

int PdfJsonTable::getViewPortHeight()
{
    return painter->viewport().height();
}

void PdfJsonTable::preparePage()
{
    painter->resetTransform();


    QJsonArray row;
    QJsonObject obj;
    int headerHeight = 0;
    bool newRow;

    for(int i=0; i < jsonHeader.count(); i++)
    {
        row = jsonHeader[i].toArray();
        newRow = true;

        for(int j=0; j < row.count(); j++)
        {
            obj = row[j].toObject();
            if(newRow)
            {
                headerHeight += obj.value("style").toObject().value("height").toDouble();
                newRow = false;
            }

            if(!printCell(i, j, obj))
                break;
        }
        painter->resetTransform();
        painter->translate(0, headerHeight);
    }

    painter->resetTransform();
    painter->setFont(QFont("tahoma", 10));
    painter->setPen(QPen(QColor(0, 0, 0), 2));
    painter->drawText(QRect(0, paperHeight-20, paperWidth, paperHeight),Qt::AlignHCenter | Qt::AlignTop, QString("Page %1").arg(pageNumber));
    pageNumber += 1;

    painter->translate(0, headerHeight);

    painter->drawLine(0, 10, paperWidth , 10);
    painter->translate(0, 20);

    currentHeight = headerHeight + 30;
}

bool PdfJsonTable::print()
{
    preparePage();

    QJsonArray row;
    QJsonObject obj;

    for(int i=0; i < jsonTable.count(); i++ )
    {
        painter->save();
        row = jsonTable[i].toArray();
        //check empty array
        if(row.count() == 0)
        {
            painter->restore();
            printer->newPage();
            preparePage();
            continue;
        }
        int rowHeight = 50;

        for(int j=0; j < row.count(); j++)
        {
            obj = row[j].toObject();
            if(j == 0)
            {
                rowHeight = obj["style"].toObject()["height"].toInt();
                if( (currentHeight + rowHeight) > (paperHeight - 30) )
                {
                    painter->restore();
                    printer->newPage();
                    preparePage();
                    painter->save();
                }
                currentHeight += rowHeight;
            }

            if(!printCell(i, j, obj))
                break;
        }
        painter->restore();
        painter->translate(0, rowHeight);
    }

    painter->end();

    return true;
}

bool PdfJsonTable::printCell(int row, int column, QJsonObject obj)
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
    int border = style.value("border").toInt();
    int rowSpan = style.value("row-span").toInt();
    QString _color = style.value("color").toString();
    QString _backgroundColor = style.value("background-color").toString();

    if(rowSpan == -1){painter->translate(width, 0); return true;}
    if(rowSpan > 1)
          height = getRowSpanHeight(row, column);

    QColor color, backgroundColor;
    if(_color.isEmpty())
        color = QColor(Qt::black);
    else
        color = QColor(_color);

    if(_backgroundColor.isEmpty())
        backgroundColor = QColor("transparent");
    else
        backgroundColor = QColor(_backgroundColor);

    QFont font(fontFamily);
    font.setPixelSize(fontSize);
    font.setBold(bold);

    height = (height == 0)? 50 : height;
    painter->setPen(QPen(QBrush(color),border));
    painter->setFont(font);
    QRect rect(0,0,width, height );
    painter->fillRect(rect, backgroundColor);

    if(type.compare("text", Qt::CaseInsensitive) == 0)
    {
        //text

        painter->drawRect(rect);

        if(align.compare("center",Qt::CaseInsensitive) == 0)
            painter->drawText(rect, Qt::AlignVCenter | Qt::AlignHCenter |  Qt::TextWordWrap , value);
        else if(align.compare("right",Qt::CaseInsensitive) == 0)
            painter->drawText(rect, Qt::AlignVCenter | Qt::AlignRight | Qt::TextWordWrap, value);
        else
            painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap, value);

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
