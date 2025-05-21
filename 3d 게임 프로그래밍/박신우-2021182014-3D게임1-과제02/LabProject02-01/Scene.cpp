#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"
#include"Shader.h"

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
//                           �¸���
//--------------------------------------------------------------------------------------------------------------------------------

void WinScene::Render(HDC hDCFrameBuffer) {  
   // "You Win!" �ؽ�Ʈ�� ȭ�� �߾ӿ� ���  
   const int centerX = FRAME_BUFFER_WIDTH / 2;  
   const int centerY = FRAME_BUFFER_HEIGHT / 2;  
   TextOutW(hDCFrameBuffer, centerX - 50, centerY - 10, L"You Win!", wcslen(L"You Win!"));  
}  

void WinScene::OnMouseClick(int x, int y) {  
   // Ŭ�� �� �޴��� ���ư���  
   CGameState::ChangeGameState(CGameState::MENU);  
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           �й��
//--------------------------------------------------------------------------------------------------------------------------------

void LossScene::Render(HDC hDCFrameBuffer) {
	// "You Win!" �ؽ�Ʈ�� ȭ�� �߾ӿ� ���  
	const int centerX = FRAME_BUFFER_WIDTH / 2;
	const int centerY = FRAME_BUFFER_HEIGHT / 2;
	TextOutW(hDCFrameBuffer, centerX - 50, centerY - 10, L"You Loss!", wcslen(L"You Loss!"));
}

void LossScene::OnMouseClick(int x, int y) {
	// Ŭ�� �� �޴��� ���ư���  
	CGameState::ChangeGameState(CGameState::MENU);
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           �޴�
//--------------------------------------------------------------------------------------------------------------------------------

MenuScene::MenuScene() {
	int x = FRAME_BUFFER_WIDTH/2, y = FRAME_BUFFER_HEIGHT/4, width = 200, height = 40, spacing = 50;

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
              CGameState::ChangeGameState(CGameState::GAME_1); // ���� ���·� ����  
          }
		  else if (m_MenuItems[i] == "Level-1")
		  {
			  CGameState::ChangeGameState(CGameState::GAME_1); // ���� ���·� ����  
		  }
		  else if (m_MenuItems[i] == "Level-2")
		  {
			  CGameState::ChangeGameState(CGameState::GAME); // ���� ���·� ����  
		  }
      }  
  }  
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           ����
//--------------------------------------------------------------------------------------------------------------------------------

CGameScene_2::CGameScene_2(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

CGameScene_2::~CGameScene_2()
{
}

void CGameScene_2::BuildObjects()
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



	m_pObstacle = new CGameObject_1 * [MAX_OBJECTS];
	CCubeMesh* Cm = new CCubeMesh(10.0f, 10.0f, 5.0f);


	m_pObstacle[0] = new CGameObject_1();
	m_pObstacle[0]->SetMesh(Cm);
	m_pObstacle[0]->SetColor(RGB(255, 0, 0));
	m_pObstacle[0]->SetPosition(-0.0f, 5.0f, -40.0f);
	m_pObstacle[0]->OnUpdateTransform();

	m_pObstacle[1] = new CGameObject_1();
	m_pObstacle[1]->SetMesh(Cm);
	m_pObstacle[1]->SetColor(RGB(255, 0, 0));
	m_pObstacle[1]->SetPosition(-0.0f, 5.0f, 40.0f);
	m_pObstacle[1]->OnUpdateTransform();

	m_pObstacle[2] = new CGameObject_1();
	m_pObstacle[2]->SetMesh(Cm);
	m_pObstacle[2]->SetColor(RGB(255, 0, 0));
	m_pObstacle[2]->SetPosition(-20.0f, 5.0f, 30.0f);
	m_pObstacle[2]->OnUpdateTransform();

	m_pObstacle[3] = new CGameObject_1();
	m_pObstacle[3]->SetMesh(Cm);
	m_pObstacle[3]->SetColor(RGB(255, 0, 0));
	m_pObstacle[3]->SetPosition(20.0f, 5.0f, 30.0f);
	m_pObstacle[3]->OnUpdateTransform();

	m_pObstacle[4] = new CGameObject_1();
	m_pObstacle[4]->SetMesh(Cm);
	m_pObstacle[4]->SetColor(RGB(255, 0, 0));
	m_pObstacle[4]->SetPosition(-20.0f, 5.0f, -30.0f);
	m_pObstacle[4]->OnUpdateTransform();

	m_pObstacle[5] = new CGameObject_1();
	m_pObstacle[5]->SetMesh(Cm);
	m_pObstacle[5]->SetColor(RGB(255, 0, 0));
	m_pObstacle[5]->SetPosition(20.0f, 5.0f, -30.0f);
	m_pObstacle[5]->OnUpdateTransform();

	CTankMesh* pTankMesh = new CTankMesh(4.0f, 4.0f, 4.0f);
	m_nObjects = 10;
	m_ppObjects = new CGameObject_1 * [m_nObjects];



	m_ppObjects[0] = new CExplosiveObject();
 
	m_ppObjects[0]->SetMesh(pTankMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -77.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);
	m_ppObjects[0]->OnUpdateTransform();
	
 

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pTankMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -74.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);
	m_ppObjects[1]->OnUpdateTransform();

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pTankMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, 0.0f, 93.0f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);
	m_ppObjects[2]->OnUpdateTransform();

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pTankMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(5.0f, 0.0f, -93.0f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);
	m_ppObjects[3]->OnUpdateTransform();

	m_ppObjects[4] = new CExplosiveObject();
	m_ppObjects[4]->SetMesh(pTankMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 83.0f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);
	m_ppObjects[4]->OnUpdateTransform();

	m_ppObjects[5] = new CExplosiveObject();
	m_ppObjects[5]->SetMesh(pTankMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -100.0f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);
	m_ppObjects[5]->OnUpdateTransform();

	m_ppObjects[6] = new CExplosiveObject();
	m_ppObjects[6]->SetMesh(pTankMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 0.0f, -87.0f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[6]->OnUpdateTransform();
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CExplosiveObject();
	m_ppObjects[7]->SetMesh(pTankMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 0.0f, 92.0f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);
	m_ppObjects[7]->OnUpdateTransform();

	m_ppObjects[8] = new CExplosiveObject();
	m_ppObjects[8]->SetMesh(pTankMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 0.0f, 77.0f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);
	m_ppObjects[8]->OnUpdateTransform();

	m_ppObjects[9] = new CExplosiveObject();
	m_ppObjects[9]->SetMesh(pTankMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 0.0f, 80.0f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);
	m_ppObjects[9]->OnUpdateTransform();
	for (int i = 0; i < 10; ++i) {
		m_ppObjects[i]->InitializeBullets();
	}


#ifdef _WITH_DRAW_AXIS
	m_pWorldAxis = new CGameObject();
	CAxisMesh* pAxisMesh = new CAxisMesh(0.5f, 0.5f, 0.5f);
	m_pWorldAxis->SetMesh(pAxisMesh);
#endif
}


