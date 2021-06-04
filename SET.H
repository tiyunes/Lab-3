#ifndef SET_H
#define SET_H
#include <functional>
#include "BinaryTree.h"
#include "SEQUENCE.H"

template<class T>
class Set: public BinaryTree<T>
{
    public:
        Set()
        {
            this->items = new BinaryTree<T>();
        }

        Set(BinaryTree<T>& tree)
        {
            this->items = new BinaryTree<T>(tree);
        }

        Set(Set<T>& s)
        {
            this->items = new BinaryTree<T>(s.GetItems());
        }

        Set(Sequence<T>* elements)
        {
            this->items = new BinaryTree<T>(elements);
        }

        int GetSize()
        {
            return this->items->GetSize();
        }

        T Get(int index)
        {
            Sequence<T>* s = (Sequence<T>*) new LinkedListSequence<T>(this->GetSize());
            s = this->ItemsSequence();
            return s->Get(index);
        }

        Sequence<T>* ItemsSequence()
        {
            return this->GetItems()->SaveToSequence();
        }

        bool Contains(T element)
        {
            return this->items->Contains(element);
        }

        bool IsEmpty()
        {
            return this->GetSize() == 0;
        }

        void Add(T element)
        {
            this->items->Add(element);
        }

        Set<T>* Balance()
        {
            Set<T>* balanceSet = new Set<T>();
            balanceSet->items = this->items->Balance();
            return balanceSet;
        }

        void Remove(T element)
        {
            this->items->Remove(element);
        }

        void Clear()
        {
            this->items->Clear();
        }

        Set<T>* Map(function<T(T)> f)
        {
            Set<T>* setMap = new Set<T>();
            setMap->items = this->items->Map(f);
            return setMap;
        }

        Set<T>* Where(function<bool(T)> f)
        {
            Set<T>* setWhere = new Set<T>();
            setWhere->items = this->items->Where(f);
            return setWhere;
        }

        T Reduce(function<T(T, T)> f)
        {
            return this->items->Reduce(f);
        }

        bool operator==(Set<T>* s)
        {
            return this->items == s->items;
        }

        Set<T>* Union(Set<T>* s)
        {
            Set<T>* unionSet = new Set<T>();
            for (int j = 0; j < s->GetSize(); j++)
            {
                unionSet->Add(s->Get(j));
            }
            Sequence<T>* sequence = (Sequence<T>*) new LinkedListSequence<T>(this->GetSize());
            sequence = this->ItemsSequence();
            for (int i = 0; i < this->GetSize(); i++)
            {
                if (unionSet->Contains(sequence->Get(i)) == false)
                {
                    unionSet->Add(sequence->Get(i));
                }
            }
            return unionSet;
        }

        Set<T>* Intersection(Set<T>* s)
        {
            Set<T>* intersectionSet = new Set<T>();
            Sequence<T>* sequenceThis = (Sequence<T>*) new LinkedListSequence<T>(this->GetSize());
            sequenceThis = this->ItemsSequence();
            Sequence<T>* sequenceS = (Sequence<T>*) new LinkedListSequence<T>(s->GetSize());
            sequenceS = s->ItemsSequence();
            for (int i = 0; i < s->GetSize(); i++)
            {
                if (this->Contains(sequenceS->Get(i)))
                {
                    intersectionSet->Add(sequenceS->Get(i));
                }
            }
            for (int j = 0; j < this->GetSize(); j++)
            {
                if (s->Contains(sequenceThis->Get(j)) && !(intersectionSet->Contains(sequenceThis->Get(j))))
                {
                    intersectionSet->Add(sequenceS->Get(j));
                }
            }
            return intersectionSet;
        }

        Set<T>* Subtraction(Set<T>* s)
        {
            Set<T>* subtractionSet = new Set<T>();
            for (int j = 0; j < this->GetSize(); j++)
            {
                subtractionSet->Add(this->Get(j));
            }
            Sequence<T>* sequence = (Sequence<T>*) new LinkedListSequence<T>(s->GetSize());
            sequence = s->ItemsSequence();
            for (int i = 0; i < s->GetSize(); i++)
            {
                if (this->Contains(sequence->Get(i)) == true)
                {
                    subtractionSet->Remove(sequence->Get(i));
                }
            }
            return subtractionSet;
        }

    public:
        BinaryTree<T>* GetItems()
        {
            return this->items;
        }

    private:
        BinaryTree<T>* items;
};

#endif // SET_H
