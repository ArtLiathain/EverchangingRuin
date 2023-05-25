#include <QApplication>
#include "../headers/mainwindow.h"
#include "../headers/Controller.h"
#include <QDebug>





int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow view;
    Model game;
    qDebug("This is running");
    Controller controller(&game, &view);
    controller.connectComponents();
    view.show();
    return a.exec();
}
