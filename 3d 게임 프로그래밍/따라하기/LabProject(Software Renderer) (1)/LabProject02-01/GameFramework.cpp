//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

void CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	::srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildFrameBuffer(); 

	BuildObjects(); 

	_tcscpy_s(m_pszFrameRate, _T("LabProject ("));
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);
}

void CGameFramework::BuildFrameBuffer()
{
	::GetClientRect(m_hWnd, &m_rcClient);

	HDC hDC = ::GetDC(m_hWnd);

    m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
    ::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
    ::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{    
    HDC hDC = ::GetDC(m_hWnd);
    ::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
    ::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::BuildObjects()
{
	CCamera* pCamera = new CCamera();
	pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	pCamera->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	pCamera->SetFOVAngle(60.0f);

	pCamera->GenerateOrthographicProjectionMatrix(1.01f, 50.0f, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

	CAirplaneMesh* pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);

	m_pPlayer = new CAirplanePlayer();
	m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
	m_pPlayer->SetMesh(pAirplaneMesh); 
	m_pPlayer->SetColor(RGB(0, 0, 255));
	m_pPlayer->SetCamera(pCamera);
	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));  //ī�޶� ������ ����

	m_pScene = new CGameScene(m_pPlayer);
	m_pScene->BuildObjects();
}

void CGameFramework::ReleaseObjects()
{
	if (m_pScene)
	{
		m_pScene->ReleaseObjects();
		delete m_pScene;
	}

	if (m_pPlayer) delete m_pPlayer;
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		if (nMessageID == WM_RBUTTONDOWN) m_pLockedObject = m_pScene->PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam); //null�� �ƴ� ���

	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:  //esc ������ ����
			::PostQuitMessage(0);
			break;
		case VK_RETURN:
			break;
		case VK_CONTROL:  //��Ʈ�� Ű ����
			((CAirplanePlayer*)m_pPlayer)->FireBullet(m_pLockedObject);
			m_pLockedObject = NULL;
			break;
		case VK_LSHIFT:
			m_pScene->ChangeGameState(CGameScene::GAME);
			break;
		default:
			m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
			break;
		}
		break;
	default:
		break;
	}
}

LRESULT CALLBACK CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_INACTIVE)
			m_GameTimer.Stop();
		else
			m_GameTimer.Start();
		break;
	}
	case WM_SIZE:
		break;
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

void CGameFramework::ProcessInput()//����� �Է��� �޾Ƶ帲
{
	static UCHAR pKeyBuffer[256];
	if (GetKeyboardState(pKeyBuffer))
	{
		DWORD dwDirection = 0;
		if (pKeyBuffer[VK_UP] & 0xF0) dwDirection |= DIR_FORWARD;
		if (pKeyBuffer[VK_DOWN] & 0xF0) dwDirection |= DIR_BACKWARD;
		if (pKeyBuffer[VK_LEFT] & 0xF0) dwDirection |= DIR_LEFT;
		if (pKeyBuffer[VK_RIGHT] & 0xF0) dwDirection |= DIR_RIGHT;
		if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;

		if (dwDirection) m_pPlayer->Move(dwDirection, 0.15f);
	}

	if (GetCapture() == m_hWnd)
	{
		SetCursor(NULL);
		POINT ptCursorPos;
		GetCursorPos(&ptCursorPos);
		float cxMouseDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		float cyMouseDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
		if (cxMouseDelta || cyMouseDelta)
		{
			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
				m_pPlayer->Rotate(cyMouseDelta, 0.0f, -cxMouseDelta);
			else
				m_pPlayer->Rotate(cyMouseDelta, cxMouseDelta, 0.0f);
		}
	}

	m_pPlayer->Update(m_GameTimer.GetTimeElapsed());
}

void CGameFramework::AnimateObjects()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed(); //���� Elapsed Ÿ���� �����´�
	if (m_pPlayer) m_pPlayer->Animate(fTimeElapsed); //�÷��̾ �ִϸ���Ʈ �Ѵ�
	if (m_pScene) m_pScene->Animate(fTimeElapsed);  //���� �ִϸ���Ʈ �Ѵ�.
}

void CGameFramework::FrameAdvance() //�� ������ ���� �� �Լ��� ������ �ݺ��Ѵ�.
{    
	m_GameTimer.Tick(60.0f); //�����ӷ���Ʈ�� 60�� �ǵ��� �Ѵ�.

	ProcessInput();//����� �Է��� �޾Ƶ帲

	AnimateObjects(); //���� �ִ� ������Ʈ�� �ִϸ���Ʈ ��

    ClearFrameBuffer(RGB(255, 255, 255));

	ChoiceGameMode(); //���� ��� ����

	//CCamera* pCamera = m_pPlayer->GetCamera();
	//if (m_pScene) m_pScene->Render(m_hDCFrameBuffer, pCamera); //�ִϸ���Ʈ �� ����� ���� ���� �����Ѵ�.


	PresentFrameBuffer(); //������ ����� ȭ�鿡 �׷��ش�.

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);
}

//�̸� , �й��� ȭ�鿡 �������
void CGameFramework::RenderTitle(HDC hDC)
{
    static float angle = 0.0f;
    angle += 0.01f; // ȸ�� �ӵ�

    // "�ڽſ�" �ؽ�Ʈ ȸ��
    SetGraphicsMode(hDC, GM_ADVANCED);
    XFORM xForm;
    xForm.eM11 = cos(angle);
    xForm.eM12 = sin(angle);
    xForm.eM21 = -sin(angle);
    xForm.eM22 = cos(angle);
    xForm.eDx = 300; // �ؽ�Ʈ ��ġ (x)
    xForm.eDy = 250; // �ؽ�Ʈ ��ġ (y)
    SetWorldTransform(hDC, &xForm);

	TextOutW(hDC, 0, 0, L"�ڽſ�", wcslen(L"�ڽſ�"));

    // ȸ������ �ʴ� "3D �������α׷��� 1" �ؽ�Ʈ
    ModifyWorldTransform(hDC, NULL, MWT_IDENTITY);
    TextOut(hDC, 320, 240, L"3D �������α׷��� 1", wcslen(L"3D �������α׷��� 1"));
}

void CGameFramework::ChoiceGameMode()// ��忡 ���� ȭ�� ���
{
	enum GameState { TITLE, MENU, GAME };

	if (m_pScene && m_pPlayer)
	{
		switch (m_pScene->GetCurrentState())
		{
		case TITLE:
			RenderTitle(m_hDCFrameBuffer); // Ÿ��Ʋ ȭ�� ������
			break;
		case MENU:
			// RenderMenu(m_hDCFrameBuffer); // �޴� ȭ�� ������
			break;
		case GAME:
			CCamera* pCamera = m_pPlayer->GetCamera();
			if (pCamera) m_pScene->Render(m_hDCFrameBuffer, pCamera); // ���� ȭ�� ������
			break;
		}
	}

}
