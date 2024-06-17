#pragma once
#include "Core/Componet/ComponentBase.h"
#undef LoadImage

class SpriteRenderer : public ComponentBase
{
public:
	SpriteRenderer(GameObjectBase& gameObject) : ComponentBase(gameObject) {}
	virtual ~SpriteRenderer();

	void LoadImage(const wchar_t* path);

protected:
	virtual void Update() override;
	virtual void Render() override;

private:
	struct ID2D1Bitmap* image = nullptr;
};
