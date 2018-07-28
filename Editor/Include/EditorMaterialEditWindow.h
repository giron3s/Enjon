
#include "EditorView.h"

#include <Entity/EntityManager.h>
#include <Graphics/Renderable.h> 
#include <Graphics/Camera.h>
#include <Scene/Scene.h>
#include <Base/World.h> 
#include <Graphics/Window.h>
#include <Asset/Asset.h>
#include <Graphics/StaticMeshRenderable.h>

namespace Enjon
{ 
	class Material;
	class Archetype;
	class EditorWorldOutlinerView;
	class EditorInspectorView;

	class EditorViewport : public EditorView
	{
		public:
			/**
			* @brief
			*/
			EditorViewport( EditorApp* app, Window* window )
				: EditorView( app, window, "Viewport", ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse )
			{ 
			}

			/**
			* @brief
			*/
			~EditorViewport( ) = default; 

			/**
			* @brief
			*/
			Vec2 GetCenterOfViewport( );	 

		protected:

			/**
			* @brief Must be overriden
			*/
			virtual void UpdateView( ) override;

			/**
			* @brief Must be overriden
			*/
			virtual void ProcessViewInput( ) override
			{ 
			}

			/**
			* @brief Must be overriden
			*/
			virtual void Initialize( ) override
			{ 
			}

			/**
			* @brief
			*/
			virtual void CaptureState( ) override;

			/**
			* @brief
			*/
			void UpdateCamera( );

		protected: 
			Vec2 mSceneViewWindowPosition;
			Vec2 mSceneViewWindowSize; 
			f32 mCameraSpeed = 10.f;
			f32 mMouseSensitivity = 10.0f;
			Transform mPreviousCameraTransform;
			Vec2 mMouseCoordsDelta = Vec2( 0.0f );
			bool mStartedFocusing = false;
			bool mFocusSet = false;
	}; 

	class EditorMaterialEditWindow : public Window
	{
		public: 

			/**
			* @brief
			*/
			EditorMaterialEditWindow( const AssetHandle< Material >& mat );

			virtual int Init( std::string windowName, int screenWidth, int screenHeight, WindowFlagsMask currentFlags = WindowFlagsMask( ( u32 )WindowFlags::RESIZABLE ) ) override; 

		protected:

			virtual void ExplicitDestroy( ) override
			{
				if ( mViewport )
				{
					delete ( mViewport );
					mViewport = nullptr;
				}
			}

			void ConstructScene( ); 

		protected: 
			EditorViewport* mViewport = nullptr;
			AssetHandle< Material > mMaterial;
			StaticMeshRenderable mRenderable;
			u32 mInitialized : 1;
			bool mViewportOpen = true;
	};

	class EditorArchetypeEditWindow : public Window 
	{
		public: 

			/**
			* @brief
			*/
			EditorArchetypeEditWindow( const AssetHandle< Archetype >& archetype );

			virtual int Init( std::string windowName, int screenWidth, int screenHeight, WindowFlagsMask currentFlags = WindowFlagsMask( ( u32 )WindowFlags::RESIZABLE ) ) override; 

		protected:

			virtual void ExplicitDestroy( ) override
			{
				if ( mViewport )
				{
					delete ( mViewport );
					mViewport = nullptr;
				}
			}

			void ConstructScene( ); 

		protected: 
			AssetHandle< Archetype > mArchetype;
			EditorWorldOutlinerView* mWorldOutlinerView = nullptr;
			EditorViewport* mViewport = nullptr;
			EditorInspectorView* mInspectorView = nullptr;
			u32 mInitialized : 1;
			bool mViewportOpen = true;
			EntityHandle mRootEntity;

	};

}