#include "stdafx.h"
#include "SingleRenderer.h"
#include"ResourceManager.h"
#include"Actor.h"
#include"GameSprite.h"

#pragma comment(lib,"msimg32.lib")

SingleRenderer::SingleRenderer() : m_Sprite(nullptr), m_AlphaValue(0)
{
}


SingleRenderer::~SingleRenderer()
{

}

void SingleRenderer::Render()
{
	if (!m_Sprite)
	{
		return;
	}

	Vector2f position = RenderPosition();

	// ����� �ӽ� ó��. �ٸ� �̹����� ��� ��ǥ Ʋ��. // �����κ�, Half ���� Actor ����� ���� ���ϰ� �Ѵ�.
	if (m_Sprite->IsAlpha())
	{
		BLENDFUNCTION BF;
		BF.BlendOp = AC_SRC_OVER;
		BF.BlendFlags = 0;
		BF.AlphaFormat = AC_SRC_ALPHA;
		BF.SourceConstantAlpha = m_AlphaValue;

		AlphaBlend(ResourceManager::Instance().GetBackBuffer(), position.GetIntX(), position.GetIntY(), static_cast<int>(m_Size.x * GetActor()->GetSclae()), static_cast<int>(m_Size.y * GetActor()->GetSclae()), m_Sprite->GetHDC(), m_Sprite->GetPosition().GetIntX(), m_Sprite->GetPosition().GetIntY(), m_Sprite->GetSize().GetIntX(), m_Sprite->GetSize().GetIntY(), BF);
	}
	else
	{
		TransparentBlt(ResourceManager::Instance().GetBackBuffer(), position.GetIntX(), position.GetIntY(), static_cast<int>(m_Size.x * GetActor()->GetSclae()), static_cast<int>(m_Size.y * GetActor()->GetSclae()), m_Sprite->GetHDC(), m_Sprite->GetPosition().GetIntX(), m_Sprite->GetPosition().GetIntY(), m_Sprite->GetSize().GetIntX(), m_Sprite->GetSize().GetIntY(), m_Sprite->GetTransColor());
	}
}

void SingleRenderer::SettingSprite(const wchar_t * _spriteName)
{
	m_Sprite = ResourceManager::Instance().FindSprite(_spriteName);
	if (m_Sprite == nullptr)
	{
		return;
	}
	m_Size = m_Sprite->GetSize();
}

void SingleRenderer::SettingSprite(const wchar_t * _pImageName, size_t _Count)
{
	m_Sprite = ResourceManager::Instance().FindSprite(_pImageName, _Count);
}
