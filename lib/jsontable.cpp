#include "jsontable.h"
#include <QFile>
#include <QByteArray>
#include <QJsonParseError>

JsonTable::JsonTable(double _default_width, double _default_height, QString _default_background_color, QString _default_color, QString _default_font_family, double _default_font_size, QObject *parent )
    : QObject{parent}
{
    this->default_width = _default_width;
    this->default_height = _default_height;
    this->default_background_color = _default_background_color;
    this->default_color = _default_color;
    this->default_font_size = _default_font_size;
    this->default_font_family = _default_font_family;
}

QJsonObject JsonTable::createStyle(double _width, double _height, QString _color, QString _backgroundColor, QString _fontFamily, double _fontSize, bool _bold, QString _align, int _border, int rowSpan)
{
    QJsonObject obj;
    obj["width"] = (_width == 0)? default_width : _width;
    obj["height"] = (_height == 0)? default_height : _height;
    obj["background-color"] = (_backgroundColor.isNull())? default_background_color : _backgroundColor ;
    obj["color"] = (_color.isNull())? default_color : _color;
    obj["font-size"]= (_fontSize == 0)? default_font_size : _fontSize;
    obj["font-family"]= (_fontFamily.isNull())? default_font_family : _fontFamily;
    obj["bold"]= _bold;
    obj["align"]= _align;// left center right
    obj["border"] = _border;
    obj["row-span"] = rowSpan; // 0:default -1:skip n>0:n-span this field will be updated by rowSpanAnalyser
    return obj;
}

QJsonObject JsonTable::createObject(QString _type, QString _value, QJsonObject _style)
{
    QJsonObject obj;
    obj["type"] = _type;
    obj["value"] = _value;
    obj["style"] = _style;
    return obj;
}

QJsonArray JsonTable::createObjects(QString _type, QStringList _values, QJsonObject _style)
{
    QJsonArray array;
    QJsonObject obj;
    for(int i=0 ; i < _values.size() ; i++  )
    {
        obj["type"] = _type;
        obj["value"] = _values[i];
        obj["style"] = _style;

        array.append(obj);
    }

    return array;
}

QJsonArray JsonTable::addObjectToRow(QJsonArray &row, QJsonObject item)
{
    row.append(item);
    return row;
}

QJsonArray JsonTable::addArrayToRow(QJsonArray &row, QJsonArray array)
{
    for(int i=0; i<array.count(); i++)
    {
        row.append(array[i].toObject());
    }

    return row;
}

void JsonTable::addRowToTable(QJsonArray &row)
{
    table.append(row);
}

void JsonTable::addRowToTable()
{
    // add empty row
    QJsonArray row;
    table.append(row);
}

QJsonArray JsonTable::emptyJsonArray(QJsonArray &array)
{
    while(array.count() > 0)
        array.removeAt(0);

    return array;
}

QByteArray JsonTable::toByteArray()
{
    QJsonDocument doc(table);
    QByteArray bytes = doc.toJson(QJsonDocument::Indented);
    return bytes;
}

QByteArray JsonTable::toByteArray(QJsonObject obj)
{
    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson(QJsonDocument::Indented);
    return bytes;
}

QByteArray JsonTable::toByteArray(QJsonArray array)
{
    QJsonDocument doc(array);
    QByteArray bytes = doc.toJson(QJsonDocument::Indented);
    return bytes;
}

bool JsonTable::saveJsonAs(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc(table);
    QByteArray bytes = doc.toJson(QJsonDocument::Indented);

    file.write(bytes);
    file.close();
    return true;
}

bool JsonTable::loadJson(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray bytes = file.readAll();

    QJsonParseError parsError;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &parsError);

    if(parsError.error != QJsonParseError::NoError)
        return false;

    table = doc.array();
    return true;
}

float JsonTable::getRowMaxHeight(QJsonArray array)
{
    double maxHeight = 0, height;
    QJsonObject item, style;
    for (int i=0; i < array.count(); i++)
    {
        item = array.at(i).toObject();
        style = item.value("style").toObject();
        height = style.value("height").toDouble();
        if(maxHeight < height)
            maxHeight = height;
    }

    if(maxHeight > 100) maxHeight = 100;
    return maxHeight;
}

