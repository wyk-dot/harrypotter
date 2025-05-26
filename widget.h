#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QProcess>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <cstring>
#include <QWidget>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_commitButton_clicked();

    void on_pushButton_clicked();

    void on_retirebutton_clicked();

    void onTableRowClicked(int row, int col);

private:
    Ui::Widget *ui;
    QString filename;
    QStringList header;
    int position[10000];
};
#endif // WIDGET_H
