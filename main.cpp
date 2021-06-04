#include <iostream>
#include <string>
#include <functional>
#include <cassert>
#include <stdexcept>
#include <complex>
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include "SET.H"
#include "BinaryTree.h"
#include "PriorityQueue.h"
#include "STUDENTS.H"
#include "TEACHER.H"

using namespace std;

int Product(int item)
{
    return 2 * item;
}

bool IsEven(int item)
{
    if (item % 2 == 0)
    {
        return true;
    }
    else return false;
}

int Sum (int a, int b)
{
    return a + b;
}

void TestSet()
{
    try
    {
        Set<int>* s1 = new Set<int>();
        assert(s1->IsEmpty() == 1);
        int a = 8; int b = 3; int c = 10; int d = 1; int e = 6; int f = 4;
        int i = 7; int g = 11; int k = 14; int l = 13; int m = 20;
        int v;
        s1->Add(a);
        assert(s1->Contains(a) == 1);
        s1->Add(b);
        assert(s1->Contains(b) == 1);
        assert(s1->GetSize() == 2);
        assert(s1->IsEmpty() == 0);
        s1->Add(c);
        assert(s1->Contains(a) && s1->Contains(b) && s1->Contains(c) == 1);
        s1->Add(d); s1->Add(e); s1->Add(f); s1->Add(i);
        s1->Add(g); s1->Add(k); s1->Add(l);
        assert(s1->GetSize() == 10);
        assert(s1->IsEmpty() == 0);
        s1->Remove(l);
        assert(s1->Contains(l) == 0);
        assert(s1->GetSize() == 9);
        assert(s1->IsEmpty() == 0);
        s1->Add(l);

        Set<int>* s2 = new Set<int>();
        s2->Add(a); s2->Add(b); s2->Add(c);
        s2->Add(d); s2->Add(e); s2->Add(m);
        assert(s2->Contains(a) == 1);
        assert(s2->Contains(b) == 1);
        assert(s2->Contains(c) == 1);
        assert(s2->Contains(d) == 1);
        assert(s2->Contains(e) == 1);
        assert(s2->Contains(m) == 1);
        assert(s2->GetSize() == 6);
        assert(s2->IsEmpty() == 0);
        assert((s1 == s2) == 0);

        Set<int>* sUnion = new Set<int>();
        sUnion = s1->Union(s2);
        assert(sUnion->Contains(a) == 1);
        assert(sUnion->Contains(b) == 1);
        assert(sUnion->Contains(c) == 1);
        assert(sUnion->Contains(d) == 1);
        assert(sUnion->Contains(e) == 1);
        assert(sUnion->Contains(f) == 1);
        assert(sUnion->Contains(g) == 1);
        assert(sUnion->Contains(i) == 1);
        assert(sUnion->Contains(k) == 1);
        assert(sUnion->Contains(l) == 1);
        assert(sUnion->Contains(m) == 1);
        assert(sUnion->GetSize() == 11);
        assert(sUnion->IsEmpty() == 0);

        Set<int>* sIntersection = new Set<int>();
        sIntersection= s1->Intersection(s2);
        assert(sIntersection->Contains(a) == 1);
        assert(sIntersection->Contains(b) == 1);
        assert(sIntersection->Contains(c) == 1);
        assert(sIntersection->Contains(d) == 1);
        assert(sIntersection->Contains(e) == 1);
        assert(sIntersection->Contains(f) == 0);
        assert(sIntersection->Contains(g) == 0);
        assert(sIntersection->Contains(i) == 0);
        assert(sIntersection->Contains(k) == 0);
        assert(sIntersection->Contains(l) == 0);
        assert(sIntersection->Contains(m) == 0);
        assert(sIntersection->GetSize() == 5);
        assert(sIntersection->IsEmpty() == 0);

        Set<int>* sSubtraction = new Set<int>();
        sSubtraction = s1->Subtraction(s2);
        assert(sSubtraction->Contains(a) == 0);
        assert(sSubtraction->Contains(b) == 0);
        assert(sSubtraction->Contains(c) == 0);
        assert(sSubtraction->Contains(d) == 0);
        assert(sSubtraction->Contains(e) == 0);
        assert(sSubtraction->Contains(f) == 1);
        assert(sSubtraction->Contains(g) == 1);
        assert(sSubtraction->Contains(i) == 1);
        assert(sSubtraction->Contains(k) == 1);
        assert(sSubtraction->Contains(l) == 1);
        assert(sSubtraction->Contains(m) == 0);
        assert(sSubtraction->GetSize() == 5);
        assert(sSubtraction->IsEmpty() == 0);

        function<int(int)> Product2 = Product;
        Set<int>* sMap = new Set<int>();
        sMap = s1->Map(Product2);
        assert(sMap->Contains(2*a) == 1);
        assert(sMap->Contains(2*b) == 1);
        assert(sMap->Contains(2*c) == 1);
        assert(sMap->Contains(2*d) == 1);
        assert(sMap->Contains(2*e) == 1);
        assert(sMap->Contains(2*f) == 1);
        assert(sMap->Contains(2*i) == 1);
        assert(sMap->Contains(2*g) == 1);
        assert(sMap->Contains(2*k) == 1);
        assert(sMap->Contains(2*l) == 1);
        assert(sMap->GetSize() == s1->GetSize());
        assert(sMap->IsEmpty() == 0);

        function<bool(int)> Even = IsEven;
        Set<int>* sWhere = new Set<int>();
        sWhere = s1->Where(Even);
        assert(sWhere->Contains(a) == 1);
        assert(sWhere->Contains(b) == 0);
        assert(sWhere->Contains(c) == 1);
        assert(sWhere->Contains(d) == 0);
        assert(sWhere->Contains(e) == 1);
        assert(sWhere->Contains(f) == 1);
        assert(sWhere->Contains(g) == 0);
        assert(sWhere->Contains(i) == 0);
        assert(sWhere->Contains(k) == 1);
        assert(sWhere->Contains(l) == 0);
        assert(sWhere->Contains(m) == 0);

        function<int(int, int)> action3 = Sum;
        int resultReduce = s1->Reduce(action3);
        assert(resultReduce == 78);

        Set<Student>* sStudent = new Set<Student>();
        StudentID* id1 = new StudentID(1, 2);
        string* firstName = new string("Ivan");
        string* lastName = new string("Ivanov");
        Student student1(id1, firstName, lastName);
        StudentID* id2 = new StudentID(3, 4);
        string* firstName2 = new string("Alex");
        string* lastName2 = new string("Smith");
        Student student2(id2, firstName2, lastName2);
        StudentID* id3 = new StudentID(8, 2);
        string* firstName3 = new string("Kevin");
        string* lastName3 = new string("Isner");
        Student student3(id3, firstName3, lastName3);
        sStudent->Add(student1);
        sStudent->Add(student2);
        assert(sStudent->Contains(student1) == 1);
        assert(sStudent->Contains(student2) == 1);
        assert(sStudent->Contains(student3) == 0);
        assert(sStudent->GetSize() == 2);
        assert(sStudent->IsEmpty() == 0);

        Set<Teacher>* sTeacher = new Set<Teacher>();
        TeacherID* id4 = new TeacherID(1, 2);
        string* firstName4 = new string("Ilya");
        string* lastName4 = new string("Butusov");
        string* subject1 = new string("Math");
        Teacher t1(id4, firstName4, lastName4, subject1);
        TeacherID* id5 = new TeacherID(3, 4);
        string* firstName5 = new string("Matvey");
        string* lastName5 = new string("Popov");
        string* subject2 = new string("Phys");
        Teacher t2(id5, firstName5, lastName5, subject2);
        TeacherID* id6 = new TeacherID(3, 4);
        string* firstName6 = new string("Ivan");
        string* lastName6 = new string("Sidorov");
        string* subject3 = new string("Chem");
        Teacher t3(id6, firstName6, lastName6, subject3);
        sTeacher->Add(t1);
        sTeacher->Add(t2);
        assert(sTeacher->Contains(t1) == 1);
        assert(sTeacher->Contains(t2) == 1);
        assert(sTeacher->Contains(t3) == 0);
        assert(sTeacher->GetSize() == 2);
        assert(sTeacher->IsEmpty() == 0);

        Set<float>* sFloat = new Set<float>();
        assert(sFloat->IsEmpty() == 1);
        float f1 = 1.2;
        float f2 = 3.71;
        float f3 = 11.4;
        float f4 = 0.8883;
        float f5 = 5.901;
        sFloat->Add(f1);
        sFloat->Add(f2);
        sFloat->Add(f3);
        sFloat->Add(f4);
        assert(sFloat->Contains(f1) == 1);
        assert(sFloat->Contains(f2) == 1);
        assert(sFloat->Contains(f3) == 1);
        assert(sFloat->Contains(f4) == 1);
        assert(sFloat->Contains(f5) == 0);
        assert(sFloat->GetSize() == 4);
        assert(sFloat->IsEmpty() == 0);
        sFloat->Clear();
        assert(sFloat->IsEmpty() == 1);

        Set<int>* sBig = new Set<int>();
        int j;
        auto start1 = chrono::high_resolution_clock::now();
        for (j = 0; j < 10000; j++)
        {
            sBig->Add(j);
        }
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end1 - start1;
        float time4 = duration.count(); //3.58933 for 10000 elements
        cout << "Set tests are correct" << endl;
    }
    catch(out_of_range &e)
    {
        cout << e.what() << endl;
    }
}

