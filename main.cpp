#include <QApplication>
//#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QDebug>
#include "lib/tabledata.h"
#include "lib/tableTemplate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TableTemplate tableTemplate(4);
    tableTemplate.setHeader({"Menu-1", "Menu-2", "Menu-3", "Menu-4"});

    tableTemplate.appentRow({"Lorem-1 ipsum odor amet, consectetuer adipiscing elit. Blandit eget vulputate cubilia convallis penatibus vivamus ante ante? Odio felis libero auctor elit, parturient donec porta tristique nullam. Scelerisque penatibus maximus erat aptent egestas mus. Eu sed euismod, hac semper arcu tortor ullamcorper vestibulum.", "Lorem-1", "Ipsum-1", "L-I-1"});
    tableTemplate.appentRow({"Lorem-2", "Data", "CX600X16"});
    tableTemplate.appentRow({"Lorem-3 ipsum", "PCM", "CX600X16", "Lorem ipsum odor amet, consectetuer adipiscing elit. Non arcu scelerisque nascetur elementum ante iaculis sapien. Facilisi faucibus dolor arcu ante consequat accumsan facilisi."});
    tableTemplate.appentRow({"lorem-4", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-5 ", "Data", "CX600X16"});
    tableTemplate.appentRow( {"Lorem-6", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-7", "Switch", "Lorem ipsum odor amet, consectetuer adipiscing elit.Lorem ipsum odor amet, consectetuer adipiscing elit.Lorem ipsum odor amet, consectetuer adipiscing elit.", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-8", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-9", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-10", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-11", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-12", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-13", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-14", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-15", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-16", "Switch", "CX600X16 NetEngine Huawei", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-17", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-18", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-1 ipsum odor amet, consectetuer adipiscing elit. Blandit eget vulputate cubilia convallis penatibus vivamus ante ante? Odio felis libero auctor elit, parturient donec porta tristique nullam. Scelerisque penatibus maximus erat aptent egestas mus. Eu sed euismod, hac semper arcu tortor ullamcorper vestibulum.", "Lorem-1", "Ipsum-1", "L-I-1"});
    tableTemplate.appentRow({"Lorem-2", "Data", "CX600X16"});
    tableTemplate.appentRow({"Lorem-3 ipsum", "PCM", "CX600X16", "Lorem ipsum odor amet, consectetuer adipiscing elit. Non arcu scelerisque nascetur elementum ante iaculis sapien. Facilisi faucibus dolor arcu ante consequat accumsan facilisi."});
    tableTemplate.appentRow({"lorem-4", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-5 ", "Data", "CX600X16"});
    tableTemplate.appentRow( {"Lorem-6", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-7", "Switch", "Lorem ipsum odor amet, consectetuer adipiscing elit.Lorem ipsum odor amet, consectetuer adipiscing elit.Lorem ipsum odor amet, consectetuer adipiscing elit.", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-8", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-9", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-10", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-11", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-12", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-13", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-14", "PCM", "CX600X16", "10G 3/0/0"});
    tableTemplate.appentRow({"Lorem-15", "Switch", "CX600X16", "1G 10/0/0"});
    tableTemplate.appentRow({"Lorem-16", "Switch", "CX600X16 NetEngine Huawei", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-17", "Switch", "CX600X16", "10G 11/0/0"});
    tableTemplate.appentRow({"Lorem-18", "Switch", "CX600X16", "10G 11/0/0"});

    tableTemplate.highlight(5);

    PdfJsonTable pdf("file.pdf","Samad Ghanbari","DaNet Report", "A3");
    double width = pdf.getViewPortWidth();
    QJsonArray table = tableTemplate.getTable(width,2);

    JsonTable *pageHeader = tableData::getHeader();
    pageHeader->updateSameWidth(width);
    pageHeader->updateHeight();
    pageHeader->updateRowSpan(true);

    pdf.setPageHeader(&pageHeader->table);
    pdf.setTable(&table,{1});
    pdf.print();



    return 1;
}
