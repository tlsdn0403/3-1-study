// ����̽��� �����ϰ� �����ϸ� ȭ�� ����� ���� ���� ���� ó�� 
// (���� ��ü�� ������ ����, ����� �Է�, �ִϸ��̼� ��)�� ����Ѵ�.

#include "stdafx.h"
#include "GameFramework.h"

#define _WITH_PLAYER_TOP
enum GameState { TITLE, MENU, GAME, GAME_1, WIN, LOSS };

GameFramework::GameFramework() {
	m_pdxgiFactory = NULL;
	m_pdxgiSwapChain = NULL;
	m_pd3dDevice = NULL;

	m_pd3dCommandAllocator = NULL;
	m_pd3dCommandQueue = NULL;
	m_pd3dPipelineState = NULL;
	m_pd3dCommandList = NULL;

	for (int i = 0; i < m_nSwapChainBuffers; i++) {
		m_ppd3dRenderTargetBuffers[i] = NULL;
		m_nFenceValues[i] = 0;
	}
	m_pScene = nullptr;

	m_pd3dRtvDescriptorHeap = NULL;
	m_nRtvDescriptorIncrementSize = 0;

	m_pd3dDepthStencilBuffer = NULL;
	m_pd3dDsvDescriptorHeap = NULL;
	m_nDsvDescriptorIncrementSize = 0;

	m_nSwapChainBufferIndex = 0;

	m_hFenceEvent = NULL;
	m_pd3dFence = NULL;

	m_nWndClientWidth = FRAME_BUFFER_WIDTH;
	m_nWndClientHeight = FRAME_BUFFER_HEIGHT;

	_tcscpy_s(m_pszFrameRate, _T("LapProject ("));
	// _tcscpy_s(char *_Dst, rsize _t _SizeInBytes, const char* _Src)
	// _tcscpy_s() �Լ� ����� �� ����:���� Overflow�� ���ų�, �߸��� �޸� ���� ������ ����
	// ��� ��� �� ���� tcscpy_s(���� ����, ������ �ϴ� ������ ũ�� + 1, ������ �ϴ� ������)

}


GameFramework::~GameFramework() {
}

bool GameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd) {
// ���� ���α׷��� ����Ǿ� �� �����찡 �����Ǹ� ȣ�� !!!

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	// Gameframework ����
	CreateDirect3DDevice();
	CreateCommandQueueAndList();
	CreateSwapChain();
	CreateRtvAndDsvDescriptorHeaps();
	CreateRenderTargetViews();
	CreateDepthStencilViews();

	// ���� ������Ʈ ����
	BuildObjects();

	return true;
}


void GameFramework::OnDestory(){
	ReleaseObjects();
	::CloseHandle(m_hFenceEvent);

#if defined(_DEBUG) 
	if (m_pd3dDebugController) m_pd3dDebugController->Release();
#endif

	for (int i = 0; i < m_nSwapChainBuffers; i++)
		if (m_ppd3dRenderTargetBuffers[i])
			m_ppd3dRenderTargetBuffers[i]->Release();

	if (m_pd3dRtvDescriptorHeap) m_pd3dRtvDescriptorHeap->Release();

	if (m_pd3dDepthStencilBuffer) m_pd3dDepthStencilBuffer->Release();
	if (m_pd3dDsvDescriptorHeap) m_pd3dDsvDescriptorHeap->Release();

	if (m_pd3dCommandAllocator)m_pd3dCommandAllocator->Release();
	if (m_pd3dCommandQueue) m_pd3dCommandQueue->Release();
	if (m_pd3dCommandList) m_pd3dCommandList->Release();

	if (m_pd3dFence) m_pd3dFence->Release();

	m_pdxgiSwapChain->SetFullscreenState(FALSE, NULL);
	if (m_pdxgiSwapChain) m_pdxgiSwapChain->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();
	if (m_pdxgiFactory) m_pdxgiFactory->Release();

}

