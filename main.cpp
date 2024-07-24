#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //header
    JsonTable *header = new JsonTable(50, "#eef", "#333", "tahoma",20);
    // 420mm /3 * 3.7 = 518
    QJsonObject style = header->createStyle(0, 100, "#00A", "#fcc","tahoma", 18, true, "center",0);
    QJsonArray row = header->createObjects("text", {"2024", "Report", "DaNet"},style);
    style = header->createStyle(50, 50, "#000", "", "tahoma", 22, true, "right", 1, 0);
    QJsonObject obj = header->createObject("img",":/tct.jpg",style);
    header->addObjectToRow(row,obj);
    header->addRowToTable(row);

    header->emptyJsonArray(row);

    style = header->createStyle(500, 80, "#000", "#f00", "tahoma", 18, true, "center");
    obj = header->createObject("text", "BA" ,style);
    header->addObjectToRow(row,obj);

    style = header->createStyle(0, 80, "#f00", "#0e0", "tahoma", 24, true, "center"); // stretch column
    obj = header->createObject("text", "Saloon Switch/Data" ,style);
    header->addObjectToRow(row,obj);

    header->addRowToTable(row);

    header->updateTableRowHeight();
    header->updateTableRowSpan();


    //table



//    QByteArray bytes = header->toByteArray(jt->table);
//    QTextStream ts(stdout);
//    ts << bytes << endl;

    PdfJsonTable *pdf = new PdfJsonTable("Primary.pdf", "test", "danet");
    int width = pdf->getViewPortWidth();
    header->updateTableWidth(width);

    pdf->setHeader(&header->table);
    pdf->setTable(&header->table);

    pdf->print();

#if QT_VERSION  > 0x051210
#else
#endif

    return 1;
}
