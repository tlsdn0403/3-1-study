
#include "stdafx.h"
#include "Mesh.h"
#include "TextMesh.h"

struct Box3D {
    XMFLOAT3 center;
    float w, h, d;
    float angle;
};
// --- 유틸리티 함수들 ---
// 직육면체(박스) 추가
void AddCuboid(XMFLOAT3 center, float w, float h, float d, XMFLOAT4 color, std::vector<DiffusedVertex>& v, std::vector<UINT>& i) {
    float hw = w * 0.5f, hh = h * 0.5f, hd = d * 0.5f;
    XMFLOAT3 vs[8] = {
        {center.x - hw, center.y + hh, center.z - hd}, {center.x + hw, center.y + hh, center.z - hd},
        {center.x + hw, center.y + hh, center.z + hd}, {center.x - hw, center.y + hh, center.z + hd},
        {center.x - hw, center.y - hh, center.z - hd}, {center.x + hw, center.y - hh, center.z - hd},
        {center.x + hw, center.y - hh, center.z + hd}, {center.x - hw, center.y - hh, center.z + hd}
    };
    UINT base = static_cast<UINT>(v.size());
    for (int j = 0; j < 8; ++j) v.push_back(DiffusedVertex(vs[j], color));
    UINT idx[] = { 3,1,0, 2,1,3, 0,5,4, 1,5,0, 3,4,7, 0,4,3, 1,6,5, 2,6,1, 2,7,6, 3,7,2, 6,4,5, 7,4,6 };
    for (int j = 0; j < 36; ++j) i.push_back(base + idx[j]);
}

// 원형 링(도넛) 추가
void AddRing(XMFLOAT3 center, float radius, float thickness, float depth, int segments, XMFLOAT4 color, std::vector<DiffusedVertex>& v, std::vector<UINT>& i) {
    float hd = depth * 0.5f;
    for (int s = 0; s < segments; ++s) {
        float a0 = XM_2PI * s / segments;
        float a1 = XM_2PI * (s + 1) / segments;
        float ca0 = cosf(a0), sa0 = sinf(a0), ca1 = cosf(a1), sa1 = sinf(a1);
        XMFLOAT3 p[8] = {
            {center.x + (radius + thickness * 0.5f) * ca0, center.y + (radius + thickness * 0.5f) * sa0, center.z + hd},
            {center.x + (radius + thickness * 0.5f) * ca1, center.y + (radius + thickness * 0.5f) * sa1, center.z + hd},
            {center.x + (radius - thickness * 0.5f) * ca1, center.y + (radius - thickness * 0.5f) * sa1, center.z + hd},
            {center.x + (radius - thickness * 0.5f) * ca0, center.y + (radius - thickness * 0.5f) * sa0, center.z + hd},
            {center.x + (radius + thickness * 0.5f) * ca0, center.y + (radius + thickness * 0.5f) * sa0, center.z - hd},
            {center.x + (radius + thickness * 0.5f) * ca1, center.y + (radius + thickness * 0.5f) * sa1, center.z - hd},
            {center.x + (radius - thickness * 0.5f) * ca1, center.y + (radius - thickness * 0.5f) * sa1, center.z - hd},
            {center.x + (radius - thickness * 0.5f) * ca0, center.y + (radius - thickness * 0.5f) * sa0, center.z - hd}
        };
        UINT base = static_cast<UINT>(v.size());
        for (int j = 0; j < 8; ++j) v.push_back(DiffusedVertex(p[j], color));
        UINT idx[] = { 0,1,2, 0,2,3, 4,7,6, 4,6,5, 0,4,5, 0,5,1, 2,6,7, 2,7,3, 1,5,6, 1,6,2, 0,3,7, 0,7,4 };
        for (int j = 0; j < 36; ++j) i.push_back(base + idx[j]);
    }
}

