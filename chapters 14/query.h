#ifndef QUERY_H
#define QUERY_H

#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>


class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no; 
    virtual ~Query_base() = default;
private:
  
    virtual QueryResult eval(const TextQuery&) const = 0;

	virtual std::string rep() const = 0;
};


class Query
{
  
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&); 
    Query(const Query& query) : q(query.q), uc(query.uc) { ++*uc;}
    Query& operator=(const Query& query);
    QueryResult eval(const TextQuery &t) const
                            { return q->eval(t); }
    std::string rep() const { return q->rep(); }
    ~Query();
private:
    Query(Query_base* query): q(query), uc(new int(1)) { }
    Query_base* q;
    int* uc;
};

inline std::ostream &operator<<(std::ostream &os, const Query &query)
{
	return os << query.rep();
}

class WordQuery: public Query_base
{
    friend class Query; 
    WordQuery(const std::string &s): query_word(s) { }
    QueryResult eval(const TextQuery &t) const
                     { return t.query(query_word); }
	std::string rep() const { return query_word; }
    std::string query_word;  
};

inline Query::Query(const std::string &s) : q(new WordQuery(s)), uc(new int(1)) { }

inline Query::~Query()
{
    if (--*uc == 0)
    {
        delete q;
        delete uc;
    }
}

inline Query& Query::operator=(const Query& query)
{
    ++*query.uc;
    if (--*uc == 0)
    {
        delete q;
        delete uc;
    }
    q = query.q;
    uc = query.uc;
    return *this;
}

class NotQuery: public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }
	std::string rep() const {return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};

class BinaryQuery: public Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) { }

	std::string rep() const { return "(" + lhs.rep() + " "
	                                     + opSym + " "
		                                 + rhs.rep() + ")"; }

    Query lhs, rhs;  
    std::string opSym;
};


//wei wan cheng
class AndQuery: public BinaryQuery
{
   
};

class OrQuery: public BinaryQuery
{
   
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
   
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
   
}

inline Query operator~(const Query &operand)
{
  
}

std::ifstream& open_file(std::ifstream&, const std::string&);
TextQuery get_file(int, char**);
bool get_word(std::string&);
bool get_words(std::string&, std::string&);
std::ostream &print(std::ostream&, const QueryResult&);

#endif
