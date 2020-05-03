#include <stdio.h>
#include <conio.h>
#include <iostream>


#include <Python.h>


using namespace std;

PyObject *pName = NULL, *pModule = NULL;
PyObject *pDict = NULL;
PyObject* sys = NULL;
PyObject* sys_path = NULL;
PyObject* folder_path = NULL;

/*
 * Загрузка интерпритатора python и модуля func.py в него.
 */
PyObject * python_init(const char str[]) {
	// Инициализировать интерпретатор Python
	Py_Initialize();

	do {
		// Загрузка модуля sys
		sys = PyImport_ImportModule("sys");
		sys_path = PyObject_GetAttrString(sys, "path");
		// Путь до наших исходников python
		folder_path = PyUnicode_FromString((const char*) "./");
		PyList_Append(sys_path, folder_path);

		// Создание Unicode объекта из UTF-8 строки
		pName = PyUnicode_FromString(str);
		if (!pName) {
			break;
		}

		// Загрузить модуль func
		pModule = PyImport_Import(pName);
		if (!pModule) {
			break;
		}

		// Словарь объектов содержащихся в модуле
		pDict = PyModule_GetDict(pModule);
		if (!pDict) {
			break;
		}

		return pDict;
	} while (0);

	// Печать ошибки
	PyErr_Print();
}

/*
 * Освобождение ресурсов интерпритатора python
 */
void
python_clear() {
	// Вернуть ресурсы системе
	Py_XDECREF(pDict);
	Py_XDECREF(pModule);
	Py_XDECREF(pName);

	Py_XDECREF(folder_path);
	Py_XDECREF(sys_path);
	Py_XDECREF(sys);

	// Выгрузка интерпритатора Python
	Py_Finalize();
}



void python_class(double* data, int size) {

	PyObject *pClass = PyDict_GetItemString(pDict, (const char *) "MathStat");
	
	PyObject * pArgs = NULL, *pVal = NULL, *pInstance = NULL;

	pArgs = PyTuple_New(size);
	for (int i = 0; i < size; i++) {
		PyTuple_SetItem(pArgs, i, PyFloat_FromDouble((data)[i]));
	}
	if(pArgs != NULL) {
		//pVal = PyObject_CallObject(pObjct, pArgs);
		pInstance = PyObject_CallObject(pClass, pArgs);
		pVal = PyObject_CallMethod(pInstance, (char*) "all", NULL);
		if (pVal != NULL) {
			for (int i = 0; i < size; i++) {
				cout << (data)[i] << " ";
			}
			// вывод результатов из кортежа
			cout<< endl << "mean = " <<  PyFloat_AsDouble(PyTuple_GetItem(pVal, 0)) <<  endl << "variance = " << PyFloat_AsDouble(PyTuple_GetItem(pVal, 1)) << endl;
			Py_XDECREF(pClass);
			Py_XDECREF(pVal);
			Py_XDECREF(pArgs);
		}
	}
	Py_XDECREF(pClass);
	Py_XDECREF(pVal);
	Py_XDECREF(pArgs);
}

void python_fun_sq(double number) {
	
	PyObject *pVal = NULL, *pArgs = NULL;
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(number));
	PyObject *pObjct = PyDict_GetItemString(pDict, (const char *) "poww");
	pVal = PyObject_CallObject(pObjct, pArgs);
	if (pVal != NULL) {
		cout << number << "^2 = " << PyFloat_AsDouble(pVal) << endl;
	}
	Py_XDECREF(pVal);
	Py_XDECREF(pArgs);
	Py_XDECREF(pObjct);
}

void python_fun_array(unsigned n) {

	PyObject *pVal = NULL, *pArgs = NULL;
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", n));
	PyObject *pObjct = PyDict_GetItemString(pDict, (const char *) "array");
	pVal = PyObject_CallObject(pObjct, pArgs);
	if (pVal != NULL) {
		// вывод содержимого кортежа(результата работы скрипта)
		for (int i = 0; i < PyTuple_Size(pVal); i++) {
			cout << PyFloat_AsDouble(PyTuple_GetItem(pVal, i)) << " ";
		}
		cout << endl;
		Py_XDECREF(pVal);
		Py_XDECREF(pArgs);
		Py_XDECREF(pObjct);
	}
	Py_XDECREF(pVal);
	Py_XDECREF(pArgs);
	Py_XDECREF(pObjct);

}



int main() {

	if (!python_init("test1")) {
		puts("python_init error");
		return -1;
	}
	int size = 10;
	double *ptrarr = new double[size];
	// заполнение массива
	for (int i = 0; i < size; i++) {
		(ptrarr)[i] = (double)rand() / RAND_MAX;
	}

	cout << "Test func pow:" << endl;
	double number = 1.1;
	// возведние в квадрат number
	python_fun_sq(number);

	cout << endl << "Test func array:" << endl;

	unsigned n = 5;
	// генерация последовательности чисел
	python_fun_array(n);

	python_clear();
	
	cout << endl << "Test Class:" << endl;
	
	python_init("test_class");
	python_class(ptrarr, size);
	python_clear();

	return 0;
}