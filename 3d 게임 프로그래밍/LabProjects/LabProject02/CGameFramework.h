#pragma once
class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory;
	//DXGI ���丮 �������̽��� ���� �������̴�.

	IDXGISwapChain3* m_pdxgiSwapChain;
	//���� ü�� �������̽��� ���� �������̴�. �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ��ϴ�.

	ID3D12Device* m_pd3dDevice;
	//Direct3D ����̽� �������̽��� ���� �������̴�. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ��ϴ�.


public:
	CGameFramework();
	~CGameFramework();
};

