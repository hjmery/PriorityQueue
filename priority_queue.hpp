#include <iostream>
#include <vector>

/*
-----------------------------------------------------------------
1.-Write the Priority Queue-Template syntax with everything-
 a. void enqueue(T value, priority_type priority)             |X|
 b. auto dequeue()										      ||
 c. iterator find(T value)								      ||
 d. void update(iterator i, priority_type priority)		      ||
 e. bool empty()										      |X|
 f. size_type size()									      ||
2.Write Iterator-Follow in class code
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
		pqNode(T val, T1 pri) {
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
    class priority_queue{
      public:
        void enqueue(T value, T1 priority)
        {
            nextNode = pqNode(value, priority);
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

	  private:
        std::vector<pqNode> queue;
    };
}