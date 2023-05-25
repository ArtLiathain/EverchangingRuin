#include "../headers/Controller.h"
#include <QApplication>
#include <QDebug>




Controller::Controller(Model *model, MainWindow *mainWindow, QObject* parent)
    : QObject(parent){
    this->game = model;
    this->view = mainWindow;
}

void Controller::updateModel(string command){
    game->processString(command);
}

void Controller::connectComponents(){
    connect(view, &MainWindow::directionButtonPressed, this, &Controller::onDirectionButtonPressed);
    connect(view, &MainWindow::consoleUsed, this, &Controller::onConsoleUsed);
    connect(game, &Model::dataChanged, this, &Controller::updateView);
}


void Controller::onDirectionButtonPressed(QString buttonName){
    game->processString("go " + buttonName.toStdString());

}

void Controller::updateView()
{
    string text = game->getState();
    QString qText = QString::fromStdString(text);
    view->updateText(qText);
}

void Controller::onConsoleUsed(QString text){
    string normaltext = text.toStdString();
    for (int index  = 0; index  < normaltext.length(); index++ ) {
        normaltext[index] = tolower(normaltext[index]);
    }
    game->processString(normaltext);
}