inline void GameFramework::CreateSwapChain() {

	// Ŭ���̾�Ʈ �簢�� ���� ��������
	RECT rcClient;
	::GetClientRect(m_hWnd, &rcClient);

	// Ŭ���̾�Ʈ �簢�� ���� ����
	m_nWndClientWidth = rcClient.right - rcClient.left;
	m_nWndClientHeight = rcClient.bottom - rcClient.top;

	// SwapChain Desc ����
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	// SwapChain Desc - �ʱ�ȭ
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	// SwapChain Desc - ũ��
	dxgiSwapChainDesc.BufferDesc.Width = m_nWndClientWidth;
	dxgiSwapChainDesc.BufferDesc.Height = m_nWndClientHeight;
	// SwapChain Desc - �ĸ���� ���÷��� ����
	dxgiSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// SwapChain Desc - ���� ���ø� ǰ�� ����
	dxgiSwapChainDesc.SampleDesc.Count = (m_bMsaa4xEnable) ? 4 : 1;
	dxgiSwapChainDesc.SampleDesc.Quality = (m_bMsaa4xEnable) ? (m_nMsaa4xQualityLevels - 1) : 0;
	// SwapChain Desc - �ĸ���ۿ� ���� ǥ�� ��� ��İ� CPU�� ���� ��� : 'CPU�� �ĸ���ۿ� ���� ����'
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	// SwapChain Desc - �ĸ������ ���� ����
	dxgiSwapChainDesc.BufferCount = m_nSwapChainBuffers;
	// SwapChain Desc - �������� ó���ϴ� ���û��� : ���� ���빰 ���
	dxgiSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; 
	// SwapChain Desc - ����ü���� ���ۿ� ���� ���û����� ���� : �������α׷��� ���÷��� ��� ���氡��
	dxgiSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	//[�����ϱ�5: ��üȭ�� ��忡�� ����ȭ���� �ػ󵵸� ����ü��(�ĸ����)�� ũ�⿡ �°� �����Ѵ�.]
	// SwapChain Desc - ������, ��üȭ�� �������
	dxgiSwapChainDesc.Windowed = TRUE;
	// SwapChain Desc - ������ : 60Hz (1�ʿ� 60��)
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60; 
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	// SwapChain Desc - ��� �������� �ڵ�
	dxgiSwapChainDesc.OutputWindow = m_hWnd;

	// Swap Chain ����
	// Command Queue, SwapChain Desc, ������ �ּ�
	HRESULT hResult = m_pdxgiFactory->CreateSwapChain(m_pd3dCommandQueue, &dxgiSwapChainDesc, (IDXGISwapChain **)&m_pdxgiSwapChain);

	// ����ü���� ���� �ĸ���� �ε����� ����
	m_nSwapChainBufferIndex = m_pdxgiSwapChain->GetCurrentBackBufferIndex();

	//��Alt+Enter�� Ű�� ������ ��Ȱ��ȭ�Ѵ�.  [����]
	hResult = m_pdxgiFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER);

#ifndef _WITH_SWAPCHAIN_FULLSCREEN_STATE 
	CreateRenderTargetViews(); 
#endif 

	// Swap Chain Full Screen Desc ����
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC dxgiSwapChainFullScreenDesc;
	// Swap Chain Full Screen Desc - �ʱ�ȭ
	::ZeroMemory(&dxgiSwapChainFullScreenDesc, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
	// Swap Chain Full Screen Desc - ������ : 60Hz 
	dxgiSwapChainFullScreenDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainFullScreenDesc.RefreshRate.Denominator = 1;
	// Swap Chain Full Screen Desc - ��ĵ���� �׸��� ��� ���� : ��ĵ ���� ������ �������� ����
	dxgiSwapChainFullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	// Swap Chain Full Screen Desc - ����� �ػ󵵿� �°� Ȯ���� : �˾Ƽ� ��
	dxgiSwapChainFullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// Swap Chain Full Screen Desc - ������, ��üȭ�� ������� : ����
	dxgiSwapChainFullScreenDesc.Windowed = TRUE;


	//m_pdxgiFactory->CreateSwapChainForHwnd //����ü���� �����Ѵ�. 
	//(m_pd3dCommandQueue, m_hWnd, &dxgiSwapChainDesc, &dxgiSwapChainFullScreenDesc,
	//	NULL, (IDXGISwapChain1 **)&m_pdxgiSwapChain);

	//��Alt+Enter�� Ű�� ������ ��Ȱ��ȭ�Ѵ�.  [����]
	m_pdxgiFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER);

	// ����ü���� ���� �ĸ���� �ε����� ����
	m_nSwapChainBufferIndex = m_pdxgiSwapChain->GetCurrentBackBufferIndex();
}

