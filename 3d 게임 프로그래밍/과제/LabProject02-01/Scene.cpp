#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

CGameState::GameState CGameState::CurrentState = CGameState::TITLE; // ���� ��� ��
void CGameState::ChangeGameState(GameState state)
{
	CurrentState = state;
}



void StartScene::Render(HDC hDCFrameBuffer)  
{  
   static float explosionScale = 1.0f;  

   if (isExploding)
   {
	   if (explosionScale < 5.0f) {
           static float explosionScale = 1.0f;
           static float ��_dx = 0.0f, ��_dy = 0.0f; 
           static float ��_dx = 0.0f, ��_dy = 0.0f; 
           static float ��_dx = 0.0f, ��_dy = 0.0f; 

           if (isExploding)
           {
               if (explosionScale < 5.0f)
               {
 
                   XFORM ��_xForm;
                   ��_dx -= 5.0f; 
                   ��_dy -= 5.0f; 
                   ��_xForm.eM11 = cos(angle) * explosionScale;
                   ��_xForm.eM12 = sin(angle) * explosionScale;
                   ��_xForm.eM21 = -sin(angle) * explosionScale;
                   ��_xForm.eM22 = cos(angle) * explosionScale;
                   ��_xForm.eDx = 250 + ��_dx; // �ؽ�Ʈ ��ġ (x)
                   ��_xForm.eDy = 250 + ��_dy; // �ؽ�Ʈ ��ġ (y)
                   SetWorldTransform(hDCFrameBuffer, &��_xForm);
                   TextOutW(hDCFrameBuffer, 0, 0, L"��", 1);

   
                   XFORM ��_xForm;
                   ��_dx -= 5.0f; 
                   ��_dy += 5.0f; 
                   ��_xForm.eM11 = cos(angle) * explosionScale;
                   ��_xForm.eM12 = sin(angle) * explosionScale;
                   ��_xForm.eM21 = -sin(angle) * explosionScale;
                   ��_xForm.eM22 = cos(angle) * explosionScale;
                   ��_xForm.eDx = 300 + ��_dx; // �ؽ�Ʈ ��ġ (x)
                   ��_xForm.eDy = 250 + ��_dy; // �ؽ�Ʈ ��ġ (y)
                   SetWorldTransform(hDCFrameBuffer, &��_xForm);
                   TextOutW(hDCFrameBuffer, 0, 0, L"��", 1);

   
                   XFORM ��_xForm;
                   ��_dx += 1.0f; 
                   ��_dy -= 5.0f; 
                   ��_xForm.eM11 = cos(angle) * explosionScale;
                   ��_xForm.eM12 = sin(angle) * explosionScale;
                   ��_xForm.eM21 = -sin(angle) * explosionScale;
                   ��_xForm.eM22 = cos(angle) * explosionScale;
                   ��_xForm.eDx = 350 + ��_dx; // �ؽ�Ʈ ��ġ (x)
                   ��_xForm.eDy = 250 + ��_dy; // �ؽ�Ʈ ��ġ (y)
                   SetWorldTransform(hDCFrameBuffer, &��_xForm);
                   TextOutW(hDCFrameBuffer, 0, 0, L"��", 1);

                   explosionScale += 0.1f;
               }
               else
               {
                   CGameState::ChangeGameState(CGameState::MENU); // ���� ���·� ����
               }

               // ������ �ؽ�Ʈ�� ����
               ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY);
               TextOutW(hDCFrameBuffer, 200, 250, L"3D �������α׷��� 1", wcslen(L"3D �������α׷��� 1"));
           }
           else
           {
               angle += 0.01f; // ȸ�� �ӵ�

               SetGraphicsMode(hDCFrameBuffer, GM_ADVANCED);
               XFORM xForm;
               xForm.eM11 = cos(angle) * explosionScale;
               xForm.eM12 = sin(angle) * explosionScale;
               xForm.eM21 = -sin(angle) * explosionScale;
               xForm.eM22 = cos(angle) * explosionScale;
               xForm.eDx = 300; // �ؽ�Ʈ ��ġ (x)
               xForm.eDy = 250; // �ؽ�Ʈ ��ġ (y)
               SetWorldTransform(hDCFrameBuffer, &xForm);

               TextOutW(hDCFrameBuffer, 0, 0, L"3D �������α׷��� 1 �ڽſ�", wcslen(L"3D �������α׷��� 1 �ڽſ�"));
           }

           ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY); // ���庯ȯ ��� �ʱ�ȭ

		  
	   }
	   else {
		   CGameState::ChangeGameState(CGameState::MENU); // ���� ���·� ����  
	   }
	   // ������ �ؽ�Ʈ�� ����  
	   ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY);
	   TextOutW(hDCFrameBuffer, 200, 250, L"3D �������α׷��� 1", wcslen(L"3D �������α׷��� 1"));
   }
   else {
        
	   angle += 0.01f; // ȸ�� �ӵ�  
	   // "�ڽſ�" �ؽ�Ʈ ȸ�� �� ���� ȿ��  
	   SetGraphicsMode(hDCFrameBuffer, GM_ADVANCED);
	   XFORM xForm;
	   xForm.eM11 = cos(angle) ;
	   xForm.eM12 = sin(angle) ;
	   xForm.eM21 = -sin(angle);
	   xForm.eM22 = cos(angle);
	   xForm.eDx = 300; // �ؽ�Ʈ ��ġ (x)  
	   xForm.eDy = 250; // �ؽ�Ʈ ��ġ (y)  
	   SetWorldTransform(hDCFrameBuffer, &xForm);

	   TextOutW(hDCFrameBuffer, 0, 0, L"3D �������α׷��� 1 �ڽſ�", wcslen(L"3D �������α׷��� 1 �ڽſ�"));
   }
 
   ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY);  //���庯ȯ ��� �ʱ�ȭ

}  
void StartScene::OnMouseClick(int x, int y)
{
	// "�ڽſ�" �ؽ�Ʈ�� ȸ�� �߽� ��ǥ�� ������ ����  
	const int centerX = 300;
	const int centerY = 250;
	const int radius = 50; // Ŭ�� ������ �ݰ�  

	// Ŭ���� ��ǥ�� �ؽ�Ʈ�� ȸ�� ��ǥ��� ��ȯ  
	float cosAngle = cos(-angle);
	float sinAngle = sin(-angle);


	int textcoordX = centerX + (50.0 * cos(angle));
	int textcoordY = centerY + (50.0 * sin(angle));

	int dx = x - textcoordX;
	int dy = y - textcoordY;
	int distanceSquared = dx + dy;

	if (distanceSquared <200)
	{
		isExploding = true; // ���� ȿ�� Ȱ��ȭ  
	}
}


