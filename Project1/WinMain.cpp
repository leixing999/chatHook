#include<windows.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "MyClass.h"
#pragma comment(lib,"MyDll.lib")/*静态链接*/
using namespace std;
/// <summary>
/// dll基础学习
/// </summary>
/// <param name="hMoudle"></param>
void DllBasic(HMODULE hMoudle) {
	if (!hMoudle) {
		cout << "加载失败" << endl;
	}
	else {
		cout << "加载成功" << endl;
	}

	int varLabel = *(int*)GetProcAddress(hMoudle, "varlabel");/*得到dll变量*/

	typedef int (*Func)();

	cout << varLabel << endl;
	Func dllFunc = (Func)GetProcAddress(hMoudle, "add1");/*得到dll函数地址*/
	cout << dllFunc() << endl;

	MyClass myClass;
	cout << myClass.add(10, 10) << endl;
}
int _tmain(int argc, _TCHAR* argv[]) {
	HMODULE dll = LoadLibrary("Mydll");

	if (!dll) {
		cout << "加载失败" << endl;
	}
	else {
		cout << "加载成功" << endl;
	}
	//DllBasic(dll);
	/*1：普通获取dll函数方式
	typedef HHOOK(*StartHook)(CHAR hookType, DWORD threadId);
	StartHook DllStartHook = (StartHook)GetProcAddress(dll, "startHook");*/
	/*2:强制函数转换*/
	HHOOK(*StartHook)(CHAR hookType, DWORD threadId) = (HHOOK(*)(CHAR hookType, DWORD threadId))GetProcAddress(dll, "StartHook");/*启动钩子函数*/
	bool(*UnHook)(HHOOK hHook) = (bool(*)(HHOOK hHook))GetProcAddress(dll, "UnHook");/*卸载钩子函数*/
	/*===============================================*/
	HHOOK hookInstance = StartHook(9, 0);/*启动线程钩子*/
	
	short szInput = 0;
	while (szInput == 0) {
		cin >> szInput;
	}

	UnHook(hookInstance);/*卸载线程钩子*/
	Sleep(20000);
}