#include <QApplication>
#include "lib/jsontable.h"
#include "lib/pdfjsontable.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JsonTable *jt = new JsonTable(0,50, "#eef", "#333", 24, "tahoma");
    // 420mm /3 * 3.7 = 518
    QJsonObject style = jt->createStyle(0, 100, "#DDF", "#00d", 24,true, "tahoma");
    QJsonArray row = jt->createObjects("text", {"2024", "Report", "DaNet"},style);
    jt->addRowToTable(row);

//    QByteArray bytes = jt->toByteArray(jt->table);
//    QTextStream ts(stdout);
    //ts << bytes << endl;

    PdfJsonTable *pdf = new PdfJsonTable(jt->table, jt->table);
    //pdf->print("Primary.pdf", "test", "danet",QPageSize::A3);
    pdf->print("Primary.pdf", "test", "danet",QPrinter::A3);

    return a.exec();
}