//--------------------------------------------------------------------------------------------------------------------------------
//                           �޴�
//--------------------------------------------------------------------------------------------------------------------------------

MenuScene::MenuScene() {
	int x = FRAMEBUFFER_WIDTH/2, y = FRAMEBUFFER_HEIGHT/4, width = 200, height = 40, spacing = 50;

	for (size_t i = 0; i < m_MenuItems.size(); ++i) {
		RECT rect = { x -width, y + static_cast<int>(i * spacing), x + width, y + height + static_cast<int>(i * spacing) };
		m_MenuItemRects.push_back(rect);
	}
}
void MenuScene::Render(HDC hDCFrameBuffer) {  
    for (size_t i = 0; i < m_MenuItems.size(); ++i) {  
        // �޴� �׸� �ؽ�Ʈ�� �׸���
		std::wstring wideText = std::wstring(m_MenuItems[i].begin(), m_MenuItems[i].end());
		DrawText(hDCFrameBuffer, wideText.c_str(), -1, &m_MenuItemRects[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);



        // ���õ� �޴� �׸� ���� ǥ�� (��: �׵θ� �׸���)
        //if (/* ����: ���� ���õ� �޴� �׸� */) {
        //    FrameRect(hDCFrameBuffer, &m_MenuItemRects[i], (HBRUSH)GetStockObject(BLACK_BRUSH));
        //}
    }  
}


void MenuScene::OnMouseClick(int x, int y)  
{  
  for (size_t i = 0; i < m_MenuItemRects.size(); ++i)  
  {  
      if (PtInRect(&m_MenuItemRects[i], POINT{ x, y }))  
      {  
          if (m_MenuItems[i] == "End")  
          {  
              ::PostQuitMessage(0); // ���α׷� ����  
          }  
          else if (m_MenuItems[i] == "Start")  
          {  
              CGameState::ChangeGameState(CGameState::GAME); // ���� ���·� ����  
          }
		  else if (m_MenuItems[i] == "Level-1")
		  {
			  CGameState::ChangeGameState(CGameState::GAME_1); // ���� ���·� ����  
		  }
      }  
  }  
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           ����
//--------------------------------------------------------------------------------------------------------------------------------

CGameScene::CGameScene(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

CGameScene::~CGameScene()
{
}

void CGameScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 200.0f;
	CFloorMesh* pWallCubeMesh = new CFloorMesh(fHalfWidth * 2.0f, fHalfDepth * 2.0f, 30);

	m_pFloorObject = new CFloorObject();
	m_pFloorObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pFloorObject->SetMesh(pWallCubeMesh);
	m_pFloorObject->SetColor(RGB(0, 0, 0));
	m_pFloorObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pFloorObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pFloorObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pFloorObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pFloorObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pFloorObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);
	m_pFloorObject->m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.05f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	CTankMesh* pCubeMesh = new CTankMesh(4.0f, 4.0f, 4.0f);

	m_nObjects = 10;
	m_ppObjects = new CGameObject * [m_nObjects];

	m_ppObjects[0] = new CExplosiveObject();
 
	m_ppObjects[0]->SetMesh(pCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -14.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);
	m_ppObjects[0]->OnUpdateTransform();

 

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -14.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);
	m_ppObjects[1]->OnUpdateTransform();

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, 0.0f, 20.0f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);
	m_ppObjects[2]->OnUpdateTransform();

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(5.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);
	m_ppObjects[3]->OnUpdateTransform();

	m_ppObjects[4] = new CExplosiveObject();
	m_ppObjects[4]->SetMesh(pCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 0.0f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);
	m_ppObjects[4]->OnUpdateTransform();

	m_ppObjects[5] = new CExplosiveObject();
	m_ppObjects[5]->SetMesh(pCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);
	m_ppObjects[5]->OnUpdateTransform();

	m_ppObjects[6] = new CExplosiveObject();
	m_ppObjects[6]->SetMesh(pCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[6]->OnUpdateTransform();
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CExplosiveObject();
	m_ppObjects[7]->SetMesh(pCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 0.0f, -20.0f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);
	m_ppObjects[7]->OnUpdateTransform();

	m_ppObjects[8] = new CExplosiveObject();
	m_ppObjects[8]->SetMesh(pCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 0.0f, -30.0f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);
	m_ppObjects[8]->OnUpdateTransform();

	m_ppObjects[9] = new CExplosiveObject();
	m_ppObjects[9]->SetMesh(pCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 0.0f, 0.0f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);
	m_ppObjects[9]->OnUpdateTransform();


#ifdef _WITH_DRAW_AXIS
	m_pWorldAxis = new CGameObject();
	CAxisMesh* pAxisMesh = new CAxisMesh(0.5f, 0.5f, 0.5f);
	m_pWorldAxis->SetMesh(pAxisMesh);
#endif
}


void CGameScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pFloorObject) delete m_pFloorObject;

#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis; //	m_pWorldAxis�� ���� ���� ��Ÿ���� ��ü
#endif
}

void CGameScene::RotateTanksToFacePlayer() {  
   XMFLOAT3 playerPosition = m_pPlayer->GetPosition();  
   for (int i = 0; i < m_nObjects; i++) {
	   m_ppObjects[i]->RotateTowardsPlayer(playerPosition);
   }
}

void CGameScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CGameScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[int(wParam - '1')];
			pExplosiveObject->m_bBlowingUp = true;
			break;
		}
		case 'A':
			for (int i = 0; i < m_nObjects; i++)
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* CGameScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	XMFLOAT3 xmf3PickPosition; //ī�޶� ��ŷ ���� (�����̴�)

	// ����Ʈ ������ �ؼ� ī�޶� ��ǥ�� ã�� , ������ȯ ����� 11�� 22 �� X,Y�� ������( ������� ���Ѵ�)   -> ī�޶� ��ǥ�� X,Y�� ���ߴ�.
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	//������鿡�� FOV�� 90����� �ϸ� D�� �׻� 1�̱�� �޴�
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);//��ŷ�� �ϴ� ���� ���ʿ� �ִ� ���̶�� ������ ����.
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX; //���� ����� �Ÿ�	
	CGameObject* pNearestObject = NULL;  //���� ����� ������Ʈ
	for (int i = 0; i < m_nObjects; i++)
	{
		float fHitDistance = FLT_MAX;
		//�� ���������� ���� �����ϰ� ������Ʈ�� �ٿ���ڽ��ϰ��� �浹�� ã�Ƴ��� �浹�� �Ǵ� ������Ʈ�߿� ���� ����� ������Ʈ
		nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance); 
		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance)) //�������� ã������ ���� �����
		{
			//������Ʈ �����Ͷ� �Ÿ��� �ٲ㼭 ������ �� ����.
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i];
		}
	}
	return(pNearestObject);
}

