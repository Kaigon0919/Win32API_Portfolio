#include "stdafx.h"
#include "AniRenderer.h"
#include"GameSprite.h"
#include"MultiSprite.h"
#include"Actor.h"
#include"ResourceManager.h"
//////////////////////////////////////////////////////////////////
//	AniRenderer													//

AniRenderer::AniRenderer() : m_AlphaValue(100)
{
}


AniRenderer::~AniRenderer()
{
	std::map<std::wstring, Animation*>::iterator itStart = m_AnimationMap.begin();
	std::map<std::wstring, Animation*>::iterator itEnd = m_AnimationMap.end();

	for (; itStart != itEnd; ++itStart)
	{
		if (itStart->second != nullptr)
		{
			delete itStart->second;
			itStart->second = nullptr;
		}
	}

}

AniRenderer::Animation * AniRenderer::FindAnimation(const wchar_t * _name)
{
	std::map<std::wstring, Animation*>::iterator taget = m_AnimationMap.find(_name);
	if (taget == m_AnimationMap.end())
	{
		return nullptr;
	}
	return taget->second;
}

bool AniRenderer::CreateAnimation(const wchar_t * _name, const wchar_t * _multiSpriteName, size_t _startIndex, size_t _endIndex, bool _loop, float _delay)
{
	AniRenderer::Animation * pFindAni = FindAnimation(_name);
	if (pFindAni)
	{
		assert(false);
		return false;
	}

	MultiSprite* pStrite = ResourceManager::Instance().FindMultiSprite(_multiSpriteName);
	if (!pStrite)
	{
		assert(false);
		return false;
	}

	Animation* newAni = new Animation(pStrite, _startIndex, _endIndex, _loop, _delay);
	newAni->SetName(_name);
	m_AnimationMap.insert(std::map<std::wstring, Animation*>::value_type(_name, newAni));

	return true;
}

void AniRenderer::ChangeAnimation(const wchar_t * _name, size_t _index)
{
	Animation* newAni = FindAnimation(_name);
	if (!newAni)
	{
		return;
	}

	m_CurAni = newAni;
	m_CurAni->Start(_index);
}

void AniRenderer::Render()
{
	if (m_CurAni == nullptr)
	{
		return;
	}

	m_CurAni->Update();
	GameSprite* pSprite = m_CurAni->GetCurSprite();

	if (pSprite)
	{
		Vector2f position = RenderPosition();
		if (pSprite->IsAlpha())
		{
			BLENDFUNCTION BF;
			BF.BlendOp = AC_SRC_OVER;
			BF.BlendFlags = 0;
			BF.AlphaFormat = AC_SRC_ALPHA;
			BF.SourceConstantAlpha = m_AlphaValue;

			AlphaBlend(ResourceManager::Instance().GetBackBuffer(), position.GetIntX(), position.GetIntY(), static_cast<int>(m_Size.x * GetActor()->GetSclae()), static_cast<int>(m_Size.y * GetActor()->GetSclae()), pSprite->GetHDC(), pSprite->GetPosition().GetIntX(), pSprite->GetPosition().GetIntY(), pSprite->GetSize().GetIntX(), pSprite->GetSize().GetIntY(), BF);
		}
		else
		{
			TransparentBlt(ResourceManager::Instance().GetBackBuffer(), position.GetIntX(), position.GetIntY(), static_cast<int>(m_Size.x * GetActor()->GetSclae()), static_cast<int>(m_Size.y * GetActor()->GetSclae()), pSprite->GetHDC(), pSprite->GetPosition().GetIntX(), pSprite->GetPosition().GetIntY(), pSprite->GetSize().GetIntX(), pSprite->GetSize().GetIntY(), pSprite->GetTransColor());
		}
	}
}


//////////////////////////////////////////////////////////////////
//	Animaition													//

AniRenderer::Animation::Animation(MultiSprite* _multySprite, size_t _startIndex, size_t _endIndex, bool _isLoop, float _frameTime)
	:m_pMultiSprite(_multySprite), m_StartIndex(_startIndex), m_EndIndex(_endIndex), m_bLoop(_isLoop), m_fTime(_frameTime), m_fCheckTime(0.0f), m_CurIndex(0), m_FrameNumber(_endIndex - _startIndex)
{
}

AniRenderer::Animation::~Animation()
{
}

void AniRenderer::Animation::Update()
{
	if (m_FrameNumber <= 0)
	{
		return;
	}

	m_fCheckTime += TimeManager::Instance().GetDeltaTime();

	if (m_fCheckTime >= m_fTime)
	{
		size_t count = (size_t)(m_fCheckTime / m_fTime);
		m_CurIndex += count;

		if (m_bLoop)
		{
			m_CurIndex %= m_FrameNumber+1;
		}
		else if(!m_bLoop && m_CurIndex > m_FrameNumber)
		{
			m_CurIndex = m_FrameNumber;
			return;
		}

		m_fCheckTime = 0.0f;
	}
}

void AniRenderer::Animation::Start(size_t _Start)
{
	if (_Start >= m_FrameNumber)
	{
		m_CurIndex = m_FrameNumber;
	}
	m_CurIndex = _Start;
	m_fCheckTime = 0;
}

GameSprite * AniRenderer::Animation::GetCurSprite()
{
	return m_pMultiSprite->GetSprite(m_CurIndex+m_StartIndex);
}
