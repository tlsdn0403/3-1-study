#pragma once

#include "GameObject.h"
#include "Camera.h"

//���� ��ü�� ������ ���̴����� �Ѱ��ֱ� ���� ����ü(��� ����)�̴�.
struct CB_GAMEOBJECT_INFO {
	XMFLOAT4X4 m_xmf4x4World;
};

//���̴� �ҽ� �ڵ带 �������ϰ� �׷��Ƚ� ���� ��ü�� �����Ѵ�.
 class Shader {
 public: 
	 Shader(); 
	 virtual ~Shader();
	 //���̴��� ���ԵǾ� �ִ� ��� ���� ��ü�鿡 ���� ���콺 ��ŷ�� �����Ѵ�.

private:
	int m_nReferences = 0;

public: 
	void AddRef() { m_nReferences++; } 
	void Release() { 
		if (--m_nReferences <= 0)
			delete this;
	}

	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
	virtual D3D12_BLEND_DESC CreateBlendState();
	virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();

	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);

	D3D12_SHADER_BYTECODE CompileShaderFromFile(const wchar_t *pszFileName, LPCSTR pszShaderName,
		LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);

	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dRootSignature);

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice,
		ID3D12GraphicsCommandList *pd3dCommandList) {	}
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList) {	}
	virtual void ReleaseShaderVariables() {	}

	virtual void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World);

	virtual void OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera);

protected: 
	// Pipeline State ��ü���� ����Ʈ(�迭)�̴�.(?)

	ID3D12PipelineState **m_ppd3dPipelineStates = NULL;
	int m_nPipelineStates = 0;
 };

 class PlayerShader : public Shader {
 public: 
	 PlayerShader();
	 virtual ~PlayerShader();

	 virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	 virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	 virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);

	 virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
 };

 class ObjectsShader : public Shader {
 public:
	 ObjectsShader();
	 virtual ~ObjectsShader();
	virtual GameObject* PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance);
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void ReleaseObjects();
	
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
	virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
	virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
	
	virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
	
	virtual void ReleaseUploadBuffers();
	
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera);

 protected:
	 GameObject **m_ppObjects = NULL;
	 int m_nObjects = 0;
 };

