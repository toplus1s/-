#pragma execution_character_set("utf-8")
#include "ims.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include<stdlib.h>
#include<conio.h>
#include <algorithm>
#include<QString>
#include<qdebug.h>
#include "global.h"

using namespace std;


string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}


void swapf(string s, string t)
{
    string temp;
    temp = s;
    s = t;
    t = temp;
}





bool system::search(QString s)
{
    string id = qstr2str(s);
    for (auto &i : tea){
        if (i.id == id)   
            return false;}
    for (auto &i : sta){
        if (i.id == id)
            return false;}
    for (auto &i : ass){
        if (i.id == id)
            return false;}
    for (auto &i : tst){
        if (i.id == id)
            return false;}
    return true;
}

bool system::search2(QString s, QString t)
{
    string id = qstr2str(s);
    string tt = qstr2str(t);
    for (auto &i : tea){
        if (i.id == id && i.id != tt)
            return false;}
    for (auto &i : sta){
        if (i.id == id && i.id != tt)
            return false;}
    for (auto &i : ass){
        if (i.id == id && i.id != tt)
            return false;}
    for (auto &i : tst){
        if (i.id == id && i.id != tt)
            return false;}
    return true;
}



QString system::find(QString id)
    {
        string s;
        extern int jilu;
        QString ss="";
        string t = qstr2str(id);
        for (auto &i : tea){s = "Status: teacher";
            if (i.id == t || i.name == t)
            {
                s+="\nID: "+i.id+"\nName: "+i.name+"\nSex: "+i.sex+"\nAge: "+i.age+"\nDepartment: "+i.department+"\nProfession: "+i.profession+"\nTitle: "+i.title+"\n\n";
                ss+= QString(QString::fromLocal8Bit(s.c_str()));
                jilu++;
            }
        }
        for (auto &i : ass){s = "Status: assistant";
            if (i.id == t || i.name == t)
            {
                s+="\nID: "+i.id+"\nName: "+i.name+"\nSex: "+i.sex+"\nAge: "+i.age+"\nlab: "+i.lab+"\nwork: "+i.work+"\n\n";
                ss+= QString(QString::fromLocal8Bit(s.c_str()));
                jilu++;
            }
        }
        for (auto &i : sta){s = "Status: staff";
            if (i.id == t || i.name == t)
            {
               s+="\nID: "+i.id+"\nName: "+i.name+"\nSex: "+i.sex+"\nAge: "+i.age+"\noffice: "+i.office+"\nwork: "+i.work+"\n\n";
               ss+= QString(QString::fromLocal8Bit(s.c_str()));
               jilu++;
            }
        }
        for (auto &i : tst){s = "Status: teacher and staff";
            if (i.id == t || i.name == t)
            {
                s+="\nID: "+i.id+"\nName: "+i.name+"\nSex: "+i.sex+"\nAge: "+i.age+"\noffice: "+i.office+"\nwork: "+i.work+"\nDepartment: "+i.department+"\nProfession: "+i.profession+"\nTitle: "+i.title+"\n\n";
                ss+= QString(QString::fromLocal8Bit(s.c_str()));
                jilu++;
            }
        }
       return ss;
    }


