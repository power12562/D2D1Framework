#include "WinUtility.h"
#include "Framework/WinGameApp.h"
#include <cassert>
#include <cstring>

std::wstring WinUtility::GetFilePath(const wchar_t* fileType)
{
	
	HWND hWnd = WinGameApp::GetHwnd();
	if (hWnd)
	{
		OPENFILENAME ofn;
		wchar_t filter[30];
		const int len = wcslen(fileType);
		wcscpy_s(filter, _ARRAYSIZE(filter), fileType);
		wchar_t temp[20] = L"\0*.";
		for (int i = 0; i < len + 1; i++)
		{
			temp[i + 3] = fileType[i]; //�ι��ڸ� �����ϴ� ���ڿ� �̿��� ���� ��ȸ�ؾ���
		}
		for (int i = 0; i < _ARRAYSIZE(temp) - 1; i++)
		{
			if (unsigned long long(i + len) == _ARRAYSIZE(filter))
				break;
			filter[i + len] = temp[i]; //�ι��ڸ� �����ϴ� ���ڿ� �̿��� ���� ��ȸ�ؾ���
		}

		wchar_t szFile[256]; // ���õ� ���� ��θ� ������ �迭
		ZeroMemory(&ofn, sizeof(ofn));
		ZeroMemory(szFile, sizeof(szFile));

		// ���� ��� ���� â �ʱ�ȭ
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;// ���͸��� ���� Ÿ�� ����
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		// ���� ��� ���� â ����
		if (GetOpenFileName(&ofn) == TRUE)
		{
			return ofn.lpstrFile; // ������ ���� ��� ��ȯ
		}
		else
		{
			return L""; // ����ڰ� ����� ��� �� ���ڿ� ��ȯ
		}
	}

	assert(!"hWnd�� �������� �ʽ��ϴ�.");
	return L""; 
}
