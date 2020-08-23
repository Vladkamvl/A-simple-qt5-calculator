#pragma once

#include <QWidget>
#include <iostream>
#include <string>
#include <vector>
#include "helpfunctions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digit_pressed();
    void dot_pressed();
    void binary_operations_pressed();
    void equal_pressed();
    void clear_delete_pressed();

private:
    double firstNum{};
    double secondNum{};
    double result{};
    bool isSecondNum{false};
    bool checkValidInput(std::string &str);
    char operatorNum{' '};
    Ui::MainWindow *ui;
    std::string numberLine{"0"};
};

