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
    QJsonObject style = header->createStyle("page-1", 0, 100, "#00A", "#fcc","tahoma", 18, true, "center",0);
    QJsonArray row = header->createObjects("text", {"2024", "Report", "DaNet"},style);
    style = header->createStyle("icon", 50, 50, "#000", "", "tahoma", 22, true, "right", 1, 0);
    QJsonObject obj = header->createObject("img",":/tct.jpg",style);
    header->addObjectToRow(row,obj);
    header->addRowToTable(row);

    header->emptyJsonArray(row);

    style = header->createStyle("exchange name", 500, 80, "#000", "#f00", "tahoma", 18, true, "center");
    obj = header->createObject("text", "BA" ,style);
    header->addObjectToRow(row,obj);

    style = header->createStyle("saloon-name", 0, 80, "#f00", "#0e0", "tahoma", 24, true, "center"); // stretch column
    obj = header->createObject("text", "Saloon Switch/Data" ,style);
    header->addObjectToRow(row,obj);

    header->addRowToTable(row);

    header->updateTableRowHeight();
    header->updateTableRowSpan();


    //table
    JsonTable *table = new JsonTable(50, "#000", "#ddd", "tahoma",16);
    style = table->createStyle("page-2", 0, 60, "#333", "#fbd","tahoma", 20, true, "center",2);
    row = table->createObjects("text", {"Exchange", "saloon", "Device", "Interface"},style);
    table->addRowToTable(row);

    style = table->createStyle("device",0, 40, "#444", "#fef","tahoma", 16, false, "left",1);
    row = table->createObjects("text", {"D\nS\nL\nA\nM", "Switch", "CX600X16", "10G 2/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"D\nS\nL\nA\nM", "Data", "CX600X16", "10G 2/0/0"},style);
    table->addRowToTable(row);

    //table->addRowToTable(); // empty row for new page

    //new page
//    style = table->createStyle(0, 60, "#333", "#fbd","tahoma", 20, true, "center",2);
//    row = table->createObjects("text", {"Exchange", "saloon", "Device", "Interface"},style);
//    table->addRowToTable(row);

//    style = table->createStyle(0, 40, "#444", "#fef","tahoma", 16, false, "left",1);
    row = table->createObjects("text", {"D\nS\nL\nA\nM", "PCM", "CX600X8", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"D\nS\nL\nA\nM", "Switch", "CX600X8", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"D\nS\nL\nA\nM", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);

    table->updateTableRowHeight();
    //table->updateTableRowSpan(2);
    table->updateTableRowSpan(true);


    PdfJsonTable *pdf = new PdfJsonTable("Primary.pdf", "test", "danet","A2","portrait",50,80,30,40);
    int width = pdf->getViewPortWidth();
    header->updateTableWidth(width);
    table->updateTableWidth(width);

//    QByteArray bytes = table->toByteArray(table->table);
//    QTextStream ts(stdout);
//    ts << bytes << endl;

    pdf->setHeader(&header->table);
    pdf->setTable(&table->table);

    pdf->print();

#if QT_VERSION  > 0x051210
#else
#endif

    return 1;
}
