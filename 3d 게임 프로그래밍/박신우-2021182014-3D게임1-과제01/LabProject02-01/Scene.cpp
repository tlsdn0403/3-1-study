#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

CGameState::GameState CGameState::CurrentState = CGameState::TITLE; // 정적 멤버 초
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
           static float 박_dx = 0.0f, 박_dy = 0.0f; 
           static float 신_dx = 0.0f, 신_dy = 0.0f; 
           static float 우_dx = 0.0f, 우_dy = 0.0f; 

           if (isExploding)
           {
               if (explosionScale < 5.0f)
               {
 
                   XFORM 박_xForm;
                   박_dx -= 5.0f; 
                   박_dy -= 5.0f; 
                   박_xForm.eM11 = cos(angle) * explosionScale;
                   박_xForm.eM12 = sin(angle) * explosionScale;
                   박_xForm.eM21 = -sin(angle) * explosionScale;
                   박_xForm.eM22 = cos(angle) * explosionScale;
                   박_xForm.eDx = 250 + 박_dx; // 텍스트 위치 (x)
                   박_xForm.eDy = 250 + 박_dy; // 텍스트 위치 (y)
                   SetWorldTransform(hDCFrameBuffer, &박_xForm);
                   TextOutW(hDCFrameBuffer, 0, 0, L"박", 1);

   
                   XFORM 신_xForm;
                   신_dx -= 5.0f; 
                   신_dy += 5.0f; 
                   신_xForm.eM11 = cos(angle) * explosionScale;
                   신_xForm.eM12 = sin(angle) * explosionScale;
                   신_xForm.eM21 = -sin(angle) * explosionScale;
                   신_xForm.eM22 = cos(angle) * explosionScale;
                   신_xForm.eDx = 300 + 신_dx; // 텍스트 위치 (x)
                   신_xForm.eDy = 250 + 신_dy; // 텍스트 위치 (y)
                   SetWorldTransform(hDCFrameBuffer, &신_xForm);
                   TextOutW(hDCFrameBuffer, 0, 0, L"신", 1);

   
                   XFORM 우_xForm;
                   우_dx += 1.0f; 
                   우_dy -= 5.0f; 
                   우_xForm.eM11 = cos(angle) * explosionScale;
                   우_xForm.eM12 = sin(angle) * explosionScale;
                   우_xForm.eM21 = -sin(angle) * explosionScale;
                   우_xForm.eM22 = cos(angle) * explosionScale;
                   우_xForm.eDx = 350 + 우_dx; // 텍스트 위치 (x)
                   우_xForm.eDy = 250 + 우_dy; // 텍스트 위치 (y)
                   SetWorldTransform(hDCFrameBuffer, &우_xForm);
                   TextOutW(hDCFrameBuffer, 0, 0, L"우", 1);

                   explosionScale += 0.1f;
               }
               else
               {
                   CGameState::ChangeGameState(CGameState::MENU); // 게임 상태로 변경
               }

               // 나머지 텍스트는 고정
               ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY);
               TextOutW(hDCFrameBuffer, 200, 250, L"3D 게임프로그래밍 1", wcslen(L"3D 게임프로그래밍 1"));
           }
           else
           {
               angle += 0.01f; // 회전 속도

               SetGraphicsMode(hDCFrameBuffer, GM_ADVANCED);
               XFORM xForm;
               xForm.eM11 = cos(angle) * explosionScale;
               xForm.eM12 = sin(angle) * explosionScale;
               xForm.eM21 = -sin(angle) * explosionScale;
               xForm.eM22 = cos(angle) * explosionScale;
               xForm.eDx = 300; // 텍스트 위치 (x)
               xForm.eDy = 250; // 텍스트 위치 (y)
               SetWorldTransform(hDCFrameBuffer, &xForm);

               TextOutW(hDCFrameBuffer, 0, 0, L"3D 게임프로그래밍 1 박신우", wcslen(L"3D 게임프로그래밍 1 박신우"));
           }

           ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY); // 월드변환 행렬 초기화

		  
	   }
	   else {
		   CGameState::ChangeGameState(CGameState::MENU); // 게임 상태로 변경  
	   }
	   // 나머지 텍스트는 고정  
	   ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY);
	   TextOutW(hDCFrameBuffer, 200, 250, L"3D 게임프로그래밍 1", wcslen(L"3D 게임프로그래밍 1"));
   }
   else {
        
	   angle += 0.01f; // 회전 속도  
	   // "박신우" 텍스트 회전 및 폭발 효과  
	   SetGraphicsMode(hDCFrameBuffer, GM_ADVANCED);
	   XFORM xForm;
	   xForm.eM11 = cos(angle) ;
	   xForm.eM12 = sin(angle) ;
	   xForm.eM21 = -sin(angle);
	   xForm.eM22 = cos(angle);
	   xForm.eDx = 300; // 텍스트 위치 (x)  
	   xForm.eDy = 250; // 텍스트 위치 (y)  
	   SetWorldTransform(hDCFrameBuffer, &xForm);

	   TextOutW(hDCFrameBuffer, 0, 0, L"3D 게임프로그래밍 1 박신우", wcslen(L"3D 게임프로그래밍 1 박신우"));
   }
 
   ModifyWorldTransform(hDCFrameBuffer, NULL, MWT_IDENTITY);  //월드변환 행렬 초기화

}  
void StartScene::OnMouseClick(int x, int y)
{
	// "박신우" 텍스트의 회전 중심 좌표와 반지름 정의  
	const int centerX = 300;
	const int centerY = 250;
	const int radius = 50; // 클릭 가능한 반경  

	// 클릭한 좌표를 텍스트의 회전 좌표계로 변환  
	float cosAngle = cos(-angle);
	float sinAngle = sin(-angle);


	int textcoordX = centerX + (50.0 * cos(angle));
	int textcoordY = centerY + (50.0 * sin(angle));

	int dx = x - textcoordX;
	int dy = y - textcoordY;
	int distanceSquared = dx + dy;

	if (distanceSquared <200)
	{
		isExploding = true; // 폭발 효과 활성화  
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//                           승리씬
//--------------------------------------------------------------------------------------------------------------------------------

void WinScene::Render(HDC hDCFrameBuffer) {  
   // "You Win!" 텍스트를 화면 중앙에 출력  
   const int centerX = FRAMEBUFFER_WIDTH / 2;  
   const int centerY = FRAMEBUFFER_HEIGHT / 2;  
   TextOutW(hDCFrameBuffer, centerX - 50, centerY - 10, L"You Win!", wcslen(L"You Win!"));  
}  

void WinScene::OnMouseClick(int x, int y) {  
   // 클릭 시 메뉴로 돌아가기  
   CGameState::ChangeGameState(CGameState::MENU);  
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           패배씬
//--------------------------------------------------------------------------------------------------------------------------------

void LossScene::Render(HDC hDCFrameBuffer) {
	// "You Win!" 텍스트를 화면 중앙에 출력  
	const int centerX = FRAMEBUFFER_WIDTH / 2;
	const int centerY = FRAMEBUFFER_HEIGHT / 2;
	TextOutW(hDCFrameBuffer, centerX - 50, centerY - 10, L"You Loss!", wcslen(L"You Loss!"));
}

void LossScene::OnMouseClick(int x, int y) {
	// 클릭 시 메뉴로 돌아가기  
	CGameState::ChangeGameState(CGameState::MENU);
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           메뉴
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
        // 메뉴 항목 텍스트를 그리기
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
              ::PostQuitMessage(0); // 프로그램 종료  
          }  
          else if (m_MenuItems[i] == "Start")  
          {  
              CGameState::ChangeGameState(CGameState::GAME_1); // 게임 상태로 변경  
          }
		  else if (m_MenuItems[i] == "Level-1")
		  {
			  CGameState::ChangeGameState(CGameState::GAME_1); // 게임 상태로 변경  
		  }
		  else if (m_MenuItems[i] == "Level-2")
		  {
			  CGameState::ChangeGameState(CGameState::GAME); // 게임 상태로 변경  
		  }
      }  
  }  
}

