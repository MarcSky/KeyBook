#include "parser.h"
#include <QDebug>
parser::parser()
{

}

list *parser::parse_data(const QByteArray &text)
{
    list * n = new list();
    QList<QByteArray> s = text.split('\n');
    for(int i = 0; i < s.size() - 1 ; i += COUNTER){
      n->addNode(QString(s[i]),QString(s[i+1]),QString(s[i+2]));
    }
    n->debug();
    return n;
}
