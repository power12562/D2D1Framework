#include "BoxRenderer.h"
#include <Framework/D2DRenderer.h>

BoxRenderer::~BoxRenderer()
{
}

void BoxRenderer::Render()
{
	const Vector2 halfSize = size * 0.5f;
	D2DRenderer::DrawRect(
		D2D1::Matrix3x2F::Translation(center.x, -center.y) * gameObject.transform.GetCameraMatrix(),
		{ -halfSize.x, -halfSize.y, halfSize.x, halfSize.y},
		color, isFill, alpha
	);
}

void BoxRenderer::SerializedJson(ordered_json& jsonObj)
{
	ordered_json box;
	box["center"] = center;
	box["size"] = size;
	box["color"] = std::vector<float>{ color.r, color.g, color.b, color.a };
	box["isFill"] = isFill;
	box["alpha"] = alpha;

	jsonObj["BoxRenderer"].push_back(box);
}

void BoxRenderer::DeSerializedJson(ordered_json& jsonObj)
{
	for (auto& box : jsonObj["BoxRenderer"])
	{
		center = box["center"];
		size = box["size"];

		std::vector<float> rgba = box["color"].get<std::vector<float>>();
		color.r = rgba[0];
		color.g = rgba[1];
		color.b = rgba[2];
		color.a = rgba[3];

		isFill = box["isFill"];
		alpha = box["alpha"];
	}
}

