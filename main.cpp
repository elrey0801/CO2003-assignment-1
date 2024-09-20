#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "list/listheader.h"
#include "list/DLinkedListTestCases.h"
#include "list/XArrayListTestCases.h"

using namespace std;


int main(int argc, char** argv) {
    cout << "Assignment-1" << endl;
    DLinkedListTestCases* dll_test = new DLinkedListTestCases();
    dll_test->test();
    XArrayListTestCases* xarr_test = new XArrayListTestCases();
    xarr_test->test();

    return 0;
}

