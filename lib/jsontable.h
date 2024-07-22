//@ written by Samad Ghanbari
// 1403-04-29
// row-object: { type, value, style }               	QJsonObject
// row: [ row-object-1 , row-object-2, row-object-3 ]	QJsonArray
// table: [ row-1, row-2 , ... ]                        QJsonArray

/*
style: { width; height; background-color; color; font-size; font-family; bold; align; row-span}
 auto vertical center align
 horizontal center by style
row-item: { type, value, style }                QJsonObject
row: [ row-item-1 , row-item-2, row-item-3 ]	QJsonArray
table: [ row-1, row-2 , ... ]                   QJsonArray

- Maximum height of a row-items will be considered as the row height
- Same value of the adjacents will be span automatically (auto row-span)
- rowSpanAnalyser : analyses the rows and insert item into cell style: row-span: n (n>0 n-row-span ; n=0 undefined ; 1:one-row-default ;n=-1 skip)
- empty array-row means new page

*/

#ifndef JSONTABLE_H
#define JSONTABLE_H

#include <QObject>
#include <QStringList>

// json
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>

class JsonTable : public QObject
{
    Q_OBJECT
public:
    explicit JsonTable(double _default_width, double _default_height, QString _default_background_color, QString _default_color, double _default_font_size, QString _default_font_family, QObject *parent = nullptr );
    QJsonObject createStyle(double _width=0, double _height=0, QString _backgroundColor=NULL, QString _color=NULL, double _fontSize=0, bool _bold=false, QString _align="center", QString _fontFamily=NULL, int rowSpan=0);
    QJsonObject createObject(QString _type, QString _value, QJsonObject _style);
    QJsonArray createObjects(QString _type, QStringList  _values, QJsonObject _style);
    QJsonArray addObjectToRow(QJsonArray &row, QJsonObject item);
    QJsonArray addArrayToRow(QJsonArray &row, QJsonArray array);
    void addRowToTable(QJsonArray &row);
    void addRowToTable(); //add empty Row
    QJsonArray emptyJsonArray(QJsonArray &array);
    QByteArray toByteArray();
    QByteArray toByteArray(QJsonObject obj);
    QByteArray toByteArray(QJsonArray array);
    bool saveJsonAs(QString fileName);
    bool loadJson(QString fileName);

    float getRowMaxHeight(QJsonArray array);
    QJsonObject updateObjectStyle(QJsonObject _object, QString _key, double _val);
    QJsonArray updateRowStyle(QJsonArray row, QString key, double val);
    void updateTableRowHeight(); // set maximum cell height to all row-objects height

    QJsonObject getRowObject(int row, int index);
    QString getType(int row, int index);
    QString getValue(int row, int index);
    QJsonObject getStyle(int row, int index);
    int getObjectRowSpan(int row, int index);
    bool setObjectRowSpan(int row, int index, int rowSpan);
    bool objectAnalyser(int row, int index);
    bool rowAnalyser(int row);
    bool tableAnalyser();






    QJsonArray table; // [ [ {}, {}, {}, ... ], [], [], [] ]
    QString default_background_color, default_color, default_font_family;
    double default_width, default_height, default_font_size;


signals:

};

#endif // JSONTABLE_H
