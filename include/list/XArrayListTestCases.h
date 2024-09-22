#include <iostream>
#include <cassert>
#include <sstream>
#include "XArrayList.h"
#include "util/Point.h" // Assuming Point class is available for testing
#include "XArrayListDemo.h"

using namespace std;

// Helper function to convert int to string
string intToStringArr(int &i)
{
    return to_string(i);
}

void testXArrayListConstructor()
{
    cout << "Testing XArrayList Constructor:" << endl;
    XArrayList<int> list;
    assert(list.empty());
    assert(list.size() == 0);
    cout << "XArrayList Constructor test passed." << endl;
}

void testXArrayListCopyConstructor()
{
    cout << "Testing XArrayList Copy Constructor:" << endl;
    XArrayList<int> list1;
    for (int i = 0; i < 5; i++)
    {
        list1.add(i);
    }
    XArrayList<int> list2(list1);
    cout << "OK " << endl;
    assert(list2.size() == list1.size());
    for (int i = 0; i < 5; i++)
    {
        assert(list2.get(i) == list1.get(i));
        
    }

    // Modify list2 to ensure deep copy
    list2.removeAt(0);
    list2.add(0, 10);
    assert(list1.get(0) != list2.get(0));

    cout << "XArrayList Copy Constructor test passed." << endl;
}

void testXArrayListAssignmentOperator()
{
    cout << "Testing XArrayList Assignment Operator:" << endl;
    XArrayList<int> list1;
    for (int i = 0; i < 5; i++)
    {
        list1.add(i);
    }

    XArrayList<int> list2;
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

    cout << "XArrayList Assignment Operator test passed." << endl;
}

void testXArrayListAdd()
{
    cout << "Testing XArrayList Add methods:" << endl;
    XArrayList<int> list;

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

    cout << "XArrayList Add methods test passed." << endl;
}

void testXArrayListRemoveAt()
{
    cout << "Testing XArrayList RemoveAt method:" << endl;
    XArrayList<int> list;
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

    cout << "XArrayList RemoveAt method test passed." << endl;
}

void testXArrayListRemoveItem()
{
    cout << "Testing XArrayList RemoveItem method:" << endl;
    XArrayList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    assert(list.removeItem(2));
    assert(list.size() == 4);
    assert(list.get(2) == 3);

    assert(!list.removeItem(10)); // Non-existent item
    assert(list.size() == 4);

    cout << "XArrayList RemoveItem method test passed." << endl;
}

void testXArrayListClear()
{
    cout << "Testing XArrayList Clear method:" << endl;
    XArrayList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    list.clear();
    assert(list.empty());
    assert(list.size() == 0);

    cout << "XArrayList Clear method test passed." << endl;
}

void testXArrayListGetAndIndexOf()
{
    cout << "Testing XArrayList Get and IndexOf methods:" << endl;
    XArrayList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i * 2);
    }

    assert(list.get(3) == 6);
    assert(list.indexOf(6) == 3);
    assert(list.indexOf(9) == -1);

    cout << "XArrayList Get and IndexOf methods test passed." << endl;
}

void testXArrayListContains()
{
    cout << "Testing XArrayList Contains method:" << endl;
    XArrayList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i * 2);
    }

    assert(list.contains(6));
    assert(!list.contains(9));

    cout << "XArrayList Contains method test passed." << endl;
}

void testXArrayListToString()
{
    cout << "Testing XArrayList ToString method:" << endl;
    XArrayList<int> list;
    for (int i = 0; i < 5; i++)
    {
        list.add(i);
    }

    string result = list.toString(&intToStringArr);
    assert(result == "[0, 1, 2, 3, 4]");

    cout << "XArrayList ToString method test passed." << endl;
}

void testXArrayListEnsureCapacity()
{
    cout << "Testing XArrayList EnsureCapacity method:" << endl;
    XArrayList<int> list;

    // Add more elements than the initial capacity
    for (int i = 0; i < 15; i++)
    {
        list.add(i);
    }

    assert(list.size() == 15);
    for (int i = 0; i < 15; i++)
    {
        assert(list.get(i) == i);
    }

    cout << "XArrayList EnsureCapacity method test passed." << endl;
}

void testXArrayListCopyFrom()
{
    cout << "Testing XArrayList copyFrom method:" << endl;
    XArrayList<int> list1;
    for (int i = 0; i < 5; i++)
    {
        list1.add(i);
    }

    XArrayList<int> list2;
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

    cout << "XArrayList copyFrom method test passed." << endl;
}

void testXArrayListRemoveInternalData()
{
    cout << "Testing XArrayList removeInternalData method:" << endl;
    XArrayList<int *> list(&XArrayList<int *>::free);
    for (int i = 0; i < 5; i++)
    {
        list.add(new int(i));
    }

    list.removeInternalData();

    assert(list.empty());
    assert(list.size() == 0);

    for (int i = 0; i < 5; i++)
    {
        list.add(new int(i));
    }
    assert(list.size() == 5);

    cout << "XArrayList removeInternalData method test passed." << endl;
}

class XArrayListTestCases
{
public:
    void test()
    {
        testXArrayListConstructor();
        testXArrayListCopyConstructor();
        testXArrayListAssignmentOperator();
        testXArrayListAdd();
        testXArrayListRemoveAt();
        testXArrayListRemoveItem();
        testXArrayListClear();
        testXArrayListGetAndIndexOf();
        testXArrayListContains();
        testXArrayListToString();
        testXArrayListEnsureCapacity();
        testXArrayListCopyFrom();
        testXArrayListRemoveInternalData();
        xlistDemo1();
        xlistDemo2();
        xlistDemo3();
        xlistDemo4();
    }
};