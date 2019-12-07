#pragma once
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <vector>

/*
-----------------------------------------------------------------
----------------------DEVELOPMENT PLAN---------------------------
-----------------------------------------------------------------
1.-Write the Priority Queue-Template syntax with everything-
 a. void enqueue(T value, priority_type priority)             |?|
 ---MAKE HEAP LOOK UP LINKS IN ASSIGNMENT					  |X|
 b. auto dequeue()										      |?|
 c. iterator find(T value)								      |?|
 ---write this before the iterator
 ---It doesn't require that the iterator exist beforehand
 d. void update(iterator i, priority_type priority)		      |X|
 ---how to do the update on a vector? Sort by priority?
 e. bool empty()										      |X|
 f. size_type size()									      |X|
 ---count, keep track of enqueues and dequeues
 g.aliases													  |X|
 ---How to do this correctly? Where?
2.Write Iterator-Follow in class code
---Where to write??? Inside Node class? Inside queue class?? Outside??
 a. iterator begin()									      |?|
 b. iterator end()										      |?|
 c. copy constructor									      |?|
 d. move contsructor									      |?|
 e. copy assignment operator							      |?|
 f. move assignment operator							      |?|
 g. incrementable										      |?|
 h. dereferenceable										      |?|
 i. relational operators									  |?|
-----------------------------------------------------------------
*/

namespace usu
{
    template <typename T, typename T1 = unsigned int>
    class pqNode
    {
      public:
        pqNode(T val, T1 pri)
        {
            value = val;
            priority = pri;
        }

        T getValue()
        {
            return value;
        }

        T1 getPriority()
        {
            return priority;
        }

        T value;
        T1 priority;
    };

    template <typename T, typename T1 = unsigned int>
    class priority_queue
    {
      public:
        using priority_type = T1;
        using value_type = T;
        using size_type = size_t;
        using pointer = T*;
        using reference = T&;
        using r_reference = T&&;

        priority_queue() = default;

        priority_queue(std::initializer_list<T> list)
        {
            size_type pos = 0;
            for (auto i = list.begin(); i != list.end(); ++i, ++pos)
            {
                queue[pos] = *i;
            }
        }

        //If the node is a leaf node
        //Def works if given the count and not the exact index. AKA give it index + 1
        bool isLeaf(int pos)
        {
            bool returnVal = pos > countNodes / 2 && pos <= countNodes;
            return returnVal;
        }

        // Return position of parent given child
        //Def works if given the count and not the exact index. AKA give it index + 1
        int parent(int pos)
        {
            if (pos <= 0)
                return -1;
            pos = static_cast<double>(pos);
            return std::round((pos - 1.0) / 2.0);
        }

        // Return position for left child of pos
        //Def works if given the count and not the exact index. AKA give it index + 1
        int leftchild(int pos)
        {
            return 2 * pos;
        }

        // Return position for right child of pos
        //Def works if given the count and not the exact index. AKA give it index + 1
        int rightchild(int pos)
        {
            return 2 * pos + 1;
        }

        // Put element in its correct place
        void siftdown(int pos)
        {
            while (!isLeaf(pos))
            {
                //set a current node and its index
                //find it's largest child
                //swap the current node with its child
                //move to that node
                int j;
                if (rightchild(pos).priority > leftchild(pos).priority)
                {
                    j = rightchild(pos);
                }
                else
                {
                    j = leftchild(pos);
                }

                if (queue[pos].priority < queue[j].priority)
                {
                    pqNode<T, T1> temp = queue[pos];
                    queue[pos] = queue[j];
                    queue[j] = temp;
                    pos = j;
                }
                else
                {
                    pos = j;
                }
            }
        }

        // Put element in its correct place
        void siftup(int pos)
        {
            while (pos != 0)
            {
                //set a current node and its index
                //swap the current node with its parent if it's larger
                //move to that node
                int j = parent(pos);
                if (queue[pos].priority > queue[j].priority)
                {
                    pqNode<T, T1> temp = queue[pos];
                    queue[pos] = queue[j];
                    queue[j] = temp;
                    pos = j;
                }
                else
                {
                    pos = j;
                }
            }
        }