setinit system::edit(QString id)
{
    setinit ss;
    string t = qstr2str(id);
    for (auto &i : tea)
        if (i.id == t || i.name == t)
        {
            ss.id = QString(QString::fromLocal8Bit(i.id.c_str()));
            ss.name = QString(QString::fromLocal8Bit(i.name.c_str()));
            ss.sex = QString(QString::fromLocal8Bit(i.sex.c_str()));
            ss.age = QString(QString::fromLocal8Bit(i.age.c_str()));
            ss.department = QString(QString::fromLocal8Bit(i.department.c_str()));
            ss.profession = QString(QString::fromLocal8Bit(i.profession.c_str()));
            ss.title = QString(QString::fromLocal8Bit(i.title.c_str()));
            ss.lab = "缺省";
            ss.work ="缺省";
            ss.office ="缺省";
            ss.status = "教师信息";
            add(ss);
            return ss;
        }
    for (auto &i : ass)
        if (i.id == t || i.name == t)
        {

            ss.id = QString(QString::fromLocal8Bit(i.id.c_str()));
            ss.name = QString(QString::fromLocal8Bit(i.name.c_str()));
            ss.sex = QString(QString::fromLocal8Bit(i.sex.c_str()));
            ss.age = QString(QString::fromLocal8Bit(i.age.c_str()));
            ss.lab = QString(QString::fromLocal8Bit(i.lab.c_str()));
            ss.work = QString(QString::fromLocal8Bit(i.work.c_str()));
            ss.office = "缺省";
            ss.department = "缺省";
            ss.profession = "缺省";
            ss.title ="缺省";
            ss.status = "实验员信息";
            add(ss);
            return ss;
        }
    for (auto &i : sta)
        if (i.id == t || i.name == t)
        {
            ss.id = QString(QString::fromLocal8Bit(i.id.c_str()));
            ss.name = QString(QString::fromLocal8Bit(i.name.c_str()));
            ss.sex = QString(QString::fromLocal8Bit(i.sex.c_str()));
            ss.age = QString(QString::fromLocal8Bit(i.age.c_str()));
            ss.office = QString(QString::fromLocal8Bit(i.office.c_str()));
            ss.work = QString(QString::fromLocal8Bit(i.work.c_str()));
            ss.department = "缺省";
            ss.profession ="缺省";
            ss.title ="缺省";
            ss.lab = "缺省";
            ss.status = "行政人员信息";
            add(ss);
            return ss;
        }
    for (auto &i : tst)
        if (i.id == t || i.name == t)
        {
            ss.id = QString(QString::fromLocal8Bit(i.id.c_str()));
            ss.name = QString(QString::fromLocal8Bit(i.name.c_str()));
            ss.sex = QString(QString::fromLocal8Bit(i.sex.c_str()));
            ss.age = QString(QString::fromLocal8Bit(i.age.c_str()));
            ss.department = QString(QString::fromLocal8Bit(i.department.c_str()));
            ss.profession = QString(QString::fromLocal8Bit(i.profession.c_str()));
            ss.title = QString(QString::fromLocal8Bit(i.title.c_str()));
            ss.office = QString(QString::fromLocal8Bit(i.office.c_str()));
            ss.work = QString(QString::fromLocal8Bit(i.work.c_str()));
            ss.lab = "缺省";
            ss.status = "教师兼行政人员信息";
            add(ss);
            return ss;
        }
   return ss;
}



void system::restore(QString t, QString s)
{
    for  (auto &i : delt){
        if (i.id == t)
            input(qstr2str(s), i);
    }
}




void system::input(string t, setinit s)
{
    for (auto &i : tea){
        if (i.id == t)
        {

            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.department = qstr2str(s.department);
            i.profession = qstr2str(s.profession);
            i.title = qstr2str(s.title);
        }
    }
    for (auto &i : ass){
        if (i.id == t)
        {
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.lab = qstr2str(s.lab);
            i.work = qstr2str(s.work);
        }
    }
    for (auto &i : sta){
        if (i.id == t)
        {
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.office =qstr2str(s.office);
            i.work = qstr2str(s.work);
        }
    }
    for (auto &i : tst){
        if (i.id == t)
        {
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.department = qstr2str(s.department);
            i.profession = qstr2str(s.profession);
            i.title = qstr2str(s.title);
            i.office =qstr2str(s.office);
            i.work = qstr2str(s.work);
        }
    }
}



void system::input(int t, setinit s)
{
        if (t == 0)
        {
            teacher i;
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.department = qstr2str(s.department);
            i.profession = qstr2str(s.profession);
            i.title = qstr2str(s.title);
            add(i);
        }
        if (t == 1)
        {
            assistant i;
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.lab = qstr2str(s.lab);
            i.work = qstr2str(s.work);
            add(i);
        }
        if (t == 2)
        {
            staff i;
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.office =qstr2str(s.office);
            i.work = qstr2str(s.work);
            add(i);
        }
        if (t == 3)
        {
            tstaff i;
            i.id = qstr2str(s.id);
            i.name =qstr2str(s.name);
            i.sex = qstr2str(s.sex);
            i.age = qstr2str(s.age);
            i.department = qstr2str(s.department);
            i.profession = qstr2str(s.profession);
            i.title = qstr2str(s.title);
            i.office =qstr2str(s.office);
            i.work = qstr2str(s.work);
            add(i);
        }
}


