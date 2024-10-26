#include "SageFrameBufferInternal.hpp"


SageFrameBufferInternal::SageFrameBufferInternal() : frameBuffer_hdl(0), depthBuffer_hdl(0), colorBuffer_hdl(0), stencilBuffer_hdl(0), depthStencilBuffer_hdl(0),
                                                     width(0), height(0)
{
}

SageFrameBufferInternal::SageFrameBufferInternal(GLuint width, GLuint height) : 
	frameBuffer_hdl(0), depthBuffer_hdl(0), colorBuffer_hdl(0), stencilBuffer_hdl(0), depthStencilBuffer_hdl(0),
	width(width), height(height)
{
	
	glCreateFramebuffers(1, &frameBuffer_hdl);

	// Color buffer
	Attach_Color_Buffer(width, height);

}


void SageFrameBufferInternal::Attach_Color_Buffer(GLint width, GLint height)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &colorBuffer_hdl);
	glTextureStorage2D(colorBuffer_hdl, 1, GL_RGBA8, width, height);
	glTextureParameteri(colorBuffer_hdl, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(colorBuffer_hdl, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Attach
	glNamedFramebufferTexture(frameBuffer_hdl, GL_COLOR_ATTACHMENT0, colorBuffer_hdl, 0);
}

void SageFrameBufferInternal::Attach_Color_Buffer(GLuint buffer_hdl)
{
	if (colorBuffer_hdl != 0)
	{
		glDeleteTextures(1, &colorBuffer_hdl);
	}
	colorBuffer_hdl = buffer_hdl;
	glNamedFramebufferTexture(frameBuffer_hdl, GL_COLOR_ATTACHMENT0, colorBuffer_hdl, 0);

}


void SageFrameBufferInternal::Attach_Depth_Buffer(GLint width, GLint height)
{
	glCreateRenderbuffers(1, &depthBuffer_hdl);
	glNamedRenderbufferStorage(depthBuffer_hdl, GL_DEPTH_COMPONENT24, width, height);


	//Attach
	glNamedFramebufferRenderbuffer(frameBuffer_hdl, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_hdl);


}


void SageFrameBufferInternal::Attach_Stencil_Buffer(GLint width, GLint height)
{
	glCreateRenderbuffers(1, &stencilBuffer_hdl);
	glNamedRenderbufferStorage(stencilBuffer_hdl, GL_STENCIL_INDEX8, width, height);

	//Attach
	glNamedFramebufferRenderbuffer(frameBuffer_hdl, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencilBuffer_hdl);

}


void SageFrameBufferInternal::Attach_Depth_Stencil_Buffer(GLint width, GLint height)
{
	glCreateRenderbuffers(1, &depthStencilBuffer_hdl);
	glNamedRenderbufferStorage(depthStencilBuffer_hdl, GL_DEPTH24_STENCIL8, width, height);

	//Attach
	glNamedFramebufferRenderbuffer(frameBuffer_hdl, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBuffer_hdl);

}




void SageFrameBufferInternal::Init(GLuint width, GLuint height)
{
	this->width = width;
	this->height = height;
	glCreateFramebuffers(1, &frameBuffer_hdl);


	int w = static_cast<int>(width);
	int h = static_cast<int>(height);

	// Color buffer
	Attach_Color_Buffer(w, h);
	Attach_Depth_Buffer(w, h);
	Attach_Stencil_Buffer(w, h);
	Attach_Depth_Stencil_Buffer(w, h);

}


GLuint SageFrameBufferInternal::Get_Frame_Buffer_Handle() const
{
	return frameBuffer_hdl;

}

GLuint SageFrameBufferInternal::Get_Color_Buffer_Handle() const
{
	return colorBuffer_hdl;

}



GLuint SageFrameBufferInternal::Get_Depth_Buffer_Handle() const
{
	return depthBuffer_hdl;

}



GLuint SageFrameBufferInternal::Get_Stencil_Buffer_Handle() const
{
	return stencilBuffer_hdl;

}



GLuint SageFrameBufferInternal::Get_Depth_Stencil_Buffer_Handle() const
{
	return depthStencilBuffer_hdl;

}






GLuint SageFrameBufferInternal::Get_Height() const
{
	return height;

}


GLuint SageFrameBufferInternal::Get_Width() const
{
	return width;
}



void SageFrameBufferInternal::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_hdl);
}

void SageFrameBufferInternal::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

SageFrameBufferInternal::~SageFrameBufferInternal()
{
	if (frameBuffer_hdl != 0)
	{
		glDeleteFramebuffers(1, &frameBuffer_hdl);
	}
	if (colorBuffer_hdl != 0)
	{
		glDeleteTextures(1, &colorBuffer_hdl);
	}
	if (depthBuffer_hdl != 0)
	{
		glDeleteRenderbuffers(1, &depthBuffer_hdl);
	}
	if (stencilBuffer_hdl != 0)
	{
		glDeleteRenderbuffers(1, &stencilBuffer_hdl);
	}
	if (depthStencilBuffer_hdl != 0)
	{
		glDeleteRenderbuffers(1, &depthStencilBuffer_hdl);
	}
}
