#ifndef PARSER_H
#define PARSER_H
#include "list.h"

#define COUNTER 3

class parser
{
public:
    parser();
    list * parse_data(const QByteArray &text);

private:
};

#endif // PARSER_H