void CGameScene_2::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pFloorObject) delete m_pFloorObject;

#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis; //	m_pWorldAxis�� ���� ���� ��Ÿ���� ��ü
#endif
}

void CGameScene_2::RotateTanksToFacePlayer() {  
   XMFLOAT3 playerPosition = m_pPlayer->GetPosition();  
   for (int i = 0; i < m_nObjects; i++) {
	   m_ppObjects[i]->RotateTowardsPlayer(playerPosition);
   }
}

void CGameScene_2::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CGameScene_2::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		case 'W':
			for (int i = 0; i < m_nObjects; i++)
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
			}
			break;
		case'S':
			
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject_1* CGameScene_2::PickObjectPointedByCursor(int xClient, int yClient, CCamera_1* pCamera)
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
	CGameObject_1* pNearestObject = NULL;  //���� ����� ������Ʈ
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

void CGameScene_2::CheckObjectByObjectCollisions()
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




void CGameScene_2::CheckObjectByWallCollisions()
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

void CGameScene_2::CheckPlayerByWallCollision()
{
	BoundingOrientedBox xmOOBBPlayerMoveCheck;
	m_pFloorObject->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_pFloorObject->m_xmf4x4World));
	XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));

	if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)) m_pFloorObject->SetPosition(m_pPlayer->m_xmf3Position);
}

void CGameScene_2::CheckObjectByBulletCollisions()
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
void CGameScene_2::CheckTankIsBlowed()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];

			if (pExplosiveObject->blowed)
			{
				// ��ũ �Ž� ������Ʈ�� ����  
				delete m_ppObjects[i];
				m_ppObjects[i] = nullptr;

				// ������Ʈ �迭�� ������  
				for (int k = i; k < m_nObjects - 1; k++)
				{
					m_ppObjects[k] = m_ppObjects[k + 1];
				}
				m_ppObjects[m_nObjects - 1] = nullptr;
				m_nObjects--;

				break;
			}
	}
	if(m_nObjects== 0)
	CGameState::ChangeGameState(CGameState::WIN); // ���� ���·� ����  
}
	


