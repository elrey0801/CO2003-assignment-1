#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "list/listheader.h"
#include "list/DLinkedListTestCases.h"
#include "list/XArrayListTestCases.h"
#include "list/MoreTest.h"

using namespace std;


int main(int argc, char** argv) {
    cout << "Assignment-1" << endl;
    DLinkedListTestCases* dll_test = new DLinkedListTestCases();
    dll_test->test();
    XArrayListTestCases* xarr_test = new XArrayListTestCases();
    xarr_test->test();
    DLinkedListTest* dll_more_test = new DLinkedListTest();
    dll_more_test->runAllTests();
    XArrayListTest* xarr_more_test = new XArrayListTest();
    xarr_more_test->runAllTests();

    return 0;
}

