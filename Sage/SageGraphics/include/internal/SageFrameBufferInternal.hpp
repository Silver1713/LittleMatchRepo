#ifndef SAGE_BUFFER_INTERNAL_HPP
#define SAGE_BUFFER_INTERNAL_HPP

#include <GL/glew.h>

class SageFrameBufferInternal
{
	GLuint frameBuffer_hdl;
	GLuint depthBuffer_hdl;
	GLuint colorBuffer_hdl;
	GLuint stencilBuffer_hdl;
	GLuint depthStencilBuffer_hdl;

	GLuint width, height;

public:
	SageFrameBufferInternal();

	SageFrameBufferInternal(GLuint width, GLuint height);

	void Init(GLuint width, GLuint height);

	void Bind();
	void Unbind();


	void Attach_Color_Buffer(GLint width, GLint height);
	void Attach_Color_Buffer(GLuint buffer_hdl);
	void Attach_Depth_Buffer(GLint width, GLint height);
	void Attach_Stencil_Buffer(GLint width, GLint height);
	void Attach_Depth_Stencil_Buffer(GLint width, GLint height);

	GLuint Get_Frame_Buffer_Handle() const;
	GLuint Get_Color_Buffer_Handle() const;
	GLuint Get_Depth_Buffer_Handle() const;
	GLuint Get_Stencil_Buffer_Handle() const;
	GLuint Get_Depth_Stencil_Buffer_Handle() const;

	GLuint Get_Width() const;
	GLuint Get_Height() const;

	~SageFrameBufferInternal();







};
#endif // !SAGE_BUFFER_INTERNAL_HPP