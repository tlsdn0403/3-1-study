#pragma once
#include"Player.h"
#include"Camera.h"
#include"GameObject.h"
#include"Mesh.h"
#include"Shader.h"
class CGameScene_1
{
public:
	CGameScene_1();
	virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature);
	virtual ~CGameScene_1();
	void changeMovingState(bool b);
	void Animate(float fElapsedTime);
	bool checkMoving();
	void changeDir(DWORD d);
	void changeSpeed(float s);

	void moveCart();

	void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera);
	void getPlayer(Player* p);

	virtual void ReleaseObjects();
	void ReleaseUploadBuffers();

	//그래픽 루트 시그너쳐를 생성한다.
	virtual ID3D12RootSignature* GetGraphicsRootSignature();

protected:
	//배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다.
	ObjectsShader* m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	GameObject** m_ppObjects = NULL;
	int m_nObjects = 0;
private:
	DWORD dwDirection = 0;
	int							m_nObjects_1 = 3;
	GameObject** m_ppObjects_1 = NULL;
	Player* m_pPlayer = NULL;
	bool isMovingCart = false;
	int dirNum = 0;
	float speed = 0.1f;
#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif




};