void GameFramework::CreateDirect3DDevice() {

#if defined(_DEBUG) 
	D3D12GetDebugInterface(__uuidof(ID3D12Debug), (void **)&m_pd3dDebugController);
	m_pd3dDebugController->EnableDebugLayer();
#endif
	// DXGI Factory ���� - m_pdxgiFactory��
	::CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void **)&m_pdxgiFactory);

	// Adapter �޸� �Ҵ�
	IDXGIAdapter1 *pd3dAdapter = NULL;

	// Adapter�� ���� ��������
	for (UINT i = 0; DXGI_ERROR_NOT_FOUND != m_pdxgiFactory->EnumAdapters1(i, &pd3dAdapter); i++) {
		// Adapter Desc ����
		DXGI_ADAPTER_DESC1 dxgiAdapterDesc;
		// Adapter Desc - Adapter �� �ɷ� ��������
		pd3dAdapter->GetDesc1(&dxgiAdapterDesc);

		// �ɷ��� �ƴ϶�� skip
		if (dxgiAdapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			continue;

		// ����̽��� �����ϴµ� �����ߴٸ�,
		if (SUCCEEDED(D3D12CreateDevice(pd3dAdapter, D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device),(void **)&m_pd3dDevice)))
			break;
	}

	// ���� ����̽� ����
	if (!pd3dAdapter){
		m_pdxgiFactory->EnumWarpAdapter(_uuidof(IDXGIFactory4), (void **)&pd3dAdapter);
		D3D12CreateDevice(pd3dAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), (void **)&m_pd3dDevice);
	}

	//[����]Ư�� ���� 12.0�� �����ϴ� �ϵ���� ����̽��� ������ �� ������ WARP ����̽��� �����Ѵ�.
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS d3dMsaaQualityLevels;
	d3dMsaaQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//Msaa4x ���� ���ø� 
	d3dMsaaQualityLevels.SampleCount = 4;

	d3dMsaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	d3dMsaaQualityLevels.NumQualityLevels = 0;
	m_pd3dDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&d3dMsaaQualityLevels, sizeof(D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS));
	
	//����̽��� �����ϴ� ���� ������ ǰ�� ������ Ȯ���Ѵ�. 
	m_nMsaa4xQualityLevels = d3dMsaaQualityLevels.NumQualityLevels;
	
	//���� ������ ǰ�� ������ 1���� ũ�� ���� ���ø��� Ȱ��ȭ�Ѵ�. 
	m_bMsaa4xEnable = (m_nMsaa4xQualityLevels > 1) ? true : false;

	//m_nFenceValue = 0; //�潺�� �����ϰ� �潺 ���� 0���� �����Ѵ�.
	m_pd3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void **)&m_pd3dFence);
	
	/*�潺�� ����ȭ�� ���� �̺�Ʈ ��ü�� �����Ѵ�(�̺�Ʈ ��ü�� �ʱⰪ�� FALSE�̴�).
	  �̺�Ʈ�� ����Ǹ�(Signal) �� ��Ʈ�� ���� �ڵ������� FALSE�� �ǵ��� �����Ѵ�.*/
	m_hFenceEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);



	if (pd3dAdapter) pd3dAdapter->Release();
}


void GameFramework::CreateCommandQueueAndList(){
	// CommandQueue Desc ����
	D3D12_COMMAND_QUEUE_DESC d3dCommandQueueDesc;
	// CommandQueue Desc - �ʱ�ȭ
	::ZeroMemory(&d3dCommandQueueDesc, sizeof(D3D12_COMMAND_QUEUE_DESC));

	// CommandQueue Desc - ���� : GPU�� ���� �����Ҽ� �ִ� ��� ����(����Ʈ)
	d3dCommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	// CommandQueue Desc - ���� : �⺻ ��� ť
	d3dCommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// ����(Direct) ��� ť�� ����
	// CommandQueue Desc, uuidof, CommandQueue ������ �ּ�
	HRESULT hResult = m_pd3dDevice->CreateCommandQueue(&d3dCommandQueueDesc, _uuidof(ID3D12CommandQueue), (void **)&m_pd3dCommandQueue);
	
	// ����(Direct) ��� �Ҵ��ڸ� ����
	// Command Allocator - ���� : GPU ���� ���� ������ ��� ���� (D3D12_COMMAND_LIST_TYPE_DIRECT)
	// ����, uuidof, Command Allocator ������ �ּ�
	hResult = m_pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void **)&m_pd3dCommandAllocator);
	
	// ����(Direct) ��� ����Ʈ�� ����
	// ��� ����� (GPU �ϳ��� 0), ���� : GPU ���� ���� ������ ��� ����, ��ɾ� ����Ʈ�� ������ ��ɾ� �Ҵ���, �ʱ� ���������� ����(NULL : ���̺귯���� �˾Ƽ�), uuidof, ���� �ּ�
	hResult = m_pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pd3dCommandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void **)&m_pd3dCommandList);
	
	//��� ����Ʈ�� �����Ǹ� ����(Open) �����̹Ƿ� ����(Closed) ���·� �����. 
	hResult = m_pd3dCommandList->Close();
}

void GameFramework::CreateRtvAndDsvDescriptorHeaps(){
	// Descriptor Heap Desc ����
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	// Descriptor Heap Desc - �ʱ�ȭ
	::ZeroMemory(&d3dDescriptorHeapDesc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
	// Descriptor Heap Desc - �������� ���� : Swap Chain Buffer�� ����
	d3dDescriptorHeapDesc.NumDescriptors = m_nSwapChainBuffers;
	// Descriptor Heap Desc - ������ Ÿ�� : RTV (Rander Target View)
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	// Descriptor Heap Desc - ���� : ����
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	// Descriptor Heap Desc - � GPU? : 0����
	d3dDescriptorHeapDesc.NodeMask = 0;

	// ���� Ÿ�� ������ ��(�������� ������ ����ü�� ������ ����)�� �����Ѵ�. 
	// Descriptor Heap Desc, uuidof, ������ �ּ�
	HRESULT hResult = m_pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dRtvDescriptorHeap);

	// ���� Ÿ�� ������ ���� ������ ũ�⸦ �����Ѵ�.
	m_nRtvDescriptorIncrementSize = m_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// Descriptor Heap Desc - �������� ���� : 1��  (����- ���ٽ� ������)
	d3dDescriptorHeapDesc.NumDescriptors = 1;
	// Descriptor Heap Desc - ������ Ÿ�� : DSV
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

	// ����-���ٽ� ������ ��(�������� ������ 1)�� �����Ѵ�. 
	hResult = m_pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dDsvDescriptorHeap);

	// ����-���ٽ� ������ ���� ������ ũ�⸦ �����Ѵ�.
	m_nDsvDescriptorIncrementSize = m_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}


