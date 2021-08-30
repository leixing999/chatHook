#include <windows.h>
#include<stdio.h>
#define MemoryHookLength 5
extern "C" int __declspec(dllexport) varlabel = 10;/*��������������C���Է�ʽ����*/
extern "C" __declspec(dllexport) int  add1(void){/*��������������C���Է�ʽ����*/
	return 123456;
}

LRESULT CALLBACK CALLBACK_WH_GETMESSAGE(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*�������е�postmessage*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}
LRESULT CALLBACK CALLBACK_WH_CALLWNDPROC (_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*�������е�sendmessage*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}
LRESULT CALLBACK CALLBACK_WH_CBT(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*�������е��¼�*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}
LRESULT CALLBACK CALLBACK_DEBUG(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*���ع��Ӵ�������*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}

LRESULT CALLBACK CALLBACK_WH_DEBUG(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*���ع��Ӵ�������*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}

LRESULT CALLBACK CALLBACK_WH_FOREGROUNDIDLE(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*�����߳�������ͣ�߳�*/
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}

LRESULT CALLBACK CALLBACK_WH_MOUSE_LL(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*������꣨�ж������ģ��Ļ���Ӳ���ģ�*/
	if (nCode == HC_ACTION) {/*���빳�ӱ����ж����*/
		MOUSEHOOKSTRUCT pMouseHook = *((PMOUSEHOOKSTRUCT)lParam);/*�����ײ������Ϣ*/
		if (pMouseHook.wHitTestCode) {/*����Ϊ1ʱ����ϵͳģ��������Ϣ��������Ӳ�������Ϣ*/
			switch (wParam)
			{
			case WM_MOUSEMOVE:
				printf("����ƶ���\n");
				return true;
				break;
			case WM_LBUTTONDOWN:
				printf("��갴����\n");
			case WM_LBUTTONUP:
				printf("���̧����\n");
			default:
				break;
			}
		}
		else {

		}

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}

LRESULT CALLBACK CALLBACK_WH_MOUSE(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*������ֻ꣬�����ص����������Ϣ*/

	if (nCode == HC_ACTION) {/*���빳�ӱ����ж����*/
		printf("�������Ϣ��\n");
		
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}

LRESULT CALLBACK CALLBACK_WH_KEYBOARD(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*���ؼ�����Ϣ*/
	printf("�м�����Ϣ��\n");
	if (nCode == HC_ACTION) {/*���빳�ӱ����ж����*/
		printf("�м�����Ϣ��\n");

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}
LRESULT CALLBACK CALLBACK_WH_KEYBOARD_LL(_In_ int nCode, _In_ WPARAM  wParam, _In_ LPARAM lParam) {/*���ؼ�����Ϣ*/

	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
	if (nCode == HC_ACTION) {/*���빳�ӱ����ж����*/
		if (WM_KEYDOWN == wParam) {
			if (key->vkCode == 97) {
				printf("�����㰴��1\n");
				return true;
			}
		}
		if (WM_KEYUP == wParam) {
			//printf("̧�����\n");
		}
		//printf("�м�����Ϣ��:%d\n",key->vkCode);

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);/*ֱ�ӽ�����һ����Ϣ���Ӵ���*/
}
HHOOK m_hook =NULL;/*����ж��ʱ��Ĺ��Ӿ��*/
HINSTANCE m_histance = 0; /*ȫ�־��*/

extern "C" __declspec(dllexport) HHOOK StartHook(CHAR hookType, DWORD threadId) {/*����һ�����Ӻ���*/

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

extern "C" __declspec(dllexport) bool UnHook(HHOOK hHook) {/*ж��һ�����Ӻ���*/
	return UnhookWindowsHookEx(hHook);
}
BYTE RecoveryMemory[MemoryHookLength];/*�ָ�������ֻ����ʱ�Ļ���*/
BYTE RecoveryMemoryMyTextOut[MemoryHookLength];
BYTE* MemoryHook(LPVOID APIAddress,/*����Ҫ��ס��API��ַ*/ LPVOID jmpAddress/*������ת��λ��*/) {

	DWORD oldProtectAttiute;
	if (VirtualProtectEx(GetCurrentProcess(), APIAddress, MemoryHookLength, PAGE_EXECUTE_READWRITE, &oldProtectAttiute))//�޸ĵ�ַ�ı�������
	{
		if (!ReadProcessMemory(GetCurrentProcess(), APIAddress, RecoveryMemory, MemoryHookLength, NULL)) {//��ȡ�ڴ��ַ��Ϣ
			printf("��ȡ�ڴ�ʧ��\n", GetLastError());
		}
		CHAR Shellcode[12];
		ZeroMemory(Shellcode, 12);
		Shellcode[0] = 0xE9;/*jmp��ת*/
		*(DWORD*)(Shellcode + 1) = (DWORD)APIAddress - (DWORD)jmpAddress - 5;/*��ַ��ת��ʽ*/
		if (!WriteProcessMemory(GetCurrentProcess(), APIAddress, Shellcode, MemoryHookLength, NULL))/*д�ڴ�����*/
		{
			printf("д�ڴ�ʧ��\n", GetLastError());
		}
	}
	VirtualProtectEx(GetCurrentProcess(), APIAddress, MemoryHookLength, oldProtectAttiute, &oldProtectAttiute);//�ָ�֮ǰ�ı�������

	return RecoveryMemory;
}
/*�ָ���ַ����*/
CHAR RecoveryCode(LPVOID APIAddress, BYTE* RecoverData) {
	if (!WriteProcessMemory(GetCurrentProcess(), APIAddress, RecoverData, MemoryHookLength, NULL))/*д�ڴ�����*/
	{
		printf("д�ڴ�ʧ��\n", GetLastError());
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



BOOL APIENTRY DllMain(HMODULE hMoudle,/*��ǰDLL���*/DWORD call_Reason,/*����ԭ��*/ LPCVOID lpReserved) {

	switch (call_Reason)
	{
	case DLL_PROCESS_ATTACH:/*�����̼��ص�ʱ��*/
		m_histance = hMoudle;
		memcpy(RecoveryMemoryMyTextOut, MemoryHook(TextOutW,/*����Ҫ��ס��API��ַ*/ MyTextOut/*������ת��λ��*/), MemoryHookLength);
		break;
	case DLL_THREAD_ATTACH:/*���������µ��̵߳�ʱ��*/
		break;
	case DLL_THREAD_DETACH:/*������һ���̹߳رյ�ʱ��*/
		break;
	case DLL_PROCESS_DETACH:/*���̱�ж�ص�ʱ��*/
		break;
	}
	return TRUE;
}