/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
same license as the rest of the engine.
-----------------------------------------------------------------------------
*/

/**
    \file
        Compositor.cpp
    \brief
        Shows OGRE's Compositor feature
	\author
		W.J. :wumpus: van der Laan
			Ogre compositor framework
		Manuel Bua
			Postfilter ideas and original out-of-core implementation
        Jeff (nfz) Doyle
            added gui framework to demo
*/

#include "Stdafx.h"
#include "CompositorSample.h"
#include "HelperLogics.h"

/*************************************************************************
	                    Sample_Compositor Methods
*************************************************************************/
CompositorSample::CompositorSample()
{
}

//--------------------------------------------------------------------------
void CompositorSample::setupView()
{
	//SdkSample::setupView();
    mCamera->setPosition(Ogre::Vector3(0,0,0));
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(1);
}

//-----------------------------------------------------------------------------------
void CompositorSample::setCompositorEnabled(Ogre::String name, bool enabled)
{
	CompositorManager::getSingleton().setCompositorEnabled(mViewport, name, enabled);
}

//-----------------------------------------------------------------------------------
void CompositorSample::setupCompositorContent(void)
{
	static bool firstTime = true;

	if (firstTime)
	{
		// Register the compositor logics
		// See comment in beginning of HelperLogics.h for explanation
		Ogre::CompositorManager& compMgr = Ogre::CompositorManager::getSingleton();
		//compMgr.registerCompositorLogic("GaussianBlur", new GaussianBlurLogic);
		compMgr.registerCompositorLogic("HDR", new HDRLogic);
		//compMgr.registerCompositorLogic("HeatVision", new HeatVisionLogic);
		firstTime = false;
	}
	
	createTextures();
    /// Create a couple of hard coded postfilter effects as an example of how to do it
	/// but the preferred method is to use compositor scripts.
	createEffects();
	//setupScene();
	registerCompositors();
	//setupControls();
	//setDragLook(true);
}
//-----------------------------------------------------------------------------------
void CompositorSample::registerCompositors(void)
{
	Ogre::Viewport *vp = mViewport;
    
    //iterate through Compositor Managers resources and add name keys to menu
    Ogre::CompositorManager::ResourceMapIterator resourceIterator =
        Ogre::CompositorManager::getSingleton().getResourceIterator();

    // add all compositor resources to the view container
    while (resourceIterator.hasMoreElements())
    {
        Ogre::ResourcePtr resource = resourceIterator.getNext();
        const Ogre::String& compositorName = resource->getName();
        // Don't add base Ogre/Scene compositor to view
        if (compositorName == "Ogre/Scene")
            continue;
		// Don't add the deferred shading compositors, thats a different demo.
		if (Ogre::StringUtil::startsWith(compositorName, "DeferredShading", false))
			continue;

		//mCompositorNames.push_back(compositorName);
		int addPosition = -1;
		if (compositorName == "HDR")
		{
			// HDR must be first in the chain
			addPosition = 0;
		}
		try 
		{
			Ogre::CompositorManager::getSingleton().addCompositor(vp, compositorName, addPosition);
			Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp, compositorName, false);
		} catch (...) {
		}
    }

	//mNumCompositorPages = (mCompositorNames.size() / COMPOSITORS_PER_PAGE) +
	//	((mCompositorNames.size() % COMPOSITORS_PER_PAGE == 0) ? 0 : 1);
}
//-----------------------------------------------------------------------------------
/*
void CompositorSample::changePage(size_t pageNum)
{
	assert(pageNum < mNumCompositorPages);
	
	mActiveCompositorPage = pageNum;
	size_t maxCompositorsInPage = mCompositorNames.size() - (pageNum * COMPOSITORS_PER_PAGE);
	for (size_t i=0; i < COMPOSITORS_PER_PAGE; i++)
	{
		String checkBoxName = "Compositor_" + Ogre::StringConverter::toString(i);
		CheckBox* cb = static_cast<CheckBox*>(mTrayMgr->getWidget(TL_TOPLEFT, checkBoxName));
		if (i < maxCompositorsInPage)
		{
			String compositorName = mCompositorNames[pageNum * COMPOSITORS_PER_PAGE + i];
			CompositorInstance *tmpCompo = CompositorManager::getSingleton().getCompositorChain(mViewport)
				->getCompositor(compositorName);

			cb->setCaption(compositorName);

			if( tmpCompo )
			{
				cb->setChecked( tmpCompo->getEnabled(), false );
				cb->show();
			}
			else
			{
				cb->setChecked( false, false );
				cb->hide();
			}

		}
		else
		{
			cb->hide();
		}
	}

	OgreBites::Button* pageButton = static_cast<OgreBites::Button*>(mTrayMgr->getWidget(TL_TOPLEFT, "PageButton"));
	Ogre::StringStream ss;
	ss << "Compositors " << pageNum + 1 << "/" << mNumCompositorPages;
	pageButton->setCaption(ss.str());
}
*/

