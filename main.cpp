#include "testform.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontid = QFontDatabase::addApplicationFont(QString("/usr/share/fonts/truetype/msyh/msyh.ttc"));
    if( fontid!=-1 )
    {
        QStringList list = QFontDatabase::applicationFontFamilies(fontid);
        QFont font(list[0]);
        a.setFont(font);
    }

    TestForm  tf;
    tf.show();

    return a.exec();
}
