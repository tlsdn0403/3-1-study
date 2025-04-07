#pragma once
//�̸� ������ �Ǵ� ��� ����
//��ü�� �� ���� ũ�Ⱑ ū ���ϵ��� �̸� ������ �صθ� ����.

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include<string>
#include<wrl.h>
#include<shellapi.h>
#include<timeapi.h>
#include <d3d12.h> //���̷�Ʈ 3d 12�� api �Լ����� ����ϱ� ���ؼ� �ʿ�
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

#include <DirectXCollision.h>
#include <DXGIDebug.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using Microsoft::WRL::ComPtr;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib") // �߰��� �κ�

#define FRAME_BUFFER_WIDTH  800
#define FRAME_BUFFER_HEIGHT 600
//������ �� ��üȭ���� ��.
//#define _WITH_SWAPCHAIN_FULLSCREEN_STATE