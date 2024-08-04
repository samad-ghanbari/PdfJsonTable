#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // page header
    JsonTable *pageHeader = new JsonTable(50, "#eef", "#333", "tahoma",20);
    // 420mm /3 * 3.7 = 518
    QJsonObject style = pageHeader->createStyle("page-1", 0, 100, "#00A", "#EEF","tahoma", 18, true, "center",0);
    QJsonArray row = pageHeader->createObjects("text", {"2024", "Report", "DaNet"},style);
    style = pageHeader->createStyle("icon", 50, 50, "#000", "", "tahoma", 22, true, "right", 1, 0);
    QJsonObject obj = pageHeader->createObject("img",":/tct.jpg",style);
    pageHeader->addObjectToRow(row,obj);
    pageHeader->addRowToTable(row);

    pageHeader->emptyJsonArray(row);

    style = pageHeader->createStyle("exchange name", 500, 80, "#F00", "#fEE", "tahoma", 18, true, "center");
    obj = pageHeader->createObject("text", "BA" ,style);
    pageHeader->addObjectToRow(row,obj);

    style = pageHeader->createStyle("saloon-name", 0, 80, "#A00", "#FDD", "tahoma", 24, true, "center"); // stretch column
    obj = pageHeader->createObject("text", "Saloon Switch/Data" ,style);
    pageHeader->addObjectToRow(row,obj);

    pageHeader->addRowToTable(row);


    //table content
    JsonTable *table = new JsonTable(50, "#888", "#ddd", "tahoma",16, 5, 20);

    style = table->createStyle("table-header", 0, 0, "#333", "#EFE","tahoma", 20, true, "center",2);
    row = table->createObjects("text", {"Exchange", "saloon", "Device", "Interface"},style);
    table->addRowToTable(row);

    style = table->createStyle("device",0, 0, "#555", "#FEE","tahoma", 16, false, "left",1);
    row = table->createObjects("text", {"DSLAM-1 Here i want to create a long text to check cell fair occupation. cell size is going to be auto resize to fit the content.  cell size is going to be auto resize to fit the content.", "Switch - Data ", "CX600X16", "10G 2/0/0"},style);
    table->addRowToTable(row);

    row = table->createObjects("text", {"DSLAM-2", "Data", "CX600X16", "10G 2/0/0"},style);
    table->addRowToTable(row);

    //table->addRowToTable(); // empty row for new page

    //new page
//    style = table->createStyle(0, 0, "#333", "#fbd","tahoma", 20, true, "center",2);
//    row = table->createObjects("text", {"Exchange", "saloon", "Device", "Interface"},style);
//    table->addRowToTable(row);

//    style = table->createStyle(0, 0, "#444", "#fef","tahoma", 16, false, "left",1);
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

    row = table->createObjects("text", {"DSLAM-11", "Saloon Switch of The Exchange Saloon Switch of The Exchange", "CX600X16", "10G 11/0/0"},style);
    //row = table->createObjects("text", {"DSLAM-11", "Switch", "CX600X16", "10G 11/0/0"},style);
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

    //row = table->createObjects("text", {"DSLAM-17", "Switch", "CX600X16 NetEngine Huawei", "10G 11/0/0"},style);
    row = table->createObjects("text", {"DSLAM-17", "Switch", "CX600X8", "10G 11/0/0"},style);
    table->addRowToTable(row);


    row = table->createObjects("text", {"DSLAM-18", "PCM", "CX600X16", "10G 3/0/0"},style);
    //row = table->createObjects("text", {"DSLAM-18", "PCM", "CX600X16", " Port 10G 3/0/0 SFP+ 10Km"},style);
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



    PdfJsonTable *pdf = new PdfJsonTable("Primary.pdf", "test", "danet","A3","landscape",50,20,20,20);
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