        void enqueue(T value, priority_type priority)
        {
            pqNode<T, T1> nextNode = pqNode<T, T1>(value, priority);
            queue.push_back(nextNode);
            queue[countNodes] = nextNode;
            if (countNodes == 0)
            {
                ++countNodes;
                return;
            }
            int parentPos = parent(countNodes);
            // Now sift up until curr's parent's key > curr's key
            while (countNodes != 0 && queue[countNodes].priority > queue[parentPos].priority)
            {
                pqNode<T, T1> temp = queue[parent(countNodes)];
                queue[parent(countNodes)] = queue[countNodes];
                queue[countNodes] = temp;
            }
            ++countNodes;
            //Is this where I should use the formula new size = (current size) * 1.25 + 1 ?
            //Why not just push back?
            //Upon thinking about it I thought it would work if i push_back everytime I enqueue and pop_back everytime I dequeue so I didn't end up using the formula
        }

        pqNode<T, T1> dequeue()
        {
            if (empty())
            {
                throw "The queue is empty!";
            }
            else
            {
                //When i do the decrement first it accesses the real last element and not one past the end
                --countNodes;
                //swap first and last element
                pqNode<T, T1> temp = queue[0];
                queue[0] = queue[countNodes];
                queue[countNodes] = temp;
                //copy last element
                pqNode<T, T1> copy = queue[countNodes];
                //delete last element
                queue.pop_back();
                siftdown(0);
                return copy;
            }
        }

        //replace int with iterator
        int find(T value)
        {
            for (int i = 0; i < countNodes; i++)
            {
                if (queue[i].value == value)
                {
                    return queue[i].value;
                }
            }
        }

        //Ask if this is the right idea for update
        //Replace int in parameters with iterator
        //This definitely is wack and I know it doesn't work but it does at least take an iterator
        void update(iterator i, priority_type priority)
        {
            i->priority = priority;
            if (i->priority > queue[parent(i->pos)].priority)
            {
                siftup(i);
            }
            else if (i->priority < queue[rightchild(i->pos)].priority && i->priority < queue[leftchild(i->pos)].priority)
            {
                siftdown(i->pos);
            }
            else
            {
                return;
            }
        }

        bool empty()
        {
            if (queue.empty())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        size_type size()
        {
            return countNodes;
        }

        class iterator
        {
          public:
            using iterator_category = std::forward_iterator_tag;
            iterator() :
                m_pos(0),
                m_data(nullptr) {}
            //copy constructor
            iterator(const iterator& obj);
            //move constructor
            iterator(const iterator&& obj);
            iterator(pointer data) :
                m_data(data),
                m_pos(0) {}
            iterator(size_type pos, pointer data) :
                m_pos(pos),
                m_data(data) {}

            iterator operator++();
            iterator operator++(int);
            //copy assignment
            iterator operator=(iterator& obj);
            //move assignment
            iterator operator=(iterator&& obj);
            //Dereference with pointer operator
            reference operator*() { return m_data[m_pos]; }
            //Dereference with dereference operator
            reference operator->() { return m_data[m_pos]; }

            bool operator==(const iterator& rhs)
            {
                return m_pos == rhs.m_pos && m_data == rhs.m_data;
            }

            bool operator!=(const iterator& rhs)
            {
                return !operator==(rhs);
            }

          private:
            size_type m_pos;
            pointer m_data;
        };

        iterator begin() { return iterator(queue); }
        iterator end() { return iterator(countNodes - 1, queue); }

      private:
        std::vector<pqNode<T, T1>> queue;
        int countNodes;
    };

    //copy constructor
    template <typename T, typename T1>
    priority_queue<T, T1>::iterator::iterator(const iterator& obj)
    {
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
    }

    //move constructor
    template <typename T, typename T1>
    priority_queue<T, T1>::iterator::iterator(const iterator&& obj) :
        m_data(nullptr),
        m_pos(0)
    {
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
        obj.m_pos = 0;
        obj.m_data = nullptr;
    }

    // Prefix ++i
    template <typename T, typename T1>
    typename priority_queue<T, T1>::iterator priority_queue<T, T1>::iterator::operator++()
    {
        m_pos++;
        return *this;
    }

    // Postfix i++
    template <typename T, typename T1>
    typename priority_queue<T, T1>::iterator priority_queue<T, T1>::iterator::operator++(int)
    {
        iterator i = *this;
        m_pos++;
        return i;
    }

    template <typename T, typename T1>
    typename priority_queue<T, T1>::iterator priority_queue<T, T1>::iterator::operator=(iterator& obj)
    {
        delete[] this->m_data;
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
        obj.m_pos = 0;
        obj.m_data = nullptr;
    }

    template <typename T, typename T1>
    typename priority_queue<T, T1>::iterator priority_queue<T, T1>::iterator::operator=(iterator&& obj)
    {
        delete[] this->m_data;
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
        obj.m_pos = 0;
        obj.m_data = nullptr;
    }
} // namespace usu