void CGameScene_2::CheckPlayerByBulletCollisions()  
{  
    CBulletObject* ppBullets;  
    for (int i = 0; i < m_nObjects; i++)  
    {  
        ppBullets = m_ppObjects[i]->GetBullets(); // �� ��ũ�� �Ѿ� �迭 ��������  
        for (int j = 0; j < 1; j++)  
        {  
            if (ppBullets != nullptr && ppBullets->m_bActive)  
            {  
                if (ppBullets->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))  
                {  
                    if (m_pPlayer->m_bShieldActive)  
                    {  
                       ppBullets->Reset(); // �� Ȱ��ȭ ���¸� �Ѿ� ����  
                    }  
                    else  
                    {
						if (m_pPlayer->m_xmOOBB.Contains(ppBullets->m_xmOOBB) && ppBullets->m_bActive)
							++colNum;
						if(colNum>10)
							CGameState::ChangeGameState(CGameState::LOSS); // ���� ���� ����  
                        return; // ���� ���� �� �Լ� ����  
                    }  
                }  
            }  
        }  
    }  
}
//
// ���� �Ѿ��� ������
//
void CGameScene_2::CheckBulletByWallCollisions()
{
   CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->m_ppBullets;

   // �÷��̾��� �Ѿ˰� ���� �浹 �˻�
   for (int i = 0; i < BULLETS; i++)
   {
	   for (int k = 0; k < 6; k++) {
		   if (ppBullets[i] && ppBullets[i]->m_bActive && ppBullets[i]->m_xmOOBB.Intersects(m_pObstacle[k]->m_xmOOBB)) // nullptr üũ �߰�
		   {

			   ppBullets[i]->Reset(); // ���� �浹�� �Ѿ��� ��Ȱ��ȭ
		   }
	   }
   }

   // �� ��ũ�� �Ѿ˰� ���� �浹 �˻�
   for (int i = 0; i < m_nObjects; i++)
   {
       CBulletObject* ppEnemyBullets = m_ppObjects[i]->GetBullets();
       for (int j = 0; j < BULLETS_1; j++) // BULLETS�� ���� ����
       {
		   for (int k = 0; k < 6; k++) {
			   if (ppEnemyBullets && ppEnemyBullets->m_bActive && ppEnemyBullets->m_xmOOBB.Intersects(m_pObstacle[k]->m_xmOOBB)) // nullptr üũ �߰�
			   {

				   ppEnemyBullets->Reset(); // ���� �浹�� �Ѿ��� ��Ȱ��ȭ

			   }
		   }
       }
   }
}

void CGameScene_2::Animate(float fElapsedTime)
{
	m_pFloorObject->Animate(fElapsedTime);  //���� �ִϸ���Ʈ ��

	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i]->Animate(fElapsedTime); //ť����� �ִϸ���Ʈ ��. ������ ������Ʈ���� ��ġ�� �ٲ� ����.
		m_ppObjects[i]->FireBullet();
	}
	for (int i = 0; i < 6; ++i) {
		m_pObstacle[i]->Animate(fElapsedTime);
	}
	RotateTanksToFacePlayer();




	//������ǥ�迡�� �浹�� �����Ѵ�.
	//�ִϸ���Ʈ �� ����� ���� �浹�� ������.
	CheckPlayerByWallCollision(); //�÷��̾�� �� �浹 �˻�

	CheckObjectByWallCollisions(); //������Ʈ�� �� 

	CheckObjectByObjectCollisions(); //������Ʈ�� ������Ʈ

	CheckObjectByBulletCollisions(); //������Ʈ�� �Ѿ�

	CheckBulletByWallCollisions();

	CheckPlayerByBulletCollisions();

	CheckTankIsBlowed();
}

void CGameScene_2::Render(HDC hDCFrameBuffer, CCamera_1* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);  //m_Viewport�� ����Ʈ ������ ����

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	m_pFloorObject->Render(hDCFrameBuffer, pCamera);
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	for(int i =0 ; i<6; ++i)
	m_pObstacle[i]->Render(hDCFrameBuffer, pCamera);

	if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);

//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}



CScene::CScene()
{
}
ID3D12RootSignature* CScene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}
ID3D12RootSignature* CScene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;
	D3D12_ROOT_PARAMETER pd3dRootParameters[2];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 16;
	pd3dRootParameters[0].Constants.ShaderRegister = 0;
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 1;
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;
	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;
	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void
			**)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();
	return(pd3dGraphicsRootSignature);
}

void CScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	CTriangleMesh* pMesh = new CTriangleMesh(pd3dDevice, pd3dCommandList);
	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];
	CRotatingObject* pRotatingObject = new CRotatingObject();
	pRotatingObject->SetMesh(pMesh);
	CDiffusedShader* pShader = new CDiffusedShader();
	pShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	pShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	pRotatingObject->SetShader(pShader);
	m_ppObjects[0] = pRotatingObject;
}
void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j]) delete m_ppObjects[j];
		delete[] m_ppObjects;
	}
}
bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
	LPARAM lParam)
{
	return(false);
}
bool CScene::ProcessInput(UCHAR* pKeysBuffer)
{
	return(false);
}
void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}

void CScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);
	//���� �������ϴ� ���� ���� �����ϴ� ���� ��ü(���̴��� �����ϴ� ��ü)���� �������ϴ� ���̴�.
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]) m_ppObjects[j]->Render(pd3dCommandList, pCamera);
	}
}

void CScene::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) if (m_ppObjects[j])
			m_ppObjects[j]->ReleaseUploadBuffers();
	}
}
