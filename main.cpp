#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QDebug>
#include "lib/tabledata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // page header
    JsonTable *pageHeader = tableData::getHeader();
    JsonTable* table = tableData::getTable();

    table->saveJsonAs("table0.json");

    PdfJsonTable *pdf = new PdfJsonTable("Primary.pdf", "test", "danet","A3","landscape");
    int width = pdf->getViewPortWidth();
    //qDebug() << width;
    pageHeader->updateSameWidth(width);

    pageHeader->updateHeight();
    pageHeader->updateRowSpan(true);
    // table
    table->updateFairCell(width, true);
    table->updateRowSpan(2);

    table->saveJsonAs("table.json");

//    QByteArray bytes = table->toByteArray(table->table);
//    QTextStream ts(stdout);
//    ts << bytes << endl;

    pdf->setPageHeader(&pageHeader->table);
//    QList<int> list;
//    list << 0;
    pdf->setTable(&table->table, {0});


    pdf->print();

#if QT_VERSION  > 0x051210
#else
#endif

    return 1;
}