//--------------------------------------------------------------------------------------------------------------------------------
//                           게임
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



	m_pObstacle = new CGameObject * [MAX_OBJECTS];
	CCubeMesh* Cm = new CCubeMesh(10.0f, 10.0f, 5.0f);


	m_pObstacle[0] = new CGameObject();
	m_pObstacle[0]->SetMesh(Cm);
	m_pObstacle[0]->SetColor(RGB(255, 0, 0));
	m_pObstacle[0]->SetPosition(-0.0f, 5.0f, -40.0f);
	m_pObstacle[0]->OnUpdateTransform();

	m_pObstacle[1] = new CGameObject();
	m_pObstacle[1]->SetMesh(Cm);
	m_pObstacle[1]->SetColor(RGB(255, 0, 0));
	m_pObstacle[1]->SetPosition(-0.0f, 5.0f, 40.0f);
	m_pObstacle[1]->OnUpdateTransform();

	m_pObstacle[2] = new CGameObject();
	m_pObstacle[2]->SetMesh(Cm);
	m_pObstacle[2]->SetColor(RGB(255, 0, 0));
	m_pObstacle[2]->SetPosition(-20.0f, 5.0f, 30.0f);
	m_pObstacle[2]->OnUpdateTransform();

	m_pObstacle[3] = new CGameObject();
	m_pObstacle[3]->SetMesh(Cm);
	m_pObstacle[3]->SetColor(RGB(255, 0, 0));
	m_pObstacle[3]->SetPosition(20.0f, 5.0f, 30.0f);
	m_pObstacle[3]->OnUpdateTransform();

	m_pObstacle[4] = new CGameObject();
	m_pObstacle[4]->SetMesh(Cm);
	m_pObstacle[4]->SetColor(RGB(255, 0, 0));
	m_pObstacle[4]->SetPosition(-20.0f, 5.0f, -30.0f);
	m_pObstacle[4]->OnUpdateTransform();

	m_pObstacle[5] = new CGameObject();
	m_pObstacle[5]->SetMesh(Cm);
	m_pObstacle[5]->SetColor(RGB(255, 0, 0));
	m_pObstacle[5]->SetPosition(20.0f, 5.0f, -30.0f);
	m_pObstacle[5]->OnUpdateTransform();

	CTankMesh* pTankMesh = new CTankMesh(4.0f, 4.0f, 4.0f);
	m_nObjects = 10;
	m_ppObjects = new CGameObject * [m_nObjects];



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


void CGameScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pFloorObject) delete m_pFloorObject;

#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis; //	m_pWorldAxis는 월드 축을 나타내는 객체
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

CGameObject* CGameScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	XMFLOAT3 xmf3PickPosition; //카메라 피킹 광선 (벡터이다)

	// 뷰포트 맵핑을 해서 카메라 좌표를 찾고 , 투영변환 행렬의 11과 22 를 X,Y에 나눈다( 역행렬을 곱한다)   -> 카메라 좌표의 X,Y를 구했다.
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	//투영평면에서 FOV가 90도라고 하면 D가 항상 1이기로 햇다
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);//피킹을 하는 가장 앞쪽에 있는 점이라고 생각을 하자.
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX; //가장 가까운 거리	
	CGameObject* pNearestObject = NULL;  //가장 가까운 오브젝트
	for (int i = 0; i < m_nObjects; i++)
	{
		float fHitDistance = FLT_MAX;
		//픽 포지션으로 가는 벡터하고 오브젝트의 바운딩박스하고의 충돌을 찾아내서 충돌이 되는 오브젝트중에 가장 가까운 오브젝트
		nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance); 
		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance)) //이전부터 찾은거중 가장 가까운
		{
			//오브젝트 포인터랑 거리를 바꿔서 루프를 다 돈다.
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i];
		}
	}
	return(pNearestObject);
}

void CGameScene::CheckObjectByObjectCollisions()
{
	//각 오브젝트들이 어떤 오브젝트하고 충돌이 일어났는지 알려주는 포인터 변수를 null로 초기화 시킨다.
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
		ContainmentType containType = m_pFloorObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB); //벽 자체의 바운딩 박스가 오브젝트의 바운딩 박스를 포함하고 있으면
		switch (containType) //컨테이너 타입에 따라서
		{
		case DISJOINT:  //오브젝트가 벽을 벗어났다는 뜻
		{
			//어느면을 벗어난 건지 찾아야 한다.
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				//오브젝트의 바운딩 박스와 , j번째의 벽평면하고의 intersects를 해서 안쪽공간으로 법선벡터가 향하고 있다고 하면 벗어나면 평면의 뒤에 있다
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pFloorObject->m_pxmf4WallPlanes[j])); 
				if (intersectType == BACK)
				{
					//j 번쨰 평면을 벗어났다.
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1) //벗어나는 평면이 있으면
			{
				//그 평면에 대해서 반사벡터를 구해서 오브젝트의 이동방향 벡터를 반사벡터로 만든다
				XMVECTOR xmvNormal = XMVectorSet(m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pFloorObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal); //반사벡터를 구함
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect); //이동방향 벡터를 반사벡터로 만든다

				//물체들은 벽에 반사되는 형태들로 이동하게 될 것임
			}
			break;
		}
		case INTERSECTS: //걸쳐저 있다는 뜻
		{
			//걸쳐저 있어도 똑같은 일을 해주면 된다.
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
		case CONTAINS: //포함한다 , 충돌하지 않았다는 뜻
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
void CGameScene::CheckTankIsBlowed()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];

			if (pExplosiveObject->blowed)
			{
				// 탱크 매시 오브젝트를 삭제  
				delete m_ppObjects[i];
				m_ppObjects[i] = nullptr;

				// 오브젝트 배열을 재정렬  
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
	CGameState::ChangeGameState(CGameState::WIN); // 게임 상태로 변경  
}
	


