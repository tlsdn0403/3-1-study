#pragma once
#include "Mesh.h"
#include <string>
#include <vector>

class TextMesh : public Mesh {
public:
    TextMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, const std::wstring& text, float size = 1.0f, XMFLOAT4 color = XMFLOAT4(1,1,1,1));
    virtual ~TextMesh();
protected:
    void CreateTextMesh(const std::wstring& text, float size, XMFLOAT4 color);
};
#include "stdafx.h"
#include "TextMesh.h"

// 문자 하나를 사각형(두 삼각형)으로 표현하는 예시
// 실제로는 폰트 텍스처(폰트 아틀라스)와 UV 좌표가 필요함
// 여기서는 단순히 각 글자를 사각형으로 나열하는 구조

TextMesh::TextMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, const std::wstring& text, float size, XMFLOAT4 color)
    : Mesh(pd3dDevice, pd3dCommandList)
{
    CreateTextMesh(text, size, color);

    m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
    m_d3dVertexBufferView.StrideInBytes = m_nStride;
    m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
}

TextMesh::~TextMesh() {}

void TextMesh::CreateTextMesh(const std::wstring& text, float size, XMFLOAT4 color)
{
    // 한 글자당 사각형(2삼각형, 6정점)으로 단순화
    m_nVertices = static_cast<UINT>(text.length()) * 6;
    m_nStride = sizeof(DiffusedVertex);
    m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    std::vector<DiffusedVertex> vertices;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float charWidth = size;
    float charHeight = size * 1.2f;

    for (size_t i = 0; i < text.length(); ++i) {
        // 각 글자를 사각형으로 배치
        // 실제 폰트 메쉬가 아니라 단순 사각형임
        float left = x;
        float right = x + charWidth;
        float top = y + charHeight;
        float bottom = y;

        // 두 삼각형
        vertices.push_back(DiffusedVertex(XMFLOAT3(left, top, z), color));
        vertices.push_back(DiffusedVertex(XMFLOAT3(right, top, z), color));
        vertices.push_back(DiffusedVertex(XMFLOAT3(right, bottom, z), color));

        vertices.push_back(DiffusedVertex(XMFLOAT3(left, top, z), color));
        vertices.push_back(DiffusedVertex(XMFLOAT3(right, bottom, z), color));
        vertices.push_back(DiffusedVertex(XMFLOAT3(left, bottom, z), color));

        x += charWidth * 1.1f; // 글자 간격
    }

    m_pd3dVertexBuffer = ::CreateBufferResource(
        nullptr, nullptr, vertices.data(), m_nStride * m_nVertices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer
    );
}
