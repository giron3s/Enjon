#include "Graphics/Scene.h"
#include "Graphics/Renderable.h"
#include "Graphics/DirectionalLight.h"
#include "Graphics/SpotLight.h"
#include "Graphics/PointLight.h"
#include "Graphics/QuadBatch.h"
#include "Graphics/GLTexture.h"
#include "Graphics/Material.h"
#include "Graphics/DeferredRenderer.h"

#include "Engine.h"

#include <algorithm>

namespace Enjon { 

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	std::vector<Renderable*> Scene::GetRenderables(RenderableSortType type)
	{
		std::vector<Renderable*> renderables(mRenderables.begin(), mRenderables.end());	

		switch(type)
		{
			case RenderableSortType::MATERIAL:
			{
				std::stable_sort(renderables.begin(), renderables.end(), CompareMaterial);
			} 
			break;
			case RenderableSortType::DEPTH:
			{
				std::stable_sort(renderables.begin(), renderables.end(), CompareDepth);
			}
			break;

			case RenderableSortType::NONE: break;
			default: break;
		}

		return renderables;
	}

	void Scene::AddRenderable(Renderable* renderable)
	{
		auto query = mRenderables.find(renderable);
		if (query == mRenderables.end())
		{
			mRenderables.insert(renderable);
			renderable->SetScene(this);
		}
	}

	void Scene::RemoveRenderable(Renderable* renderable)
	{
		auto query = mRenderables.find(renderable);
		if (query != mRenderables.end())
		{
			renderable->SetScene(nullptr);
			mRenderables.erase(renderable);
		}
	}

	void Scene::AddQuadBatch(QuadBatch* batch)
	{
		auto query = mQuadBatches.find(batch);
		if (query == mQuadBatches.end())
		{
			batch->SetScene(this);
			mQuadBatches.insert(batch);
		}
	}

	void Scene::RemoveQuadBatch(QuadBatch* batch)
	{
		auto query = mQuadBatches.find(batch);
		if (query != mQuadBatches.end())
		{
			batch->SetScene(nullptr);
			mQuadBatches.erase(batch);
		}
	}

	void Scene::AddDirectionalLight(DirectionalLight* light)
	{
		auto query = mDirectionalLights.find(light);
		if (query == mDirectionalLights.end())
		{
			mDirectionalLights.insert(light);
			light->SetScene(this);
		}
	}

	void Scene::RemoveDirectionLight(DirectionalLight* light)
	{
		auto query = mDirectionalLights.find(light);
		if (query != mDirectionalLights.end())
		{
			mDirectionalLights.erase(light);
			light->SetScene(nullptr);
		}
	}

	void Scene::AddPointLight(PointLight* light)
	{
		auto query = mPointLights.find(light);
		if (query == mPointLights.end())
		{
			mPointLights.insert(light);
			light->SetScene(this);
		}
	}

	void Scene::RemovePointLight(PointLight* light)
	{
		auto query = mPointLights.find(light);
		if (query != mPointLights.end())
		{
			mPointLights.erase(light);
			light->SetScene(nullptr);
		}
	}

	void Scene::AddSpotLight(SpotLight* light)
	{
		auto query = mSpotLights.find(light);
		if (query == mSpotLights.end())
		{
			mSpotLights.insert(light);
			light->SetScene(this);
		}
	}

	void Scene::RemoveSpotLight(SpotLight* light)
	{
		auto query = mSpotLights.find(light);
		if (query != mSpotLights.end())
		{
			mSpotLights.erase(light);
			light->SetScene(nullptr);
		}
	}

	void Scene::SetAmbientSettings(AmbientSettings& settings)
	{
		mAmbientSettings = settings;
	}

	void Scene::SetAmbientColor(ColorRGBA16& color)
	{
		mAmbientSettings.mColor = color;
		mAmbientSettings.mIntensity = color.a;
	}

	bool Scene::CompareDepth(Renderable* a, Renderable* b)
	{
		// Get camera position
		v3 camPos = Engine::GetInstance()->GetGraphics()->GetSceneCamera()->GetPosition();

		// Get a pos
		v3 aPos = a->GetPosition();
		// Get b pos
		v3 bPos = b->GetPosition();

		f32 aDist = (camPos - aPos).Length();
		f32 bDist = (camPos - bPos).Length();

		return aDist < bDist;
	}

	bool Scene::CompareMaterial(Renderable* a, Renderable* b)
	{
		// TODO(): Set this up to where materials have a unique id and sort by that
		GLTexture texA = a->GetMaterial()->GetTexture(TextureSlotType::ALBEDO);
		GLTexture texB = b->GetMaterial()->GetTexture(TextureSlotType::ALBEDO);


		return texA.id > texB.id;
	}

}
