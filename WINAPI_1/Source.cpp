#define _CRT_SECURE_NO_WARNINGS
#define PATH L"D:\\Study\\Myxin\\С\\WINAPI_1\\otv.txt"
#define PATH1 L"D:\\Study\\Myxin\\С\\WINAPI_1\\koef.txt"
#define COUNT 100 * sizeof(WCHAR)

#include <Windows.h>
#include <stdio.h>
#include <math.h>

void SaveOTV(LPWSTR otv)
{
	HANDLE hFile = CreateFileW(PATH,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	OVERLAPPED olf = { 0 };
	olf.Offset = 0;
	LPCTSTR Bufferwrite = otv;
	DWORD ActualCount = 0;
	WriteFile(hFile, Bufferwrite, wcslen(Bufferwrite) * sizeof(WCHAR), &ActualCount, &olf);
	LPWSTR BufferRead = calloc(COUNT, sizeof(WCHAR));
	if(!ReadFile(hFile, BufferRead, COUNT, &ActualCount, &olf))
	{
		MessageBox(NULL, L"Произошла ошибка", L"Ошибка", MB_OK);
	}
	else
	{
		MessageBox(NULL, BufferRead, L"Содержание файла", MB_OK);
	}
	olf.Offset = ActualCount;
	CloseHandle(hFile);
}
void KvadUr(LPWSTR ar)
{
	
	int d = ((int)ar[1]-48) * ((int)ar[1] - 48) - 4 * ((int)ar[0] - 48) * ((int)ar[2] - 48);
		if (d < 0)
		{
			MessageBox(NULL, L"Нет корней", L"Результат", MB_OK);
			LPWSTR mesinfo = malloc(COUNT);
			swprintf(mesinfo, COUNT, L"Нет корней. Дискрименант равен %d", d);
			SaveOTV(mesinfo);
			free(mesinfo);
		}
		else if (d > 0)
		{
			float x1 = ((int)(-ar[1] - 48) + sqrt(d)) / (2 * ((int)ar[0] - 48));
			float x2 = ((int)(-ar[1] - 48) - sqrt(d)) / (2 * ((int)ar[0] - 48));
			LPWSTR mes = malloc(COUNT);
			swprintf(mes, COUNT, L"Первый корень: %f, второй корень: %f", x1, x2);
			MessageBox(NULL, mes, L"Результат", MB_OK);
			LPWSTR mesinfo = malloc(COUNT);
			swprintf(mesinfo, COUNT, L"Первый корень: %f, второй корень: %f\nДва корня. Дискрименант равен %d",x1,x2,d);
			free(mes);
			SaveOTV(mesinfo);
			free(mesinfo);
		}
		else
		{
			float x = ((int)(-ar[1]) - 48) / (2 * ((int)ar[0] - 48));
			LPWSTR mes = malloc(COUNT);
			swprintf(mes, COUNT, L"Корень: %f", x);
			MessageBox(NULL, mes, L"Результат", MB_OK);
			LPWSTR mesinfo = malloc(COUNT);
			swprintf(mesinfo, COUNT, L"Корень: %f\nОдин корень. Дискрименант равен %d", x, d);
			free(mes);
			SaveOTV(mesinfo);
			free(mesinfo);
		}

	}

//BYTE WcharToByte(WCHAR C)
//{
//	switch (C)
//	{
//	case L'0':
//		return 0;
//	case L'1':
//		return 1;
//	case L'2':
//		return 2;
//	case L'3':
//		return 3;
//	case L'4':
//		return 4;
//	case L'5':
//		return 5;
//	case L'6':
//		return 6;
//	case L'7':
//		return 7;
//	case L'8':
//		return 8;
//	case L'9':
//		return 9;
//	default:
//			return 225;
//	}
//}
//int LpwstrToInt(LPWSTR S)
//{
//	int rez = 0;
//	DWORD len = wcslen(S);
//	WCHAR C[COUNT];
//	swprintf(C, COUNT, L"%s", S);
//	for (int i = 0; i < len; i++)
//	{
//		rez += WcharToByte(C[i]) * pow(10, len - i - 1);
//	}
//	return rez;
//}

int WINAPI wWinMain(HINSTANCE hINSTANCE, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	HANDLE hFile = CreateFileW(PATH1,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	OVERLAPPED olf = { 0 };
	olf.Offset = 0;
	DWORD ActualCount = 0;
	LPWSTR BufferRead = calloc(COUNT, sizeof(WCHAR));
	if (!ReadFile(hFile, BufferRead, COUNT, &ActualCount, &olf))
	{
		MessageBox(NULL, L"Произошла ошибка", L"Ошибка", MB_OK);
	}
	else
	{
		MessageBox(NULL, BufferRead, L"Содержание файла", MB_OK);
		LPWSTR Buffer = calloc(COUNT, sizeof(WCHAR));

		int a = wcslen(BufferRead);
		int j = 0;

		for (int i = 0; i < a; i++)
		{
			if (BufferRead[i] == ' ' || BufferRead[i] == 65279)
			{
				continue;
			}
			Buffer[j] = BufferRead[i];
			j++;
		}

		KvadUr(Buffer);
	}
	olf.Offset = ActualCount;
	CloseHandle(hFile);
	return 0;
}