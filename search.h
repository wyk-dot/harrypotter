#ifndef SEARCH_H
#define SEARCH_H

#include <QString>
#include <QTableWidget>

using namespace std;

class Search
{
public:
    Search();
    static void bruteforce(QString text, QString model, QTableWidgetItem *item[5], QString page);
};

#endif // SEARCH_H
