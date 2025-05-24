#pragma once
//������ ������ ũ��� ��Ⱦ��(Aspect Ratio)�� ��Ÿ���� ����� ������ ���� �����Ѵ�.
#define ASPECT_RATIO (float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

//ī�޶��� ����(���: Mode)�� ��Ÿ���� ����� ������ ���� �����Ѵ�.
#define FIRST_PERSON_CAMERA 0x01
#define SPACESHIP_CAMERA 0x02
#define THIRD_PERSON_CAMERA 0x03

class Player;


struct VS_CB_CAMERA_INFO {
	XMFLOAT4X4 m_xmf4x4View;
	XMFLOAT4X4 m_xmf4x4Projection;
};

class Camera {
protected:
	// ī�޶��� ��ġ(������ǥ��) ����
	XMFLOAT3 m_xmf3Position;

	// ī�޶��� ���� x-��(Right), y-��(Up), z-��(Look)�� ��Ÿ���� ����
	XMFLOAT3 m_xmf3Right;
	XMFLOAT3 m_xmf3Up;
	XMFLOAT3 m_xmf3Look;

	// ī�޶� x-��, z-��, y-������ �󸶸�ŭ ȸ���ߴ� ���� ��Ÿ���� ����
	float m_fPitch;
	float m_fRoll;
	float m_fYaw;
	
	// ī�޶��� ����(1��Ī ī�޶�, �����̽�-�� ī�޶�, 3��Ī ī�޶�)�� ��Ÿ����.
	DWORD m_nMode;
	
	// �÷��̾ �ٶ� ��ġ �����̴�. �ַ� 3��Ī ī�޶󿡼� ���ȴ�.
	XMFLOAT3 m_xmf3LookAtWorld;
	
	// �÷��̾�� ī�޶��� �������� ��Ÿ���� �����̴�. �ַ� 3��Ī ī�޶󿡼� ���ȴ�.
	XMFLOAT3 m_xmf3Offset;
	
	// �÷��̾ ȸ���� �� �󸶸�ŭ�� �ð��� ������Ų �� ī�޶� ȸ����ų ���ΰ��� ��Ÿ����.
	float m_fTimeLag;
	
	// ī�޶� ��ȯ ��� 
	XMFLOAT4X4 m_xmf4x4View;
	// ���� ��ȯ ��� 
	XMFLOAT4X4 m_xmf4x4Projection;
	// ����Ʈ
	D3D12_VIEWPORT m_d3dViewport;
	// ���� �簢��
	D3D12_RECT m_d3dScissorRect;

	// ī�޶� ������ �ִ� �÷��̾ ���� ������
	Player *m_pPlayer = NULL;

public: 
	Camera();
	Camera(Camera *pCamera);
	virtual ~Camera();

