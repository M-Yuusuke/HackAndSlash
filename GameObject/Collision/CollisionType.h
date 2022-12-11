#pragma once
//------------------------------------------------------------------
// @brief コリジョン形状種類
//------------------------------------------------------------------

namespace Calculation
{
	enum class CollisionType
	{
		Line,          // 線分
		Sphere,        // 球
		Capsule,       // カプセル
		Model          // モデル（メッシュ)
	};
}