//
// Created by xirhxq on 2022/3/8.
//
#include "python/Python.h"

int main(){
    Py_Initialize();

    PyRun_SimpleString("print 'hello'");

    Py_Finalize();
}