void system:: recycle(QString s)
{
    for (auto i = delt.begin(); i != delt.end(); ++i)
        if ((*i).id == s)
        {
                qDebug()<<"执行!";
                input(i->intst,*i);
                delt.erase(i);
                break;
        }
}



QString system::output1(bool x,int y)
{
    if(x==1)
    {
        if(y==0||y==30||y==6)
        {
            QString ss="\t教师信息\n";
            string s;
            for (auto i : tea)
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.department+" "+i.profession+" "+i.title+"\n";
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else if(y==15)
        {
            QString ss="\t教师信息\n";
            string s;
            for (auto i : tea)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                    s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.department+" "+i.profession+" "+i.title+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else
        {
            QString ss="\t教师信息\n";
            string s;
            for (auto i : tea)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "女")
                    s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.department+" "+i.profession+" "+i.title+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
    }
    return "";
}

QString system::output2(bool x,int y)
{
    if(x==1)
    {
        if(y==0||y==30||y==6)
        {
            QString ss="\t实验员信息\n";
            string s;
            for (auto i : ass)
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.lab+" "+i.work+"\n";
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else if(y==15)
        {
            QString ss="\t实验员信息\n";
            string s;
            for (auto i : ass)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.lab+" "+i.work+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else
        {
            QString ss="\t实验员信息\n";
            string s;
            for (auto i : ass)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "女")
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.lab+" "+i.work+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
    }
    return "";
}

QString system::output3(bool x,int y)
{
    if(x==1)
    {
        if(y==0||y==30||y==6)
        {
            QString ss="\t行政人员信息\n";
            string s;
            for (auto i : sta)
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.office+" "+i.work+"\n";
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else if(y==15)
        {
            QString ss="\t行政人员信息\n";
            string s;
            for (auto i : sta)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.office+" "+i.work+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else
        {
            QString ss="\t行政人员信息\n";
            string s;
            for (auto i : sta)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "女")
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.office+" "+i.work+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
    }
    return "";
}

QString system::output4(bool x,int y)
{
    if(x==1)
    {
        if(y==0||y==30||y==6)
        {
            QString ss="\t教师兼行政人员信息\n";
            string s;
            for (auto i : tst)
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.office+" "+i.department+" "+i.profession+" "+i.title+"\n";
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else if(y==15)
        {
            QString ss="\t教师兼行政人员信息\n";
            string s;
            for (auto i : tst)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.office+" "+i.department+" "+i.profession+" "+i.title+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
        else
        {
            QString ss="\t教师兼行政人员信息\n";
            string s;
            for (auto i : tst)
            {
                if(QString(QString::fromLocal8Bit(i.sex.c_str())) == "女")
                s+=i.id+" "+i.name+" "+i.sex+" "+i.age+" "+i.office+" "+i.department+" "+i.profession+" "+i.title+"\n";
            }
            ss+= QString(QString::fromLocal8Bit(s.c_str()));
            return ss;
        }
    }
    return "";
}






bool system::del(string t)
{
        for (auto i = tea.begin(); i != tea.end(); ++i)
            if ((*i).id == t || (*i).name == t)
            {
                setinit s;
                s.id=QString(QString::fromLocal8Bit((*i).id.c_str()));
                s.name=QString(QString::fromLocal8Bit((*i).name.c_str()));
                s.sex=QString(QString::fromLocal8Bit((*i).sex.c_str()));
                s.age=QString(QString::fromLocal8Bit((*i).age.c_str()));
                s.profession=QString(QString::fromLocal8Bit((*i).profession.c_str()));
                s.office="0";
                s.department=QString(QString::fromLocal8Bit((*i).department.c_str()));
                s.title=QString(QString::fromLocal8Bit((*i).title.c_str()));
                s.work="0";
                s.lab="0";
                s.status=s1;
                s.intst = 0;
                add(s);
                tea.erase(i);
                return 1;
            }
        for (auto i = ass.begin(); i != ass.end(); ++i)
            if ((*i).id == t || (*i).name == t)
            {
                setinit s;
                s.id=QString(QString::fromLocal8Bit((*i).id.c_str()));
                s.name=QString(QString::fromLocal8Bit((*i).name.c_str()));
                s.sex=QString(QString::fromLocal8Bit((*i).sex.c_str()));
                s.age=QString(QString::fromLocal8Bit((*i).age.c_str()));
                s.profession="0";
                s.office="0";
                s.department="0";
                s.title="0";
                s.work=QString(QString::fromLocal8Bit((*i).work.c_str()));
                s.lab=QString(QString::fromLocal8Bit((*i).lab.c_str()));
                s.status=s2;
                    s.intst = 1;
                add(s);
                ass.erase(i);
                return 1;
            }
        for (auto i = sta.begin(); i != sta.end(); ++i)
            if ((*i).id == t || (*i).name == t)
            {
                setinit s;
                s.id=QString(QString::fromLocal8Bit((*i).id.c_str()));
                s.name=QString(QString::fromLocal8Bit((*i).name.c_str()));
                s.sex=QString(QString::fromLocal8Bit((*i).sex.c_str()));
                s.age=QString(QString::fromLocal8Bit((*i).age.c_str()));
                s.profession="0";
                s.office=QString(QString::fromLocal8Bit((*i).office.c_str()));
                s.department="0";
                s.title="0";
                s.work=QString(QString::fromLocal8Bit((*i).work.c_str()));
                s.lab="0";
                s.status=s3;
                    s.intst = 2;
                add(s);
                sta.erase(i);
                return 1;
            }
        for (auto i = tst.begin(); i != tst.end(); ++i)
            if ((*i).id == t || (*i).name == t)
            {
                setinit s;
                s.id=QString(QString::fromLocal8Bit((*i).id.c_str()));
                s.name=QString(QString::fromLocal8Bit((*i).name.c_str()));
                s.sex=QString(QString::fromLocal8Bit((*i).sex.c_str()));
                s.age=QString(QString::fromLocal8Bit((*i).age.c_str()));
                s.profession=QString(QString::fromLocal8Bit((*i).profession.c_str()));
                s.office=QString(QString::fromLocal8Bit((*i).office.c_str()));
                s.department=QString(QString::fromLocal8Bit((*i).department.c_str()));
                s.title=QString(QString::fromLocal8Bit((*i).title.c_str()));
                s.work=QString(QString::fromLocal8Bit((*i).work.c_str()));
                s.lab="0";
                s.status=s4;
                    s.intst = 3;
                add(s);
                tst.erase(i);
                return 1;
            }
        return 0;

    }




cal system::calc()
    {
        cal sum;
        //string t = "男 ";
        unsigned long long cnt1 = tea.size(), cnt2 = ass.size(), cnt3 = sta.size(), cnt4 = tst.size();
        unsigned long long summ = num();
        unsigned long long tt = 0;
        for (auto i : tea)
            if (QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                tt++;
        for (auto i : ass)
            if (QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                tt++;
        for (auto i : sta)
            if (QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                tt++;
        for (auto i : tst)
            if (QString(QString::fromLocal8Bit(i.sex.c_str())) == "男")
                tt++;
        sum.tean =cnt1 ;
        sum.assn =cnt2 ;
        sum.stan = cnt3 ;
        sum.tstn = cnt4 ;
        sum.alln = summ ;
        sum.maln = tt;
        sum.femn =summ-tt ;
        return sum;
    }










void system::save(string s)
{
        ofstream out(s, ios::out);
        extern QString password;
        string pass = qstr2str(password);
        out<<pass<<endl;
        out << qstr2str(s1) << endl;
        for (auto i : tea)
            out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.department << " " << i.profession << " " << i.title << endl;
        out << endl;
        out << qstr2str(s2) << endl;
        for (auto i : ass)
            out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.lab << " " << i.work << endl;
        out << endl;
        out <<  qstr2str(s3) << endl;
        for (auto &i : sta)
            out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.office << " " << i.work << endl;
        out << endl;
        out <<  qstr2str(s4)  << endl;
        for (auto &i : tst)
            out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.department << " " << i.profession << " " << i.title<<" "<<i.office <<" "<<i.work << endl;
    }









void system::exportf(string s)
{
    ofstream out(s, ios::out);
    out << qstr2str(s1) << endl << "ID        " <<qstr2str(" 姓名 ")<<qstr2str(" 性别 ")<<qstr2str(" 年龄 ")<<qstr2str("     系部     ")<<qstr2str("     专业     ")<<qstr2str(" 职称 ")<<endl;
    for (auto i : tea)
        out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.department << " " << i.profession << " " << i.title << endl;
    out << endl;
    out << qstr2str(s2) << endl << "ID        " <<qstr2str(" 姓名 ")<<qstr2str(" 性别 ")<<qstr2str(" 年龄 ")<<qstr2str("     实验室     ")<<qstr2str("     职务     ")<<endl;
    for (auto i : ass)
        out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.lab << " " << i.work << endl;
    out << endl;
    out << qstr2str(s3) << endl << "ID        " <<qstr2str(" 姓名 ")<<qstr2str(" 性别 ")<<qstr2str(" 年龄 ")<<qstr2str("     办公室     ")<<qstr2str("     职务     ")<<endl;
    for (auto &i : sta)
        out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.office << " " << i.work << endl;
    out << endl;
    out << qstr2str(s4) << endl << "ID        " <<qstr2str(" 姓名 ")<<qstr2str(" 性别 ")<<qstr2str(" 年龄 ")<<qstr2str("     系部     ")<<qstr2str("     专业     ")<<qstr2str(" 职称 ")<<qstr2str("     办公室     ")<<qstr2str("     职务     ")<<endl;
    for (auto &i : tst)
        out << i.id << " " << i.name << " " << i.sex << " " << i.age << " " << i.department << " " << i.profession << " " << i.title<<" "<<i.office <<" "<<i.work << endl;
}





bool system::open(string s)
    {
        tea.clear();
        sta.clear();
        ass.clear();
        tst.clear();
        ifstream is(s, ios::in);
        string t;
        if (is>>t)
        {
            if(t != qstr2str(s1))
            {
                extern QString password;
                password = QString(QString::fromLocal8Bit(t.c_str()));
                return 0;
            }
            else
            {
                teacher b;
                while (is >> b.id)
                {
                    if (b.id[0] > '9' || b.id[0] < '0')
                        break;
                    is >> b.name >> b.sex >> b.age >> b.department >> b.profession >> b.title;
                    tea.push_back(b);
                }
            }
        }
        if (1)
        {
            assistant b;
            while (is >> b.id)
            {
                if (b.id[0] > '9' || b.id[0] < '0')
                    break;
                is >> b.name >> b.sex >> b.age >> b.lab >> b.work;
                ass.push_back(b);
            }
        }
        if (1)
        {
            staff b;
            while (is >> b.id)
            {
                if (b.id[0] > '9' || b.id[0] < '0')
                    break;
                is >> b.name >> b.sex >> b.age >> b.office >> b.work;
                sta.push_back(b);
            }
        }
        if (1)
        {
            tstaff b;
            while (is >> b.id)
            {
                if (b.id[0] > '9' || b.id[0] < '0')
                    break;
                is >> b.name >> b.sex >> b.age >> b.department >> b.profession >> b.title >>b.office >> b.work;
                tst.push_back(b);
            }
        }
        is.close();
        return 1;
    }


void system::openff(string s)
    {
        tea.clear();
        sta.clear();
        ass.clear();
        tst.clear();
        ifstream is(s, ios::in);
        string t;
        if (is>>t)
        {
            is>>t;
                teacher b;
                while (is >> b.id)
                {
                    if (b.id[0] > '9' || b.id[0] < '0')
                        break;
                    is >> b.name >> b.sex >> b.age >> b.department >> b.profession >> b.title;
                    tea.push_back(b);
                }

        }
        if (1)
        {
            assistant b;
            while (is >> b.id)
            {
                if (b.id[0] > '9' || b.id[0] < '0')
                    break;
                is >> b.name >> b.sex >> b.age >> b.lab >> b.work;
                ass.push_back(b);
            }
        }
        if (1)
        {
            staff b;
            while (is >> b.id)
            {
                if (b.id[0] > '9' || b.id[0] < '0')
                    break;
                is >> b.name >> b.sex >> b.age >> b.office >> b.work;
                sta.push_back(b);
            }
        }
        if (1)
        {
            tstaff b;
            while (is >> b.id)
            {
                if (b.id[0] > '9' || b.id[0] < '0')
                    break;
                is >> b.name >> b.sex >> b.age >> b.department >> b.profession >> b.title >>b.office >> b.work;
                tst.push_back(b);
            }
        }
        is.close();
    }



