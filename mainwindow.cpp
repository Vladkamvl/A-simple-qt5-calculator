#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->number_line->setText(QString::fromStdString(numberLine));
    connect(ui->btn_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_9, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->btn_dot, SIGNAL(released()), this, SLOT(dot_pressed()));
    connect(ui->btn_plus, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->btn_minus, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->btn_division, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->btn_procent, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->btn_multiplic, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->btn_clear, SIGNAL(released()), this, SLOT(clear_delete_pressed()));
    connect(ui->btn_delete, SIGNAL(released()), this, SLOT(clear_delete_pressed()));
    connect(ui->btn_equal, SIGNAL(released()), this, SLOT(equal_pressed()));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::digit_pressed()
{
    if(numberLine == "0" || isSecondNum){
        numberLine = "";
    }
    QPushButton *btn = qobject_cast<QPushButton *>(QObject::sender());
    numberLine += (btn->text()).toStdString();
    ui->number_line->setText(QString::fromStdString(numberLine));
    if(isSecondNum){
        secondNum = QString::fromStdString(numberLine).toDouble();
    }
}

void MainWindow::dot_pressed()
{
    if(numberLine == "0"){
        numberLine = "";
    }
    if(checkValidInput(numberLine)) numberLine += ".";
    ui->number_line->setText(QString::fromStdString(numberLine));
}

void MainWindow::binary_operations_pressed()
{
    if(numberLine == "0"){
        numberLine = "";
    }
    QPushButton *btn = qobject_cast<QPushButton *>(QObject::sender());
    if(btn->text() == "+"){
        if(!isSecondNum){
            firstNum = QString::fromStdString(numberLine).toDouble();
            isSecondNum = true;
        }
        if(checkValidInput(numberLine)) numberLine += "+";
        operatorNum = '+';
    }else if(btn->text() == "-"){
        if(!isSecondNum){
            firstNum = QString::fromStdString(numberLine).toDouble();
            isSecondNum = true;
        }
        if(checkValidInput(numberLine)) numberLine += "-";
        operatorNum = '-';
    }else if(btn->text() == "*"){
        if(!isSecondNum){
            firstNum = QString::fromStdString(numberLine).toDouble();
            isSecondNum = true;
        }
        if(checkValidInput(numberLine)) numberLine += "*";
        operatorNum = '*';
    }else if(btn->text() == "%"){
        if(!isSecondNum){
            firstNum = QString::fromStdString(numberLine).toDouble();
            isSecondNum = true;
        }
        if(checkValidInput(numberLine)) numberLine += "%";
        operatorNum = '%';
    }else if(btn->text() == "/"){
        if(!isSecondNum){
            firstNum = QString::fromStdString(numberLine).toDouble();
            isSecondNum = true;
        }
        if(checkValidInput(numberLine)) numberLine += "/";
        operatorNum = '/';
    }

    ui->number_line->setText(QString::fromStdString(numberLine));
}

void MainWindow::equal_pressed()
{
    switch(operatorNum){
        case '+':
            result = firstNum + secondNum;
        break;
        case '-':
            result = firstNum - secondNum;
        break;
        case '%':
            result = static_cast<int>(firstNum) % static_cast<int>(secondNum);
        break;
        case '*':
            result = firstNum * secondNum;
        break;
        case '/':
            result = firstNum / secondNum;
        break;
        default:
            result = ' ';
        break;
    }
    if(result == ' '){
        ui->number_line->setText("Something operand is empty");
    }else{
        ui->number_line->setText(QString::number(result));
    }
    isSecondNum = false;
    numberLine = "0";
}

void MainWindow::clear_delete_pressed()
{
    QPushButton *btn = qobject_cast<QPushButton *>(QObject::sender());
    if(btn->text() == "<-"){
        if(numberLine!= ""){
            numberLine.pop_back();
        }
    }else if(btn->text() == "clear"){
        numberLine = "0";
    }
    ui->number_line->setText(QString::fromStdString(numberLine));
}
bool MainWindow::checkValidInput(std::string &str)
{
    std::size_t pos = str.size() - 1;
    if(str[pos] == '%' || str[pos] == '+' || str[pos] == '-' || str[pos] == '*' || str[pos] == '/' || str[pos] == '.' || str == "" || isSecondNum){
        return false;
    }
    return true;
}
