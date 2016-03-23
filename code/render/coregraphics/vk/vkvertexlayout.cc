//------------------------------------------------------------------------------
// vkvertexlayout.cc
// (C) 2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "vkvertexlayout.h"
#include "vkrenderdevice.h"
#include "vktypes.h"

namespace Vulkan
{

__ImplementClass(Vulkan::VkVertexLayout, 'VKVL', Base::VertexLayoutBase);
//------------------------------------------------------------------------------
/**
*/
VkVertexLayout::VkVertexLayout()
{
	// empty
	memset(this->vertexStreams, 0, sizeof(this->vertexStreams));
}

//------------------------------------------------------------------------------
/**
*/
VkVertexLayout::~VkVertexLayout()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
void
VkVertexLayout::Setup(const Util::Array<CoreGraphics::VertexComponent>& c)
{
	// call parent class
	Base::VertexLayoutBase::Setup(c);

	// create binds
	this->binds.Resize(VkRenderDevice::MaxNumVertexStreams);
	this->attrs.Resize(this->components.Size());

	uint32_t numUsedStreams = 0;
	IndexT streamIndex;
	for (streamIndex = 0; streamIndex < VkRenderDevice::MaxNumVertexStreams; streamIndex++)
	{
		if (this->vertexStreams[streamIndex] != 0)
		{
			this->binds[numUsedStreams].binding = numUsedStreams;
			this->binds[numUsedStreams].inputRate = numUsedStreams > 0 ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;
			this->binds[numUsedStreams].stride = 1;
			numUsedStreams++;
		}
	}
	IndexT curOffset[VkRenderDevice::MaxNumVertexStreams] = { 0 };

	IndexT compIndex;
	for (compIndex = 0; compIndex < this->components.Size(); compIndex++)
	{
		const CoreGraphics::VertexComponent& component = this->components[compIndex];
		VkVertexInputAttributeDescription* attr = &this->attrs[compIndex];

		attr->binding = component.GetStreamIndex();
		attr->location = component.GetSemanticName();
		attr->format = VkTypes::AsVkVertexType(component.GetFormat());
		attr->offset = curOffset[component.GetStreamIndex()];
		curOffset[component.GetStreamIndex()] += component.GetByteSize();
	}

	this->vertexInfo =
	{
		VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		NULL,
		0,
		numUsedStreams,
		this->binds.Begin(),
		this->attrs.Size(),
		this->attrs.Begin()
	};

	// finish up the info struct
	this->info.pVertexInputState = &this->vertexInfo;
}

//------------------------------------------------------------------------------
/**
*/
void
VkVertexLayout::Discard()
{
	VertexLayoutBase::Discard();
}

//------------------------------------------------------------------------------
/**
*/
void
VkVertexLayout::Apply()
{
	VkRenderDevice::Instance()->SetVertexLayoutPipelineInfo(this->info);
}

} // namespace Vulkan