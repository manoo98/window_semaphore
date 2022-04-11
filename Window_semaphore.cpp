
//#include "Window_Semaphore.h"

#include <iostream>
#include <Windows.h>
#include <thread>
#include <stdlib.h>

#define INFINITY
using namespace std;

HANDLE hsemaphore;
int a, b, c;


DWORD WINAPI input_thread(LPVOID lpParameter);
DWORD WINAPI output_thread(LPVOID lpParameter);


int main()
{
	HANDLE hthread1;
	HANDLE hthread2;

	hsemaphore = CreateSemaphore(NULL, 0, 1, NULL);
	if (hsemaphore == NULL)
	{
		cout << "Kindly wait, Semaphore Not Created. \n S_Resourcer is busy.\n\n" << endl;
		cout << "Error: " << GetLastError() << endl;
	}
	cout << "Semaphore is Created. " << hsemaphore << endl;



	hthread1 = CreateThread(NULL, 0, &input_thread, NULL, 0, 0);
	Sleep(5000);
	hthread2 = CreateThread(NULL, 0, &output_thread, NULL, 0, 0);


	WaitForSingleObject(hthread1, INFINITE);
	WaitForSingleObject(hthread2, INFINITE);

	CloseHandle(hthread1);
	CloseHandle(hthread2);

	CloseHandle(hsemaphore);

	system("PAUSE");

	return 0;
}




// INPUT THREADS
DWORD WINAPI input_thread(LPVOID lpParameter)
{
	AcquireSemaphore(hsemaphore, 0, 1);
	cout << "Enter first value" << endl;
	cin >> a;

	cout << "Enter second value" << endl;
	cin >> b;

	//operators();

	ReleaseSemaphore(hsemaphore, 1, 0);
	return 0;
}


// OUTPUT THREADS
DWORD WINAPI output_thread(LPVOID lpParameter)
{
	WaitForSingleObject(hsemaphore, 2000);
	cout << "Waiting for the result" << endl;
	c = a + b;
	Sleep(1000);
	cout << "Result: " << c << endl;
	return 0;
}
