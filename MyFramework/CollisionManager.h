#pragma once
#include<list>
#include<map>

class Level;
class ActorCollision;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

#pragma region InnerClass
private:
	class ColGroup
	{
	public:
		ColGroup();
		~ColGroup();

	public:
		std::wstring name;
	private:
		// �浹�� ��ü ���� ����.
		std::list<ActorCollision*> m_ColList;

		std::list<ActorCollision*>::iterator m_itThisStart;
		std::list<ActorCollision*>::iterator m_itThisEnd;

		std::list<ActorCollision*>::iterator m_itOtherStart;
		std::list<ActorCollision*>::iterator m_itOtherEnd;

		// �׷� ���� �ڷᱸ��.
		std::list<ColGroup*> m_OtherColGroup;

		std::list<ColGroup*>::iterator m_itGroupStart;
		std::list<ColGroup*>::iterator m_itGroupEnd;

	public:
		// �浹 ���� �׷� ����.
		void Link(ColGroup* _otherGroup);

		// �浹�� ��ü ���� ����.
		void PushCol(ActorCollision* _col);

		void ColCheck(ColGroup* _otherGroup);
		void ColUpdate();
		void ColSetting();
		void Release();
		void DebugRender();
	};
#pragma endregion

private:
	std::map<std::wstring, ColGroup*> m_ColMap;
	std::map<std::wstring, ColGroup*>::iterator m_itFind;

private:
	ColGroup* FindColGroup(const wchar_t * _GroupName);

public:
	void PushCol(const wchar_t* _GroupName, ActorCollision* _Col);
	void Link(const wchar_t* _Left, const wchar_t* _Right);

	void ColUpdate();
	void Release();
	void DebugRender();
};

