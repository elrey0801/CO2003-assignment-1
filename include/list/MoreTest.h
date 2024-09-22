#include <iostream>
#include <cassert>
#include "DLinkedList.h"
#include "util/Point.h"
#include "XArrayList.h"

class DLinkedListTest {
private:
    static void testConstructor() {
        DLinkedList<int> list;
        assert(list.empty());
        assert(list.size() == 0);
        
        DLinkedList<Point*> pointList(&DLinkedList<Point*>::free, &Point::pointEQ);
        assert(pointList.empty());
        assert(pointList.size() == 0);
    }

    static void testCopyConstructor() {
        DLinkedList<int> list1;
        for (int i = 0; i < 5; i++) list1.add(i);
        
        DLinkedList<int> list2(list1);
        assert(list1.size() == list2.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list2.get(i));
    }

    static void testAssignmentOperator() {
        DLinkedList<int> list1;
        for (int i = 0; i < 5; i++) list1.add(i);
        
        DLinkedList<int> list2;
        list2 = list1;
        assert(list1.size() == list2.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list2.get(i));
        
        // Test self-assignment
        list1 = list1;
        assert(list1.size() == 5);
        for (int i = 0; i < 5; i++) assert(list1.get(i) == i);
    }

    static void testDestructor() {
        // This is difficult to test directly, but we can check for memory leaks
        // using tools like Valgrind
    }

    static void testAdd() {
        DLinkedList<int> list;
        list.add(1);
        list.add(2);
        list.add(3);
        assert(list.size() == 3);
        assert(list.get(0) == 1);
        assert(list.get(1) == 2);
        assert(list.get(2) == 3);
        
        list.add(0, 0);
        assert(list.size() == 4);
        assert(list.get(0) == 0);
        
        try {
            list.add(10, 10); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
    }

    static void testRemoveAt() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.removeAt(2) == 2);
        assert(list.size() == 4);
        assert(list.get(2) == 3);
        
        try {
            list.removeAt(10); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
    }

    static void testRemoveItem() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        list.add(2); // Add duplicate
        
        assert(list.removeItem(2));
        assert(list.size() == 5);
        assert(list.get(2) == 3);
        
        assert(!list.removeItem(10)); // Non-existent item
    }

    static void testEmptyAndSize() {
        DLinkedList<int> list;
        assert(list.empty());
        assert(list.size() == 0);
        
        list.add(1);
        assert(!list.empty());
        assert(list.size() == 1);
        
        list.removeAt(0);
        assert(list.empty());
        assert(list.size() == 0);
    }

    static void testClear() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        list.clear();
        assert(list.empty());
        assert(list.size() == 0);
        
        list.add(1);
        assert(!list.empty());
    }

    static void testGet() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.get(2) == 2);
        list.get(2) = 10;
        assert(list.get(2) == 10);
        
        try {
            list.get(10); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
    }

    static void testIndexOf() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        list.add(2); // Add duplicate
        
        assert(list.indexOf(2) == 2);
        assert(list.indexOf(10) == -1);
    }

    static void testContains() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.contains(2));
        assert(!list.contains(10));
    }

    static void testToString() {
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.toString() == "[0, 1, 2, 3, 4]");
    }

    static void testCopyFrom() {
        DLinkedList<int> list1;
        for (int i = 0; i < 5; i++) list1.add(i);
        
        DLinkedList<int> list2;
        list2.copyFrom(list1);
        
        assert(list1.size() == list2.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list2.get(i));
    }

    static void testRemoveInternalData() {
        // This is an internal method, typically called by destructor or clear.
        // We can indirectly test it through clear() or destructor behavior.
        DLinkedList<int*> list;
        for (int i = 0; i < 5; i++) list.add(new int(i));
        
        list.clear(); // Should call removeInternalData
        assert(list.empty());
        assert(list.size() == 0);
    }

    static void testGetPreviousNodeOf() {
        // This is a protected method, so we'll need to test it indirectly
        // through public methods that use it, like removeAt or add(index, element)
        DLinkedList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        list.add(2, 10); // This should use getPreviousNodeOf internally
        assert(list.get(2) == 10);
        assert(list.size() == 6);
    }

public:
    static void runAllTests() {
        testConstructor();
        testCopyConstructor();
        testAssignmentOperator();
        testDestructor();
        testAdd();
        testRemoveAt();
        testRemoveItem();
        testEmptyAndSize();
        testClear();
        testGet();
        testIndexOf();
        testContains();
        testToString();
        testCopyFrom();
        testRemoveInternalData();
        testGetPreviousNodeOf();
        std::cout << "All DLinkedList tests passed!" << std::endl;
    }
};


class XArrayListTest {
private:
    static void testConstructor() {
        XArrayList<int> list;
        assert(list.empty());
        assert(list.size() == 0);
        
        XArrayList<Point*> pointList(&XArrayList<Point*>::free, &Point::pointEQ);
        assert(pointList.empty());
        assert(pointList.size() == 0);
        cout << "testConstructor: OK" << endl;
    }

