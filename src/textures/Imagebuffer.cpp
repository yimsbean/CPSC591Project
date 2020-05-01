// ==========================================================================
// Pixel Rendering and Image Saving Support Code
//  - requires the OpenGL Mathmematics (GLM) library: http://glm.g-truc.net
//  - requires the Magick++ development libraries: http://www.imagemagick.org
//  -   or the FreeImage library: http://freeimage.sourceforge.net
//  -   or the STB image write library: https://github.com/nothings/stb
//
// You may use this code (or not) however you see fit for your work.
//
// Set the #defines below to choose the image library you have installed on
// your system, that you will be using for your assignment. Then compile and
// link this source file with your project.
//
// Authors: Sonny Chan, Alex Brown
//          University of Calgary
// Date:    2016-2018
// ==========================================================================

#include <iostream>
#include <glm/common.hpp>

#include "Imagebuffer.h"

using namespace std;
using namespace glm;

// --------------------------------------------------------------------------

ImageBuffer::ImageBuffer()
    : m_textureName(0), m_framebufferObject(0),
    m_width(0), m_height(0), m_modified(false)
{
}

ImageBuffer::~ImageBuffer()
{
    Destroy();
}

void ImageBuffer::ResetModified()
{
    m_modified = false;
    m_modifiedLower = m_height;
    m_modifiedUpper = 0;
}

// --------------------------------------------------------------------------

bool ImageBuffer::Initialize()
{
    // retrieve the current viewport size
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    m_width = viewport[2];
    m_height = viewport[3];
    m_imageData.clear();
    // allocate image data
    m_imageData.resize(m_width * m_height);
    for (int i = 0, k = 0; i < m_height; ++i)
        for (int j = 0; j < m_width; ++j, ++k)
        {
            int p = (i >> 4) + (j >> 4);
            float c = 0.2 + ((p & 1) ? 0.1f : 0.0f);
            m_imageData[k] = vec3(c);
        }

    // allocate texture object
    if (!m_textureName)
        glGenTextures(1, &m_textureName);
    glBindTexture(GL_TEXTURE_RECTANGLE, m_textureName);
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                GL_FLOAT, &m_imageData[0]);
    glBindTexture(GL_TEXTURE_RECTANGLE, 0);
    ResetModified();

    // allocate framebuffer object
    if (!m_framebufferObject)
        glGenFramebuffers(1, &m_framebufferObject);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebufferObject);
    glFramebufferTexture(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textureName, 0);

    // check framebuffer status
    GLenum status = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        cout << "ImageBuffer ERROR: Framebuffer object not complete!" << endl;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    return (status == GL_FRAMEBUFFER_COMPLETE);
}

void ImageBuffer::Destroy()
{
    if (m_framebufferObject) {
        glDeleteFramebuffers(1, &m_framebufferObject);
        m_framebufferObject = 0;
    }
    if (m_textureName) {
        glDeleteTextures(1, &m_textureName);
        m_textureName = 0;
    }
}


// --------------------------------------------------------------------------

void ImageBuffer::SetPixel(int x, int y, vec3 colour)
{
    int index = y * m_width + x;
    if(OPTIMIZED_METHOD)
        if(m_imageData[index] == colour) return;
    m_imageData[index] = colour;
    //SetPixelColourInRange(index);
    // mark that something was changed
    m_modified = true;
    m_modifiedLower = std::min(m_modifiedLower, y);
    m_modifiedUpper = std::max(m_modifiedUpper, y+1);
}

// --------------------------------------------------------------------------

void ImageBuffer::AdditiveBlendPixel(int x, int y, vec3 colour)
{
    int index = y * m_width + x;
    if(OPTIMIZED_METHOD)
        if(m_imageData[index] == colour) return;
    //preservation of energy!
    //float t = 0.5f;
    //m_imageData[index] = t*m_imageData[index] + (1-t)*colour;
    m_imageData[index] = m_imageData[index] + colour;
    //SetPixelColourInRange(index);
    // mark that something was changed
    m_modified = true;
    m_modifiedLower = std::min(m_modifiedLower, y);
    m_modifiedUpper = std::max(m_modifiedUpper, y+1);
}

void ImageBuffer::MultiplicativeBlendPixel(int x, int y, vec3 colour)
{
    int index = y * m_width + x;
    if(OPTIMIZED_METHOD)
        if(m_imageData[index] == colour) return;
    //preservation of energy?
    m_imageData[index] = m_imageData[index] * (colour);
    //SetPixelColourInRange(index);
    // mark that something was changed
    m_modified = true;
    m_modifiedLower = std::min(m_modifiedLower, y);
    m_modifiedUpper = std::max(m_modifiedUpper, y+1);
}
void ImageBuffer::SetPixelOnLight(int x, int y, vec3 colour)
{
    int index = y * m_width + x;
    if(OPTIMIZED_METHOD)
        if(m_imageData[index] == colour) return;
    //preservation of energy!
    //float t = 0.5f;
    //m_imageData[index] = t*m_imageData[index] + (1-t)*colour;
    //if(colour == glm::vec3(0.f,0.f,0.f)) return;
    m_imageData[index] = colour;
    //SetPixelColourInRange(index);
    // mark that something was changed
    m_modified = true;
    m_modifiedLower = std::min(m_modifiedLower, y);
    m_modifiedUpper = std::max(m_modifiedUpper, y+1);
}
void ImageBuffer::SetPixelColourInRange(int index){
    if(m_imageData[index].x > 1.f)
        m_imageData[index].x = 1.f;
    if(m_imageData[index].y > 1.f)
        m_imageData[index].y = 1.f;
    if(m_imageData[index].z > 1.f)
        m_imageData[index].z = 1.f;

    if(m_imageData[index].x < 0.f)
        m_imageData[index].x = 0.f;
    if(m_imageData[index].y < 0.f)
        m_imageData[index].y = 0.f;
    if(m_imageData[index].z < 0.f)
        m_imageData[index].z = 0.f;
}
// --------------------------------------------------------------------------

void ImageBuffer::Render()
{
    if (!m_framebufferObject) return;
    
    // check for modifications to the image data and update texture as needed
    if (m_modified)
    {
        int sizeY = m_modifiedUpper - m_modifiedLower;
        int index = m_modifiedLower * m_width;

        // bind texture and copy only the rows that have been changed
        glBindTexture(GL_TEXTURE_RECTANGLE, m_textureName);
        glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, m_modifiedLower, 
                        m_width, sizeY, GL_RGB, GL_FLOAT, &m_imageData[index]);
        glBindTexture(GL_TEXTURE_RECTANGLE, 0);

        // mark that we've updated the texture
        ResetModified();
    }

    // bind the framebuffer object with our texture in it and copy to screen
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebufferObject);
    glBlitFramebuffer(0, 0, m_width, m_height,
                    0, 0, m_width, m_height,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

// --------------------------------------------------------------------------
