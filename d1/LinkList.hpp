/*
* @file LinkList
* @author MercedesKK
* @date 2022-9-7
* @brief the Linklist written by me
* @email 2455650395@qq.com
*/
#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include <iostream>

namespace MercedesKK
{
    /// this is a node class used by list
    template <typename T>
    class Node
    {
    public:
        T data;         ///< each node of the data
        Node<T>* pnext; ///< pointer to the next node
    };

    /// class for Linklist
    template <typename T>
    class LinkList
    {
    private:
        int length;      ///< the list of length
        Node<T>* header; ///< the list of head pointer

    public:
        LinkList();
        LinkList(const LinkList<T>& list);
        LinkList<T>& operator=(const LinkList<T>& rhs);
        ~LinkList();

    public:
        /// add the data before the first node
        void headAdd(const T& data);

        /// add the data after the last node \n
        /// www
        void rearAdd(const T& data);

        /// @return the size of list
        int size() const;

        /// @return wheather the list is empty
        bool isEmpty() const;

        /// print the data in the list from the first node to the last 
        void print() const;

        /// @return return the n position node  
        T getElement(int n) const;

        /// @note insert the data before the position n node
        void insert(int n, const T& data);

        /// @note erase the data on the position n node
        void erase(int n);

        /// @note modify the pos n node to data
        void modify(int n, const T& data);

        /// @warning the param is data! Not position!
        /// @return return the position  
        int find(const T& data);

        /// the same as clear
        void destroy();

        // void sort();
    };

    template <typename T>
    LinkList<T>::LinkList() : header(nullptr), length(0) {};

    template <typename T>
    LinkList<T>::LinkList(const LinkList<T>& rhs) : header(nullptr), length(0)
    {
        int i = 1;
        while (i <= rhs.size())
        {
            rearAdd(rhs.getElement(i));
            i++;
        }
    }

    template <typename T>
    LinkList<T>& LinkList<T>::operator=(const LinkList<T>& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        destroy();
        for (int i = 1; i <= rhs.size(); ++i)
        {
            rearAdd(rhs.getElement(i));
        }
        return *this;
    }

    template <typename T>
    LinkList<T>::~LinkList()
    {
        destroy();
    }

    template <typename T>
    void LinkList<T>::headAdd(const T& data)
    {
        Node<T>* pnode = new Node<T>;
        pnode->data = data;
        pnode->pnext = nullptr;
        if (header == nullptr)
        {
            header = pnode;
        }
        else
        {
            pnode->pnext = header;
            header = pnode;
        }
        length++;
    }

    template <typename T>
    void LinkList<T>::rearAdd(const T& data)
    {
        Node<T>* pnode = new Node<T>;
        pnode->data = data;
        pnode->pnext = nullptr;
        if (header == nullptr)
        {
            header = pnode;
        }
        else
        {
            Node<T>* rear = header;
            while (rear->pnext != nullptr)
                rear = rear->pnext;
            rear->pnext = pnode;
        }
        length++;
    }

    template <typename T>
    int LinkList<T>::size() const
    {
        return length;
    }

    template <typename T>
    bool LinkList<T>::isEmpty() const
    {
        return header == nullptr;
    }

    template <typename T>
    void LinkList<T>::print() const
    {
        Node<T>* ptmp = header;
        while (ptmp != nullptr)
        {
            std::cout << ptmp->data << std::endl;
            ptmp = ptmp->pnext;
        }
    }

    template <typename T>
    T LinkList<T>::getElement(int n) const
    {
        if (n < 1 || n > length)
        {
            throw "获取元素位置非法！";
        }
        else
        {
            int i = 1;
            Node<T>* ptmp = header;
            while (i++ < n)
            {
                ptmp = ptmp->pnext;
            }
            return ptmp->data;
        }
    }

    template <typename T>
    void LinkList<T>::insert(int n, const T& data)
    {
        if (n < 1 || n > length)
        {
            std::cout << "插入元素位置非法！" << std::endl;
        }
        else
        {
            if (n == 1)
            {
                Node<T>* ptmp = new Node<T>;
                ptmp->data = data;
                ptmp->pnext = header;
                header = ptmp;
            }
            else
            {
                int i = 1;
                Node<T>* ptmp = header;
                while (++i < n)
                {
                    ptmp = ptmp->pnext;
                }
                Node<T>* pinsert = new Node<T>;
                pinsert->data = ptmp->data;
                pinsert->pnext = ptmp->pnext;
                ptmp->pnext = pinsert;
            }
            length++;
        }
    }

    template <typename T>
    void LinkList<T>::erase(int n)
    {
        if (n < 1 || n > length)
        {
            std::cout << "删除元素位置非法！" << std::endl;
        }
        else
        {
            Node<T>* deleteElement;
            if (n == 1)
            {
                deleteElement = header;
                header = header->pnext;
            }
            else
            {
                int i = 1;
                Node<T>* ptmp = header;
                while (++i < n)
                {
                    ptmp = ptmp->pnext;
                }
                deleteElement = ptmp->pnext;
                ptmp->pnext = deleteElement->pnext;
            }
            delete deleteElement;
            length--;
        }
    }

    template <typename T>
    void LinkList<T>::modify(int n, const T& data)
    {
        if (n < 1 || n > length)
        {
            std::cout << "修改元素位置非法！" << std::endl;
        }
        else
        {
            if (n == 1)
            {
                header->data = data;
            }
            else
            {
                Node<T>* ptmp = header;
                int i = 1;
                while (i++ < n)
                {
                    ptmp = ptmp->pnext;
                }
                ptmp->data = data;
            }
        }
    }

    template <typename T>
    int LinkList<T>::find(const T& data)
    {
        int i = 1;
        int last = -1;
        Node<T>* ptmp = header;
        while (ptmp)
        {
            if (ptmp->data == data)
            {
                last = i;
                break;
            }
            i++;
            ptmp = ptmp->pnext;
        }
        return last;
    }

    template <typename T>
    void LinkList<T>::destroy()
    {
        while (header != NULL)
        {
            Node<T>* ptmp = header;
            header = header->pnext;
            delete ptmp;
        }
        length = 0;
    }
}

#endif // !_LINKLIST_H_
