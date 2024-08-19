#ifndef TABLEDATA_H
#define TABLEDATA_H

#include "lib/jsontable.h"
#include <QJsonArray>
#include <QJsonObject>

class tableData
{
public:
    explicit tableData(){}
    static JsonTable* getHeader()
    {
        // page header
        JsonTable *pageHeader = new JsonTable(0, "#eef", "#000", "tahoma",20);
        // 420mm /3 * 3.7 = 518
        QJsonObject style = pageHeader->createStyle("page-1", 0, 100, "#00A", "","tahoma", 24, true, "center",0);
        QJsonArray row = pageHeader->createObjects("text", {"2024", "Report", "DaNet"},style);
        style = pageHeader->createStyle("icon", 70, 50, "#000", "", "tahoma", 22, true, "center", 0, 0, 0);
        QJsonObject obj = pageHeader->createObject("img",":/tct.png",style);
        pageHeader->addObjectToRow(row,obj);
        pageHeader->addRowToTable(row);

        pageHeader->emptyJsonArray(row);

        style = pageHeader->createStyle("exchange name", 500, 80, "#008", "#EEF", "tahoma", 18, true, "center");
        obj = pageHeader->createObject("text", "Title-1" ,style);
        pageHeader->addObjectToRow(row,obj);

        style = pageHeader->createStyle("saloon-name", 0, 80, "#A00", "#FDD", "tahoma", 36, true, "center"); // stretch column
        obj = pageHeader->createObject("text", "Title-2" ,style);
        pageHeader->addObjectToRow(row,obj);

        pageHeader->addRowToTable(row);


        return pageHeader;


    }

    static JsonTable *getTable()
    {
         //table content
        JsonTable *table = new JsonTable(0, "#000", "#ddd", "tahoma",16, 5, 20);

        QJsonObject style = table->createStyle("table-header", 0, 0, "#000", "#EFE","tahoma", 20, true, "center",2);
        QJsonArray row = table->createObjects("text", {"Menu-1", "Menu-2", "Menu-3", "Menu-4"},style);
        table->addRowToTable(row);

        style = table->createStyle("device",0, 0, "#000", "#FEE","tahoma", 16, false, "left",2);
        row = table->createObjects("text", {"Lorem-1 ipsum odor amet, consectetuer adipiscing elit. Blandit eget vulputate cubilia convallis penatibus vivamus ante ante? Odio felis libero auctor elit, parturient donec porta tristique nullam. Scelerisque penatibus maximus erat aptent egestas mus. Eu sed euismod, hac semper arcu tortor ullamcorper vestibulum.", "Lorem-1", "Ipsum-1", "L-I-1"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-2", "Data", "CX600X16"},style);
        QJsonObject style1 = table->createStyle("icon",0 , 0, "#000", "", "",0, true, "center",1);
        QJsonObject obj = table->createObject("img",":/git.png",style1);
        table->addObjectToRow(row, obj);
        table->addRowToTable(row);


        row = table->createObjects("text", {"Lorem-3 ipsum", "PCM", "CX600X16", "Lorem ipsum odor amet, consectetuer adipiscing elit. Non arcu scelerisque nascetur elementum ante iaculis sapien. Facilisi faucibus dolor arcu ante consequat accumsan facilisi."},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"lorem-4", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-5 ", "Data", "CX600X16"},style);
        style1 = table->createStyle("icon",0 , 0, "#000", "", "",0, true, "center",1);
        obj = table->createObject("img",":/kuber.png",style1);
        table->addObjectToRow(row, obj);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-6", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-7", "Switch", "Lorem ipsum odor amet, consectetuer adipiscing elit.Lorem ipsum odor amet, consectetuer adipiscing elit.Lorem ipsum odor amet, consectetuer adipiscing elit.", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-8", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);


        row = table->createObjects("text", {"Lorem-9", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-10", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);


        row = table->createObjects("text", {"Lorem-11 ", "Data"},style);
        style1 = table->createStyle("icon",0 , 0, "#000", "", "",0, true, "center",1);
        obj = table->createObject("img",":/docker.png",style1);
        table->addObjectToRow(row, obj);
        obj = table->createObject("img",":/ansible.png",style1);
        table->addObjectToRow(row, obj);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-12", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-13", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-14", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);



        row = table->createObjects("text", {"Lorem-15", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-16", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        //row = table->createObjects("text", {"Lorem-17", "Switch", "CX600X16 NetEngine Huawei", "10G 11/0/0"},style);
        row = table->createObjects("text", {"Lorem-17", "Switch", "CX600X8", "10G 11/0/0"},style);
        table->addRowToTable(row);


        row = table->createObjects("text", {"Lorem-18", "PCM", "CX600X16", "10G 3/0/0"},style);
        //row = table->createObjects("text", {"Lorem-18", "PCM", "CX600X16", " Port 10G 3/0/0 SFP+ 10Km"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-19", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-20", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);



        row = table->createObjects("text", {"Lorem-21", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-22", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-23", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-24", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-25", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-26", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-27", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-28", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-29", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-30", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-31", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-32", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-33", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-34", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-35", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-36", "PCM", "CX600X16", "10G 3/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-37", "Switch", "CX600X16", "1G 10/0/0"},style);
        table->addRowToTable(row);

        row = table->createObjects("text", {"Lorem-38", "Switch", "CX600X16", "10G 11/0/0"},style);
        table->addRowToTable(row);

        //table->setAlternativeRows("#FFFFFF", "#EEEFEF", 1);
        table->setAlternativeRows();
        //highlight row
        table->highlightRow(5, "#FFAABB");
        // highligh rows
        table->highlightRow({8,14,20});

        return table;
    }

};

#endif // TABLEDATA_H
