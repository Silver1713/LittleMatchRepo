#include "SageFrameBuffer.hpp"
#include "SageFrameBufferPimpl.hpp"


void SageFrameBuffer::Attach_Color_Buffer(int width, int height)
{
	pimpl_frameBuffer->Attach_Color_Buffer(width, height);
}

void SageFrameBuffer::Attach_Color_Buffer(unsigned buffer_hdl)
{
	pimpl_frameBuffer->Attach_Color_Buffer(buffer_hdl);
}

void SageFrameBuffer::Attach_Depth_Buffer(int width, int height)
{
	pimpl_frameBuffer->Attach_Depth_Buffer(width, height);
}

void SageFrameBuffer::Attach_Depth_Stencil_Buffer(int width, int height)
{
	pimpl_frameBuffer->Attach_Depth_Stencil_Buffer(width, height);
}

void SageFrameBuffer::Attach_Stencil_Buffer(int width, int height)
{
	pimpl_frameBuffer->Attach_Stencil_Buffer(width, height);
}

void SageFrameBuffer::Bind()
{
	pimpl_frameBuffer->Bind();
}



void SageFrameBuffer::Unbind()
{
	pimpl_frameBuffer->Unbind();
}



unsigned SageFrameBuffer::Get_Color_Buffer_Handle() const
{
	return pimpl_frameBuffer->Get_Color_Buffer_Handle();
}


unsigned SageFrameBuffer::Get_Depth_Buffer_Handle() const
{
	return pimpl_frameBuffer->Get_Depth_Buffer_Handle();
}


unsigned SageFrameBuffer::Get_Depth_Stencil_Buffer_Handle() const
{
	return pimpl_frameBuffer->Get_Depth_Stencil_Buffer_Handle();
}

unsigned SageFrameBuffer::Get_Frame_Buffer_Handle() const
{
	return pimpl_frameBuffer->Get_Frame_Buffer_Handle();
}


unsigned SageFrameBuffer::Get_Height() const
{
	return pimpl_frameBuffer->Get_Height();
}

unsigned SageFrameBuffer::Get_Stencil_Buffer_Handle() const
{
	return pimpl_frameBuffer->Get_Stencil_Buffer_Handle();
}

unsigned SageFrameBuffer::Get_Width() const
{
	return pimpl_frameBuffer->Get_Width();
}

void SageFrameBuffer::Init(unsigned width, unsigned height)
{
	pimpl_frameBuffer->Init(width, height);
}

SageFrameBuffer::SageFrameBuffer() : pimpl_frameBuffer(std::make_unique<SageFrameBufferPimpl>()) {}

SageFrameBuffer::SageFrameBuffer(unsigned width, unsigned height) : pimpl_frameBuffer(std::make_unique<SageFrameBufferPimpl>(width, height)){}


SageFrameBuffer::~SageFrameBuffer()
{
	pimpl_frameBuffer.reset();
	pimpl_frameBuffer = nullptr;
}


















