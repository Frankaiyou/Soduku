#include "widget.h"
#include "soduku.h"
#include "ui_widget.h"
#include "QStandardItemModel"
#include "QMessageBox"
#include <QDebug>
#include <QTimer>
#include <time.h>
#include <things.h>
#include <qheaderview.h>
using namespace std;

Widget::~Widget() { delete ui; }
Things* obj;
Widget::Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Widget) {
        ui->setupUi(this);
        obj = new Things(); // 新建用到的所有对象
        obj->Init(); // 初始化用到的所有对象
        ui->tableView->setModel(obj->model); // 显示该表格
        ui->tableView->setAlternatingRowColors(true); // 相邻两行颜色不同
        ui->tableView->horizontalHeader()->setVisible(false);// 水平不可见
        ui->tableView->verticalHeader()->setVisible(false);// 垂直不可见
        for (int i = 0; i < 9; i += 1) {
            ui->tableView->setColumnWidth(i, 30);
            ui->tableView->setRowHeight(i, 30);
            ui->tableView->horizontalHeader()->setResizeMode(i, QHeaderView::Fixed); // 固定列宽
            ui->tableView->verticalHeader()->setResizeMode(i, QHeaderView::Fixed); // 固定行宽
        }
        this->connect(obj->time, SIGNAL(timeout()), this, SLOT(countTime())); //设置定时器以及槽函数
}

void Widget:: countTime() { // 0.1秒自动调用一次来刷新定时器
    ui->lcdNumber->display(int(clock() - obj->BeginTime) / 1000.0);
}

bool FaFaTa;
void Widget::on_pushButton_clicked() {
    FaFaTa = true;
    obj->M->init(35);
    for (int i = 0; i < 9; i += 1)
        for (int j = 0; j < 9; j += 1)
            if (obj->M->Pos(i, j)) {
                obj->model->setItem(i, j, new QStandardItem(QString::number(obj->M->Pos(i, j)))); // 设置单元格内容
                obj->model->item(i, j)->setForeground(QBrush(QColor(255, 0, 0)));   // 文字设置为红色
                obj->model->item(i, j)->setFlags(obj->model->item(i, j)->flags() & ~Qt::ItemIsEditable); // 设置次单元格为不可修改
                obj->model->item(i, j)->setTextAlignment(Qt::AlignCenter); // 设置为居中对齐
            }
            else obj->model->setItem(i, j, new QStandardItem("")); // 显示空白
    obj->BeginTime = clock(); // 设置定时器起始的真实事件
    obj->time->start(100);  // 开始计时, 每0.1秒刷新一次.
}

void Widget::on_pushButton_3_clicked() {
    if (not FaFaTa) {
        ui->label->setText("need to init");
        return ;
    }
    obj->time->stop(); // 暂停计时器
    ui->label->setText("start check");
    bool flag = 0;
    for (int i = 0; i < 9; i += 1) {
        for (int j = 0; j < 9; j += 1)
            if (obj->model->item(i, j)->text() == "") { //此单元格为空白
                ui->label->setText("Not Completed");
                flag = true; break;
            }
            else {
                int str = obj->model->item(i, j)->text().toInt(); // 获取到填的值
                if (not obj->M->Set(i, j, str)) {
                    flag = true; break;
                }
            }
        if (flag) break;
    }
    if (not flag) {
        ui->label->setText("victory"); // 成功
    }
    if (flag) obj->time->start(100); // 失败, 继续计时
}


void Widget::on_pushButton_2_clicked() {
    if (not FaFaTa) {
        ui->label->setText("need to init");
        return ;
    }
    obj->time->stop();// 停止计时
    for (int i = 0; i < 9; i += 1)
        for (int j = 0; j < 9; j += 1) {
            obj->model->setItem(i, j, new QStandardItem(QString::number(obj->M->GetYuan(i, j)))); // 显示数独的答案
            obj->model->item(i, j)->setTextAlignment(Qt::AlignCenter); // 居中对齐
        }
}
