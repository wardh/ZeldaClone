#pragma once

enum class eRenderLayer;
namespace DX2D
{
	class CSprite;
}
struct RenderCommand
{
	Matrix33<float> mySpace;
	DX2D::CSprite* mySprite;
};