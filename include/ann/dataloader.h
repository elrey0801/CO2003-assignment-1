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
    // xvector<int>* index_container = new xvector<int>();
    xt::xarray<int> index_container;
    int taken_range;


public:
    DataLoader(Dataset<DType, LType>* ptr_dataset,
            int batch_size,
            bool shuffle=true,
            bool drop_last=false){
        /*TODO: Add your code to do the initialization */
        this->ptr_dataset = ptr_dataset;
        this->shuffle = shuffle;
        this->drop_last = drop_last;
        this->batch_size = batch_size;
        this->taken_range = this->ptr_dataset->len();
        if(drop_last)
            this->taken_range = (this->taken_range / batch_size) * batch_size;
        // for(int i = 0; i < this->taken_range; ++i)
        //     index_container->add(i);
        this->index_container = xt::arange(this->taken_range);

        cout << "Before:::" << endl;
        for(auto n : this->index_container) cout << n << " ";

        if(shuffle) {
            // std::random_device seed;
            // std::mt19937 generator(seed());
            // for(int i = this->taken_range - 1; i > 0; --i) {
            //     std::uniform_int_distribution<> dis(0, i);
            //     int swap_index = dis(generator);
            //     int temp = this->index_container->get(i);
            //     this->index_container->get(i) = this->index_container->get(swap_index);
            //     this->index_container->get(swap_index) = temp;
            // }
            xt::random::shuffle(this->index_container);
        }
        
        cout << "After:::" << endl;
        for(auto n : this->index_container) cout << n << " ";
    }

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
    
    /*TODO: Add your code here to support iteration on batch*/
    
    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, this->taken_range);
    }

    class Iterator {
    private:
        DataLoader<DType, LType>* dataloader;
        int data_index;
    
    public:
        Iterator(DataLoader<DType, LType>* dataloader, int data_index) {
            this->dataloader = dataloader;
            this->data_index = data_index;
        }
        bool operator!=(const Iterator& iterator) {
            return this->data_index != iterator.data_index;
        }
        Iterator &operator++() {
            this->data_index = min(this->data_index + this->dataloader->batch_size, this->dataloader->taken_range);
            // this->data_index += this->dataloader->batch_size;
            return *this;
        }
        Batch<DType, LType> operator*() {
            int end_batch_index = min(this->data_index + this->dataloader->batch_size, this->dataloader->taken_range);
            auto data_shape = this->dataloader->ptr_dataset->get_data_shape();
            auto label_shape = this->dataloader->ptr_dataset->get_label_shape();
            data_shape[0] = end_batch_index - this->data_index;
            label_shape[0] = end_batch_index - this->data_index;
            xt::xarray<DType> batch_data = xt::zeros<DType>(data_shape);
            xt::xarray<LType> batch_label = xt::zeros<LType>(label_shape);

            for(int i = this->data_index; i < end_batch_index; i++) {
                // auto item = this->dataloader->ptr_dataset->getitem(this->dataloader->index_container->get(i));
                auto item = this->dataloader->ptr_dataset->getitem(this->dataloader->index_container(i));
                xt::view(batch_data, i - this->data_index) = item.getData();
                xt::view(batch_label, i - this->data_index) = item.getLabel();
            }

            return Batch<DType, LType>(batch_data, batch_label);        
        }
    };


    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};


#endif /* DATALOADER_H */

