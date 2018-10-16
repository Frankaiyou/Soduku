#include "widget.h"
#include "soduku.h"
#include "ui_widget.h"
#include "QStandardItemModel"
#include "QMessageBox"
#include <QDebug>
#include <QTimer>
#include <time.h>
#include <things.h>
using namespace std;

Widget::~Widget() { delete ui; }
Things* obj;
Widget::Widget(QWidget *parent) : QWidget(parent),
    ui(new Ui::Widget) {
        ui->setupUi(this);
        obj = new Things();
        obj->Init();
        ui->tableView->setModel(obj->model);
        ui->tableView->setAlternatingRowColors(true);
//        ui->tableView->setStyleSheet("QTableView{background-color: rgb(250, 250, 255);"
//                                     "alternate-background-color: rgb(255, 245, 245);"
//                                     "font: 10pt YaHeiConsola}");
        std:: string str = "A";
        for (int i = 0; i < 9; i += 1) {
            obj->model->setHeaderData(i, Qt::Horizontal,QString::fromLocal8Bit(str.c_str()));
            ui->tableView->setColumnWidth(i, 30);
            ui->tableView->setRowHeight(i, 30);
            str[0] += 1;
            ui->tableView->horizontalHeader()->setResizeMode(i, QHeaderView::Fixed);
            ui->tableView->verticalHeader()->setResizeMode(i, QHeaderView::Fixed);
        }
        this->connect(obj->time, SIGNAL(timeout()), this, SLOT(countTime()));
}

void Widget:: countTime() {
    ui->lcdNumber->display(int(clock() - obj->BeginTime) / 1000.0);
}

bool FaFaTa;
void Widget::on_pushButton_clicked() {
    FaFaTa = true;
    obj->M->init(35);
    for (int i = 0; i < 9; i += 1)
        for (int j = 0; j < 9; j += 1)
            if (obj->M->Pos(i, j)) {
                obj->model->setItem(i, j, new QStandardItem(QString::number(obj->M->Pos(i, j))));
                obj->model->item(i, j)->setForeground(QBrush(QColor(255, 0, 0)));
                obj->model->item(i, j)->setFlags(obj->model->item(i, j)->flags() & ~Qt::ItemIsEditable);
            }
            else obj->model->setItem(i, j, new QStandardItem(""));
    obj->BeginTime = clock();
    obj->time->start(100);
}

void Widget::on_pushButton_3_clicked() {
    if (not FaFaTa) {
        ui->label->setText("need to init");
        return ;
    }
    obj->time->stop();
    ui->label->setText("start check");
    bool flag = 0;
    for (int i = 0; i < 9; i += 1) {
        for (int j = 0; j < 9; j += 1)
            if (obj->model->item(i, j)->text() == "") {
                ui->label->setText("Not Completed");
                flag = true; break;
            }
            else {
                int str = obj->model->item(i, j)->text().toInt();
                if (not obj->M->Set(i, j, str)) {
                    flag = true; break;
                }
            }
        if (flag) break;
    }
    if (not flag) {
        ui->label->setText("victory");
    }
    if (flag) obj->time->start(100);
}

void Widget::on_pushButton_2_clicked() {
    if (not FaFaTa) {
        ui->label->setText("need to init");
        return ;
    }
    for (int i = 0; i < 9; i += 1)
        for (int j = 0; j < 9; j += 1)
            obj->model->setItem(i, j, new QStandardItem(QString::number(obj->M->GetYuan(i, j))));
}
