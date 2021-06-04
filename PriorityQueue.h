#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "BinaryTree.h"
#include "STUDENTS.H"
#include "TEACHER.H"
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>

template<class T, class K>
class PriorityQueue
{
    public:
        PriorityQueue()
        {
            this->elements = new BinaryTree<T>();
            this->priority = vector<pair<K, T>>(0);
        }

        PriorityQueue(Sequence<T>* s, vector<pair<K, T>> v)
        {
            this->elements = new BinaryTree<T>(s);
            this->priority = v;
        }

        PriorityQueue(PriorityQueue<T, K>, vector<pair<K, T>> queueP)
        {
            this->elements = new BinaryTree<T>();
            this->elements = queueP->elements;
            this->priority = queueP.priority;
        }

        T FindMax()
        {
            T maxElement;
            vector<K> v(0);
            for (int i = 0; i < this->GetSize(); i++)
            {
                v.push_back(this->priority[i].first);
            }
            sort(v.begin(), v.end());
            K maxPriority = v.back();
            for (int i = 0; i < this->GetSize(); i++)
            {
                if (this->priority[i].first == maxPriority)
                {
                    maxElement = this->priority[i].second;
                    break;
                }
            }
            return maxElement;
        }

        T Top()
        {
            return this->FindMax();
        }

        int GetSize()
        {
            return this->elements->GetSize();
        }

        BinaryTree<T>* GetElements()
        {
            return this->elements;
        }

        vector<pair<K, T>> GetPriorityVector()
        {
            return this->priority;
        }

        void SetPriorityVector(vector<pair<K, T>> v1)
        {
            this->priority = v1;
        }

        void SetElements(BinaryTree<T>* t)
        {
            this->elements = t;
        }

        K GetPriority(T item)
        {
            K priorityValue;
            BinaryTreeNode<T>* n = new BinaryTreeNode<T>();
            n = this->elements->Find(item);
            for (int i = 0; i < this->priority.size(); i++)
            {
                if (this->priority[i].second == n->Get())
                {
                    priorityValue = this->priority[i].first;
                    break;
                }
            }
            return priorityValue;
        }

        bool IsEmpty()
        {
            return this->elements->IsEmpty();
        }

        void Push(T item, K priorityValue)
        {
            this->elements->Add(item);
            pair<K, T> p1;
            p1.first = priorityValue;
            p1.second = item;
            this->priority.push_back(p1);
        }

        void Pop(T item)
        {
            sort(this->priority.begin(), this->priority.end());
            this->priority.pop_back();
            this->elements->Remove(item);
            Sequence<int>* s = (Sequence<int>*) new LinkedListSequence<int>(this->GetSize());
            s = this->GetElements()->SaveToSequence();
        }

        void Pop()
        {
            this->Pop(this->FindMax());
        }

        PriorityQueue<T, K>* Map(function<T(T)> f)
        {
            PriorityQueue<T, K>* queueMap = new PriorityQueue<T, K>();
            queueMap->elements = new BinaryTree<T>();
            queueMap->elements = this->elements->Map(f);
            Sequence<T>* s = (Sequence<T>*) new LinkedListSequence<T>(queueMap->GetSize());
            s = queueMap->elements->SaveToSequence();
            Sequence<T>* sThis = (Sequence<T>*) new LinkedListSequence<T>(this->GetSize());
            sThis = this->elements->SaveToSequence();
            for (int i = 0; i < this->GetSize(); i++)
            {
                pair<K, T> p1;
                p1.first = this->GetPriority(sThis->Get(i));
                p1.second = queueMap->elements->Find(s->Get(i))->Get();
                queueMap->priority.push_back(p1);
            }
            return queueMap;
        }

        PriorityQueue<T, K>* Where(function<bool(T)> f)
        {
            PriorityQueue<T, K>* queueWhere = new PriorityQueue<T, K>();
            queueWhere->elements = new BinaryTree<T>();
            queueWhere->elements = this->elements->Where(f);
            Sequence<T>* s = (Sequence<T>*) new LinkedListSequence<T>(queueWhere->GetSize());
            s = queueWhere->elements->SaveToSequence();
            for (int i = 0; i < queueWhere->elements->GetSize(); i++)
            {
                pair<K, T> p1;
                p1.first = queueWhere->GetPriority(s->Get(i));
                p1.second = queueWhere->elements->Find(s->Get(i))->Get();
                queueWhere->priority.push_back(p1);
            }
            return queueWhere;
        }

        T Reduce(function<T(T, T)> f)
        {
            return this->elements->Reduce(f);
        }

        PriorityQueue<T, K>* Concat(PriorityQueue<T, K>* q2)
        {
            PriorityQueue<T, K>* concatQueue = new PriorityQueue<T, K>();
            concatQueue->elements = new BinaryTree<T>();
            Sequence<T>* s1 = (Sequence<T>*) new LinkedListSequence<T>(this->GetSize());
            s1 = this->elements->SaveToSequence();
            Sequence<T>* s2 = (Sequence<T>*) new LinkedListSequence<T>(q2->GetSize());
            s2 = q2->GetElements()->SaveToSequence();
            for (int i = 0; i < this->GetSize(); i++)
            {
                concatQueue->elements->Add(s1->Get(i));
                pair<K, T> p1;
                p1.first = this->GetPriority(s1->Get(i));
                p1.second = this->elements->Find(s1->Get(i))->Get();
                concatQueue->priority.push_back(p1);
            }
            for (int j = 0; j < q2->GetSize(); j++)
            {
                concatQueue->elements->Add(s2->Get(j));
                pair<K, T> p2;
                p2.first = q2->GetPriority(s2->Get(j));
                p2.second = q2->GetElements()->Find(s2->Get(j))->Get();
                concatQueue->priority.push_back(p2);
            }
            return concatQueue;
        }

        ~PriorityQueue() = default;

    protected:

    private:
        BinaryTree<T>* elements;
        vector<pair<K, T>> priority;
};

#endif // PRIORITYQUEUE_H
