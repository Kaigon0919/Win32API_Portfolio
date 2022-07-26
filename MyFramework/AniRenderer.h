#pragma once
#include "ActorRenderer.h"
#include"NameBase.h"

class GameSprite;
class MultiSprite;
class AniRenderer : public ActorRenderer
{
public:
	AniRenderer();
	~AniRenderer();

#pragma region InnerClass
private: // inner Class
	class Animation : public NameBase
	{
	public:
		Animation(MultiSprite* _multySprite, size_t _startIndex, size_t _endIndex, bool _isLoop,float _frameTime);
		~Animation();
	private:
		MultiSprite* m_pMultiSprite;
		size_t m_StartIndex;
		size_t m_EndIndex;
		size_t m_CurIndex;
		size_t m_FrameNumber;
		float m_fTime;
		float m_fCheckTime;
		bool m_bLoop;
	public:
		inline bool IsEnd()
		{
			return m_CurIndex == m_FrameNumber && m_fTime <= m_fCheckTime;
		}
		GameSprite* GetCurSprite();
		inline size_t GetCurIndex()const
		{
			return m_CurIndex;
		}

	public:
		void Update();
		void Start(size_t _Start);
	};
#pragma endregion

private:
	std::map<std::wstring, Animation*> m_AnimationMap;
	Animation * m_CurAni;
	BYTE m_AlphaValue;
public:
	bool IsCurAni(const wchar_t * _name)const
	{
		if (m_CurAni)
		{
			return m_CurAni->NameEqual(_name);
		}
		return false;
	}
	bool IsEnd()const
	{
		return m_CurAni->IsEnd();
	}
	inline size_t GetCurIndex()const
	{
		return m_CurAni->GetCurIndex();
	}
	inline void SetAlphaValue(BYTE alpha)
	{
		m_AlphaValue = alpha;
	}
private:
	Animation* FindAnimation(const wchar_t* _name);

public:
	bool CreateAnimation(const wchar_t* _name, const wchar_t* _multiSpriteName, size_t _startIndex, size_t _endIndex, bool _loop = true, float _delay = 0.1f);
	void ChangeAnimation(const wchar_t* _name, size_t _index = 0);
public:
	virtual void Render() override;


};

