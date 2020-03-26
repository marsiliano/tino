#include "../gui/MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(gui_resources);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}
