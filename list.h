#ifndef LIST_H
#define LIST_H
#include <QtCore>
#define OK 1
#define BAD -1

#pragma pack(push, 1)
struct nodes
{
    QString site;
    QString password;
    QString name;
    unsigned int id;
    nodes * next;
    nodes * prev;
};
#pragma pack(pop)

struct ListNode
{
    nodes * head;
    nodes * tail;
    unsigned int count_size;
};

class list
{
public:
    list();
    ~list();
    int addNode(QString site, QString pass, QString name);
    int deleteNode(unsigned int id);
    int deleteAll(void);
    void debug(void);
    int getSizeNode(void) {return count_node;}
    QString getPassword(unsigned int id);
    QString getName(unsigned int id);
    QString getSite(unsigned int id);
    QList<QStringList> list::getOneNode(unsigned int id);


private:
    unsigned int count_node;
    unsigned int _id;
    //ListNode * listnode;
    nodes * head;
    nodes * tail;
};

#endif // LIST_H
