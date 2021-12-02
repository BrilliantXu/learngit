#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

class Person {
friend ostream & operator<<( ostream &out, Person a1);
private:
    int num;
    string name;
    string job;
    string work;
    
public:
    friend class CMD;
    Person() {
        num = -1;
        name = "0";
        job = "0";
        work = "0";
    }
    Person(int & num1, string &name1, string &job1, string &work1){
        num = num1;
        name = name1;
        job = job1;
        work = work1;

    }

    void display() {
        cout << num << " : "<< name << " : " << job << " : " << work <<endl;
    }

    void numchange(int &s){ num = s; }
    virtual void namechange(string &s){ name = s; }
    void jobchange(string &s){ job = s; }
    void workchange(string &s){ work = s; }
    friend void workerchange();

};

class Worker:public Person {
    using Person::Person;
    void workerchange(Worker* W1, string &temp) {
        W1->namechange(temp);
    }

};

class Manger:public Person {
    using Person::Person;
    void workerchange(Manger* W1, string &temp) {
        W1->namechange(temp);
    }

};

class BOSS:public Person {
    using Person::Person;
    void workerchange(Worker* W1, string &temp) {
        W1->namechange(temp);
    }

};


class EmpSqlist{
public:
    struct ESqlist{
    Person data;
    ESqlist *nest;
    };

    ESqlist *head;
    ESqlist *top = head;

    EmpSqlist() {
        head = new ESqlist;
        head->data = Person();
        head->nest = NULL;
    }

    bool  EmpInsert(int i, Person* data) {
        ESqlist *t = head;
        int j = 0;
        if(t == NULL)return false;
        if(i < 1)return false;
        while(t && j < i-1){
            t = t->nest; j++;   
        }
        ESqlist *temp = new ESqlist;
        temp->nest = t->nest;
        temp->data = *data;
        t->nest = temp;
        return true;
    }

    bool EmpGet(int i, Person &recv) {  //将引用改成地址为什么就不行？参数的传递不成功。why 就是因为在声
        int j = 0;                      //明结构指针的时候，并没有开辟地址，所以要用new函数创建一个函数的实例
        ESqlist *temp = head;
        if (i < 0) return false;
        while (temp && j < i) {
            temp = temp->nest;
            j++;
        }
        if (!temp) { return false;}
        if (i==j) {
            recv = (temp->data);
            return true;
        }
        return false;
    }


    bool EmpDelete(int i) {
        int j = 0;                      //明结构指针的时候，并没有开辟地址，所以要用new函数创建一个函数的实例
        ESqlist *temp = head;
        if (i < 0) return false;
        while (temp && j < i-1) {
            temp = temp->nest;
            j++;
        }
        if (!temp) { return false;}
        if (j==i-1) {
            temp->nest = temp->nest->nest;
            delete temp->nest;
            return true;
        }
        return false;
    }


    bool EmpShow(int i) {
        int j = 0;                      //明结构指针的时候，并没有开辟地址，所以要用new函数创建一个函数的实例
        ESqlist *temp = head;
        if (i < 0) return false;
        while (temp && j < i) {
            temp = temp->nest;
            j++;
        }
        if (!temp) { return false;}
        if (j==i) {
            cout << (temp->data);
            return true;
        }
        return false;
    }

};

    ostream & operator<<( ostream &out, Person a1) {
        out << a1.num << " : "<< a1.name << " : " << a1.job << " : " << a1.work;
        return out;
    }


class CMD {
public:   
    int *Key_Input() {
       int *a =  new int;
       cin >> *a;
        if(*a < 0 || *a > 9) {
            cout << "The input was not allowed  please try again!" <<endl;
            return NULL;
        }
       return a; 
    }

    void show() {
        cout << "****************************************"<< endl;
        cout << "*****Welcome to the configration********"<< endl;
        cout << "*************0.退出管理系统**************"<< endl;
        cout << "*************1.增加职工信息**************"<< endl;
        cout << "*************2.删除离职职工**************"<< endl;
        cout << "*************3.修改职工信息**************"<< endl;
        cout << "*************4.查找职工信息**************"<< endl;
        cout << "*************5.按照编号排序**************"<< endl;
        cout << "*************6.清空管理系统**************"<< endl;
        cout << "*************7.显示职工信息**************"<< endl;
        cout << "*************8.XD不知道干嘛**************"<< endl;
        cout << "****************************************"<< endl;             
    }

    int  quit() {
        cout << "  SEE U  " << endl; 
        int i;
        cin >>  i;
        exit(0);
    }




};



int main() {
    // CMD a1;
    // int Key_in = *a1.Key_Input();
    // cout << "   " << Key_in<< "  Confirm!" << endl;

    EmpSqlist a1;
    int i1 = 123;
    int i2 = 321;
    string s1 = "sanzhang";
    Person *P1 = new Person(i1, s1, s1, s1) ;
    Person *P2 = new Person(i2, s1, s1, s1) ;
    Person P3;
    a1.EmpInsert(1,P1);
    a1.EmpInsert(2,P2);;
    P3.display();
    a1.EmpGet(1,P3);
    P3.display();
    a1.EmpGet(2,P3);
    P3.display();
    a1.EmpDelete(1);
    a1.EmpShow(1);
    return 0;
}