// 곡선 획(아크) 추가(반원 등)
void AddCurvedStroke(XMFLOAT3 center, float radius, float thickness, float angleStart, float angleEnd, int segments, float depth, XMFLOAT4 color, std::vector<DiffusedVertex>& v, std::vector<UINT>& i) {
    float hd = depth * 0.5f;
    float a0 = XMConvertToRadians(angleStart);
    float a1 = XMConvertToRadians(angleEnd);
    for (int s = 0; s < segments; ++s) {
        float t0 = a0 + (a1 - a0) * s / segments;
        float t1 = a0 + (a1 - a0) * (s + 1) / segments;
        float ca0 = cosf(t0), sa0 = sinf(t0), ca1 = cosf(t1), sa1 = sinf(t1);
        XMFLOAT3 p[8] = {
            {center.x + (radius + thickness * 0.5f) * ca0, center.y + (radius + thickness * 0.5f) * sa0, center.z + hd},
            {center.x + (radius + thickness * 0.5f) * ca1, center.y + (radius + thickness * 0.5f) * sa1, center.z + hd},
            {center.x + (radius - thickness * 0.5f) * ca1, center.y + (radius - thickness * 0.5f) * sa1, center.z + hd},
            {center.x + (radius - thickness * 0.5f) * ca0, center.y + (radius - thickness * 0.5f) * sa0, center.z + hd},
            {center.x + (radius + thickness * 0.5f) * ca0, center.y + (radius + thickness * 0.5f) * sa0, center.z - hd},
            {center.x + (radius + thickness * 0.5f) * ca1, center.y + (radius + thickness * 0.5f) * sa1, center.z - hd},
            {center.x + (radius - thickness * 0.5f) * ca1, center.y + (radius - thickness * 0.5f) * sa1, center.z - hd},
            {center.x + (radius - thickness * 0.5f) * ca0, center.y + (radius - thickness * 0.5f) * sa0, center.z - hd}
        };
        UINT base = static_cast<UINT>(v.size());
        for (int j = 0; j < 8; ++j) v.push_back(DiffusedVertex(p[j], color));
        UINT idx[] = { 0,1,2, 0,2,3, 4,7,6, 4,6,5, 0,4,5, 0,5,1, 2,6,7, 2,7,3, 1,5,6, 1,6,2, 0,3,7, 0,7,4 };
        for (int j = 0; j < 36; ++j) i.push_back(base + idx[j]);
    }
}

// 네모 프레임(사각형 테두리) 추가
void AddFrameBox(XMFLOAT3 center, float size, float thickness, float depth, XMFLOAT4 color, std::vector<DiffusedVertex>& v, std::vector<UINT>& i) {
    float hs = size * 0.5f;
    // 위, 아래, 왼, 오 4개 박스
    AddCuboid(XMFLOAT3(center.x, center.y + hs - thickness * 0.5f, center.z), size, thickness, depth, color, v, i);
    AddCuboid(XMFLOAT3(center.x, center.y - hs + thickness * 0.5f, center.z), size, thickness, depth, color, v, i);
    AddCuboid(XMFLOAT3(center.x - hs + thickness * 0.5f, center.y, center.z), thickness, size - thickness * 2.0f, depth, color, v, i);
    AddCuboid(XMFLOAT3(center.x + hs - thickness * 0.5f, center.y, center.z), thickness, size - thickness * 2.0f, depth, color, v, i);
}
TextMeshDiffused_3::TextMeshDiffused_3(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
    float fWidth, float fHeight, float fDepth)
{
    float thickness = fWidth * 0.12f; // 외곽선 두께
    float left = -fWidth * 0.5f;
    float right = fWidth * 0.5f;
    float top = fHeight * 0.5f;
    float bottom = -fHeight * 0.5f;
    float stepY = fHeight / 4.0f;       // 가로줄 사잇값
    float stepX = fWidth / 5.0f;        // 오른쪽 세로줄 시작 x좌표

    XMFLOAT4 color = RANDOM_COLOR;

   
    std::vector<Box3D> boxes = {
        // 윗 가로줄
        { XMFLOAT3((left + right) * 0.5f, top - stepY * 0.0f, 0), (right - left), thickness, fDepth, 0.0f },
        // 가운데 가로줄
        { XMFLOAT3((left + right) * 0.5f, top - stepY * 2.0f, 0), (right - left), thickness, fDepth, 0.0f },
        // 아랫 가로줄
        { XMFLOAT3((left + right) * 0.5f, bottom, 0), (right - left), thickness, fDepth, 0.0f },
        // 오른쪽 세로줄
        { XMFLOAT3(right, (top + bottom) * 0.5f, 0), thickness, (top - bottom), fDepth, 0.0f }
    };

    // [2] 각 박스를 8정점+12삼각형(36인덱스)로 쌓기
    std::vector<DiffusedVertex> vertices;
    std::vector<UINT> indices;
    auto addCuboid = [&](XMFLOAT3 center, float w, float h, float d, float zrot, XMFLOAT4 color) {
        // (zrot는 여기서는 0만 사용, 확장 필요하면 구현)
        float hw = w * 0.5f, hh = h * 0.5f, hd = d * 0.5f;
        // 8 꼭짓점
        XMFLOAT3 vs[8] = {
            {center.x - hw, center.y + hh, center.z - hd}, // 0
            {center.x + hw, center.y + hh, center.z - hd}, // 1
            {center.x + hw, center.y + hh, center.z + hd}, // 2
            {center.x - hw, center.y + hh, center.z + hd}, // 3
            {center.x - hw, center.y - hh, center.z - hd}, // 4
            {center.x + hw, center.y - hh, center.z - hd}, // 5
            {center.x + hw, center.y - hh, center.z + hd}, // 6
            {center.x - hw, center.y - hh, center.z + hd}  // 7
        };
        UINT base = static_cast<UINT>(vertices.size());
        for (int i = 0; i < 8; ++i) vertices.push_back(DiffusedVertex(vs[i], color));
        // 12 삼각형(36 인덱스)
        UINT idx[] = {
            3,1,0, 2,1,3, // 윗면
            0,5,4, 1,5,0, // 앞면
            3,4,7, 0,4,3, // 왼면
            1,6,5, 2,6,1, // 오른면
            2,7,6, 3,7,2, // 뒷면
            6,4,5, 7,4,6  // 아랫면
        };
        for (int i = 0; i < 36; ++i) indices.push_back(base + idx[i]);
        };

    for (auto& b : boxes)
        addCuboid(b.center, b.w, b.h, b.d, b.angle, color);

    // [3] 버퍼 생성
    m_nVertices = static_cast<UINT>(vertices.size());
    m_nStride = sizeof(DiffusedVertex);
    m_pd3dVertexBuffer = ::CreateBufferResource(
        pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer
    );
    m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
    m_d3dVertexBufferView.StrideInBytes = m_nStride;
    m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

    m_nIndices = static_cast<UINT>(indices.size());
    m_pd3dIndexBuffer = ::CreateBufferResource(
        pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer
    );
    m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
    m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
    m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
    m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}








