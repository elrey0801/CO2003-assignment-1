/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataset.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 3:59 PM
 */

#ifndef DATASET_H
#define DATASET_H
#include "ann/xtensor_lib.h"
using namespace std;

template<typename DType, typename LType>
class DataLabel{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
public:
    DataLabel(xt::xarray<DType> data,  xt::xarray<LType> label):
    data(data), label(label){
    }
    xt::xarray<DType> getData() const{ return data; }
    xt::xarray<LType> getLabel() const{ return label; }
};

template<typename DType, typename LType>
class Batch{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
public:
    Batch(xt::xarray<DType> data,  xt::xarray<LType> label):
    data(data), label(label){
    }
    virtual ~Batch(){}
    xt::xarray<DType>& getData(){return data; }
    xt::xarray<LType>& getLabel(){return label; }
};


template<typename DType, typename LType>
class Dataset{
private:
public:
    Dataset(){};
    virtual ~Dataset(){};
    
    virtual int len()=0;
    virtual DataLabel<DType, LType> getitem(int index)=0;
    // temperary change to size_t
    virtual xt::svector<size_t> get_data_shape()=0;
    virtual xt::svector<size_t> get_label_shape()=0;
    // virtual xt::svector<unsigned long> get_data_shape()=0;
    // virtual xt::svector<unsigned long> get_label_shape()=0;
    
};

//////////////////////////////////////////////////////////////////////
template<typename DType, typename LType>
class TensorDataset: public Dataset<DType, LType>{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
    // temperary change to size_t
    // xt::svector<unsigned long> data_shape, label_shape;
    xt::svector<size_t> data_shape, label_shape;
    
public:
    /* TensorDataset: 
     * need to initialize:
     * 1. data, label;
     * 2. data_shape, label_shape
    */
    TensorDataset(xt::xarray<DType> data, xt::xarray<LType> label){
        /* TODO: your code is here for the initialization
         */
        this->data = data;
        this->label = label;
        // this->data_shape = xt::svector<unsigned long>(data.shape().begin(), data.shape().end());
        // this->label_shape = xt::svector<unsigned long>(label.shape().begin(), label.shape().end());
        this->data_shape = data.shape();
        this->label_shape = label.shape();
    }
    /* len():
     *  return the size of dimension 0
    */
    int len(){
        /* TODO: your code is here to return the dataset's length
         */
        return this->data.shape()[0]; //remove it when complete
    }
    
    /* getitem:
     * return the data item (of type: DataLabel) that is specified by index
     */
    DataLabel<DType, LType> getitem(int index){
        /* TODO: your code is here
         */
        if(index < 0 || index >= this->len())
            throw std::out_of_range("Invalid index");
        auto i_data = xt::view(this->data, index);
        xt::xarray<LType> i_label;
        if(this->label_shape.size() != 0)
            i_label = xt::view(this->label, index);
        return DataLabel<DType, LType>(i_data, i_label);
    }
    
    // temperary change to size_t
    // xt::svector<unsigned long> get_data_shape(){
    xt::svector<size_t> get_data_shape(){
        /* TODO: your code is here to return data_shape
         */
        return this->data_shape;
    }
    // temperary change to size_t
    // xt::svector<unsigned long> get_label_shape(){
    xt::svector<size_t> get_label_shape(){
        /* TODO: your code is here to return label_shape
         */
        return this->label_shape;
    }
};


// template<typename DType, typename LType>
// class ImageFolderDataset : public Dataset<DType, LType> {
    
// };



#endif /* DATASET_H */

