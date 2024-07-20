#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JsonTable *jt = new JsonTable(50,40, "#eee", "#333", 14, "tahoma");
    QJsonObject style = jt->createStyle(100, 50, "#fefefe", "#000", 14, "tahoma");
    QJsonArray row = jt->createObjects("text", {"2024", "Report", "DaNet"},style);
    jt->addRowToTable(row);

//    QByteArray bytes = jt->toByteArray(jt->table);
//    QTextStream ts(stdout);
    //ts << bytes << endl;

    PdfJsonTable *pdf = new PdfJsonTable(jt->table, jt->table);
    pdf->print("Primary.pdf", "test", "danet");

    return a.exec();
}
