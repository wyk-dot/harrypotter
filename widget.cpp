#include "widget.h"
#include "search.h"
#include "ui_widget.h"
#include <cstring>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->cmdLineEdit, SIGNAL(returnPressed()), this, SLOT(on_commitButton_clicked()));
    ui->tableWidget->setColumnCount(5);
    header << "序号" << "人名/地名" << "页码" << "章节" << "书名";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0, 75);
    ui->tableWidget->setColumnWidth(1, 250);
    ui->tableWidget->setColumnWidth(2, 100);
    ui->tableWidget->setColumnWidth(3, 100);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_commitButton_clicked()
{
    QString model=ui->cmdLineEdit->text();
    QFile file(filename);
    if (model.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请输入一个人名/地名");
        return;
    }
    if (filename.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
        return;
    }
    ui->tableWidget->setRowCount(0);                           //下一次搜索之前将上一次的表格数据删掉
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "无法打开文件");
        return;
    }
    int n=filename.size(), i=0, j=0, nCount=0, times=0;        //nCount用于记录表格的行数， page用于记录页数
    //bool ok;
    QString line, tename, chapter, page;                       //line用于存储每一次从文本当中读取到的内容，tename用于存储书的名字, chapter用于记录章节数
    for (int k=n;k>=0;k--)                                     //此循环用于从文件地址里面提取书名
    {
        if (filename[k]=='.') j=k;
        if (filename[k]=='/') {i=k;break;}
    }
    tename=filename.mid(i+1, j-i-1);
    QTableWidgetItem *item[5];
    line=file.readLine();
    if (line=="CHAPTER ONE\n" || line=="Chapter one\n") chapter="1";//先将第一行文本内容读出来，判断在哪一个章节
    if (line=="CHAPTER ZERO\n") chapter="0";
    if (line=="Foreword\n") chapter="前言";
    while(!file.atEnd())
    {
        line=file.readLine();
        ui->textEdit->setText(line);
        times+=Search::bruteforce(line, model);
        if ((line.size()<= 4 || line=="viii\n") && line!="\n")
        {
            for (int i=0;i<times;i++, nCount++)
            {
                nCount=ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(nCount);
                item[2]=new QTableWidgetItem(line.trimmed());
                ui->tableWidget->setItem(nCount, 2, item[2]);
            }

            times=0;
        }
    }
    file.close();
    nCount=ui->tableWidget->rowCount();
    for (int i=0;i<nCount;i++)
    {
        item[0]=new QTableWidgetItem(QString("%1").arg(i+1));
        ui->tableWidget->setItem(i, 0, item[0]);
        item[1]=new QTableWidgetItem(model);
        ui->tableWidget->setItem(i, 1, item[1]);
        item[3]=new QTableWidgetItem(chapter);
        ui->tableWidget->setItem(i, 3, item[3]);
        item[4]=new QTableWidgetItem(tename);
        ui->tableWidget->setItem(i, 4, item[4]);
    }
}


void Widget::on_pushButton_clicked()
{
    filename=QFileDialog::getOpenFileName(this, tr("打开文件"), ".../", tr("文本文件(*txt)"));
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this, "警告", "无法打开文件");
        return;
    }
    ui->openfile->setText(filename);
    file.close();
}


void Widget::on_retirebutton_clicked()
{
    this->close();
}

