#pragma once
#include <cmath>
#include <iostream>
#include <vector>

/*
-----------------------------------------------------------------
----------------------DEVELOPMENT PLAN---------------------------
-----------------------------------------------------------------
1.-Write the Priority Queue-Template syntax with everything-
 a. void enqueue(T value, priority_type priority)             |?|
 ---MAKE HEAP LOOK UP LINKS IN ASSIGNMENT
 b. auto dequeue()										      |?|
 c. iterator find(T value)								      |?|
 ---write this before the iterator
 ---It doesn't require that the iterator exist beforehand
 d. void update(iterator i, priority_type priority)		      |?|
 ---how to do the update on a vector? Sort by priority?
 e. bool empty()										      |X|
 f. size_type size()									      |X|
 ---count, keep track of enqueues and dequeues
 g.aliases													  |?|
 ---How to do this correctly? Where?
2.Write Iterator-Follow in class code
---Where to write??? Inside Node class? Inside queue class?? Outside??
 a. iterator begin()									      ||
 b. iterator end()										      ||
 c. copy constructor									      ||
 d. move contsructor									      ||
 e. copy assignment operator							      ||
 f. move assignment operator							      ||
 g. incrementable										      ||
 h. dereferenceable										      ||
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
        void update(int i, priority_type priority)
        {
            //Sort vector according to priorities with highest priority as element 0
            //how to use the binary predicate to sort based on priorities
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

      private:
        std::vector<pqNode<T, T1>> queue;
        int countNodes;
    };
} // namespace usu