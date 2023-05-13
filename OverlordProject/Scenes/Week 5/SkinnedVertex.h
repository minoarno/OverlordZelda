#pragma once
#include "DirectXMath.h"
#include "Utils/VertexHelper.h"
#include <stdexcept>

struct SkinnedVertex
{
	SkinnedVertex(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& normal, const DirectX::XMFLOAT4& color, float blendRatio = 0.5f)
		: blendRatio{ blendRatio }
		, originalVertex{ position, normal, color }
		, transformedVertex{ position, normal, color }
	{
		if ((blendRatio < 0.f) || (1.f < blendRatio))
			throw std::invalid_argument("blendRatio is not a value between 0 and 1");
	}
	float blendRatio;
	VertexPosNormCol originalVertex;
	VertexPosNormCol transformedVertex;
};
