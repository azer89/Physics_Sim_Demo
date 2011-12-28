
#ifndef _CompositorChainReaction_H_
#define _CompositorChainReaction_H_

#include "Ogre.h"

using namespace Ogre;

class CompositorSample
{
public:
	CompositorSample();

	void setupCompositorContent(void);
	void cleanupContent(void);
	void setCompositorEnabled(Ogre::String name, bool enabled);

	void SetMotionBlur(bool enabled);
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
	bool isMotionBlurActive;
};


#endif