void CGameScene::CheckObjectByObjectCollisions()
{
	//�� ������Ʈ���� � ������Ʈ�ϰ� �浹�� �Ͼ���� �˷��ִ� ������ ������ null�� �ʱ�ȭ ��Ų��.
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL; 
  
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void CGameScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		ContainmentType containType = m_pFloorObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB); //�� ��ü�� �ٿ�� �ڽ��� ������Ʈ�� �ٿ�� �ڽ��� �����ϰ� ������
		switch (containType) //�����̳� Ÿ�Կ� ����
		{
		case DISJOINT:  //������Ʈ�� ���� ����ٴ� ��
		{
			//������� ��� ���� ã�ƾ� �Ѵ�.
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				//������Ʈ�� �ٿ�� �ڽ��� , j��°�� ������ϰ��� intersects�� �ؼ� ���ʰ������� �������Ͱ� ���ϰ� �ִٰ� �ϸ� ����� ����� �ڿ� �ִ�
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pFloorObject->m_pxmf4WallPlanes[j])); 
				if (intersectType == BACK)
				{
					//j ���� ����� �����.
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1) //����� ����� ������
			{
				//�� ��鿡 ���ؼ� �ݻ纤�͸� ���ؼ� ������Ʈ�� �̵����� ���͸� �ݻ纤�ͷ� �����
				XMVECTOR xmvNormal = XMVectorSet(m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal); //�ݻ纤�͸� ����
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect); //�̵����� ���͸� �ݻ纤�ͷ� �����

				//��ü���� ���� �ݻ�Ǵ� ���µ�� �̵��ϰ� �� ����
			}
			break;
		}
		case INTERSECTS: //������ �ִٴ� ��
		{
			//������ �־ �Ȱ��� ���� ���ָ� �ȴ�.
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pFloorObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS: //�����Ѵ� , �浹���� �ʾҴٴ� ��
			break;
		}
	}
}

void CGameScene::CheckPlayerByWallCollision()
{
	BoundingOrientedBox xmOOBBPlayerMoveCheck;
	m_pFloorObject->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_pFloorObject->m_xmf4x4World));
	XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));

	if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)) m_pFloorObject->SetPosition(m_pPlayer->m_xmf3Position);
}

void CGameScene::CheckObjectByBulletCollisions()
{
	CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->m_ppBullets;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
				ppBullets[j]->Reset();
			}
		}
	}
}

void CGameScene::Animate(float fElapsedTime)
{
	m_pFloorObject->Animate(fElapsedTime);  //���� �ִϸ���Ʈ ��

	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i]->Animate(fElapsedTime); //ť����� �ִϸ���Ʈ ��. ������ ������Ʈ���� ��ġ�� �ٲ� ����.
		m_ppObjects[i]
	}
	RotateTanksToFacePlayer();




	//������ǥ�迡�� �浹�� �����Ѵ�.
	//�ִϸ���Ʈ �� ����� ���� �浹�� ������.
	CheckPlayerByWallCollision(); //�÷��̾�� �� �浹 �˻�

	CheckObjectByWallCollisions(); //������Ʈ�� �� 

	CheckObjectByObjectCollisions(); //������Ʈ�� ������Ʈ

	CheckObjectByBulletCollisions(); //������Ʈ�� �Ѿ�
}

void CGameScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);  //m_Viewport�� ����Ʈ ������ ����

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	m_pFloorObject->Render(hDCFrameBuffer, pCamera);
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);

//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}


