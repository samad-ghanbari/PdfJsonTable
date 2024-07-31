#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // page header
    JsonTable *pageHeader = new JsonTable(50, "#eef", "#333", "tahoma",20);
    // 420mm /3 * 3.7 = 518
    QJsonObject style = pageHeader->createStyle("page-1", 0, 100, "#00A", "#fcc","tahoma", 18, true, "center",0);
    QJsonArray row = pageHeader->createObjects("text", {"2024", "Report", "DaNet"},style);
    style = pageHeader->createStyle("icon", 50, 50, "#000", "", "tahoma", 22, true, "right", 1, 0);
    QJsonObject obj = pageHeader->createObject("img",":/tct.jpg",style);
    pageHeader->addObjectToRow(row,obj);
    pageHeader->addRowToTable(row);

    pageHeader->emptyJsonArray(row);

    style = pageHeader->createStyle("exchange name", 500, 80, "#000", "#f00", "tahoma", 18, true, "center");
    obj = pageHeader->createObject("text", "BA" ,style);
    pageHeader->addObjectToRow(row,obj);

    style = pageHeader->createStyle("saloon-name", 0, 80, "#f00", "#0e0", "tahoma", 24, true, "center"); // stretch column
    obj = pageHeader->createObject("text", "Saloon Switch/Data" ,style);
    pageHeader->addObjectToRow(row,obj);

    pageHeader->addRowToTable(row);

    pageHeader->updateHeight();
    pageHeader->updateRowSpan(true);

      //table header
    JsonTable *tableHeader = new JsonTable(50, "#000", "#ddd", "tahoma",16);
    style = tableHeader->createStyle("page-2", 0, 60, "#333", "#fbd","tahoma", 20, true, "center",2);
    row = tableHeader->createObjects("text", {"Exchange", "saloon", "Device", "Interface"},style);
    tableHeader->addRowToTable(row);



    //table content
    JsonTable *table = new JsonTable(50, "#000", "#ddd", "tahoma",16);

    style = table->createStyle("device",0, 40, "#444", "#fef","tahoma", 16, false, "left",1);
    row = table->createObjects("text", {"DSLAM-1", "Switch", "CX600X16", "10G 2/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-2", "Data", "CX600X16", "10G 2/0/0"},style);
    table->addRowToTable(row);

    //table->addRowToTable(); // empty row for new page

    //new page
//    style = table->createStyle(0, 60, "#333", "#fbd","tahoma", 20, true, "center",2);
//    row = table->createObjects("text", {"Exchange", "saloon", "Device", "Interface"},style);
//    table->addRowToTable(row);

//    style = table->createStyle(0, 40, "#444", "#fef","tahoma", 16, false, "left",1);
    row = table->createObjects("text", {"DSLAM-3", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-4", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-5", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);



    row = table->createObjects("text", {"DSLAM-6", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-7", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-8", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);



    row = table->createObjects("text", {"DSLAM-9", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-10", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-11", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);



    row = table->createObjects("text", {"DSLAM-12", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-13", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-14", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);



    row = table->createObjects("text", {"DSLAM-15", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-16", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-17", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);



    row = table->createObjects("text", {"DSLAM-18", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-19", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-20", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);



    row = table->createObjects("text", {"DSLAM-21", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-22", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-23", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-24", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-25", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-26", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-27", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-28", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-29", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-30", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-31", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-32", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-33", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-34", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-35", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-36", "PCM", "CX600X16", "10G 3/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-37", "Switch", "CX600X16", "1G 10/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-38", "Switch", "CX600X16", "10G 11/0/0"},style);
    table->addRowToTable(row);





    table->updateHeight();
    table->updateRowSpan(2);
    table->updateRowSpan(false);


    PdfJsonTable *pdf = new PdfJsonTable("Primary.pdf", "test", "danet","A3","landscape",50,20,20,20);
    int width = pdf->getViewPortWidth();
    pageHeader->updateSameWidth(width);
    table->updateSameWidth(width);
    tableHeader->updateSameWidth(width);

//    QByteArray bytes = table->toByteArray(table->table);
//    QTextStream ts(stdout);
//    ts << bytes << endl;

    pdf->setPageTitle(&pageHeader->table);
    pdf->setTableHeader(&tableHeader->table);
    pdf->setTable(&table->table);


    pdf->print();

#if QT_VERSION  > 0x051210
#else
#endif

    return 1;
}
