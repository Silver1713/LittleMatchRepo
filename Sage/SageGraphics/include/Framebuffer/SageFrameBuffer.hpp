#ifndef SAGE_FRAME_BUFFER_HPP
#define SAGE_FRAME_BUFFER_HPP
#include <memory>

class SageFrameBuffer
{
	class SageFrameBufferPimpl;

	std::unique_ptr<SageFrameBufferPimpl> pimpl_frameBuffer;
public:
	SageFrameBuffer();
	SageFrameBuffer(unsigned width, unsigned height);
	void Init(unsigned width, unsigned height);
	void Bind();
	void Unbind();
	void Attach_Color_Buffer(int width, int height);
	void Attach_Color_Buffer(unsigned buffer_hdl);
	void Attach_Depth_Buffer(int width, int height);
	void Attach_Stencil_Buffer(int width, int height);
	void Attach_Depth_Stencil_Buffer(int width, int height);
	unsigned Get_Frame_Buffer_Handle() const;
	unsigned Get_Color_Buffer_Handle() const;
	unsigned Get_Depth_Buffer_Handle() const;
	unsigned Get_Stencil_Buffer_Handle() const;
	unsigned Get_Depth_Stencil_Buffer_Handle() const;
	unsigned Get_Width() const;
	unsigned Get_Height() const;
	~SageFrameBuffer();

};

#endif // !SAGE_FRAME_BUFFER_HPP
