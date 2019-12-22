#ifndef IMS_H
#define IMS_H

#include<string>
#include<vector>
#include<QString>

using namespace std;




class person
{
public:
    string  id, name, sex, age;
};

class teacher :public person
{
public:
    string department, profession, title;
};

class assistant :public person
{
public:
    string lab, work;
};

class staff :public person
{
public:
    string  office, work;
};

class tstaff :public person
{
public:
    string  office, work, department, profession, title;
};

class setinit
{
public:
    QString status, id, name, sex, age, department, profession, title, lab, work, office;
    int intst;
};

class cal
{
public:
    unsigned long long tean,assn,stan,tstn,alln,maln,femn;
};

class system
{
public:
    vector<teacher>tea;
    vector<assistant>ass;
    vector<staff>sta;
    vector<tstaff>tst;
    vector<setinit>delt;
    void add(teacher t)
    {
        tea.push_back(t);
    }
    void add(assistant t)
    {
        ass.push_back(t);
    }
    void add(staff t)
    {
        sta.push_back(t);
    }
    void add(tstaff t)
    {
        tst.push_back(t);
    }
    void add(setinit t)
    {
        delt.push_back(t);
    }
    bool search(QString s);
    QString find(QString id);
    setinit edit(QString id);
    void input(string id, setinit s);
    void input(int t, setinit s);
    QString output1(bool x,int y);
    QString output2(bool x,int y);
    QString output3(bool x,int y);
    QString output4(bool x,int y);
    bool del(string t);
    cal calc();
    void save(string s);
    bool open(string s);
    void openff(string s);
    void exportf(string s);
    void recycle(QString s);
    void restore(QString t, QString s);
    bool search2(QString s, QString t);
    void init();
    unsigned long long num()
    {
        return tea.size() + ass.size() + sta.size() + tst.size();
    }


private:
        //string s1,s2,s3,s4;
        QString s1="教师信息", s2="实验员信息", s3="行政人员信息", s4="教师兼行政人员信息";
};



#endif // IMS_H
