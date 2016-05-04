#include<iostream>
#include<stdio.h>
#include<Windows.h>
#include<string.h>
//static LPCTSTR g_szMutexName = "w2kdg.ProcTerm.mutex.Suicide";
typedef struct BACK_PACK {
	SYSTEMTIME start_time;
	PROCESS_INFORMATION pi;
}BACK_PACK;

void Child();
void Parent(char*);
BACK_PACK StartClone();

int main(int argc, char* argv[]) {

	Parent(argv[1]);
	system("pause");
	return 0;
}

BACK_PACK StartClone(char* Filename) {
	char szFilename[MAX_PATH] = {0};
	// get current file path
	// szFilename = C:\Users\bit_zt\documents\visual studio 2015\Projects\test\Debug\mytime.exe
	// \"%s\" task.exe
	char* s = "C:\\Users\\bit_zt\\documents\\visual studio 2015\\Projects\\test\\Debug\\\0";
	strcat_s(szFilename, s);
	strcat_s(szFilename, Filename);


	STARTUPINFO si;		// 子进程的启动信息结构
	ZeroMemory(reinterpret_cast<void*>(&si), sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;		// 接收返回的子进程信息

	struct BACK_PACK son_thread_info;

	GetSystemTime(&son_thread_info.start_time);

	BOOL bCreateOK = CreateProcess(
		szFilename,				// 启动的进程名称，含路径
		NULL,					// 命令行参数，本程序中为空
		NULL,					// 进程安全性，缺省值
		NULL,					// 线程安全性，缺省值
		FALSE,					// 不继承句柄
		CREATE_NEW_CONSOLE,		// 创建新窗口
		NULL,					// 新环境环境块为空，子进程使用父进程环境块 
		NULL,					// 新进程驱动器和目录，子进程使用父进程...
		&si,					//
		&pi);
	son_thread_info.pi = pi;

	return son_thread_info;
}

void Parent(char* Filename) {
	printf("Creating the child process and waited child process to quit.\n");
	BACK_PACK pack = StartClone(Filename);
	HANDLE hchild = pack.pi.hProcess;
	if (hchild != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(hchild, INFINITE);

		CloseHandle(hchild);			// 取消父子进程之间联系
		CloseHandle(pack.pi.hThread);

		SYSTEMTIME start_time = pack.start_time, end_time;
		GetSystemTime(&end_time);
		printf("The child process had quited.\n");
		printf("-------------------------------\n");
		printf("begin at %dhour %dm %d.%ds\n", start_time.wHour, start_time.wMinute, start_time.wSecond, start_time.wMilliseconds);
		printf("begin at %dhour %dm %d.%ds\n", end_time.wHour, end_time.wMinute, end_time.wSecond, end_time.wMilliseconds);
		printf("running time is %ds.\n", (end_time.wMinute - start_time.wMinute) * 60 + (end_time.wSecond - start_time.wSecond));
		printf("-------------------------------\n");
	}
	else {
		printf("Create child process failed.\n");
	}
}
