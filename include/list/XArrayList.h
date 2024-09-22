/*
 * File:   XArrayList.h
 */

#ifndef XARRAYLIST_H
#define XARRAYLIST_H
#include "list/IList.h"
#include <memory.h>
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class XArrayList : public IList<T>
{
public:
    class Iterator; // forward declaration

protected:
    T *data;                                 // dynamic array to store the list's items
    int capacity;                            // size of the dynamic array
    int count;                               // number of items stored in the array
    bool (*itemEqual)(T &lhs, T &rhs);       // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(XArrayList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    XArrayList(
        void (*deleteUserData)(XArrayList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0,
        int capacity = 10);
    XArrayList(const XArrayList<T> &list);
    XArrayList<T> &operator=(const XArrayList<T> &list);
    ~XArrayList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T &get(int index);
    int indexOf(T item);
    bool contains(T item);
    string toString(string (*item2str)(T &) = 0);
    // Inherit from IList: BEGIN

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(XArrayList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    Iterator begin()
    {
        return Iterator(this, 0);
    }
    Iterator end()
    {
        return Iterator(this, count);
    }

    /** free:
     * if T is pointer type:
     *     pass THE address of method "free" to XArrayList<T>'s constructor:
     *     to:  remove the user's data (if needed)
     * Example:
     *  XArrayList<Point*> list(&XArrayList<Point*>::free);
     *  => Destructor will call free via function pointer "deleteUserData"
     */
    static void free(XArrayList<T> *list)
    {
        typename XArrayList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }
public: ///// dont forget to set it back to protected
    void checkIndex(int index);     // check validity of index for accessing
    void ensureCapacity(int index); // auto-allocate if needed

    /** equals:
     * if T: primitive type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     * if T: object type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     *      Therefore, class of type T MUST override operator ==
     * if T: pointer type:
     *      indexOf, contains: will use function pointer "itemEqual"
     *      to: compare two items of T type
     *      Therefore:
     *      (1): must pass itemEqual to the constructor of XArrayList
     *      (2): must define a method for comparing
     *           the content pointed by two pointers of type T
     *          See: definition of "equals" of class Point for more detail
     */
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

    void copyFrom(const XArrayList<T> &list);

    void removeInternalData();

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    // Iterator: BEGIN
    class Iterator
    {
    private:
        int cursor;
        XArrayList<T> *pList;

    public:
        Iterator(XArrayList<T> *pList = 0, int index = 0)
        {
            this->pList = pList;
            this->cursor = index;
        }
        Iterator &operator=(const Iterator &iterator)
        {
            cursor = iterator.cursor;
            pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            T item = pList->removeAt(cursor);
            if (removeItemData != 0)
                removeItemData(item);
            cursor -= 1; // MUST keep index of previous, for ++ later
        }

        T &operator*()
        {
            return pList->data[cursor];
        }
        bool operator!=(const Iterator &iterator)
        {
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            this->cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
    // Iterator: END
};

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
XArrayList<T>::XArrayList(
    void (*deleteUserData)(XArrayList<T> *),
    bool (*itemEqual)(T &, T &),
    int capacity)
{
    // TODO
    if(capacity < 0) capacity = 10;
    this->capacity = capacity;
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;
    this->count = 0;
    this->data = new T[this->capacity];
}

template <class T>
void XArrayList<T>::copyFrom(const XArrayList<T> &list)
{
    /*
     * Copies the contents of another XArrayList into this list.
     * Initializes the list with the same capacity as the source list and copies all elements.
     * Also duplicates user-defined comparison and deletion functions, if applicable.
     */
    // TODO
    this->removeInternalData();
    this->itemEqual = list.itemEqual;
    this->deleteUserData = list.deleteUserData;
    if(list.count > 0) {
        this->capacity = list.count;
        this->data = new T[this->capacity];
        for(int i = 0; i < list.count; ++i) 
            this->add(list.data[i]);
    }  
}

template <class T>
void XArrayList<T>::removeInternalData()
{
    /*
     * Clears the internal data of the list by deleting the dynamic array and any user-defined data.
     * If a custom deletion function is provided, it is used to free the stored elements.
     * Finally, the dynamic array itself is deallocated from memory.
     */
    // TODO
    if(this->deleteUserData) 
        this->deleteUserData(this);
    if(this->data != nullptr)
        delete[] this->data;
    this->count = 0;
    this->capacity = 10;
    this->data = new T[this->capacity];
}

template <class T>
XArrayList<T>::XArrayList(const XArrayList<T> &list)
{
    // TODO
    this->data = nullptr;
    this->itemEqual = nullptr;
    this->deleteUserData = nullptr;
    this->copyFrom(list);
}

template <class T>
XArrayList<T> &XArrayList<T>::operator=(const XArrayList<T> &list)
{
    // TODO
    this->clear();
    this->copyFrom(list);
    return *this;
}

template <class T>
XArrayList<T>::~XArrayList()
{
    // TODO
    if(!this->data) 
        return;
    if(this->deleteUserData) 
        this->deleteUserData(this);
    if(this->data)
        delete[] data;
}

template <class T>
void XArrayList<T>::add(T e)
{
    // TODO
    this->ensureCapacity(this->count);
    this->data[this->count] = e;
    this->count++;
}

template <class T>
void XArrayList<T>::add(int index, T e)
{
    // TODO
    if(index < 0 || index > this->count) throw std::out_of_range("Invalid index");
    this->ensureCapacity(this->count);
    if(index == this->count) {
        this->add(e);
        return;
    }
    for(int i = this->count; i > index; --i) this->data[i] = this->data[i-1];
    this->data[index] = e;
    this->count++;
}

template <class T>
T XArrayList<T>::removeAt(int index)
{
    // TODO
    this->checkIndex(index);
    T return_value = this->data[index];
    for(int i = index; i < this->count - 1; ++i) this->data[i] = this->data[i+1];
    this->count--;
    return return_value;
}

template <class T>
bool XArrayList<T>::removeItem(T item, void (*removeItemData)(T))
{
    // TODO
    for(int i = 0; i < this->count; ++i) {
        if(equals(this->data[i], item, this->itemEqual)) {
            if(removeItemData) removeItemData(this->data[i]);
            this->removeAt(i);
            return true;
        }
    }
    return false;
}

template <class T>
bool XArrayList<T>::empty()
{
    // TODO
    return this->count == 0;
}

template <class T>
int XArrayList<T>::size()
{
    // TODO
    return this->count;
}

template <class T>
void XArrayList<T>::clear()
{
    // TODO
    if(this->deleteUserData) 
        this->deleteUserData(this);
    this->count = 0;
    this->capacity = 10;
}

template <class T>
T &XArrayList<T>::get(int index)
{
    // TODO
    if(index < 0 || index >= count) throw std::out_of_range("Invalid index");
    return this->data[index];
}

template <class T>
int XArrayList<T>::indexOf(T item)
{
    // TODO
    for(int i = 0; i < this->count; ++i)
        if(equals(this->data[i], item, this->itemEqual)) return i;

    return -1;
}
template <class T>
bool XArrayList<T>::contains(T item)
{
    // TODO
    return this->indexOf(item) != -1;
}

template <class T>
string XArrayList<T>::toString(string (*item2str)(T &))
{
    /**
     * Converts the array list into a string representation, formatting each element using a user-defined function.
     * If no function is provided, it uses the default string representation for each element.
     * Example: Given an array list with elements {1, 2, 3} and a function that converts integers to strings, calling toString would return "[1, 2, 3]".
     *
     * @param item2str A function pointer for converting items of type T to strings. If null, default to the string conversion of T.
     * @return A string representation of the array list with elements separated by commas and enclosed in square brackets.
     */

    // TODO
    stringstream s;
    s << "[";
    for(int i = 0; i < this->count; ++i) {
        if(item2str) s << item2str(this->data[i]);
        else s << this->data[i];
        if(i != this->count - 1) s << ", ";
    }
    s << "]";
    return s.str();
}

//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////
template <class T>
void XArrayList<T>::checkIndex(int index)
{
    /**
     * Validates whether the given index is within the valid range of the list.
     * Throws an std::out_of_range exception if the index is negative or exceeds the number of elements.
     * Ensures safe access to the list's elements by preventing invalid index operations.
     */
    // TODO
    if(index < 0 || index >= this->count) throw std::out_of_range("Invalid index");
}
template <class T>
void XArrayList<T>::ensureCapacity(int index)
{
    /**
     * Ensures that the list has enough capacity to accommodate the given index.
     * If the index is out of range, it throws an std::out_of_range exception. If the index exceeds the current capacity,
     * reallocates the internal array with increased capacity, copying the existing elements to the new array.
     * In case of memory allocation failure, catches std::bad_alloc.
     */
    // TODO
    if(index < 0 || index > this->count) throw std::out_of_range("Invalid index");
    if(index != this->count || this->count + 1 < this->capacity) return;
    T* newDataPointer = nullptr;
    try {
        this->capacity = (this->capacity + 1) * 2;
        newDataPointer = new T[this->capacity];
        if(this->data != nullptr) {
            for(int i = 0; i < this->count; ++i) 
                newDataPointer[i] = this->data[i];
            delete[] this->data;
        }
        this->data = newDataPointer;
    } catch (const std::bad_alloc& e) {
        delete[] newDataPointer;
    }

}

#endif /* XARRAYLIST_H */
