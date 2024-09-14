#include <iostream>
#include <cassert>
#include <sstream>
#include "DLinkedList.h"
#include "util/Point.h"
#include "DLinkedListDemo.h"

using namespace std;

// Helper function to convert int to string
string intToString(int &i)
{
    return to_string(i);
}

void testConstructor()
{
    cout << "Testing Constructor:" << endl;
    DLinkedList<int> list;
    assert(list.empty());
    assert(list.size() == 0);
    cout << "Constructor test passed." << endl;
}

void testCopyConstructor()
{
    cout << "Testing Copy Constructor:" << endl;
    DLinkedList<int> list1;
    for (int i = 0; i < 5; i++)
    {
        list1.add(i);
    }

    DLinkedList<int> list2(list1);
    assert(list2.size() == list1.size());
    for (int i = 0; i < 5; i++)
    {
        assert(list2.get(i) == list1.get(i));
    }

    // Modify list2 to ensure deep copy
    list2.removeAt(0);
    list2.add(0, 10);
    assert(list1.get(0) != list2.get(0));

    cout << "Copy Constructor test passed." << endl;
}

void testAssignmentOperator()
{
    cout << "Testing Assignment Operator:" << endl;
    DLinkedList<int> list1;
    for (int i = 0; i < 5; i++)
    {
        list1.add(i);
    }

    DLinkedList<int> list2;
    list2 = list1;
    assert(list2.size() == list1.size());
    for (int i = 0; i < 5; i++)
    {
        assert(list2.get(i) == list1.get(i));
    }

    // Modify list2 to ensure deep copy
    list2.removeAt(0);
    list2.add(0, 10);
    assert(list1.get(0) != list2.get(0));

    cout << "Assignment Operator test passed." << endl;
}

void testAdd()
{
    cout << "Testing Add methods:" << endl;
    DLinkedList<int> list;

    // Test add(T e)
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }
    assert(list.size() == 5);
    assert(list.get(4) == 4);

    // Test add(int index, T e)
    list.add(2, 10);
    assert(list.size() == 6);
    assert(list.get(2) == 10);

    // Test adding at the beginning
    list.add(0, 20);
    assert(list.size() == 7);
    assert(list.get(0) == 20);

    // Test adding at the end
    list.add(list.size(), 30);
    assert(list.size() == 8);
    assert(list.get(list.size() - 1) == 30);

    cout << "Add methods test passed." << endl;
}

void testRemoveAt()
{
    cout << "Testing RemoveAt method:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    int removed = list.removeAt(2);
    assert(removed == 2);
    assert(list.size() == 4);
    assert(list.get(2) == 3);

    // Test removing first element
    removed = list.removeAt(0);
    assert(removed == 0);
    assert(list.size() == 3);
    assert(list.get(0) == 1);

    // Test removing last element
    removed = list.removeAt(list.size() - 1);
    assert(removed == 4);
    assert(list.size() == 2);

    cout << "RemoveAt method test passed." << endl;
}

void testRemoveItem()
{
    cout << "Testing RemoveItem method:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    assert(list.removeItem(2));
    assert(list.size() == 4);
    assert(list.get(2) == 3);

    assert(!list.removeItem(10)); // Non-existent item
    assert(list.size() == 4);

    cout << "RemoveItem method test passed." << endl;
}

void testClear()
{
    cout << "Testing Clear method:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    list.clear();
    assert(list.empty());
    assert(list.size() == 0);

    cout << "Clear method test passed." << endl;
}

void testGetAndIndexOf()
{
    cout << "Testing Get and IndexOf methods:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i * 2);
    }

    assert(list.get(3) == 6);
    assert(list.indexOf(6) == 3);
    assert(list.indexOf(9) == -1);

    cout << "Get and IndexOf methods test passed." << endl;
}

void testContains()
{
    cout << "Testing Contains method:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i * 2);
    }

    assert(list.contains(6));
    assert(!list.contains(9));

    cout << "Contains method test passed." << endl;
}

void testToString()
{
    cout << "Testing ToString method:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    string result = list.toString(&intToString);
    assert(result == "[0, 1, 2, 3, 4]");

    cout << "ToString method test passed." << endl;
}

void testPointList()
{
    cout << "Testing DLinkedList with Point objects:" << endl;
    DLinkedList<Point *> pointList(&DLinkedList<Point *>::free, &Point::pointEQ);

    pointList.add(new Point(1.0, 2.0, 3.0));
    pointList.add(new Point(4.0, 5.0, 6.0));
    pointList.add(new Point(7.0, 8.0, 9.0));

    assert(pointList.size() == 3);
    assert(pointList.contains(new Point(4.0, 5.0, 6.0)));

    Point *removed = pointList.removeAt(1);
    assert(removed->getX() == 4.0 && removed->getY() == 5.0 && removed->getZ() == 6.0);
    delete removed;

    assert(pointList.size() == 2);

    pointList.clear(); // This should call the custom deleter

    cout << "DLinkedList with Point objects test passed." << endl;
}

void testIterator()
{
    cout << "Testing Iterator:" << endl;
    DLinkedList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    int expected = 0;
    for (DLinkedList<int>::Iterator it = list.begin(); it != list.end(); it++)
    {
        assert(*it == expected);
        expected++;
    }

    // Test iterator remove
    DLinkedList<int>::Iterator it = list.begin();
    it++; // Move to second element
    it.remove();
    assert(list.size() == 4);
    assert(list.get(1) == 2);

    cout << "Iterator test passed." << endl;
}

void testCopyFrom()
{
    cout << "Testing copyFrom method:" << endl;
    DLinkedList<int> list1;
    for (int i = 0; i < 5; i++)
    {
        list1.add(i);
    }

    DLinkedList<int> list2;
    list2.copyFrom(list1);

    assert(list2.size() == list1.size());
    for (int i = 0; i < 5; i++)
    {
        assert(list2.get(i) == list1.get(i));
    }

    // Modify list2 to ensure deep copy
    list2.removeAt(0);
    list2.add(0, 10);
    assert(list1.get(0) != list2.get(0));

    cout << "copyFrom method test passed." << endl;
}

void testRemoveInternalData()
{
    cout << "Testing removeInternalData method:" << endl;
    DLinkedList<int *> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(new int(i));
    }

    list.removeInternalData();

    assert(list.empty());
    assert(list.size() == 0);

    cout << "removeInternalData method test passed." << endl;
}

void testDestructor()
{
    cout << "Testing Destructor:" << endl;
    DLinkedList<int *> *list = new DLinkedList<int *>(&DLinkedList<int *>::free);
    for (int i = 0; i < 5; i++)
    {
        list->add(new int(i));
    }

    delete list; // This should call the destructor and free all memory

    cout << "Destructor test passed (no crashes or memory leaks)." << endl;
}

class DLinkedListTestCases
{

public:
    void test()
    {
        testConstructor();
        testCopyConstructor();
        testAssignmentOperator();
        testAdd();
        testRemoveAt();
        testRemoveItem();
        testClear();
        testGetAndIndexOf();
        testContains();
        testToString();
        testPointList();
        testIterator();
        testCopyFrom();
        testRemoveInternalData();
        testDestructor();
        dlistDemo1();
        dlistDemo2();
        dlistDemo3();
        dlistDemo4();
        dlistDemo5();
        dlistDemo6();
    }
};