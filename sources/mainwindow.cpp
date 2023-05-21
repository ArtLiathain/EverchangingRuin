
#include "../headers/mainwindow.h"
#include "./ui_mainwindow.h"
#include "../headers/Model.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    QString text = myTextField->text();
    QString qstr = QString::fromStdString("\n" + temp.go(text.toStdString()));

    Console->setText(Console->toPlainText() + qstr);
    myTextField->setText("");

}

void MainWindow::onDirectionButtonPressed(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonName = button->objectName();
        QString qstr = QString::fromStdString(temp.go(buttonName.toStdString()));

        Console->setText(qstr);
    }

}



