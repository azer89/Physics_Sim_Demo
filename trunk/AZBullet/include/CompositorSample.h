
#ifndef _CompositorChainReaction_H_
#define _CompositorChainReaction_H_

#include "OgreConfigFile.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

using namespace Ogre;
//using namespace OgreBites;

#define COMPOSITORS_PER_PAGE 8

class CompositorSample
{
public:
	CompositorSample();

	void setupCompositorContent(void);
	void cleanupContent(void);
	void setCompositorEnabled(Ogre::String name, bool enabled);

	//bool frameRenderingQueued(const FrameEvent& evt);

public:
	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewport;


protected:
	void setupView(void);
	void setupControls(void);
	void setupScene(void);
	void createEffects(void);
	void createTextures(void);

	void registerCompositors();
	//void changePage(size_t pageNum);

protected:
	//SceneNode * mSpinny;
	//StringVector mCompositorNames;
	//size_t mActiveCompositorPage;
	//size_t mNumCompositorPages;	

	//String mDebugCompositorName;
	TextureUnitState* mDebugTextureTUS;

};


#endif