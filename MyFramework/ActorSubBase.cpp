#include "stdafx.h"
#include "ActorSubBase.h"
#include"Actor.h"

ActorSubBase::ActorSubBase()
{
}


ActorSubBase::~ActorSubBase()
{
}

bool ActorSubBase::IsUpdate() const
{
	return UpdateBase::IsUpdate() && GetActor()->IsUpdate();
}
bool ActorSubBase::IsDeath() const
{
	return UpdateBase::IsDeath() || GetActor()->IsDeath();
}

Vector2f ActorSubBase::GetParentPos() const
{
	return  GetActor()->GetPosition() + m_Pivot;
}

Vector2f ActorSubBase::GetScreenPos() const
{
	return GetActor()->GetScreenPosition() + m_Pivot;
}
