#include "WinUtility.h"
#include "Framework/WinGameApp.h"
#include "../resource.h"
#include <tchar.h>
#include <cassert>
#include <cstring>

std::wstring WinUtility::GetOpenFilePath(const wchar_t* fileType)
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

std::wstring WinUtility::GetSaveAsFilePath(const wchar_t* fileType)
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
		ofn.lpstrTitle = L"�ٸ� �̸����� ����";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

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

bool WinUtility::ShowConfirmationDialog(const wchar_t* title, const wchar_t* text)
{
	// MessageBox �Լ� ȣ��
	int result = MessageBox
	(
		NULL,                // �θ� â �ڵ� (NULL�� �θ� â�� ������ �ǹ�)
		text,    // �޽��� �ڽ��� ǥ���� �ؽ�Ʈ
		title,     // �޽��� �ڽ��� ����
		MB_OKCANCEL | MB_ICONQUESTION // Ȯ�� �� ��� ��ư�� ������ �޽��� �ڽ� ��Ÿ��
	);

	// ����ڰ� ���� ��ư�� ���� true �Ǵ� false ��ȯ
	if (result == IDOK) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

struct DialogDataInt 
{
	LPCWSTR title;
	LPCWSTR message;
};

INT_PTR CALLBACK DialogProcInt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	DialogDataInt* data;
	if (message == WM_INITDIALOG)
	{
		data = (DialogDataInt*)lParam;
		SetWindowText(hDlg, data->title); // ���̾�α� ���� ����
		SetDlgItemText(hDlg, IDC_STATIC_TEXT, data->message); // �޽��� ����
		WinGameApp::WinToScrrenCenter(hDlg);
		return (INT_PTR)TRUE;
	}
	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK) {
				TCHAR buffer[10];
				GetDlgItemText(hDlg, IDC_EDIT1, buffer, 10);
				int value = _ttoi(buffer);
				EndDialog(hDlg, value);
			}
			else {
				EndDialog(hDlg, -1);
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

int WinUtility::GetIntFromUser(HWND hWnd, LPCWSTR title, LPCWSTR text)
{
	DialogDataInt data = { title, text };
	int reslut = DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT_INT_DIALOG), hWnd, DialogProcInt, (LPARAM)&data);
	if (auto error = GetLastError())
	{
		assert(false);
	}
	return reslut;
}


struct DialogDataVector
{
	LPCWSTR title;
	Vector2* vector2;
};

INT_PTR CALLBACK DialogProcVector(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Vector2* temp = nullptr;
	DialogDataVector* data;	
	if (message == WM_INITDIALOG)
	{		
		data = (DialogDataVector*)lParam;
		temp = data->vector2;
		SetWindowText(hDlg, data->title); // ���̾�α� ���� ����
		SetDlgItemText(hDlg, IDC_EDIT1, L"Width");
		SetDlgItemText(hDlg, IDC_EDIT2, L"Height");
		WinGameApp::WinToScrrenCenter(hDlg);
		return (INT_PTR)TRUE;
	}
	switch (message)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK) {
				TCHAR buffer1[30];
				TCHAR buffer2[30];
				GetDlgItemText(hDlg, IDC_EDIT1, buffer1, 10);
				GetDlgItemText(hDlg, IDC_EDIT2, buffer2, 10);
				float x = static_cast<float>(_ttof(buffer1));
				float y = static_cast<float>(_ttof(buffer2));
				if (temp)
				{
					temp->x = x;
					temp->y = y;
					EndDialog(hDlg, 1);
				}
				else
					EndDialog(hDlg, -1);		
			}
			else {
				EndDialog(hDlg, -1);
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


Vector2 WinUtility::GetVector2FromUser(HWND hWnd, LPCWSTR title)
{
	Vector2 temp;
	DialogDataVector  data = { title ,&temp };
	bool reslut = DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT_VECTOR2_DIALOG), hWnd, DialogProcVector, (LPARAM)&data);
	if (!reslut)
	{
		assert(false);
	}
	return temp;
}