TextMeshDiffused_D::TextMeshDiffused_D(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
    float fWidth, float fHeight, float fDepth)
{

    float thickness = fWidth * 0.12f;
    float left = -fWidth * 0.5f;
    float right = fWidth * 0.5f;
    float top = fHeight * 0.5f;
    float bottom = -fHeight * 0.5f;
    XMFLOAT4 color = RANDOM_COLOR;

    struct Box3D {
        XMFLOAT3 center;
        float w, h, d;
    };
    std::vector<Box3D> boxes = {
        // 윗 가로줄 (좌~우 세로줄 안쪽까지)
        { XMFLOAT3(0, top - thickness * 0.5f, 0), fWidth - thickness, thickness, fDepth },
        // 아랫 가로줄 (좌~우 세로줄 안쪽까지)
        { XMFLOAT3(0, bottom + thickness * 0.5f, 0), fWidth - thickness, thickness, fDepth },
        // 왼 세로줄 (윗~아래 가로줄 안쪽까지)
        { XMFLOAT3(left + thickness * 0.5f, 0, 0), thickness, fHeight - 2 * thickness, fDepth },
        // 오른 세로줄 (윗~아래 가로줄 안쪽까지)
        { XMFLOAT3(right - thickness * 0.5f, 0, 0), thickness, fHeight - 2 * thickness, fDepth }
    };

    std::vector<DiffusedVertex> vertices;
    std::vector<UINT> indices;
    auto addCuboid = [&](XMFLOAT3 center, float w, float h, float d, XMFLOAT4 color) {
        float hw = w * 0.5f, hh = h * 0.5f, hd = d * 0.5f;
        XMFLOAT3 vs[8] = {
            {center.x - hw, center.y + hh, center.z - hd},
            {center.x + hw, center.y + hh, center.z - hd},
            {center.x + hw, center.y + hh, center.z + hd},
            {center.x - hw, center.y + hh, center.z + hd},
            {center.x - hw, center.y - hh, center.z - hd},
            {center.x + hw, center.y - hh, center.z - hd},
            {center.x + hw, center.y - hh, center.z + hd},
            {center.x - hw, center.y - hh, center.z + hd}
        };
        UINT base = static_cast<UINT>(vertices.size());
        for (int i = 0; i < 8; ++i) vertices.push_back(DiffusedVertex(vs[i], color));
        UINT idx[] = {
            3,1,0, 2,1,3, // 윗면
            0,5,4, 1,5,0, // 앞면
            3,4,7, 0,4,3, // 왼면
            1,6,5, 2,6,1, // 오른면
            2,7,6, 3,7,2, // 뒷면
            6,4,5, 7,4,6  // 아랫면
        };
        for (int i = 0; i < 36; ++i) indices.push_back(base + idx[i]);
        };

    for (auto& b : boxes)
        addCuboid(b.center, b.w, b.h, b.d, color);

    m_nVertices = static_cast<UINT>(vertices.size());
    m_nStride = sizeof(DiffusedVertex);
    m_pd3dVertexBuffer = ::CreateBufferResource(
        pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer
    );
    m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
    m_d3dVertexBufferView.StrideInBytes = m_nStride;
    m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

    m_nIndices = static_cast<UINT>(indices.size());
    m_pd3dIndexBuffer = ::CreateBufferResource(
        pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer
    );
    m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
    m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
    m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
    m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


// "게임" 이미지를 각진/곡선 3D 메시로 수작업 생성하는 예시
TextMeshDiffused_Game::TextMeshDiffused_Game(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
    float fWidth, float fHeight, float fDepth)
{
    // 전체 영역 크기 기준 (이미지 비율 감안, 실제 배치 조정 필요)
    float thickness = fWidth * 0.10f;
    float boxDepth = fDepth;
    float x0 = -fWidth * 0.5f;
    float x1 = -fWidth * 0.2f;
    float x2 = 0.0f;
    float x3 = fWidth * 0.2f;
    float x4 = fWidth * 0.5f;
    float y0 = fHeight * 0.35f;
    float y1 = 0.0f;
    float y2 = -fHeight * 0.35f;

    XMFLOAT4 color = RANDOM_COLOR;

    std::vector<DiffusedVertex> vertices;
    std::vector<UINT> indices;

    // [1] 'ㄱ' (왼쪽 세로줄 + 위쪽 가로줄)
    // 세로줄
    AddCuboid(XMFLOAT3(x0 + thickness * 0.5f, y1, 0), thickness, fHeight * 0.7f, boxDepth, color, vertices, indices);
    // 가로줄
    AddCuboid(XMFLOAT3(x0 + (x1 - x0) * 0.5f, y0, 0), (x1 - x0), thickness, boxDepth, color, vertices, indices);

    // [2] 'ㅔ' (오른쪽 2개의 곡선 세로줄)
    // 첫 번째 곡선(왼쪽)
    AddCurvedStroke(XMFLOAT3(x1 + thickness, y0 * 0.9f, 0), fHeight * 0.27f, thickness, -80.0f, 80.0f, 10, boxDepth, color, vertices, indices);
    // 두 번째 곡선(오른쪽)
    AddCurvedStroke(XMFLOAT3(x2, y1, 0), fHeight * 0.35f, thickness, -90.0f, 90.0f, 10, boxDepth, color, vertices, indices);

    // [3] 내부 가로 획(ㅔ의 가로줄)
    AddCuboid(XMFLOAT3(x1 + (x2 - x1) * 0.35f, y1, 0), (x2 - x1) * 0.7f, thickness, boxDepth, color, vertices, indices);

    // [4] 'ㅇ' (원)
    AddRing(XMFLOAT3(x3 + thickness * 2.0f, y0, 0), fHeight * 0.16f, thickness, boxDepth, 32, color, vertices, indices);

    // [5] 'ㅁ' (네모 프레임)
    AddFrameBox(XMFLOAT3(x3 + thickness * 2.0f, y2, 0), fHeight * 0.23f, thickness, boxDepth, color, vertices, indices);

    // [6] 'ㅣ' (오른쪽 세로줄)
    AddCuboid(XMFLOAT3(x4 - thickness * 0.5f, y1, 0), thickness, fHeight * 0.7f, boxDepth, color, vertices, indices);

    // 버퍼 생성(생략, 이전과 동일)
    m_nVertices = static_cast<UINT>(vertices.size());
    m_nStride = sizeof(DiffusedVertex);
    m_pd3dVertexBuffer = ::CreateBufferResource(
        pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer
    );
    m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
    m_d3dVertexBufferView.StrideInBytes = m_nStride;
    m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

    m_nIndices = static_cast<UINT>(indices.size());
    m_pd3dIndexBuffer = ::CreateBufferResource(
        pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer
    );
    m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
    m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
    m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
    m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