void CGameScene::CheckPlayerByBulletCollisions()  
{  
    CBulletObject* ppBullets;  
    for (int i = 0; i < m_nObjects; i++)  
    {  
        ppBullets = m_ppObjects[i]->GetBullets(); // 적 탱크의 총알 배열 가져오기  
        for (int j = 0; j < 1; j++)  
        {  
            if (ppBullets != nullptr && ppBullets->m_bActive)  
            {  
                if (ppBullets->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))  
                {  
                    if (m_pPlayer->m_bShieldActive)  
                    {  
                       ppBullets->Reset(); // 방어막 활성화 상태면 총알 제거  
                    }  
                    else  
                    {
						if (m_pPlayer->m_xmOOBB.Contains(ppBullets->m_xmOOBB) && ppBullets->m_bActive)
							++colNum;
						if(colNum>10)
							CGameState::ChangeGameState(CGameState::LOSS); // 게임 상태 변경  
                        return; // 상태 변경 후 함수 종료  
                    }  
                }  
            }  
        }  
    }  
}
//
// 벽이 총알을 막아줌
//
void CGameScene::CheckBulletByWallCollisions()
{
   CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->m_ppBullets;

   // 플레이어의 총알과 벽의 충돌 검사
   for (int i = 0; i < BULLETS; i++)
   {
	   for (int k = 0; k < 6; k++) {
		   if (ppBullets[i] && ppBullets[i]->m_bActive && ppBullets[i]->m_xmOOBB.Intersects(m_pObstacle[k]->m_xmOOBB)) // nullptr 체크 추가
		   {

			   ppBullets[i]->Reset(); // 벽에 충돌한 총알은 비활성화
		   }
	   }
   }

   // 적 탱크의 총알과 벽의 충돌 검사
   for (int i = 0; i < m_nObjects; i++)
   {
       CBulletObject* ppEnemyBullets = m_ppObjects[i]->GetBullets();
       for (int j = 0; j < BULLETS_1; j++) // BULLETS로 루프 수정
       {
		   for (int k = 0; k < 6; k++) {
			   if (ppEnemyBullets && ppEnemyBullets->m_bActive && ppEnemyBullets->m_xmOOBB.Intersects(m_pObstacle[k]->m_xmOOBB)) // nullptr 체크 추가
			   {

				   ppEnemyBullets->Reset(); // 벽에 충돌한 총알은 비활성화

			   }
		   }
       }
   }
}

void CGameScene::Animate(float fElapsedTime)
{
	m_pFloorObject->Animate(fElapsedTime);  //벽을 애니메이트 함

	for (int i = 0; i < m_nObjects; i++) {
		m_ppObjects[i]->Animate(fElapsedTime); //큐브들을 애니메이트 함. 각각의 오브젝트들은 위치가 바뀔 것임.
		m_ppObjects[i]->FireBullet();
	}
	for (int i = 0; i < 6; ++i) {
		m_pObstacle[i]->Animate(fElapsedTime);
	}
	RotateTanksToFacePlayer();




	//월드좌표계에서 충돌을 감지한다.
	//애니메이트 된 결과에 따라서 충돌을 감지함.
	CheckPlayerByWallCollision(); //플레이어랑 벽 충돌 검사

	CheckObjectByWallCollisions(); //오브젝트랑 벽 

	CheckObjectByObjectCollisions(); //오브젝트랑 오브젝트

	CheckObjectByBulletCollisions(); //오브젝트랑 총알

	CheckBulletByWallCollisions();

	CheckPlayerByBulletCollisions();

	CheckTankIsBlowed();
}

void CGameScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);  //m_Viewport를 뷰포트 값으로 설정

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



