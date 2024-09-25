/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include "list/listheader.h"
#include <random>

using namespace std;

template<typename DType, typename LType>
class DataLoader{
public:
    class Iterator;
private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    /*TODO: add more member variables to support the iteration*/
    xvector<int> index_container;

public:
    DataLoader(Dataset<DType, LType>* ptr_dataset,
            int batch_size,
            bool shuffle=true,
            bool drop_last=false){
        /*TODO: Add your code to do the initialization */
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(index_container.begin(), index_container.end(), g);
    }
    virtual ~DataLoader(){}

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
    
    /*TODO: Add your code here to support iteration on batch*/
    
    Iterator begin() {

    }

    Iterator end() {

    }

    class Iterator {
    private:
        DataLoader<DType, LType>* dataloader;
        int data_index;
    
    public:
        Iterator(DataLoader<DType, LType>* dataloader) {
            this->dataloader = dataloader;
            this->data_index = 0;
        }
        bool operator!=(const Iterator& iterator) {
            return this->data_index != iterator.data_index;
        }
        Iterator &operator++() {
            this->data_index += this->dataloader->batch_size;
            return *this;
        }
        Batch<DType, LType> &operator*() {
            int end_batch_index = min(this->data_index + this->dataloader->batch_size, this->dataloader->ptr_dataset->len());
            
        }
    };


    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};


#endif /* DATALOADER_H */