void GameFramework::CreateRenderTargetViews(){
	// Rtv CPU Descriptor Handle ���� - ���� ������ ��Ÿ���� CPU ������ �ڵ� ù �ּҸ� ����
	D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle = m_pd3dRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	// Swap Chain Buffer�� ������ŭ �ݺ�
	for (UINT i = 0; i < m_nSwapChainBuffers; i++)	{
		// ����ü���� i��° �ĸ����, uuidof��, Render Target Buffer[i]�� ��ȯ
		HRESULT hResult = m_pdxgiSwapChain->GetBuffer(i, __uuidof(ID3D12Resource),(void **)&m_ppd3dRenderTargetBuffers[i]);

		// ���� ������� d3dRtvCPUDescriptorHandle(�ּ�)�� ������ Render Target Buffer[i]�� �����
		m_pd3dDevice->CreateRenderTargetView(m_ppd3dRenderTargetBuffers[i], NULL, d3dRtvCPUDescriptorHandle);
		d3dRtvCPUDescriptorHandle.ptr += m_nRtvDescriptorIncrementSize;
	}
}

// ���� - ���ٽ� �� ����
void GameFramework::CreateDepthStencilViews(){
	// Resource Desc ����
	D3D12_RESOURCE_DESC d3dResourceDesc;
	// Resource Desc - ���ҽ� ���� : 2D �ؽ���
	d3dResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	// Resource Desc - ���ҽ��� ��� ���ĵǴ°�? : 0 == 64KB
	d3dResourceDesc.Alignment = 0;
	// Resource Desc - ���� ũ�� : Ŭ���̾�Ʈ ���� ����
	d3dResourceDesc.Width = m_nWndClientWidth;
	// Resource Desc - ���� ũ�� : Ŭ���̾�Ʈ ���� ����
	d3dResourceDesc.Height = m_nWndClientHeight;
	// Resource Desc - ���� �Ǵ� �迭�� ũ��
	d3dResourceDesc.DepthOrArraySize = 1;
	// Resource Desc - �Ӹʷ���
	d3dResourceDesc.MipLevels = 1;
	// Resource Desc - ���ҽ� ���� : ���� 24��Ʈ (��ȣȭx 0 ~ 1), ���ٽ� 8��Ʈ (��ȣ x ����) 
	d3dResourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	// Resource Desc - ���� ���ø� (�ȼ����� ���� ����) : �ϸ� 4, ���ϸ� 1��
	d3dResourceDesc.SampleDesc.Count = (m_bMsaa4xEnable) ? 4 : 1;
	// Resource Desc - ���� ���ø� : �ϸ� ���� - 1, ǰ�� ���� 0 == ���� ���ø� ���� ����
	d3dResourceDesc.SampleDesc.Quality = (m_bMsaa4xEnable) ? (m_nMsaa4xQualityLevels - 1) : 0;
	// Resource Desc - ������ ���ҽ��� 1���� ���ҽ��� �����ϱ� ���� ��� : ����Ϳ� ����
	d3dResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	// Resource Desc - � �信�� ��� �������� : DSV ���
	d3dResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// Resource Heap Desc ����
	D3D12_HEAP_PROPERTIES d3dHeapProperties;
	// Resource Heap Desc - �ʱ�ȭ
	::ZeroMemory(&d3dHeapProperties, sizeof(D3D12_HEAP_PROPERTIES));
	// Resource Heap Desc - ���� ���� : GPU �а� ����, CPU �Ұ� (��κ��� ���ҽ�)
	d3dHeapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	// Resource Heap Desc - ���� ���� CPU ������ �Ӽ� (CPU�� ��� ���� �����Ѱ�, �Ұ��Ѱ�)
	d3dHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	// Resource Heap Desc - ���� ���� �޸� Ǯ( CPU vs GPU �뿪���� ��� �� ū�� )
	d3dHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	// Resource Heap Desc - GPU ����� : 0 == 1���̻� // 1 == 1��
	d3dHeapProperties.CreationNodeMask = 1;
	// Resource Heap Desc - ���� ����Ϳ��� ���ҽ��� �� �� �ִ� ��� ���� (� GPU�� �����Ҽ� �ֳ�?)
	d3dHeapProperties.VisibleNodeMask = 1;

	// ������ ����� ������ ����
	// Clear Value Desc ����
	D3D12_CLEAR_VALUE d3dClearValue;
	// Clear Value Desc - � �����ΰ�
	d3dClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	// Clear Value Desc - ���̰� (0.0 ~ 1.0)
	d3dClearValue.DepthStencil.Depth = 1.0f;
	// Clear Value Desc - ���ٽ� �� (0 ~ 255)
	d3dClearValue.DepthStencil.Stencil = 0;


	// Device�� ����-���ٽ� ���۸� �����Ѵ�.
	// Heap Properties Desc �ּ�,  �� �ɼ� : ����, Resource Desc �ּ�, Resource State (����), ���� �ּ�(?), � ���·�, ������ �ּ�
	m_pd3dDevice->CreateCommittedResource(&d3dHeapProperties, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE, &d3dClearValue, __uuidof(ID3D12Resource), (void **)&m_pd3dDepthStencilBuffer);

	// ����-���ٽ� �������� �� ���� �ּҸ� �޴´�
	D3D12_CPU_DESCRIPTOR_HANDLE d3dDsvCPUDescriptorHandle = m_pd3dDsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	
	// ����-���ٽ� ���ۿ� ����-���ٽ� ������ �ڵ��� �ִ´�
	m_pd3dDevice->CreateDepthStencilView(m_pd3dDepthStencilBuffer, NULL, d3dDsvCPUDescriptorHandle);
}

