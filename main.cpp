#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "list/listheader.h"
// #include "list/DLinkedListTestCases.h"
// #include "list/XArrayListTestCases.h"
// #include "list/MoreTest.h"
#include "ann/dataloader.h"
#include "ann/dataset.h"
#include "ann/xtensor_lib.cpp"
#include "list/DLinkedListDemo.h"
#include "list/XArrayListDemo.h"
#include "ann/DataLoaderDemo.h"

using namespace std;

int main(int argc, char **argv)
{
    case_data_wo_label_1();
    case_data_wi_label_1();
    case_batch_larger_nsamples();
    return 0;
}
