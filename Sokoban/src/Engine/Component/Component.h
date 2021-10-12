#pragma once

#include "Engine/Object/Object.h"

namespace Elysia::Engine
{
class Component : public Object
{
	DECLARE_TYPENAME(Component);

public:
	Component(const tstring& _name);

	virtual ~Component() override;

	virtual void OnPaint() const;

	void SetActive(bool value);

	bool IsActive() const;

private:
	bool isActive;
};
}; // namespace Elysia::Engine
