#ifndef TABLETEMPLATE_H
#define TABLETEMPLATE_H

#include <QJsonObject>
#include <QJsonArray>
#include "lib/jsontable.h"
#include <QStringList>

class TableTemplate
{
public:
    explicit TableTemplate(int _columnCount, QJsonObject _headerStyle={}, QJsonObject _contentStyle={} ) :
        table(40,"#000", "#FFF","tahoma",14)
    {
        columnCount = _columnCount;

        if(_headerStyle.isEmpty())
        {
            headerStyle = table.createStyle("Table Header",0,0,"#558","#EEF","Tahoma",14,true,"center",1,0,2);
        }
        else
            headerStyle = _headerStyle;
        if(_contentStyle.isEmpty())
        {
            contentStyle = table.createStyle("Table Content",0,0,NULL,NULL,NULL,0,false,"left");
        }
        else
            contentStyle = _contentStyle;
    }

    bool setHeader(QStringList headerList)
    {

        if(headerList.size() == columnCount)
        {
            QJsonArray row = table.createObjects("text",headerList,headerStyle);
            table.addRowToTable(row);
        }
        else
            return false;

        return true;
    }

    bool appentRow(QStringList rowList)
    {
        if(rowList.size() == columnCount)
        {
            QJsonArray row = table.createObjects("text",rowList,contentStyle);
            table.addRowToTable(row);
        }
        else
            return false;

        return true;
    }

    void highlight(int row)
    {
        table.highlightRow(row);
    }

    QJsonArray getTable(double width, int columnSpanNumber, bool justifyWidth = true)
    {
        if(justifyWidth)
        {
            table.updateFairCell(width, true);
            table.updateRowSpan(columnSpanNumber);
        }
        else
        {
            table.updateSameWidth(width);
            table.updateHeight();
            table.updateRowSpan(true,columnSpanNumber);
        }


        return table.table;
    }


    int columnCount;
    QJsonObject headerStyle, contentStyle;
    JsonTable table;
};

#endif // TABLETEMPLATE_H
