#include "texture.hpp"
#include "SOIL2/stb_image.h"
#include "wrapper/checkError.hpp"
#include <cassert>

Texture::Texture(std::string_view path, GLuint uint)
    : m_unit{ uint }
{
    // check if texture unit is valid
    assert(this->m_unit >= 0 && this->m_unit <= 31);

    /*--- read image ---*/
    int channels{};
    // reverse the y-axis
    stbi_set_flip_vertically_on_load(true);
    // load image
    auto data{
        stbi_load(path.data(), &this->m_width, &this->m_height, &channels, STBI_rgb_alpha)
    };

    /*--- create texture ---*/
    // generate texture object
    GLCALL(glGenTextures(1, &this->m_objId));
    // activate texture unit
    GLCALL(glActiveTexture(GL_TEXTURE0 + this->m_unit));
    // bind texture object
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->m_objId));
    // send texture data to GPU
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_width, this->m_height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, data));
    // gennerate mipmaps
    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
    // release image data in memory
    stbi_image_free(data);
    // set texture filtering
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // set texture wrapping
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

Texture::~Texture()
{
    if (this->m_objId) {
        GLCALL(glDeleteTextures(1, &this->m_objId));
        this->m_objId = 0;
    }
}

GLuint Texture::bind(GLuint texObj)
{
    // activate texture unit
    GLCALL(glActiveTexture(GL_TEXTURE0 + this->m_unit));
    // bind texture object
    GLCALL(glBindTexture(GL_TEXTURE_2D, texObj));
    // set current texture object
    GLuint oldTexObj{ this->m_objId };
    this->m_objId = texObj;
    // return old texture object
    return oldTexObj;
}
