
#include "../headers/mainwindow.h"
#include "./ui_mainwindow.h"
#include "../headers/Model.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EverchangingRuin)
{
    ui->setupUi(this);
    myTextField = ui->MyLineEdit;
    Model temp;
    Console = ui->textBrowser;
    Console->setPlainText(QString::fromStdString(temp.printWelcome()));

    QObject::connect(myTextField, &QLineEdit::returnPressed, this, &MainWindow::onLineEditReturnPressed);
    QObject::connect(ui->north, &QPushButton::pressed, this, &MainWindow::onDirectionButtonPressed);
    QObject::connect(ui->south, &QPushButton::pressed, this, &MainWindow::onDirectionButtonPressed);
    QObject::connect(ui->east, &QPushButton::pressed, this, &MainWindow::onDirectionButtonPressed);
    QObject::connect(ui->west, &QPushButton::pressed, this, &MainWindow::onDirectionButtonPressed);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onLineEditReturnPressed(){
    emit consoleUsed(myTextField->text());
    myTextField->setText("");

}



void MainWindow::onDirectionButtonPressed(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonName = button->objectName();

        qDebug("Ran 22");
        emit directionButtonPressed(buttonName);
    }
}

void MainWindow::updateText(QString text){
    Console->setText(text);
}
