#include <iostream>
#include <vector>

/*
-----------------------------------------------------------------
----------------------DEVELOPMENT PLAN---------------------------
-----------------------------------------------------------------
1.-Write the Priority Queue-Template syntax with everything-
 a. void enqueue(T value, priority_type priority)             |?|
 b. auto dequeue()										      |?|
 c. iterator find(T value)								      |?|
 ---write this before the iterator
 ---It doesn't require that the iterator exist beforehand
 d. void update(iterator i, priority_type priority)		      |?|
 ---how to do the update on a vector? Sort by priority?
 e. bool empty()										      |X|
 f. size_type size()									      |X|
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

      private:
        T value;
        T1 priority;
    };

    template <typename T, typename T1 = unsigned int>
    class priority_queue
    {
      public:
        //am I doing this right? there's no way it's that simple, but if so, why do we do it?
        using priority_type = T1;
        using value_type = T;
        using size_type = size_t;

        void enqueue(T value, priority_type priority)
        {
            nextNode = pqNode(value, priority);
            //Is this where I should use the formula new size = (current size) * 1.25 + 1 ?
            //Why not just push back?
            queue.push_back(nextNode);
        }

        auto dequeue()
        {
            if (this->empty())
            {
                throw "The queue is empty!";
            }
            else
            {
                //copy this->queue.begin() into into an iterator
                //this->queue.erase(this->queue.begin());
                //this->update();
                //return copy from first line
            }
        }

        iterator find(T value)
        {
            for (int i = 0; i < this->size(); i++)
            {
                if (queue[i].getValue() == value)
                {
                    //return iterator to value
                }
            }
        }

        bool wayToSort(priority_type i, priority_type j) { return i < j; }

        //Ask if this is the right idea for update
        void update(iterator i, priority_type priority)
        {
            //Sort vector according to priorities with highest priority as element 0
            //how to use the binary predicate to sort based on priorities
            sort(queue.begin(), queue.end(), wayToSort());
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
            return queue.size();
        }

      private:
        std::vector<pqNode> queue;
    };
} // namespace usu