QJsonObject JsonTable::updateObjectStyle(QJsonObject _object, QString _key, double _val)
{
    QJsonObject style;
    if(_object.contains("style"))
    {
        style = _object["style"].toObject();
        if( style.contains(_key) )
            style[_key] = _val;

        _object["style"] = style;
    }

    return _object;
}

QJsonArray JsonTable::updateRowStyle(QJsonArray row, QString key, double val)
{
    QJsonObject item;
    for(int i=0; i < row.count(); i++)
    {
        item = this->updateObjectStyle(row.at(i).toObject(), key , val);
        row.removeAt(i);
        row.insert(i, item);
    }

    return row;
}

void JsonTable::updateTableRowHeight()
{
    double maxHeight;
    QJsonArray row;
    for(int i = 0; i < table.count(); i++ )
    {
        maxHeight = this->getRowMaxHeight(table[i].toArray());
        row = this->updateRowStyle(table[i].toArray(), "height", maxHeight);
        table.removeAt(i);
        table.insert(i, row);
    }
}

QJsonObject JsonTable::getRowObject(int row, int index)
{
    QJsonObject obj = table[row].toArray()[index].toObject();
    return obj;
}

QString JsonTable::getType(int row, int index)
{
    QJsonObject obj = table[row].toArray()[index].toObject();
    QString type = obj.value("type").toString();
    return type;
}

QString JsonTable::getValue(int row, int index)
{
    QJsonObject obj = table[row].toArray()[index].toObject();
    QString value = obj.value("value").toString();
    return value;
}

QJsonObject JsonTable::getStyle(int row, int index)
{
    QJsonObject obj = table[row].toArray()[index].toObject();
    obj = obj.value("style").toObject();
    return obj;
}

int JsonTable::getObjectRowSpan(int row, int index)
{
    QJsonObject obj = table[row].toArray()[index].toObject();
    int value = obj["style"].toObject()["row-span"].toInt();
    return value;
}

bool JsonTable::setObjectRowSpan(int row, int index, int rowSpan)
{
    QJsonArray array = table[row].toArray();
    QJsonObject obj = array[index].toObject();
    QJsonObject style = obj["style"].toObject();
    style["row-span"] = rowSpan;
    obj["style"] = style;
    array.removeAt(index);
    array.insert(index, obj);
    table.removeAt(row);
    table.insert(row,array);

    int span = table[row].toArray()[index].toObject()["style"].toObject().value("row-span").toInt();
    if(span == rowSpan) return true; else return false;
}

bool JsonTable::updateObjectRowSpan(int row, int index)
{
    int span = 1;
    bool res = true;
    QString baseValue = this->getValue(row, index);
    int baseSpan = this->getObjectRowSpan(row, index);
    if(baseSpan != 0) return res;

    if(row == (table.count()-1)) // last row
    {
        res = res && setObjectRowSpan(row, index, span);
    }

    QString tempValue;
    for(int r=row+1; r<table.count(); r++)
    {
        if(table[r].toArray().count() >= index)
        {
            tempValue = getValue(r, index);
            if(baseValue.compare(tempValue, Qt::CaseSensitive) == 0)
            {
                span++;
                res = res && setObjectRowSpan(row, index, span);
                res = res && setObjectRowSpan(r, index, -1);
            }
            else
            {
                res = res && setObjectRowSpan(row, index, span);
                break;
            }
        }
        else
        {
            res = res && setObjectRowSpan(row, index, span);
            break;
        }
    }

    return res;
}

bool JsonTable::updateArrayRowSpan(int row)
{
    QJsonArray Row = table[row].toArray();
    bool res = true;
    for(int i=0; i<Row.count(); i++)
    {
        res = res && updateObjectRowSpan(row,i);
    }
    return res;
}

bool JsonTable::updateTableRowSpan()
{
    bool res = true;
    for(int r=0; r<table.count(); r++)
    {
        res = res && updateArrayRowSpan(r);
    }
    return res;
}



