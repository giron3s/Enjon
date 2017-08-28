#include "Graphics/RenderTarget.h"
#include "Utils/Errors.h"
#include <stdio.h>

namespace Enjon { 

	RenderTarget::RenderTarget()
	{
		Width = 1024;
		Height = 1024;
	}

	RenderTarget::RenderTarget(uint32 _Width, uint32 _Height, GLuint TexParam)
	{
		// Save extensions
		Width  = _Width;
		Height = _Height;

	    glGenFramebuffers(1, &FrameBufferID);
	    glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);

	    // Bind the color render target
		glBindRenderbufferEXT(GL_RENDERBUFFER, TargetID);
		glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_RGBA, Width, Height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, TargetID);

	    // - color buffer
	    glGenTextures(1, &Texture);
	    glBindTexture(GL_TEXTURE_2D, Texture);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Width, Height, 0, GL_RGB, GL_FLOAT, NULL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexParam);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);
		glGenerateMipmap(GL_TEXTURE_2D);

		glGenTextures(1, &DepthBuffer);
	    glBindTexture(GL_TEXTURE_2D, DepthBuffer);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	   	GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0}; 
	   	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthBuffer, 0);
	    glDrawBuffer(GL_NONE);
	    glReadBuffer(GL_NONE);
	 
	    // - Create and attach depth buffer (renderbuffer)
	    // glGenRenderbuffers(1, &DepthBuffer);
	    // glBindRenderbuffer(GL_RENDERBUFFER, DepthBuffer);
	    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Width, Height);
	    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBuffer);
	    // - Finally check if framebuffer is complete
	    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	        std::cout << "Framebuffer not complete!" << std::endl;

	    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	RenderTarget::~RenderTarget()
	{
		glDeleteTextures(1, &Texture);
		glDeleteFramebuffersEXT(1, &FrameBufferID);
		glDeleteRenderbuffersEXT(1, &TargetID);
		glDeleteRenderbuffersEXT(1, &DepthBuffer);
	}

	void RenderTarget::Bind(BindType Type, bool clear)
	{
		switch(Type)
		{
			case BindType::WRITE:
			{
				// Bind our FBO and set the viewport to the proper size
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBufferID);
				glPushAttrib(GL_VIEWPORT_BIT);
				glViewport(0, 0, Width, Height);

				if (clear) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glActiveTextureARB(GL_TEXTURE0_ARB);
				glEnable(GL_TEXTURE_2D);

				// Specify what to render an start acquiring
				GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
				glDrawBuffers(1, buffers);
			} break;

			case BindType::READ:
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER, FrameBufferID);
			} break;
		}
	}
			
	void RenderTarget::Unbind()
	{
		// Stop acquiring and unbind the FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glPopAttrib();
	}
}
