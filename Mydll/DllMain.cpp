#include <windows.h>
#include<stdio.h>
#define MemoryHookLength 5
extern "C" int __declspec(dllexport) varlabel = 10;/*导出变量并按照C语言方式导出*/
extern "C" __declspec(dllexport) int  add1(void){/*导出函数并按照C语言方式导出*/
	return 123456;
}

LRESULT CALLBACK CALLBACK_WH_GETMESSAGE(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截所有的postmessage*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}
LRESULT CALLBACK CALLBACK_WH_CALLWNDPROC (_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截所有的sendmessage*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}
LRESULT CALLBACK CALLBACK_WH_CBT(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截所有的事件*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}
LRESULT CALLBACK CALLBACK_DEBUG(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截钩子创建类型*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}

LRESULT CALLBACK CALLBACK_WH_DEBUG(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截钩子创建类型*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}

LRESULT CALLBACK CALLBACK_WH_FOREGROUNDIDLE(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截线程休眠暂停线程*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}

LRESULT CALLBACK CALLBACK_WH_MOUSE_LL(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截鼠标（判断鼠标是模拟的还是硬件的）*/
	if (nCode == HC_ACTION) {/*进入钩子必须判断这个*/
		MOUSEHOOKSTRUCT pMouseHook = *((PMOUSEHOOKSTRUCT)lParam);/*构建底层鼠标消息*/
		if (pMouseHook.wHitTestCode) {/*当他为1时候，是系统模拟的鼠标消息，否则是硬件鼠标消息*/
			switch (wParam)
			{
			case WM_MOUSEMOVE:
				printf("鼠标移动了\n");
				return true;
				break;
			case WM_LBUTTONDOWN:
				printf("鼠标按下了\n");
			case WM_LBUTTONUP:
				printf("鼠标抬起了\n");
			default:
				break;
			}
		}
		else {

		}

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}

LRESULT CALLBACK CALLBACK_WH_MOUSE(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截鼠标，只能拦截到所有鼠标消息*/

	if (nCode == HC_ACTION) {/*进入钩子必须判断这个*/
		printf("有鼠标消息了\n");
		
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}

LRESULT CALLBACK CALLBACK_WH_KEYBOARD(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截键盘消息*/
	printf("有键盘消息了\n");
	if (nCode == HC_ACTION) {/*进入钩子必须判断这个*/
		printf("有键盘消息了\n");

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}
LRESULT CALLBACK CALLBACK_WH_KEYBOARD_LL(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*拦截键盘消息*/

	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
	if (nCode == HC_ACTION) {/*进入钩子必须判断这个*/
		if (WM_KEYDOWN == wParam) {
			if (key->vkCode == 97) {
				printf("不让你按下1\n");
				return true;
			}
		}
		if (WM_KEYUP == wParam) {
			//printf("抬起键盘\n");
		}
		//printf("有键盘消息了:%d\n",key->vkCode);

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*直接进入下一个消息钩子处理*/
}
HHOOK m_hook =NULL;/*用于卸载时候的钩子句柄*/
HINSTANCE m_histance = 0; /*全局句柄*/

extern "C" __declspec(dllexport) HHOOK StartHook(CHAR hookType, DWORD threadId) {/*创建一个钩子函数*/

	switch (hookType)
	{
	case 1:
		m_hook = SetWindowsHookEx(WH_GETMESSAGE, CALLBACK_WH_GETMESSAGE, m_histance, threadId);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
	
		m_hook = SetWindowsHookEx(WH_KEYBOARD_LL, CALLBACK_WH_KEYBOARD_LL, m_histance, threadId);
		MSG msg;
		while (GetMessage(&msg,NULL,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		break;
	case 10:
		break;
	}
	return m_hook;
}

extern "C" __declspec(dllexport) bool UnHook(HHOOK hHook) {/*卸载一个钩子函数*/
	return UnhookWindowsHookEx(hHook);
}
BYTE RecoveryMemory[MemoryHookLength];/*恢复的数据只是临时的缓存*/
BYTE RecoveryMemoryMyTextOut[MemoryHookLength];
BYTE* MemoryHook(LPVOID APIAddress,/*我们要勾住的API地址*/ LPVOID jmpAddress/*我们跳转的位置*/) {

	DWORD oldProtectAttiute;
	if (VirtualProtectEx(GetCurrentProcess(), APIAddress, MemoryHookLength, PAGE_EXECUTE_READWRITE, &oldProtectAttiute))//修改地址的保护属性
	{
		if (!ReadProcessMemory(GetCurrentProcess(), APIAddress, RecoveryMemory, MemoryHookLength, NULL)) {//读取内存地址信息
			printf("读取内存失败\n", GetLastError());
		}
		CHAR Shellcode[12];
		ZeroMemory(Shellcode, 12);
		Shellcode[0] = 0xE9;/*jmp跳转*/
		*(DWORD*)(Shellcode + 1) = (DWORD)APIAddress - (DWORD)jmpAddress - 5;/*地址跳转公式*/
		if (!WriteProcessMemory(GetCurrentProcess(), APIAddress, Shellcode, MemoryHookLength, NULL))/*写内存数据*/
		{
			printf("写内存失败\n", GetLastError());
		}
	}
	VirtualProtectEx(GetCurrentProcess(), APIAddress, MemoryHookLength, oldProtectAttiute, &oldProtectAttiute);//恢复之前的保护属性

	return RecoveryMemory;
}
/*恢复地址函数*/
CHAR RecoveryCode(LPVOID APIAddress, BYTE* RecoverData) {
	if (!WriteProcessMemory(GetCurrentProcess(), APIAddress, RecoverData, MemoryHookLength, NULL))/*写内存数据*/
	{
		printf("写内存失败\n", GetLastError());
		return -1;
	}
	return 0;
}




BOOL WINAPI MyTextOut(_In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c)LPCWSTR lpString, _In_ int c) {
	BOOL ret = FALSE;
	if (c)
	{
		wprintf(lpString);
	}
	RecoveryCode(TextOutW,RecoveryMemoryMyTextOut);
	ret =TextOutW( hdc,  x,  y, lpString, c);
	return ret;
}



BOOL APIENTRY DllMain(HMODULE hMoudle,/*当前DLL句柄*/DWORD call_Reason,/*调用原因*/ LPCVOID lpReserved) {

	switch (call_Reason)
	{
	case DLL_PROCESS_ATTACH:/*被进程加载的时候*/
		m_histance = hMoudle;
		memcpy(RecoveryMemoryMyTextOut, MemoryHook(TextOutW,/*我们要勾住的API地址*/ MyTextOut/*我们跳转的位置*/), MemoryHookLength);
		break;
	case DLL_THREAD_ATTACH:/*当进程有新的线程的时候*/
		break;
	case DLL_THREAD_DETACH:/*进程有一个线程关闭的时候*/
		break;
	case DLL_PROCESS_DETACH:/*进程被卸载的时候*/
		break;
	}
	return TRUE;
}