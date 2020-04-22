#include <stdio.h>
#include <conio.h>
#include <Python.h>

#include <iostream>

using namespace std;

double compute(double x)
{
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;
	double result = 0.0;
	Py_Initialize();
	pName = PyUnicode_FromString("test_module");
	cout << pName << std::endl;
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, "func");
		if (pFunc && PyCallable_Check(pFunc))
		{
			pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(x));
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				result = PyFloat_AsDouble(pValue);
				Py_DECREF(pValue);
			}
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	Py_Finalize();

	return result;
}






int main(int argc, char *argv[])
{
	//PyObject *pName, *pModule, *pDict, *pFunc, *pValue;

	//if (argc < 3)
	//{
	//	printf("Usage: exe_name python_source function_name\n");
	//	return 1;
	//}

	//// Инициализировать интерпретатор Python
	//Py_Initialize();

	//// Построить объект имени
	//pName = PyUnicode_FromString(argv[1]);

	//// Загрузить объект модуля
	//pModule = PyImport_Import(pName);

	//// pDict – заимствованная ссылка
	//pDict = PyModule_GetDict(pModule);

	//// pFunc – тоже заимствованная ссылка
	//pFunc = PyDict_GetItemString(pDict, argv[2]);

	//if (PyCallable_Check(pFunc))
	//{
	//	PyObject_CallObject(pFunc, NULL);
	//}
	//else
	//{
	//	PyErr_Print();
	//}

	//// Вернуть ресурсы системе
	//Py_DECREF(pModule);
	//Py_DECREF(pName);

	//// Завершить интерпретатор Python
	//Py_Finalize();
	cout << compute(5);


	return 0;
}



