#pragma once
//------------------------------------------------------------------------------
/**
    @class UI::RTPlugin
    
    (C) 2015-2016 Individual contributors, see AUTHORS file
*/
#include "core/refcounted.h"
#include "timing/time.h"
#include "frame/framebatch.h"
#include "rendermodules/rt/rtplugin.h"

//------------------------------------------------------------------------------
namespace UI
{
class UiRTPlugin : public RenderModules::RTPlugin
{
    __DeclareClass(UiRTPlugin);
public:
    /// constructor
    UiRTPlugin();
    /// destructor
    virtual ~UiRTPlugin();

	/// called when plugin is registered on the render-thread side
	virtual void OnRegister();
	/// called when plugin is unregistered on the render-thread side
	virtual void OnUnregister();

    /// called when rendering a frame batch
    virtual void OnRenderFrameBatch(const Ptr<Frame::FrameBatch>& frameBatch);

	/// called if the window size has changed
	virtual void OnWindowResized(SizeT width, SizeT height);

private:
	Ptr<UiServer> uiServer;
};

} // namespace UI
//------------------------------------------------------------------------------