void GameFramework::FrameAdvance(){
	m_GameTimer.Tick(0.0f);
	
	ProcessInput();
	
	AnimateObject();

	//��� �Ҵ��ڿ� ��� ����Ʈ�� �����Ѵ�.
	HRESULT hResult = m_pd3dCommandAllocator->Reset();
	hResult = m_pd3dCommandList->Reset(m_pd3dCommandAllocator, NULL);

	// Resource Barrier ����
	D3D12_RESOURCE_BARRIER d3dResourceBarrier;
	// Resource Barrier - �ʱ�ȭ
	::ZeroMemory(&d3dResourceBarrier, sizeof(D3D12_RESOURCE_BARRIER));
	// Resource Barrier - ���� : ���� �庮
	d3dResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	// Resource Barrier - ���ҽ� �庮�� �и� �ϱ� ���� ���� 
	d3dResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	// Resource Barrier - �������� ��� ���ҽ� : ���� �Ҵ��� ����Ÿ�� ����
	d3dResourceBarrier.Transition.pResource = m_ppd3dRenderTargetBuffers[m_nSwapChainBufferIndex];
	// Resource Barrier - ���� ���� : 'PRESENT�� ��ǥ�� ���'
	d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	// Resource Barrier - ���� ���� : '���� Ÿ���� ��ǥ�� ���'
	d3dResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// Resource Barrier - ���� ���ҽ��� �ε��� : ��� ���� ���ҽ�
	d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	// Resource Barrier
	// �迭 ������ ����, �迭 �ּ�
	m_pd3dCommandList->ResourceBarrier(1, &d3dResourceBarrier);

	// ���� Ÿ�ٿ� �ش��ϴ� �������� CPU ���� �ּ�(�ڵ�)�� �޾�
	D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle =
		m_pd3dRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	// ������ ���� Ÿ�ٿ� �ش��ϴ� �ּҸ� ����Ѵ�.
	d3dRtvCPUDescriptorHandle.ptr += (m_nSwapChainBufferIndex * m_nRtvDescriptorIncrementSize);

	// ���ϴ� �������� ���� Ÿ�� �並 �����.
	float pfClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	m_pd3dCommandList->ClearRenderTargetView(d3dRtvCPUDescriptorHandle, pfClearColor, 0, NULL);
	
	//����-���ٽ� �������� CPU ���� �ּҸ� �޾ƿ´�.
	D3D12_CPU_DESCRIPTOR_HANDLE d3dDsvCPUDescriptorHandle =
		m_pd3dDsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	// ���ϴ� ������ ����-���ٽ�(��)�� �����.
	m_pd3dCommandList->ClearDepthStencilView(d3dDsvCPUDescriptorHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, NULL);
	
	// ���� Ÿ�� ��, ����-���ٽ� �並 ���-���� �ܰ�(OM)�� ����
	m_pd3dCommandList->OMSetRenderTargets(1, &d3dRtvCPUDescriptorHandle, TRUE, &d3dDsvCPUDescriptorHandle);

	// ������
	switch (pGameState->GetCurrentState()) {
	case GAME:
		if (m_pScene) m_pScene->Render(m_pd3dCommandList, m_pCamera);
		break;
	case TITLE:
		if (m_pStartScene) m_pStartScene->Render(m_pd3dCommandList, m_pCamera);
		break;
	}


	//3��Ī ī�޶��� �� �÷��̾ �׻� ���̵��� �������Ѵ�.
#ifdef _WITH_PLAYER_TOP
//���� Ÿ���� �״�� �ΰ� ���� ���۸� 1.0���� ����� �÷��̾ �������ϸ� �÷��̾�� ������ �׷��� ���̴�.
	m_pd3dCommandList->ClearDepthStencilView(d3dDsvCPUDescriptorHandle,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, NULL);
#endif
	//3��Ī ī�޶��� �� �÷��̾ �������Ѵ�.
	/*if (m_pPlayer) m_pPlayer->Render(m_pd3dCommandList, m_pCamera);*/
	
	/*���� ���� Ÿ�ٿ� ���� �������� �����⸦ ��ٸ���.*/

	// ������ ���� Resource Barrier ����
	// Resource Barrier - ���� ���� : '���� Ÿ���� ��ǥ�� ���'
	d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// Resource Barrier - ���� ���� : 'PRESENT�� ��ǥ�� ���'
	d3dResourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	// Resource Barrier - ���� ���ҽ��� �ε��� : ��� ���� ���ҽ�
	d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	// Resource Barrier
	// �迭 ������ ����, �迭 �ּ�
	m_pd3dCommandList->ResourceBarrier(1, &d3dResourceBarrier);
	
	// ��� ����Ʈ�� ���� ����
	hResult = m_pd3dCommandList->Close(); 

	// ��� ����Ʈ�� ��� ť�� �߰�
	ID3D12CommandList *ppd3dCommandLists[] = { m_pd3dCommandList };
	m_pd3dCommandQueue->ExecuteCommandLists(_countof(ppd3dCommandLists)/*1*/, ppd3dCommandLists);
	
	// GPU�� ��� ��� ����Ʈ�� ������ �� ���� ��ٸ���.
	WaitForGpuComplete(); 
	
	// ������ �� ������ Present - ���÷��� ���
	m_pdxgiSwapChain->Present(0, 0 /*&dxgiPresentParameters*/);

	MoveToNextFrame();

	/*::_itow_s(m_nCurrentFrameRate, (m_pszFrameRate + 12), 37, 10);
	::wcscat_s((m_pszFrameRate + 12), 37, _T(" FPS)"));*/

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);

	//m_nSwapChainBufferIndex = m_pdxgiSwapChain->GetCurrentBackBufferIndex();
}


