#ifndef SEARCH_H
#define SEARCH_H

#include <QString>
#include <QTableWidget>

using namespace std;

class Search
{
public:
    Search();
    static int bruteforce(QString text, QString model);
};

#endif // SEARCH_H