void TestPriorityQueue()
{
    try
    {
        int a = 8; int b = 3; int c = 10; int d = 1; int e = 6; int f = 4;
        int i = 7; int g = 11; int k = 14; int l = 13; int m = 20;
        PriorityQueue<int, int>* q1 = new PriorityQueue<int, int>();
        assert(q1->IsEmpty() == 1);
        q1->Push(a, 1);
        assert(q1->Top() == a);
        assert(q1->GetPriority(q1->Top()) == 1);
        q1->Push(b, 4);
        assert(q1->Top() == b);
        assert(q1->GetPriority(q1->Top()) == 4);
        q1->Push(c, 3);
        assert(q1->Top() == b);
        assert(q1->GetPriority(q1->Top()) == 4);
        assert(q1->GetSize() == 3);
        assert(q1->IsEmpty() == 0);
        q1->Pop();
        assert(q1->Top() == c);
        assert(q1->GetPriority(q1->Top()) == 3);
        assert(q1->GetSize() == 2);
        assert(q1->IsEmpty() == 0);
        q1->Push(d, 0);
        assert(q1->Top() == c);
        assert(q1->GetPriority(q1->Top()) == 3);
        assert(q1->GetSize() == 3);
        assert(q1->IsEmpty() == 0);

        function<int(int)> Product2 = Product;
        PriorityQueue<int, int>* qMap = new PriorityQueue<int, int>();
        qMap = q1->Map(Product2);
        assert(qMap->Top() == 2*c);
        assert(qMap->GetPriority(qMap->Top()) == 3);
        assert(qMap->GetSize() == 3);
        assert(qMap->IsEmpty() == 0);
        cout << endl;

        PriorityQueue<int, int>* q2 = new PriorityQueue<int, int>();
        assert(q2->IsEmpty() == 1);
        q2->Push(e, 10);
        assert(q2->Top() == e);
        assert(q2->GetPriority(q2->Top()) == 10);
        q2->Push(f, 2);
        assert(q2->Top() == e);
        assert(q2->GetPriority(q2->Top()) == 10);
        q2->Push(i, 5);
        assert(q2->Top() == e);
        assert(q2->GetPriority(q2->Top()) == 10);
        assert(q2->GetSize() == 3);
        assert(q2->IsEmpty() == 0);
        q2->Pop();
        assert(q2->Top() == i);
        assert(q2->GetPriority(q2->Top()) == 5);
        assert(q2->GetSize() == 2);
        assert(q2->IsEmpty() == 0);
        q2->Push(k, 20);
        assert(q2->Top() == k);
        assert(q2->GetPriority(q2->Top()) == 20);
        assert(q2->GetSize() == 3);
        assert(q2->IsEmpty() == 0);

        PriorityQueue<int, int>* qConcat = new PriorityQueue<int, int>();
        Sequence<int>* s = (Sequence<int>*) new LinkedListSequence<int>();
        s = q2->GetElements()->SaveToSequence();
        qConcat = q1->Concat(q2);
        assert(qConcat->Top() == k);
        assert(qConcat->GetPriority(qConcat->Top()) == 20);
        assert(qConcat->GetSize() == 6);
        assert(qConcat->IsEmpty() == 0);

        float f1 = 1.2;
        float f2 = 3.71;
        float f3 = 11.4;
        float f4 = 0.8883;
        float f5 = 5.901;
        PriorityQueue<float, int>* qFloat = new PriorityQueue<float, int>();
        assert(qFloat->IsEmpty() == 1);
        qFloat->Push(f1, 5);
        qFloat->Push(f2, 6);
        qFloat->Push(f3, 2);
        qFloat->Push(f4, 8);
        qFloat->Push(f5, 15);
        assert(qFloat->Top() == f5);
        assert(qFloat->GetPriority(qFloat->Top()) == 15);
        assert(qFloat->GetSize() == 5);
        assert(qFloat->IsEmpty() == 0);

        PriorityQueue<Student, int>* qStudent = new PriorityQueue<Student, int>();
        StudentID* id1 = new StudentID(1, 2);
        string* firstName = new string("Ivan");
        string* lastName = new string("Ivanov");
        Student student1(id1, firstName, lastName);
        StudentID* id2 = new StudentID(3, 4);
        string* firstName2 = new string("Alex");
        string* lastName2 = new string("Smith");
        Student student2(id2, firstName2, lastName2);
        StudentID* id3 = new StudentID(8, 2);
        string* firstName3 = new string("Kevin");
        string* lastName3 = new string("Isner");
        Student student3(id3, firstName3, lastName3);
        qStudent->Push(student1, 7);
        qStudent->Push(student2, 2);
        assert(qStudent->Top() == student1);
        assert(qStudent->GetPriority(qStudent->Top()) == 7);
        assert(qStudent->GetSize() == 2);
        assert(qStudent->IsEmpty() == 0);

        PriorityQueue<Teacher, int>* qTeacher = new PriorityQueue<Teacher, int>();
        TeacherID* id4 = new TeacherID(1, 2);
        string* firstName4 = new string("Ilya");
        string* lastName4 = new string("Butusov");
        string* subject1 = new string("Math");
        Teacher t1(id4, firstName4, lastName4, subject1);
        TeacherID* id5 = new TeacherID(3, 4);
        string* firstName5 = new string("Matvey");
        string* lastName5 = new string("Popov");
        string* subject2 = new string("Phys");
        Teacher t2(id5, firstName5, lastName5, subject2);
        TeacherID* id6 = new TeacherID(3, 4);
        string* firstName6 = new string("Ivan");
        string* lastName6 = new string("Sidorov");
        string* subject3 = new string("Chem");
        Teacher t3(id6, firstName6, lastName6, subject3);
        qTeacher->Push(t1, 3);
        qTeacher->Push(t2, 10);
        assert(qTeacher->Top() == t2);
        assert(qTeacher->GetPriority(qTeacher->Top()) == 10);
        assert(qTeacher->GetSize() == 2);
        assert(qTeacher->IsEmpty() == 0);

        cout << "Priority queue tests are correct" << endl;
        cout << endl;
    }
    catch(out_of_range &e)
    {
        cout << e.what() << endl;
    }
}
int main()
{
    try
    {
        TestSet();
        TestPriorityQueue();

        int setSize1, setSize2, i;
        cout << "Enter the number of elements in 1st set: " << endl;
        cin >> setSize1;
        int setElements1[setSize1];
        cout << "Enter the elements of 1st set: " << endl;
        for (i = 0; i < setSize1; i++)
        {
            cin >> setElements1[i];
        }
        Set<int>* s1 = new Set<int>();
        for (i = 0; i < setSize1; i++)
        {
            s1->Add(setElements1[i]);
        }
        cout << "1st set is ready" << endl;
        cout << endl;

        cout << "Enter the number of elements in 2nd set: " << endl;
        cin >> setSize2;
        int setElements2[setSize2];
        cout << "Enter the elements of 2nd set: " << endl;
        for (i = 0; i < setSize2; i++)
        {
            cin >> setElements2[i];
        }
        Set<int>* s2 = new Set<int>();
        for (i = 0; i < setSize2; i++)
        {
            s2->Add(setElements2[i]);
        }
        cout << "2nd set is ready" << endl;
        cout << endl;

        Set<int>* sUnion = new Set<int>();
        sUnion = s1->Union(s2);
        cout << "The size of union of two sets: " << sUnion->GetSize() << endl;
        cout << "The elements of union of two sets: " << endl;
        for (i = 0; i < sUnion->GetSize(); i++)
        {
            cout << sUnion->Get(i) << endl;
        }
        cout << endl;

        Set<int>* sIntersection = new Set<int>();
        sIntersection = s1->Intersection(s2);
        cout << "The size of intersection of two sets: " << sIntersection->GetSize() << endl;
        cout << "The elements of intersection of two sets: " << endl;
        for (i = 0; i < sIntersection->GetSize(); i++)
        {
            cout << sIntersection->Get(i) << endl;
        }
        cout << endl;

        Set<int>* sSubtraction = new Set<int>();
        sSubtraction = s1->Subtraction(s2);
        cout << "The size of subtraction S1 - S2: " << sSubtraction->GetSize() << endl;
        cout << "The elements of subtraction S1 - S2: " << endl;
        for (i = 0; i < sSubtraction->GetSize(); i++)
        {
            cout << sSubtraction->Get(i) << endl;
        }
        cout << endl;

        PriorityQueue<int, int>* pQueue1 = new PriorityQueue<int, int>();
        PriorityQueue<int, int>* pQueue2 = new PriorityQueue<int, int>();
        int qSize1, qSize2;
        cout << "Enter the size of 1st priority queue: " << endl;
        cin >> qSize1;
        vector<pair<int, int>> v1(qSize1);
        int values1[qSize1];
        int priority1[qSize1];
        for (i = 0; i < qSize1; i++)
        {
            cout << "Enter the value of element: ";
            cin >> values1[i];
            cout << "Enter the priority value of element: ";
            cin >> priority1[i];
            pQueue1->Push(values1[i], priority1[i]);
        }
        cout << "1st priority queue is ready" << endl;
        cout << "Top element of 1st queue: " << pQueue1->Top() << endl;
        cout << "Max priority value of 1st queue: " << pQueue1->GetPriority(pQueue1->Top()) << endl;
        cout << endl;

        cout << "Enter the size of 2nd priority queue: " << endl;
        cin >> qSize2;
        vector<pair<int, int>> v2(qSize2);
        int values2[qSize2];
        int priority2[qSize2];
        for (i = 0; i < qSize2; i++)
        {
            cout << "Enter the value of element: ";
            cin >> values2[i];
            cout << "Enter the priority value of element: ";
            cin >> priority2[i];
            pQueue2->Push(values2[i], priority2[i]);
        }
        cout << "2nd priority queue is ready" << endl;
        cout << "Top element of 2nd queue: " << pQueue2->Top() << endl;
        cout << "Max priority value of 2nd queue: " << pQueue2->GetPriority(pQueue2->Top()) << endl;
        cout << endl;

        PriorityQueue<int, int>* pQueueConcat = new PriorityQueue<int, int>();
        pQueueConcat = pQueue1->Concat(pQueue2);
        cout << "Concat priority queue is ready" << endl;
        cout << "Size of concat queue: " << pQueueConcat->GetSize() << endl;
        cout << "Top element of concat queue: " << pQueueConcat->Top() << endl;
        cout << "Max priority value of concat queue: " << pQueueConcat->GetPriority(pQueueConcat->Top()) << endl;
        cout << endl;

    }
    catch(out_of_range &e)
    {
        cout << e.what() << endl;
    }
}