void GameFramework::WaitForGpuComplete(){
	//CPU �潺�� ���� �����Ѵ�. 
	UINT64 nFenceValue = ++m_nFenceValues[m_nSwapChainBufferIndex];
	
	HRESULT hResult = m_pd3dCommandQueue->Signal(m_pd3dFence, nFenceValue);
	//GPU�� �潺�� ���� �����ϴ� ����� ��� ť�� �߰��Ѵ�. 
	if (m_pd3dFence->GetCompletedValue() < nFenceValue)	{
		//�潺�� ���� ���� ������ ������ ������ �潺�� ���� ���� ������ ���� �� ������ ��ٸ���. 
		hResult = m_pd3dFence->SetEventOnCompletion(nFenceValue, m_hFenceEvent); ::WaitForSingleObject(m_hFenceEvent, INFINITE);
	}
}


void GameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam){
	switch (nMessageID)	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		// ���콺 ĸ�� - ���� ���콺 ��ġ�� �����´�.
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos); 
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		// ���콺 ĸ�� - ����
		::ReleaseCapture(); 
		break;
	case WM_MOUSEMOVE:
		break;
	default: break;
	}

}

void GameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam){
	switch (nMessageID)	{
	case WM_KEYUP:
		switch (wParam)		{
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;

		case VK_RETURN:
			break;

		case VK_F1:
		case VK_F2:
		case VK_F3:
			if (m_pPlayer)
				m_pCamera = m_pPlayer->ChangeCamera((DWORD)(wParam - VK_F1 + 1), m_GameTimer.GetTimeElapsed());
			break;

		case VK_F8:
			break;

		case VK_F9:
			ChangeSwapChainState();
			break;
		default: break;
		}
		break;
	default: break;
	}

}

