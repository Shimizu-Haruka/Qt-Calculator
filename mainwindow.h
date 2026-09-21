#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QListWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QListWidget *m_historyList;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    double calculate(QString caculText);
    void operatorCompare(QStack<double> &s , int opt , double temp);
};
#endif // MAINWINDOW_H
