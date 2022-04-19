/*
Name: Emmanuela Filev-Mihalak
Class: CS210
Project Three
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream> 

using namespace std;


void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Project_Three");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Project_Three");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}


int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Project_Three");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void DisplayMenu() {
	// shows user each option available, including terminating the program
	cout << "Grocery Item Tracker" << endl;
	cout << "1: Display list of all items purchased and frequency of each item purchased" << endl;
	cout << "2: Show how many times a specific item was purchased" << endl;
	cout << "3: Create a text-based histogram listing all items purchased in a day" << endl;
	cout << "4: Exit program" << endl;
	cout << endl;
	cout << "Enter your selection:" << endl;
}

// Opens file frequency.dat and creates text-based histogram based on info
void ItemHistogram() {
	string item;
	int frequency;

	cout << endl;

	// Opens file in which Python info was added about groceries
	ifstream inFS;
	inFS.open("frequency.dat");

	// Validates file 
	if (!inFS.is_open()) {
		cout << "Could not open file frequency.dat." << endl;
		return;
	}

	inFS >> item;

	while (!inFS.fail()) {
		inFS >> frequency;

		cout << item << " ";

		// Loop adds asterisk for each occurrence of item in list 
		for (int i = 0; i < frequency; i++) {
			cout << "*";
		}

		cout << endl;

		inFS.clear(); // Clears container and resets
		inFS >> item; // Reads next line starting with name and resets loop	
	}


	inFS.close();
}

void main()
{
	int menuChoice = 0;
	string itemEntry = "";

	// Switches between menu option inputs 
	while (menuChoice != 4) {
		DisplayMenu();
		cin >> menuChoice;
		switch (menuChoice) {
		case 1:
			// Calls ListFrequency function in Python
			CallProcedure("ListFrequency");
			cout << endl;
			break;
		case 2:
			// Asks for input and calls ItemFrequency function in Python
			cout << "Enter item:" << endl;
			cin >> itemEntry;
			callIntFunc("ItemFrequency", itemEntry);
			break;
		case 3:
			// Calls FileTransfer function in Python and ItemHistogram function in C++
			CallProcedure("FileTransfer");
			ItemHistogram();
			break;
		case 4:
			cout << "Program exited." << endl;
			break;
			// Validates input
		default:
			cout << "Invalid input. Please try again" << endl;
			break;
		}
	}

}