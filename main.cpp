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


// string shape2str(xt::svector<unsigned long> vec){
//     stringstream ss;
//     ss << "(";
//     for(int idx=0; idx < vec.size(); idx++){
//         ss << vec[idx] << ", ";
//     }
//     string res = ss.str();
//     if(vec.size() > 1) res = res.substr(0, res.rfind(','));
//     else res = res.substr(0, res.rfind(' '));
//     return res + ")";
// }


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
    int nsamples = 100;
    xt ::xarray<double> X = xt ::random ::randn<double>({nsamples, 10});
    xt ::xarray<double> T = xt ::random ::randn<double>({nsamples, 5});
    TensorDataset<double, double> ds(X, T);
    DataLoader<double, double> loader(&ds, 30, true, true);
    for (auto batch : loader)
    {
        // cout << shape2str(batch.getData().shape()) << endl ;
        
        
        // auto batch_data_shape = batch.getData().shape();
        // auto batch_label_shape = batch.getLabel().shape();
        // // xt::svector<unsigned long> test = xt::svector<unsigned long>(X.shape().begin(), X.shape().end());
        // // cout << shape2str(test) << endl;
        cout << shape2str(xt::svector<unsigned long>(batch.getData().shape().begin(), batch.getData().shape().end())) << endl;
        cout << shape2str(xt::svector<unsigned long>(batch.getLabel().shape().begin(), batch.getLabel().shape().end())) << endl;
        // cout << shape2str(xt::svector<unsigned long>(batch_label_shape.begin(), batch_label_shape.end())) << endl;
    }

    return 0;
}