//-----------------------------------------------------------------------------------
void CompositorSample::cleanupContent(void)
{
	mDebugTextureTUS->setContentType(TextureUnitState::CONTENT_NAMED);
	CompositorManager::getSingleton().removeCompositorChain(mViewport);
	//mCompositorNames.clear();
}
//-----------------------------------------------------------------------------------
/*
void CompositorSample::setupControls(void) 
{
	mTrayMgr->createButton(TL_TOPLEFT, "PageButton", "Compositors", 175);

	for (size_t i=0; i < COMPOSITORS_PER_PAGE; i++)
	{
		String checkBoxName = "Compositor_" + Ogre::StringConverter::toString(i);
		CheckBox* cb = mTrayMgr->createCheckBox(TL_TOPLEFT, checkBoxName, "Compositor", 175);
		cb->hide();
	}

	changePage(0);
	
	mDebugTextureSelectMenu = mTrayMgr->createThickSelectMenu(TL_TOPRIGHT, "DebugRTTSelectMenu", "Debug RTT", 180, 5);
	mDebugTextureSelectMenu->addItem("None");

	mTrayMgr->createSeparator(TL_TOPRIGHT, "DebugRTTSep1");  // this is a hack to give the debug RTT a bit more room

	DecorWidget* debugRTTPanel = mTrayMgr->createDecorWidget(TL_NONE, "DebugRTTPanel", "SdkTrays/Picture");
	OverlayContainer* debugRTTContainer = (OverlayContainer*)debugRTTPanel->getOverlayElement();
	mDebugTextureTUS = debugRTTContainer->getMaterial()->getBestTechnique()->getPass(0)->getTextureUnitState(0);
	//mDebugTextureTUS->setTextureName("CompositorDemo/DebugView");
	debugRTTContainer->setDimensions(128, 128);
	debugRTTContainer->getChild("DebugRTTPanel/PictureFrame")->setDimensions(144, 144);
	debugRTTPanel->hide();

	mTrayMgr->createSeparator(TL_TOPRIGHT, "DebugRTTSep2");  // this is a hack to give the debug RTT a bit more room

	mTrayMgr->showCursor();
	mTrayMgr->showLogo(TL_BOTTOMLEFT);
	mTrayMgr->toggleAdvancedFrameStats();
}
*/
//-----------------------------------------------------------------------------------
/*
void CompositorSample::checkBoxToggled(OgreBites::CheckBox * box)
{
	if (Ogre::StringUtil::startsWith(box->getName(), "Compositor_", false))
	{
		String compositorName = box->getCaption();

		String activeTex = mDebugTextureSelectMenu->getSelectedItem();

		if (!box->isChecked())
		{
			//Remove the items from the debug menu and remove debug texture if from disabled compositor
			bool debuggingRemovedTex = StringUtil::startsWith(activeTex, compositorName, false);
			if (debuggingRemovedTex)
			{
				mDebugTextureTUS->setContentType(TextureUnitState::CONTENT_NAMED);
				mDebugTextureSelectMenu->selectItem(0, true);
			}
			for (unsigned int i = 1; i < mDebugTextureSelectMenu->getNumItems(); i++)
			{
				if (StringUtil::startsWith(mDebugTextureSelectMenu->getItems()[i], compositorName, false))
				{
					mDebugTextureSelectMenu->removeItem(i);
					i--;
				}
			}
			if (!debuggingRemovedTex)
			{
				//Selection clears itself when removing items. Restore.
				mDebugTextureSelectMenu->selectItem(activeTex, false);
			}
		}

		CompositorManager::getSingleton().setCompositorEnabled(mViewport, compositorName, box->isChecked());

		
		if (box->isChecked())
		{
			//Add the items to the selectable texture menu
			CompositorInstance* instance = CompositorManager::getSingleton().getCompositorChain(mViewport)->getCompositor(compositorName);
			if (instance)
			{
				CompositionTechnique::TextureDefinitionIterator it = instance->getTechnique()->getTextureDefinitionIterator();
				while (it.hasMoreElements())
				{
					CompositionTechnique::TextureDefinition* texDef = it.getNext();
					size_t numTextures = texDef->formatList.size();
					if (numTextures > 1)
					{
						for (size_t i=0; i<numTextures; i++)
						{
							//Dirty string composition. NOT ROBUST!
							mDebugTextureSelectMenu->addItem(compositorName + ";" + texDef->name + ";" + 
								Ogre::StringConverter::toString((Ogre::uint32)i));
						}
					}
					else
					{
						mDebugTextureSelectMenu->addItem(compositorName + ";" + texDef->name);
					}
				}
				mDebugTextureSelectMenu->selectItem(activeTex, false);
			}
		}
	}
}
*/
//-----------------------------------------------------------------------------------
/*
void CompositorSample::buttonHit(OgreBites::Button* button)
{
	size_t nextPage = (mActiveCompositorPage + 1) % mNumCompositorPages;
	changePage(nextPage);
}
*/
//-----------------------------------------------------------------------------------
/*
void CompositorSample::itemSelected(OgreBites::SelectMenu* menu)
{
	if (menu->getSelectionIndex() == 0)
	{
		mDebugTextureTUS->setContentType(TextureUnitState::CONTENT_NAMED);
		mTrayMgr->getWidget("DebugRTTPanel")->hide();
		mTrayMgr->removeWidgetFromTray("DebugRTTPanel");
		return;
	}

	mTrayMgr->getWidget("DebugRTTPanel")->show();
	mTrayMgr->moveWidgetToTray("DebugRTTPanel", TL_TOPRIGHT, mTrayMgr->getNumWidgets(TL_TOPRIGHT) - 1);
	StringVector parts = StringUtil::split(menu->getSelectedItem(), ";");
	mDebugTextureTUS->setContentType(TextureUnitState::CONTENT_COMPOSITOR);

	if (parts.size() == 2)
	{
		mDebugTextureTUS->setCompositorReference(parts[0], parts[1]);
	}
	else
	{
		mDebugTextureTUS->setCompositorReference(parts[0], parts[1], 
			StringConverter::parseUnsignedInt(parts[2]));
	}
}
*/
//-----------------------------------------------------------------------------------
/*
void CompositorSample::setupScene(void)
{
}
*/
//-----------------------------------------------------------------------------------
/*
bool CompositorSample::frameRenderingQueued(const FrameEvent& evt)
{
}
*/
//-----------------------------------------------------------------------------------
/// Create the hard coded postfilter effects
void CompositorSample::createEffects(void)
{
	// Motion blur effect
	Ogre::CompositorPtr comp3 = Ogre::CompositorManager::getSingleton().create(
			"Motion Blur", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		);
	{
		Ogre::CompositionTechnique *t = comp3->createTechnique();
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("scene");
			def->width = 0;
			def->height = 0;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("sum");
			def->width = 0;
			def->height = 0;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("temp");
			def->width = 0;
			def->height = 0;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		/// Render scene
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_PREVIOUS);
			tp->setOutputName("scene");
		}
		/// Initialisation pass for sum texture
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_PREVIOUS);
			tp->setOutputName("sum");
			tp->setOnlyInitial(true);
		}
		/// Do the motion blur
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			tp->setOutputName("temp");
			{ Ogre::CompositionPass *pass = tp->createPass();
			pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
			pass->setMaterialName("Ogre/Compositor/Combine");
			pass->setInput(0, "scene");
			pass->setInput(1, "sum");
			}
		}
		/// Copy back sum texture
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			tp->setOutputName("sum");
			{ Ogre::CompositionPass *pass = tp->createPass();
			pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
			pass->setMaterialName("Ogre/Compositor/Copyback");
			pass->setInput(0, "temp");
			}
		}
		/// Display result
		{
			Ogre::CompositionTargetPass *tp = t->getOutputTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			{ Ogre::CompositionPass *pass = tp->createPass();
			pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
			pass->setMaterialName("Ogre/Compositor/MotionBlur");
			pass->setInput(0, "sum");
			}
		}
	}
	/// Heat vision effect
	Ogre::CompositorPtr comp4 = Ogre::CompositorManager::getSingleton().create(
			"Heat Vision", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		);
	{
		Ogre::CompositionTechnique *t = comp4->createTechnique();
		t->setCompositorLogicName("HeatVision");
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("scene");
			def->width = 256;
			def->height = 256;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("temp");
			def->width = 256;
			def->height = 256;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		/// Render scene
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_PREVIOUS);
			tp->setOutputName("scene");
		}
		/// Light to heat pass
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			tp->setOutputName("temp");
			{
				Ogre::CompositionPass *pass = tp->createPass();
				pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
				pass->setIdentifier(0xDEADBABE); /// Identify pass for use in listener
				pass->setMaterialName("Fury/HeatVision/LightToHeat");
				pass->setInput(0, "scene");
			}
		}
		/// Display result
		{
			Ogre::CompositionTargetPass *tp = t->getOutputTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			{
				Ogre::CompositionPass *pass = tp->createPass();
				pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
				pass->setMaterialName("Fury/HeatVision/Blur");
				pass->setInput(0, "temp");
			}
		}
	}
}
//--------------------------------------------------------------------------
void CompositorSample::createTextures(void)
{
	using namespace Ogre;

	TexturePtr tex = TextureManager::getSingleton().createManual(
		"HalftoneVolume",
		"General",
		TEX_TYPE_3D,
		64,64,64,
		0,
		PF_A8
	);

	HardwarePixelBufferSharedPtr ptr = tex->getBuffer(0,0);
	ptr->lock(HardwareBuffer::HBL_DISCARD);
	const PixelBox &pb = ptr->getCurrentLock();
	Ogre::uint8 *data = static_cast<Ogre::uint8*>(pb.data);

	size_t height = pb.getHeight();
	size_t width = pb.getWidth();
	size_t depth = pb.getDepth();
	size_t rowPitch = pb.rowPitch;
	size_t slicePitch = pb.slicePitch;

	for (size_t z = 0; z < depth; ++z)
	{
		for (size_t y = 0; y < height; ++y)
		{
			for(size_t x = 0; x < width; ++x)
			{
				float fx = 32-(float)x+0.5f;
				float fy = 32-(float)y+0.5f;
				float fz = 32-((float)z)/3+0.5f;
				float distanceSquare = fx*fx+fy*fy+fz*fz;
				data[slicePitch*z + rowPitch*y + x] =  0x00;
				if (distanceSquare < 1024.0f)
					data[slicePitch*z + rowPitch*y + x] +=  0xFF;
			}
		}
	}
	ptr->unlock();

	//Ogre::Viewport *vp = mRoot->getAutoCreatedWindow()->getViewport(0); 
	Ogre::Viewport* vp = this->mViewport;

	TexturePtr tex2 = TextureManager::getSingleton().createManual(
		"DitherTex",
		"General",
		TEX_TYPE_2D,
		vp->getActualWidth(),vp->getActualHeight(),1,
		0,
		PF_A8
	);

	HardwarePixelBufferSharedPtr ptr2 = tex2->getBuffer(0,0);
	ptr2->lock(HardwareBuffer::HBL_DISCARD);
	const PixelBox &pb2 = ptr2->getCurrentLock();
	Ogre::uint8 *data2 = static_cast<Ogre::uint8*>(pb2.data);
	
	size_t height2 = pb2.getHeight();
	size_t width2 = pb2.getWidth();
	size_t rowPitch2 = pb2.rowPitch;

	for (size_t y = 0; y < height2; ++y)
	{
		for(size_t x = 0; x < width2; ++x)
		{
			data2[rowPitch2*y + x] = Ogre::Math::RangeRandom(64.0,192);
		}
	}
	
	ptr2->unlock();
}
