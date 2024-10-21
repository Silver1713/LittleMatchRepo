#include "SageFrameBufferInternal.hpp"
#include "SageFrameBufferPimpl.hpp"




SageFrameBuffer::SageFrameBufferPimpl::SageFrameBufferPimpl()
{
	internal_FrameBuffer = std::make_unique<SageFrameBufferInternal>();

}

SageFrameBuffer::SageFrameBufferPimpl::SageFrameBufferPimpl(unsigned width, unsigned height)
{
	internal_FrameBuffer = std::make_unique<SageFrameBufferInternal>(width, height);
}

void SageFrameBuffer::SageFrameBufferPimpl::Init(unsigned width, unsigned height)
{
	internal_FrameBuffer->Init(width, height);
}


void SageFrameBuffer::SageFrameBufferPimpl::Bind()
{
	internal_FrameBuffer->Bind();
}

void SageFrameBuffer::SageFrameBufferPimpl::Unbind()
{
	internal_FrameBuffer->Unbind();
}

void SageFrameBuffer::SageFrameBufferPimpl::Attach_Color_Buffer(int width, int height)
{
	internal_FrameBuffer->Attach_Color_Buffer(width, height);
}

void SageFrameBuffer::SageFrameBufferPimpl::Attach_Color_Buffer(unsigned buffer_hdl)
{
	internal_FrameBuffer->Attach_Color_Buffer(buffer_hdl);
}

void SageFrameBuffer::SageFrameBufferPimpl::Attach_Depth_Buffer(int width, int height)
{
	internal_FrameBuffer->Attach_Depth_Buffer(width, height);
}

void SageFrameBuffer::SageFrameBufferPimpl::Attach_Depth_Stencil_Buffer(int width, int height)
{
	internal_FrameBuffer->Attach_Depth_Stencil_Buffer(width, height);
}

void SageFrameBuffer::SageFrameBufferPimpl::Attach_Stencil_Buffer(int width, int height)
{
	internal_FrameBuffer->Attach_Stencil_Buffer(width, height);
}


unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Frame_Buffer_Handle() const
{
	return internal_FrameBuffer->Get_Frame_Buffer_Handle();
}


unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Color_Buffer_Handle() const
{
	return internal_FrameBuffer->Get_Color_Buffer_Handle();
}


unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Depth_Buffer_Handle() const
{
	return internal_FrameBuffer->Get_Depth_Buffer_Handle();
}



unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Stencil_Buffer_Handle() const
{
	return internal_FrameBuffer->Get_Stencil_Buffer_Handle();
}


unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Depth_Stencil_Buffer_Handle() const
{
	return internal_FrameBuffer->Get_Depth_Stencil_Buffer_Handle();
}

unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Height() const
{
	return internal_FrameBuffer->Get_Height();
}

unsigned SageFrameBuffer::SageFrameBufferPimpl::Get_Width() const
{
	return internal_FrameBuffer->Get_Width();
}

SageFrameBuffer::SageFrameBufferPimpl::~SageFrameBufferPimpl()
{
	internal_FrameBuffer.reset();
	internal_FrameBuffer = nullptr;
}