    static void testCopyConstructorAndAssignment() {
        XArrayList<int> list1;
        for (int i = 0; i < 5; i++) list1.add(i);
        
        XArrayList<int> list2(list1);
        assert(list1.size() == list2.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list2.get(i));
        
        XArrayList<int> list3;
        list3 = list1;
        assert(list1.size() == list3.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list3.get(i));
        cout << "testCopyConstructorAndAssignment: OK" << endl;
    }

    static void testAdd() {
        XArrayList<int> list;
        for (int i = 0; i < 15; i++) list.add(i); // Test capacity expansion
        assert(list.size() == 15);
        for (int i = 0; i < 15; i++) assert(list.get(i) == i);
        
        list.add(0, -1);
        assert(list.size() == 16);
        assert(list.get(0) == -1);
        
        try {
            list.add(20, 20); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
        cout << "testAdd: OK" << endl;
    }

    static void testRemoveAt() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.removeAt(2) == 2);
        assert(list.size() == 4);
        assert(list.get(2) == 3);
        
        try {
            list.removeAt(10); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
        cout << "testRemoveAt: OK" << endl;
    }

    static void testRemoveItem() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        list.add(2); // Add duplicate
        
        assert(list.removeItem(2));
        assert(list.size() == 5);
        assert(list.get(2) == 3);
        
        assert(!list.removeItem(10)); // Non-existent item
        cout << "testRemoveItem: OK" << endl;
    }

    static void testEmptyAndSize() {
        XArrayList<int> list;
        assert(list.empty());
        assert(list.size() == 0);
        
        list.add(1);
        assert(!list.empty());
        assert(list.size() == 1);
        
        list.removeAt(0);
        assert(list.empty());
        assert(list.size() == 0);
        cout << "testEmptyAndSize: OK" << endl;
    }

    static void testClear() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        list.clear();
        assert(list.empty());
        assert(list.size() == 0);
        
        list.add(1);
        assert(!list.empty());
        cout << "testClear: OK" << endl;
    }

    static void testGet() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.get(2) == 2);
        list.get(2) = 10;
        assert(list.get(2) == 10);
        
        try {
            list.get(10); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
        cout << "testGet: OK" << endl;
    }

    static void testIndexOf() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        list.add(2); // Add duplicate
        
        assert(list.indexOf(2) == 2);
        assert(list.indexOf(10) == -1);
        cout << "testIndexOf: OK" << endl;
    }

    static void testContains() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.contains(2));
        assert(!list.contains(10));
        cout << "testContains: OK" << endl;
    }

    static void testToString() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        assert(list.toString() == "[0, 1, 2, 3, 4]");
        cout << "testToString: OK" << endl;
    }

    static void testEnsureCapacity() {
        XArrayList<int> list;
        for (int i = 0; i < 10; i++) list.add(i);
        
        list.ensureCapacity(10);
        assert(list.size() == 10);
        for (int i = 0; i < 10; i++) assert(list.get(i) == i);
        
        for (int i = 10; i < 25; i++) list.add(i);
        assert(list.size() == 25);
        for (int i = 0; i < 25; i++) assert(list.get(i) == i);
        cout << "testEnsureCapacity: OK" << endl;
    }

    static void testRemoveInternalData() {
        XArrayList<int*> list(&XArrayList<int*>::free);
        for (int i = 0; i < 5; i++) list.add(new int(i));
        
        list.clear(); // This should call removeInternalData
        assert(list.empty());
        assert(list.size() == 0);
        cout << "testRemoveInternalData: OK" << endl;
    }

    static void testOperatorAssignment() {
        XArrayList<int> list1;
        for (int i = 0; i < 5; i++) list1.add(i);
        
        XArrayList<int> list2;
        list2 = list1;
        
        assert(list1.size() == list2.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list2.get(i));
        
        list1.add(5);
        assert(list1.size() != list2.size()); // Ensure deep copy
        cout << "testOperatorAssignment: OK" << endl;
    }

    static void testCopyFrom() {
        XArrayList<int> list1;
        for (int i = 0; i < 5; i++) list1.add(i);
        
        XArrayList<int> list2;
        list2.copyFrom(list1);
        
        assert(list1.size() == list2.size());
        for (int i = 0; i < 5; i++) assert(list1.get(i) == list2.get(i));
        cout << "testCopyFrom: OK" << endl;
    }

    static void testCheckIndex() {
        XArrayList<int> list;
        for (int i = 0; i < 5; i++) list.add(i);
        
        try {
            list.get(-1); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }

        try {
            list.get(5); // Should throw exception
            assert(false);
        } catch (const std::out_of_range&) {
            assert(true);
        }
        cout << "testCheckIndex: OK" << endl;
    }

public:
    static void runAllTests() {
        testConstructor();
        testCopyConstructorAndAssignment();
        testAdd();
        testRemoveAt();
        testRemoveItem();
        testEmptyAndSize();
        testClear();
        testGet();
        testIndexOf();
        testContains();
        testToString();
        testEnsureCapacity();
        testRemoveInternalData();
        testOperatorAssignment();
        testCopyFrom();
        testCheckIndex();
        std::cout << "All XArrayList tests passed!" << std::endl;
    }
};




