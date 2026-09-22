#include<QLineEdit>
#include<QWidget>
#include<QStack>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QPushButton>
#include<QListWidget>
#include<QThread>
#include<QFont>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);//this属于this窗口 QWidget空白矩形
    setCentralWidget(central);//认定为中央区域
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    QLineEdit *text = new QLineEdit("0" , central);//输入框

    QPushButton *btn7 = new QPushButton("7" , central);//按钮
    QPushButton *btn8 = new QPushButton("8" , central);
    QPushButton *btn9 = new QPushButton("9" , central);
    QPushButton *btn1 = new QPushButton("1" , central);
    QPushButton *btn2 = new QPushButton("2" , central);
    QPushButton *btn3 = new QPushButton("3" , central);
    QPushButton *btn4 = new QPushButton("4" , central);
    QPushButton *btn5 = new QPushButton("5" , central);
    QPushButton *btn6 = new QPushButton("6" , central);
    QPushButton *btn0 = new QPushButton("0" , central);
    QPushButton *btnc = new QPushButton("C" , central);
    QPushButton *btn_dy = new QPushButton("=" , central);
    QPushButton *btn_plus = new QPushButton("+" , central);
    QPushButton *btn_minus = new QPushButton("-" , central);
    QPushButton *btn_times = new QPushButton("*" , central);
    QPushButton *btn_divides = new QPushButton("/" , central);
    QPushButton *btn_show_history = new QPushButton("show History" , central);
    // QLineEdit *display = new QLineEdit("hello Qt." , central);
    // display->setReadOnly(1);//设置只读

    // QVBoxLayout *layout = new QVBoxLayout(central);//垂直布局容器
    // layout->addWidget(btn7);//自动排布
    // layout->addWidget(btn0);
    // layout->addWidget(display);
    QGridLayout *grid = new QGridLayout();//空白表格布局管理器，装在central中
    mainLayout->addLayout(grid);

    // grid->addWidget(central , 0 , 0 , 1 , 3);//0 , 0 起始  占1行 3列 central 放入 grid中
    grid->addWidget(btn7 , 1 , 0);
    // grid->addWidget(display , 3 , 3);

    grid->addWidget(btn4 , 2, 0);
    grid->addWidget(btn5 , 2, 1);
    grid->addWidget(btn6 , 2, 2);


    grid->addWidget(btn1, 3, 0);
    grid->addWidget(btn2 , 3, 1);
    grid->addWidget(btn3, 3, 2);


    grid->addWidget(btn0 , 4, 1);
    grid->addWidget(btnc , 4, 0);
    grid->addWidget(btn_dy , 4, 2);

    grid->addWidget(btn8 , 1, 1);
    grid->addWidget(btn9 , 1, 2);

    grid->addWidget(text , 0 , 0 , 1 , 4);

    grid->addWidget(btn_plus , 1, 3);
    grid->addWidget(btn_minus , 2, 3);
    grid->addWidget(btn_times , 3, 3);
    grid->addWidget(btn_divides , 4, 3);

    QLineEdit *hello = new QLineEdit("Hello caculator." , central);
    hello->setReadOnly(1);
    grid->addWidget(hello , 5 , 0 , 1 , 4);
    grid->addWidget(btn_show_history , 5 , 3 , 1 , 1);
    btn_show_history->setVisible(!m_history_visiable);

    QList<QPushButton*> buttonList = {btn0 , btn1 , btn2 , btn3 , btn4 , btn5 , btn6 , btn7 , btn8 , btn9 , btn_minus , btn_divides , btn_plus , btn_times , btnc};
    //将所有按钮地址存入列表中

    QFont font;
    font.setPointSize(15);

    for(auto *btn : buttonList)//大小控制
    {
        btn->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
        btn->setFont(font);
    }
    btn_dy->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
    btn_dy->setFont(font);

    for(auto *btn :buttonList)//连接器
    {
        connect(btn , &QPushButton::clicked , this , [text , btn]()
        {
            if(btn->text() != "C" && btn->text() != "=" && text->text() != "0")
            {
                text->setText(text->text() + btn->text());
            }
            else if(btn->text() == "C")
            {
                text->setText("0");
            }
            else if(text->text() == "0")
            {
                text->setText(btn->text());
            }
        });
    }
    connect(btn_dy , &QPushButton::clicked , this , [this , hello , text]()
    {
        hello->setText(QString::number(calculate(text->text())));
        m_historyList->addItem(text->text() + " = " + QString::number(calculate(text->text())));
    });

    QWidget *historyPanel = new QWidget(central);
    mainLayout->addWidget(historyPanel);
    QVBoxLayout *historyLayout = new QVBoxLayout(historyPanel);
    historyPanel->setMinimumWidth(0);
    historyPanel->setMaximumWidth(450);

    QWidget *HistoryList = new QWidget(historyPanel);
    historyLayout->addWidget(HistoryList);

    QPushButton *clearHistory = new QPushButton("clear" , historyPanel);
    QPushButton *hideHistory = new QPushButton("hide" , historyPanel);

    historyLayout->addWidget(hideHistory);
    historyLayout->addWidget(clearHistory);

    m_historyList = new QListWidget(historyPanel);
    historyLayout->addWidget(m_historyList);

    //hide animation
    m_history_expand_animation = new QPropertyAnimation(historyPanel , "maximumWidth" , this);
    m_history_expand_animation->setEasingCurve(QEasingCurve::OutCirc);
    m_history_expand_animation->setDuration(800);//set existing time


    connect(hideHistory , &QPushButton::clicked , this , [this , hideHistory , clearHistory , hello , grid , btn_show_history , historyPanel]()
            {
        m_history_visiable = !m_history_visiable;
        btn_show_history->setVisible(!m_history_visiable);
        if(m_history_visiable)
            {
            hideHistory->setText("hide");
            grid->addWidget(hello , 5 , 0 , 1 , 4);

            m_history_expand_animation->stop();
            m_history_expand_animation->setStartValue(historyPanel->maximumWidth());
            m_history_expand_animation->setEndValue(450);
            m_history_expand_animation->start();
        }
        else
            {
            // hideHistory->setText("show");
            grid->addWidget(hello , 5 , 0 , 1 , 3);

            m_history_expand_animation->stop();
            m_history_expand_animation->setStartValue(historyPanel->maximumWidth());
            m_history_expand_animation->setEndValue(0);
            m_history_expand_animation->start();
        }
        // m_historyList->setVisible(m_history_visiable);
        // clearHistory->setVisible(m_history_visiable);
        // hideHistory->setVisible(m_history_visiable);

    });

    connect(btn_show_history , &QPushButton::clicked , this , [this , hideHistory , clearHistory , hello , grid , btn_show_history , historyPanel]()
            {
                m_history_visiable = !m_history_visiable;
                // m_historyList->setVisible(m_history_visiable);
                // clearHistory->setVisible(m_history_visiable);
                // hideHistory->setVisible(m_history_visiable);
                btn_show_history->setVisible(!m_history_visiable);

                if(m_history_visiable)
                {
                    hideHistory->setText("hide");
                    grid->addWidget(hello , 5 , 0 , 1 , 4);

                    m_history_expand_animation->stop();
                    m_history_expand_animation->setStartValue(historyPanel->maximumWidth());
                    m_history_expand_animation->setEndValue(450);
                    m_history_expand_animation->start();
                }
                else
                {
                    // hideHistory->setText("show");
                    grid->addWidget(hello , 5 , 0 , 1 , 3);

                    m_history_expand_animation->setStartValue(historyPanel->maximumWidth());
                    m_history_expand_animation->setEndValue(0);
                    m_history_expand_animation->start();
                }
            });

    connect(clearHistory, &QPushButton::clicked, this, [this]() {
        m_historyList->clear();
    });

};