LRESULT GameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam){
	switch (nMessageID) {
	case WM_SIZE:	{
		m_nWndClientWidth = LOWORD(lParam);
		m_nWndClientHeight = HIWORD(lParam);
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	} 
	return(0);
}

void GameFramework::BuildObjects(){

	// Ŀ�ǵ� ����Ʈ ����
	m_pd3dCommandList->Reset(m_pd3dCommandAllocator, NULL);

	// Scene ���� -> Scene ��ü ����
	switch (pGameState->GetCurrentState()) {
	case GAME:
		m_pScene = new Scene();
		m_pScene->BuildObjects(m_pd3dDevice, m_pd3dCommandList);
		
	case TITLE:
		m_pStartScene = new StartScene();
		m_pStartScene->BuildObjects(m_pd3dDevice, m_pd3dCommandList);

	}
	// Player ����
	AirplanePlayer* pAirplanePlayer = new AirplanePlayer(m_pd3dDevice, m_pd3dCommandList, m_pStartScene->GetGraphicsRootSignature());
	// GameFramework�� Player�� �����ϰ�
	m_pPlayer = pAirplanePlayer;
	// Player�� Camera�� GameFramework�� Camera�� 
	m_pCamera = m_pPlayer->GetCamera();


	

	//�� ��ü�� �����ϱ� ���Ͽ� �ʿ��� �׷��� ��� ����Ʈ���� ��� ť�� �߰��Ѵ�.
	m_pd3dCommandList->Close();
	ID3D12CommandList *ppd3dCommandLists[] = { m_pd3dCommandList };
	m_pd3dCommandQueue->ExecuteCommandLists(1, ppd3dCommandLists);

	//�׷��� ��� ����Ʈ���� ��� ����� ������ ��ٸ���.
	WaitForGpuComplete();


	switch (pGameState->GetCurrentState()) {
	case GAME:
		//�׷��� ���ҽ����� �����ϴ� ������ ������ ���ε� ���۵��� �Ҹ��Ų��.
		if (m_pScene) m_pScene->ReleaseUploadBuffers();
	case TITLE:
		if (m_pStartScene) m_pStartScene->ReleaseUploadBuffers();

	}
	//m_GameTimer.Reset();
}

void GameFramework::ReleaseObjects(){
	switch (pGameState->GetCurrentState()) {
	case GAME:
	{
		if (m_pScene) {
			m_pScene->ReleaseObjects();
			delete m_pScene;
			break;
		}
	}
	case TITLE:
		if (m_pStartScene) {
			m_pStartScene->ReleaseObjects();
			delete m_pStartScene;
			break;
		}
	}
}

void GameFramework::ProcessInput(){
	static UCHAR pKeyBuffer[256];

	DWORD dwDirection = 0;
	/*Ű������ ���� ������ ��ȯ�Ѵ�. ȭ��ǥ Ű(���桯, ���硯, ���衯, ���顯)�� ������
	�÷��̾ ������/����(���� x-��), ��/ ��(���� z-��)�� �̵��Ѵ�.
	��Page Up���� ��Page Down�� Ű�� ������ �÷��̾ ��/�Ʒ�(���� y-��)�� �̵��Ѵ�.*/
	
	if (::GetKeyboardState(pKeyBuffer)) { 
		if (pKeyBuffer[VK_UP] & 0xF0) dwDirection |= DIR_FORWARD;
		if (pKeyBuffer[VK_DOWN] & 0xF0) dwDirection |= DIR_BACKWARD;
		if (pKeyBuffer[VK_LEFT] & 0xF0) dwDirection |= DIR_LEFT;
		if (pKeyBuffer[VK_RIGHT] & 0xF0) dwDirection |= DIR_RIGHT; 
		if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;
	}
	
	float cxDelta = 0.0f, cyDelta = 0.0f;
	
	POINT ptCursorPos;
	/*���콺�� ĸ�������� ���콺�� �󸶸�ŭ �̵��Ͽ��� ���� ����Ѵ�.
	���콺 ���� �Ǵ� ������ ��ư�� ������ ���� �޽���(WM_LBUTTONDOWN, WM_RBUTTONDOWN)�� ó���� �� ���콺�� ĸ���Ͽ���. 
	�׷��Ƿ� ���콺�� ĸ�ĵ� ���� ���콺 ��ư�� ������ ���¸� �ǹ��Ѵ�. 
	���콺 ��ư�� ������ ���¿��� ���콺�� �¿� �Ǵ� ���Ϸ� �����̸� �� ���̾ x-�� �Ǵ� y-������ ȸ���Ѵ�.*/ 
	
	if (::GetCapture() == m_hWnd) {
		//���콺 Ŀ���� ȭ�鿡�� ���ش�(������ �ʰ� �Ѵ�). 
		::SetCursor(NULL);
		
		//���� ���콺 Ŀ���� ��ġ�� �����´�.
		::GetCursorPos(&ptCursorPos);
		
		//���콺 ��ư�� ���� ���¿��� ���콺�� ������ ���� ���Ѵ�. 
		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
		
		//���콺 Ŀ���� ��ġ�� ���콺�� �������� ��ġ�� �����Ѵ�.
		::SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y); 
	} 
	
	//���콺 �Ǵ� Ű �Է��� ������ �÷��̾ �̵��ϰų�(dwDirection) ȸ���Ѵ�(cxDelta �Ǵ� cyDelta).
	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f)) {
		if (cxDelta || cyDelta) { 
			/*cxDelta�� y-���� ȸ���� ��Ÿ���� cyDelta�� x-���� ȸ���� ��Ÿ����.
			������ ���콺 ��ư�� ������ ��� cxDelta�� z-���� ȸ���� ��Ÿ����.*/ 
			if (pKeyBuffer[VK_RBUTTON] & 0xF0) m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
			
			else m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);        
		} 

		/*�÷��̾ dwDirection �������� �̵��Ѵ�(�����δ� �ӵ� ���͸� �����Ѵ�).
		�̵� �Ÿ��� �ð��� ����ϵ��� �Ѵ�. �÷��̾��� �̵� �ӷ��� (50/��)�� �����Ѵ�.*/
		
		if (dwDirection) m_pPlayer->Move(dwDirection, 50.0f * m_GameTimer.GetTimeElapsed(), true);
	}

	//�÷��̾ ������ �̵��ϰ� ī�޶� �����Ѵ�. �߷°� �������� ������ �ӵ� ���Ϳ� �����Ѵ�.
	m_pPlayer->Update(m_GameTimer.GetTimeElapsed()); 
}