	// ī�޶��� ������ ���̴� ���α׷����� �����ϱ� ���� ��� ����
	// ��� ���� - ����
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	// ��� ���� - ����
	virtual void ReleaseShaderVariables();
	// ��� ���� - ����
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	
	// ī�޶� ��ȯ ��� ����
	void GenerateViewMatrix();
	void GenerateViewMatrix(XMFLOAT3 xmf3Position, XMFLOAT3 xmf3LookAt, XMFLOAT3 xmf3Up);
	void GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fAspectRatio, float fFOVAngle);
	
	/*ī�޶� ������ ȸ���� �ϰ� �Ǹ� ������ �Ǽ� ������ ����Ȯ�� ������
	ī�޶��� ���� x-��(Right), y-��(Up), z��(LookAt)�� ���� �������� ���� �� �ִ�.
	ī�޶��� ���� x-��(Right), y-��(Up), z-��(LookAt)�� ���� �����ϵ��� ������ش�.*/
	// ī�޶� ���� x,y,z ���� �����ϰ� ����
	void RegenerateViewMatrix();

	// ī�޶� ����Ʈ ����
	void SetViewport(int xTopLeft, int yTopLeft, int nWidth, int nHeight, float fMinZ = 0.0f, float fMaxZ = 1.0f);
	// ī�޶� ���� ����
	void SetScissorRect(LONG xLeft, LONG yTop, LONG xRight, LONG yBottom);
	virtual void SetViewportsAndScissorRects(ID3D12GraphicsCommandList *pd3dCommandList);

	// Player Set & Get
	void SetPlayer(Player *pPlayer) { m_pPlayer = pPlayer; }
	Player *GetPlayer() { return(m_pPlayer); }

	// Mode Set & Get
	void SetMode(DWORD nMode) { m_nMode = nMode; }
	DWORD GetMode() { return(m_nMode); }

	// ��ġ Set & Get
	void SetPosition(XMFLOAT3 xmf3Position) { m_xmf3Position = xmf3Position; }
	XMFLOAT3& GetPosition() { return(m_xmf3Position); }

	// Look��ġ Set & Get
	void SetLookAtPosition(XMFLOAT3 xmf3LookAtWorld) { m_xmf3LookAtWorld = xmf3LookAtWorld; }
	XMFLOAT3& GetLookAtPosition() { return(m_xmf3LookAtWorld); }

	// ī�޶� x,y,z �� Get
	XMFLOAT3& GetRightVector() { return(m_xmf3Right); }
	XMFLOAT3& GetUpVector() { return(m_xmf3Up); }
	XMFLOAT3& GetLookVector() { return(m_xmf3Look); }

	// ī�޶� x,y,z ���� ȸ���� Get
	float& GetPitch() { return(m_fPitch); }
	float& GetRoll() { return(m_fRoll); }
	float& GetYaw() { return(m_fYaw); }

	// Player�� ī�޶��� offset Get
	void SetOffset(XMFLOAT3 xmf3Offset) { m_xmf3Offset = xmf3Offset; }
	XMFLOAT3& GetOffset() { return(m_xmf3Offset); }

	// ī�޶� ȸ���� �����ð� Set & Get
	void SetTimeLag(float fTimeLag) { m_fTimeLag = fTimeLag; }
	float GetTimeLag() { return(m_fTimeLag); }

	// ī�޶� ��ȯ ��� Get
	XMFLOAT4X4 GetViewMatrix() { return(m_xmf4x4View); }
	// ī�޶� ���� ��� Get
	XMFLOAT4X4 GetProjectionMatrix() { return(m_xmf4x4Projection); }
	// ī�޶� �� ��Ʈ Get
	D3D12_VIEWPORT GetViewport() { return(m_d3dViewport); }
	// ī�޶� ���� �簢�� Get
	D3D12_RECT GetScissorRect() { return(m_d3dScissorRect); }

	// ī�޶� xmf3Shift ��ŭ �߰��� �̵�
	virtual void Move(XMFLOAT3& xmf3Shift) {
		m_xmf3Position.x += xmf3Shift.x;
		m_xmf3Position.y += xmf3Shift.y;
		m_xmf3Position.z += xmf3Shift.z;
	}
	
	// ī�޶� x-��, y-��, z-������ ȸ���ϴ� �����Լ�
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f) { }

	// ī�޶��� �̵�, ȸ���� ���� ī�޶��� ������ �����ϴ� �����Լ�
	virtual void Update(XMFLOAT3& xmf3LookAt, float fTimeElapsed) { } 
	
	// 3��Ī ī�޶󿡼� ī�޶� �ٶ󺸴� ������ ����. �Ϲ������� �÷��̾ �ٶ󺸵��� ����
	virtual void SetLookAt(XMFLOAT3& xmf3LookAt) { } 
};

class SpaceShipCamera : public Camera {
public:
	SpaceShipCamera(Camera *pCamera);
	virtual ~SpaceShipCamera() { }
	
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
};

class FirstPersonCamera : public Camera {
public:
	FirstPersonCamera(Camera *pCamera);
	virtual ~FirstPersonCamera() { }
	
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
};

class ThirdPersonCamera : public Camera {
public:
	ThirdPersonCamera(Camera *pCamera);
	virtual ~ThirdPersonCamera() { }
	
	virtual void Update(XMFLOAT3& xmf3LookAt, float fTimeElapsed);
	virtual void SetLookAt(XMFLOAT3& vLookAt);
};