void MainWindow::operatorCompare(QStack<double> &s , int opt , double temp)
{
    if(opt == 0)
    {
        s.push(temp);
    }
    else if(opt == 1)
    {
        s.push(temp);
    }
    else if(opt == 2)
    {
        s.push(-temp);
    }
    else if(opt == 3)
    {
        double top_num = s.top();
        s.pop();
        s.push(top_num * temp);
    }
    else if(opt == 4)
    {
        if(temp != 0)
        {
            double top_num = s.top();
            s.pop();
            s.push(top_num / temp);
        }
        else
        {
            return;
        }
    }
    return;
}

double MainWindow::calculate(QString calcuText)
{
    int calcuOperator = 0;// 1:+
    double temp = 0;
    QStack<double> calcuStack;
    for(auto i : calcuText)
    {
        if(i >= '0' && i <= '9')
        {
            if(temp == 0)
            {
                temp += i.digitValue();
            }
            else
            {
                temp *= 10;
                temp += i.digitValue();
            }
        }
        else if(i == '+')
        {
            operatorCompare(calcuStack , calcuOperator , temp);
            temp = 0;
            calcuOperator = 1;
        }
        else if(i == '-')
        {
            operatorCompare(calcuStack , calcuOperator , temp);
            temp = 0;
            calcuOperator = 2;
        }
        else if(i == '*')
        {
            operatorCompare(calcuStack , calcuOperator , temp);
            temp = 0;
            calcuOperator = 3;
        }
        else if(i == '/')
        {
            operatorCompare(calcuStack , calcuOperator , temp);
                temp = 0;
            calcuOperator = 4;
        }
        else
        {

        }
    }
    operatorCompare(calcuStack , calcuOperator , temp);
    double calcu_sum = 0;
    while(!calcuStack.empty())
    {
        calcu_sum += calcuStack.top();
        calcuStack.pop();
    }
    return calcu_sum;
}

MainWindow::~MainWindow() = default;
