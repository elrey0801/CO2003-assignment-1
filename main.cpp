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

using namespace std;


int main(int argc, char **argv)
{
    // cout << "Assignment-1" << endl;
    // DLinkedListTestCases* dll_test = new DLinkedListTestCases();
    // dll_test->test();
    // XArrayListTestCases* xarr_test = new XArrayListTestCases();
    // xarr_test->test();
    // DLinkedListTest* dll_more_test = new DLinkedListTest();
    // dll_more_test->runAllTests();
    // XArrayListTest* xarr_more_test = new XArrayListTest();
    // xarr_more_test->runAllTests();
    int nsamples = 90;
    xt ::xarray<double> X = xt ::random ::randn<double>({nsamples, 10});
    xt ::xarray<double> T = xt ::random ::randn<double>({nsamples, 5});
    TensorDataset<double, double> ds(X, T);
    DataLoader<double, double> loader(&ds, 31, true, false);
    for (auto batch : loader)
    {
        // cout << shape2str(xt::svector<unsigned long>(batch.getData().shape().begin(), batch.getData().shape().end())) << endl;
        // cout << shape2str(xt::svector<unsigned long>(batch.getLabel().shape().begin(), batch.getLabel().shape().end())) << endl;
        cout << shape2str(batch.getData().shape()) << endl;
        cout << shape2str(batch.getLabel().shape()) << endl;
    }
    return 0;
}
