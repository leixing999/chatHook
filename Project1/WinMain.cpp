#include<windows.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "MyClass.h"
#pragma comment(lib,"MyDll.lib")/*��̬����*/
using namespace std;
/// <summary>
/// dll����ѧϰ
/// </summary>
/// <param name="hMoudle"></param>
void DllBasic(HMODULE hMoudle) {
	if (!hMoudle) {
		cout << "����ʧ��" << endl;
	}
	else {
		cout << "���سɹ�" << endl;
	}

	int varLabel = *(int*)GetProcAddress(hMoudle, "varlabel");/*�õ�dll����*/

	typedef int (*Func)();

	cout << varLabel << endl;
	Func dllFunc = (Func)GetProcAddress(hMoudle, "add1");/*�õ�dll������ַ*/
	cout << dllFunc() << endl;

	MyClass myClass;
	cout << myClass.add(10, 10) << endl;
}
int _tmain(int argc, _TCHAR* argv[]) {
	HMODULE dll = LoadLibrary("Mydll");

	if (!dll) {
		cout << "����ʧ��" << endl;
	}
	else {
		cout << "���سɹ�" << endl;
	}
	//DllBasic(dll);
	/*1����ͨ��ȡdll������ʽ
	typedef HHOOK(*StartHook)(CHAR hookType, DWORD threadId);
	StartHook DllStartHook = (StartHook)GetProcAddress(dll, "startHook");*/
	/*2:ǿ�ƺ���ת��*/
	HHOOK(*StartHook)(CHAR hookType, DWORD threadId) = (HHOOK(*)(CHAR hookType, DWORD threadId))GetProcAddress(dll, "StartHook");/*�������Ӻ���*/
	bool(*UnHook)(HHOOK hHook) = (bool(*)(HHOOK hHook))GetProcAddress(dll, "UnHook");/*ж�ع��Ӻ���*/
	/*===============================================*/
	HHOOK hookInstance = StartHook(9, 0);/*�����̹߳���*/
	
	short szInput = 0;
	while (szInput == 0) {
		cin >> szInput;
	}

	UnHook(hookInstance);/*ж���̹߳���*/
	Sleep(20000);
}