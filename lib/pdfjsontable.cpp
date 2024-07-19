#include "pdfjsontable.h"
#include <QPainter>
#include <QPrinter>

PdfJsonTable::PdfJsonTable(QJsonArray &table, QObject *parent)
    : QObject{parent}, jsonTable(table), painter(new QPainter())
{
    pageNumber = 1;
    error = "";

}

void PdfJsonTable::preparePage()
{
    painter->resetTransform();
    painter->save();

    painter->setFont(QFont("tahoma", 10));
    painter->translate(10, painter->viewport().height() );
    painter->setPen(QPen(QColor(0, 0, 0), 2));
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
    painter->restore();
    painter->translate(10,topBlank);
}

bool PdfJsonTable::printTable(QPrinter *printer)
{
    if(!painter->begin(printer))
    {
        error = "painter->begin error.";
        return false;
    }



    return true;
}

bool PdfJsonTable::print(QString outputPath, QString Creator, QString DocName, QString Program)
{
    QPrinter *printer = new QPrinter(QPrinter::ScreenResolution);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Landscape);
    printer->setPaperSize(QPrinter::A3);
    printer->setOutputFileName(outputPath);
    printer->setCreator(Creator);
    printer->setDocName(DocName);
    printer->setPrintProgram(Program);

    if(printTable(printer))
        return true;
    else
        return false;
}

QString PdfJsonTable::lastError()
{
    return error;
}
