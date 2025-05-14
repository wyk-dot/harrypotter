#include "search.h"

Search::Search() {}
int Search::bruteforce(QString text, QString model)
{
    int n=text.size(), m=model.size(),p=0, j=0, times=0;
    for (int k=0;k<n-m;k++)
    {
        for (p=0, j=k;p<m;p++, j++)
        {
            if (text[j]!=model[p]) break;
        }
        if (p==m) times+=1;
    }
    return times;
}
