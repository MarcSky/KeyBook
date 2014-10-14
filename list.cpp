#include "list.h"

list::list()
{
    head = NULL;
    tail = NULL;
    _id = 0;
    count_node = 0;
}
list::~list()
{
    nodes * first = head;
    nodes * n;
    while(first) {
        n = first->next;
        delete first;
        first = n;
    }
    head = tail = NULL;
    count_node = 0;
}

int list::addNode(QString site, QString password, QString name)
{
    nodes * node = new nodes;
    node->site = site;
    node->password = password;
    node->name = name;
    node->id = _id++;
    node->next = NULL;
    node->prev = NULL;

    if(!head) {
        head = tail = node;
    }
    else {
        node->prev = tail;
        tail->next = node;
        tail = tail->next;
    }
    count_node = 0;
    return OK;
}

void list::debug(void)
{
    nodes * first = head;
    while(first)
    {
        qDebug() << first->site + ' ' + first->name + ' ' + first->password;
        first = first->next;
    }
}

int list::deleteNode(unsigned int id)
{
    nodes * first = head;
    while(first->id == id) {
        first = first->next;
        delete first;
        count_node--;
    }
    return OK;
}

int list::deleteAll(void)
{
    nodes * first = head;
    nodes * n;
    while(first) {
        n = first->next;
        delete first;
        first = n;
    }
    head = tail = NULL;
    count_node = 0;
    return OK;
}

QString list::getName(unsigned int id)
{
    nodes * first = head;
    while(first)
    {
        if(first->id == id) return first->name;
        first = first->next;
    }
}

QString list::getSite(unsigned int id)
{
    nodes * first = head;
    while(first) {
        if(first->id == id) return first->site;
        first = first->next;
    }
}

QString list::getPassword(unsigned int id)
{
    nodes * first = head;
    while(first) {
        if(first->id == id) return first->password;
        first = first->next;
    }
}

QList<QStringList> list::getOneNode(unsigned int id) {
    QList<QStringList> temp;
    nodes * first = head;
    while(first) {
        if(first->id == id) {
            QStringList tmp;
            tmp.append(first->password);
            tmp.append(first->site);
            tmp.append(first->name);
            temp.append(tmp);
        }
        first = first->next;
    }
    return temp;
}


