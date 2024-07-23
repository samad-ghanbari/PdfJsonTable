#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JsonTable *jt = new JsonTable(0,50, "#eef", "#333", "tahoma",20);
    // 420mm /3 * 3.7 = 518
    QJsonObject style = jt->createStyle(0, 100, "#000", "#ffc","tahoma", 18, true, "center",1);
    QJsonArray row = jt->createObjects("text", {"2024", "Report", "DaNet"},style);
    style = jt->createStyle(0, 50, "#000", "#FFF", "tahoma", 22, true, "right", 1, 0);
    QJsonObject obj = jt->createObject("img",":/tct.jpg",style);
    jt->addObjectToRow(row,obj);
    jt->addRowToTable(row);

    jt->emptyJsonArray(row);

    style = jt->createStyle(500, 80, "#000", "#ffe", "tahoma", 18, true, "center");
    obj = jt->createObject("text", "BA" ,style);
    jt->addObjectToRow(row,obj);

    style = jt->createStyle(-1, 80, "#f00", "#ffd", "tahoma", 24, true, "center"); // stretch column
    obj = jt->createObject("text", "Saloon Switch/Data" ,style);
    jt->addObjectToRow(row,obj);

    jt->addRowToTable(row);

    jt->updateTableRowHeight();
    jt->updateTableRowSpan();

//    QByteArray bytes = jt->toByteArray(jt->table);
//    QTextStream ts(stdout);
//    ts << bytes << endl;

    PdfJsonTable *pdf = new PdfJsonTable(jt->table, jt->table);
    //pdf->print("Primary.pdf", "test", "danet",QPageSize::A3);
    pdf->print("Primary.pdf", "test", "danet",QPrinter::A3);

    return a.exec();
}
