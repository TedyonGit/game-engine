#pragma once
#include <glad/glad.h>

class Framebuffer
{
public:
    unsigned int FBO, TextureID, RBO;
    int Width, Height;

    Framebuffer(int width, int height)
    {
        Create(width, height);
    }

    ~Framebuffer()
    {
        glDeleteFramebuffers(1, &FBO);
        glDeleteTextures(1, &TextureID);
        glDeleteRenderbuffers(1, &RBO);
    }

    void Bind()   const { glBindFramebuffer(GL_FRAMEBUFFER, FBO); }
    void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0);   }

    void Resize(int width, int height)
    {
        if (width == Width && height == Height) return;

        Width  = width;
        Height = height;

        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
    }

private:
    void Create(int width, int height)
    {
        Width  = width;
        Height = height;

        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureID, 0);

        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};