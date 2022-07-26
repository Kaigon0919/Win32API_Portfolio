#include "stdafx.h"
#include "ActorRenderer.h"
#include"Actor.h"
#include"Level.h"

ActorRenderer::ActorRenderer() : m_bCamera(true)
{
}


ActorRenderer::~ActorRenderer()
{
}

Vector2f ActorRenderer::RenderPosition()
{
	Vector2f renderPosition = GetActor()->GetPosition() + (m_Pivot * GetActor()->GetSclae()) - (m_Size.GetHalf() * GetActor()->GetSclae());
	if (m_bCamera)
	{
		renderPosition -= GetActor()->GetLevel()->GetCameraPosition();
	}
	return renderPosition;
}