void GameFramework::AnimateObject(){
	switch (pGameState->GetCurrentState()) {
	case GAME:
	{
		if (m_pScene) {
			m_pScene->AnimateObjects(m_GameTimer.GetTimeElapsed());
			break;
		}
	}
	case TITLE:
		if (m_pStartScene) {
			m_pStartScene->AnimateObjects(m_GameTimer.GetTimeElapsed());
			break;
		}
	}

		
}


// [�����ϱ� 5�� fullscreenmode ]
void GameFramework::ChangeSwapChainState(){
	//gpu�� ���������� ��ٷ���
	WaitForGpuComplete(); 
	
	BOOL bFullScreenstate = false; 
	// ���� ��ũ�� ��带 �޾ƿ�
	m_pdxgiSwapChain->GetFullscreenState(&bFullScreenstate, nullptr);
	// ���� ��ũ�� ����� �ݴ�� ����
	m_pdxgiSwapChain->SetFullscreenState(!bFullScreenstate, nullptr); 

	// Swap Chain ũ�� ����
	// Target Parameter Desc ����
	DXGI_MODE_DESC dxgiTargetParameters;
	// Target Parameter Desc - ���� : RGBA (�븻����¡x)
	dxgiTargetParameters.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	// Target Parameter Desc - ���� ũ�� : Ŭ���̾�Ʈ ���� ũ���
	dxgiTargetParameters.Width = m_nWndClientWidth; 
	// Target Parameter Desc - ���� ũ�� : Ŭ���̾�Ʈ ���� ũ���
	dxgiTargetParameters.Height = m_nWndClientHeight; 
	// Target Parameter Desc - ������ : 60Hz (1�ʿ� 60��)
	dxgiTargetParameters.RefreshRate.Numerator = 60; 
	dxgiTargetParameters.RefreshRate.Denominator = 1; 
	// Target Parameter Desc - ����� �ػ󵵿� �°� Ȯ���� : �˾Ƽ� ��
	dxgiTargetParameters.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// Target Parameter Desc - ��ĵ���� �׸��� ��� ���� : ��ĵ ���� ������ �������� ����
	dxgiTargetParameters.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; 
	
	// ����ü���� ������ ��� �϶�, �������� ũ�� ����
	// ����ü���� ��ü ȭ�� ��� �϶�, ����ȭ�� ��� ����
	m_pdxgiSwapChain->ResizeTarget(&dxgiTargetParameters);

	// ��� ����Ÿ�� �� (com ��ü) Release
	// Ŭ���̾�Ʈ ������ ũ�Ⱑ ����Ǹ�, DXGI�� �˾Ƽ� ������� ũ�� ����
	// �ĸ���� ũ�⸦ �������� �ĸ������ ������ �����ؾ���
	for (int i = 0; i < m_nSwapChainBuffers; i++) 
		if (m_ppd3dRenderTargetBuffers[i]) m_ppd3dRenderTargetBuffers[i]->Release();

	// ����ü���� ũ�� ����
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc; 
	// ���� ����ü���� �޾�
	m_pdxgiSwapChain->GetDesc(&dxgiSwapChainDesc); 
	// ����ü���� ���� ����, �ٲ� Ŭ���̾�Ʈ ���� ����,���� ����, �ٲ� �ĸ������ ����(����), ����ü�� flag
	m_pdxgiSwapChain->ResizeBuffers(m_nSwapChainBuffers, m_nWndClientWidth, m_nWndClientHeight, 
		dxgiSwapChainDesc.BufferDesc.Format, dxgiSwapChainDesc.Flags);
	// ���� ����ü���� �ε����� �޾�
	m_nSwapChainBufferIndex = m_pdxgiSwapChain->GetCurrentBackBufferIndex();

	// ���� Ÿ���� ����� ������ �ٽ� ���� 
	CreateRenderTargetViews();
}

void GameFramework::MoveToNextFrame() {
	// ���� ����ü�� ������ �ε����� �޾�
	m_nSwapChainBufferIndex = m_pdxgiSwapChain->GetCurrentBackBufferIndex();
	// ���� ����ü�� ���ۿ� �ش��ϴ� �潺�� �ѱ�� 1�� ���� ��
	UINT64 nFenceValue = ++m_nFenceValues[m_nSwapChainBufferIndex];
	// ���� �潺���� �����ϴ� ���ť�� �������� �־�
	HRESULT hResult = m_pd3dCommandQueue->Signal(m_pd3dFence, nFenceValue);

	// ������ �潺���� �޾� ����ü���� �潺�� ���� ������,
	if (m_pd3dFence->GetCompletedValue() < nFenceValue) {
		// ����ü���� ���� �Ǹ�, Event�� ����
		hResult = m_pd3dFence->SetEventOnCompletion(nFenceValue, m_hFenceEvent);
		::WaitForSingleObject(m_hFenceEvent, INFINITE); 
	}
}

