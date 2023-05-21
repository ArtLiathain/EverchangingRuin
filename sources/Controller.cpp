#include "../headers/Controller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow view;
    Model game;
    Controller controller(&game, &view);
    view.show();
    return a.exec();
}

Controller::Controller(Model *model, MainWindow *mainWindow, QObject* parent)
    : QObject(parent){
    this->game = model;
    this->view = mainWindow;
}

void Controller::updateModel(string command){
    game->processString(command);
}

void Controller::connectComponents(){
    connect(view, &MainWindow::onDirectionButtonPressed, this, &Controller::onDirectionButtonPressed);

}


void Controller::onDirectionButtonPressed(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonName = button->objectName();
        QString qstr = QString::fromStdString(temp.go(buttonName.toStdString()));

        Console->setText(qstr);
    }

}






