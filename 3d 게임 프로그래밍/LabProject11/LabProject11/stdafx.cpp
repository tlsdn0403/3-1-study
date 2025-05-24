#include "stdafx.h"

/*���� ���ҽ��� �����ϴ� �Լ��̴�. ������ �� ������ ���� ���� ���ҽ��� �����ϰ� �ʱ�ȭ �����Ͱ� ������ �ʱ�ȭ �Ѵ�.*/ 
ID3D12Resource *CreateBufferResource(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, void *pData, UINT nBytes,
	D3D12_HEAP_TYPE d3dHeapType, D3D12_RESOURCE_STATES d3dResourceStates, ID3D12Resource **ppd3dUploadBuffer) {

	// Resource �޸� �Ҵ�
	ID3D12Resource *pd3dBuffer = NULL;

	// Resource Heap Desc ����
	D3D12_HEAP_PROPERTIES d3dHeapPropertiesDesc;
	// Resource Heap Desc - �ʱ�ȭ
	::ZeroMemory(&d3dHeapPropertiesDesc, sizeof(D3D12_HEAP_PROPERTIES));
	// Resource Heap Desc - ���� ����
	d3dHeapPropertiesDesc.Type = d3dHeapType;
	// Resource Heap Desc - ���� ���� CPU ������ �Ӽ� (CPU�� ��� ���� �����Ѱ�, �Ұ��Ѱ�)
	d3dHeapPropertiesDesc.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	// Resource Heap Desc - ���� ���� �޸� Ǯ( CPU vs GPU �뿪���� ��� �� ū�� )
	d3dHeapPropertiesDesc.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	// Resource Heap Desc - GPU ����� : 0 == 1���̻� // 1 == 1��
	d3dHeapPropertiesDesc.CreationNodeMask = 1;
	// Resource Heap Desc - ���� ����Ϳ��� ���ҽ��� �� �� �ִ� ��� ���� (����?)
	d3dHeapPropertiesDesc.VisibleNodeMask = 1;

	// Resource Desc - ����
	D3D12_RESOURCE_DESC d3dResourceDesc;
	// Resource Desc - �ʱ�ȭ
	::ZeroMemory(&d3dResourceDesc, sizeof(D3D12_RESOURCE_DESC));
	// Resource Desc - ���ҽ� ���� : ���� 
	d3dResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	// Resource Desc - ���ҽ��� ��� ���ĵǴ°�? : 0 == 64KB
	d3dResourceDesc.Alignment = 0;
	// Resource Desc - ���� ũ�� : ���� ������ ũ��
	d3dResourceDesc.Width = nBytes;
	// Resource Desc - ���� ũ��
	d3dResourceDesc.Height = 1;
	// Resource Desc - ���� �Ǵ� �迭�� ũ��
	d3dResourceDesc.DepthOrArraySize = 1;
	// Resource Desc - �Ӹʷ���
	d3dResourceDesc.MipLevels = 1;
	// Resource Desc - ���ҽ� ���� : �˾Ƽ� ��
	d3dResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	// Resource Desc - ���� ���ø� : �ȼ����� ���� ���� 1��
	d3dResourceDesc.SampleDesc.Count = 1;
	// Resource Desc - ���� ���ø� : ǰ�� ���� 0 == ���� ���ø� ���� ����
	d3dResourceDesc.SampleDesc.Quality = 0;
	// Resource Desc - ������ ���ҽ��� 1���� ���ҽ��� �����ϱ� ���� ��� : �ؽ��� �����Ͱ� ��켱 ������ ����
	d3dResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// Resource Desc - � �信�� ��� �������� : ��� ����
	d3dResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	// Resource State(����) - ��� ����� ���ΰ� : ���� ������ ��ǥ�� ���
	D3D12_RESOURCE_STATES d3dResourceInitialStates = D3D12_RESOURCE_STATE_COPY_DEST;

	// Resource Heap type == D3D12_HEAP_TYPE_UPLOAD �϶� : ���ε带 ���� CPU ����ȭ (CPU �����ͷ� ���ҽ� �ʱ�ȭ, �ݺ����� ���ε�)
	// '���ε� ���� ���� ����'�� ����
	if (d3dHeapType == D3D12_HEAP_TYPE_UPLOAD) 
		d3dResourceInitialStates = D3D12_RESOURCE_STATE_GENERIC_READ;
	// Resource Heap type == D3D12_HEAP_TYPE_READBACK �϶� : �б� ���� ��
	// '���� ������ ��ǥ�� ���'���� ����
	else if (d3dHeapType == D3D12_HEAP_TYPE_READBACK) 
		d3dResourceInitialStates = D3D12_RESOURCE_STATE_COPY_DEST;

	// Device�� ���ҽ� ����
	// Heap Properties Desc �ּ�,  �� �ɼ� : ����, Resource Desc �ּ�, Resource State (����), ����(?), � ���·�, ������ �ּ�
	HRESULT hResult = pd3dDevice->CreateCommittedResource(&d3dHeapPropertiesDesc, D3D12_HEAP_FLAG_NONE,
		&d3dResourceDesc, d3dResourceInitialStates, NULL, __uuidof(ID3D12Resource), (void **)&pd3dBuffer);

	// �������� �����Ͱ� ������
	if (pData) {

		// ������ ���ҽ��� Heap type�� ����
		switch (d3dHeapType) {
		// ������ ���ҽ��� Heap type��
		// 'GPU�� �а� ���� �����ϰ�, CPU�� ���� �Ұ� (��κ��� ���ҽ����� ����)' �϶�,
		case D3D12_HEAP_TYPE_DEFAULT:{
			// ���ε� ���۰� ���� ���,(?)
			if (ppd3dUploadBuffer) {
				// '���ε带 ���� CPU���ٿ� ����ȭ' Ÿ������ ����
				d3dHeapPropertiesDesc.Type = D3D12_HEAP_TYPE_UPLOAD;
				// ���ε� ���۷� ���� : ���ҽ� ���¸� ���ε� ���� ���� ���� 
				pd3dDevice->CreateCommittedResource(&d3dHeapPropertiesDesc, D3D12_HEAP_FLAG_NONE, &d3dResourceDesc,
					D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource), (void **)ppd3dUploadBuffer);
				
				// ���ε� ���۸� �����Ͽ� �ʱ�ȭ �����͸� ���ε� ���ۿ� �����Ѵ�.

				// CPU���� ���� ���� : { begin, end } end <= begin�̸� ���� ����
				D3D12_RANGE d3dReadRange = { 0, 0 };
				UINT8 *pBufferDataBegin = NULL;

				// ���ε� ������ ���ҽ� ���� (���ε� ���� ����) : ���ҽ��� ���� CPU�����͸� ��ȯ (���� ������)
				// ���� ���ҽ� �ε��� or 0 == ����, CPU�� ������ �޸� ����(NULL�� ���, ��ü ���� ���ҽ�), ���� ���ҽ��� �ּ�
				(*ppd3dUploadBuffer)->Map(0, &d3dReadRange, (void **)&pBufferDataBegin);
				// ���ε� ���ۿ� ����
				memcpy(pBufferDataBegin, pData, nBytes);
				// ���� ���ҽ� �ε��� or 0 == ����, CPU�� ������ �޸� ����(NULL�� ���, ��ü ���� ���ҽ�)
				(*ppd3dUploadBuffer)->Unmap(0, NULL);
				// ���ε� ������ ������ ����Ʈ ���ۿ� �����Ѵ�.
				// GPU���� ���ҽ� ��ü�� ���� : ppd3dUploadBuffer(���ε� ����)���� pd3dBuffer(���� �Ҵ��� ����)��
				// ���� : D3D12_HEAP_TYPE_UPLOAD -> D3D12_HEAP_TYPE_DEFAULT
				pd3dCommandList->CopyResource(pd3dBuffer, *ppd3dUploadBuffer);

				// Resource Barrier ����
				D3D12_RESOURCE_BARRIER d3dResourceBarrier;
				// Resource Barrier - �ʱ�ȭ
				::ZeroMemory(&d3dResourceBarrier, sizeof(D3D12_RESOURCE_BARRIER));
				// Resource Barrier - ���� : ���� �庮
				d3dResourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				// Resource Barrier - ���ҽ� �庮�� �и� �ϱ� ���� ���� 
				d3dResourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				// Resource Barrier - �������� ��� ���ҽ� : ���� �Ҵ��� ���ҽ� ����
				d3dResourceBarrier.Transition.pResource = pd3dBuffer;
				// Resource Barrier - ���� ���� : '���� ������ ��ǥ�� ���'
				d3dResourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
				// Resource Barrier - ���� ���� : ������ ���·�
				d3dResourceBarrier.Transition.StateAfter = d3dResourceStates;
				// Resource Barrier - ���� ���ҽ��� �ε��� : ��� ���� ���ҽ�
				d3dResourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				// Resource Barrier
				// �迭 ������ ����, �迭 �ּ�
				pd3dCommandList->ResourceBarrier(1, &d3dResourceBarrier);
			}
			break;
		} 
		// ������ ���ҽ��� Heap type��
		// '���ε带 ���� CPU���ٿ� ����ȭ' �϶�,
		case D3D12_HEAP_TYPE_UPLOAD: { 

			// CPU���� ���� ���� : { begin, end } end <= begin�̸� ���� ����
			D3D12_RANGE d3dReadRange = { 0, 0 };
			UINT8 *pBufferDataBegin = NULL;

			pd3dBuffer->Map(0, &d3dReadRange, (void **)&pBufferDataBegin);
			memcpy(pBufferDataBegin, pData, nBytes);
			pd3dBuffer->Unmap(0, NULL); 
			break; 
		} 
		// ������ ���ҽ��� Heap type��
		// '���� ������ ��ǥ�� ���' �϶�,
		case D3D12_HEAP_TYPE_READBACK:
			break;
		}
	} 
	return(pd3dBuffer);
}