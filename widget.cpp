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
        obj = new Things(); // �½��õ������ж���
        obj->Init(); // ��ʼ���õ������ж���
        ui->tableView->setModel(obj->model); // ��ʾ�ñ��
        ui->tableView->setAlternatingRowColors(true); // ����������ɫ��ͬ
        ui->tableView->horizontalHeader()->setVisible(false);// ˮƽ���ɼ�
        ui->tableView->verticalHeader()->setVisible(false);// ��ֱ���ɼ�
        for (int i = 0; i < 9; i += 1) {
            ui->tableView->setColumnWidth(i, 30);
            ui->tableView->setRowHeight(i, 30);
            ui->tableView->horizontalHeader()->setResizeMode(i, QHeaderView::Fixed); // �̶��п�
            ui->tableView->verticalHeader()->setResizeMode(i, QHeaderView::Fixed); // �̶��п�
        }
        this->connect(obj->time, SIGNAL(timeout()), this, SLOT(countTime())); //���ö�ʱ���Լ��ۺ���
}

void Widget:: countTime() { // 0.1���Զ�����һ����ˢ�¶�ʱ��
    ui->lcdNumber->display(int(clock() - obj->BeginTime) / 1000.0);
}

bool FaFaTa;
void Widget::on_pushButton_clicked() {
    FaFaTa = true;
    obj->M->init(35);
    for (int i = 0; i < 9; i += 1)
        for (int j = 0; j < 9; j += 1)
            if (obj->M->Pos(i, j)) {
                obj->model->setItem(i, j, new QStandardItem(QString::number(obj->M->Pos(i, j)))); // ���õ�Ԫ������
                obj->model->item(i, j)->setForeground(QBrush(QColor(255, 0, 0)));   // ��������Ϊ��ɫ
                obj->model->item(i, j)->setFlags(obj->model->item(i, j)->flags() & ~Qt::ItemIsEditable); // ���ôε�Ԫ��Ϊ�����޸�
                obj->model->item(i, j)->setTextAlignment(Qt::AlignCenter); // ����Ϊ���ж���
            }
            else obj->model->setItem(i, j, new QStandardItem("")); // ��ʾ�հ�
    obj->BeginTime = clock(); // ���ö�ʱ����ʼ����ʵ�¼�
    obj->time->start(100);  // ��ʼ��ʱ, ÿ0.1��ˢ��һ��.
}

void Widget::on_pushButton_3_clicked() {
    if (not FaFaTa) {
        ui->label->setText("need to init");
        return ;
    }
    obj->time->stop(); // ��ͣ��ʱ��
    ui->label->setText("start check");
    bool flag = 0;
    for (int i = 0; i < 9; i += 1) {
        for (int j = 0; j < 9; j += 1)
            if (obj->model->item(i, j)->text() == "") { //�˵�Ԫ��Ϊ�հ�
                ui->label->setText("Not Completed");
                flag = true; break;
            }
            else {
                int str = obj->model->item(i, j)->text().toInt(); // ��ȡ�����ֵ
                if (not obj->M->Set(i, j, str)) {
                    flag = true; break;
                }
            }
        if (flag) break;
    }
    if (not flag) {
        ui->label->setText("victory"); // �ɹ�
    }
    if (flag) obj->time->start(100); // ʧ��, ������ʱ
}


void Widget::on_pushButton_2_clicked() {
    if (not FaFaTa) {
        ui->label->setText("need to init");
        return ;
    }
    obj->time->stop();// ֹͣ��ʱ
    for (int i = 0; i < 9; i += 1)
        for (int j = 0; j < 9; j += 1) {
            obj->model->setItem(i, j, new QStandardItem(QString::number(obj->M->GetYuan(i, j)))); // ��ʾ�����Ĵ�
            obj->model->item(i, j)->setTextAlignment(Qt::AlignCenter); // ���ж���
        }
}
