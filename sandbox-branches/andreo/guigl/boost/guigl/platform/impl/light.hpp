/*=================================---------------------------------------------
Copyright 2009 Stjepan Rajko, Torba Andrey

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#ifndef BOOST__GUIGL__GL__LIGHT_HPP
#define BOOST__GUIGL__GL__LIGHT_HPP

namespace boost{ namespace guigl { namespace gl {

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light<GLfloat>(GLenum i_light, GLenum pname, GLfloat param)
    {
        BOOST_ASSERT(GL_LIGHT0 <= i_light && i_light <= GL_LIGHT7);
        glLightf(i_light, pname, param);
    }

    template<>
    inline void light<GLint>(GLenum i_light, GLenum pname, GLint param)
    {
        BOOST_ASSERT(GL_LIGHT0 <= i_light && i_light <= GL_LIGHT7);
        glLighti(i_light, pname, param);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light<GLfloat>(GLenum i_light, GLenum pname, GLfloat const* params)
    {
        BOOST_ASSERT(GL_LIGHT0 <= i_light && i_light <= GL_LIGHT7);
        glLightfv(i_light, pname, params);
    }

    template<>
    inline void light<GLint>(GLenum i_light, GLenum pname, GLint const* params)
    {
        BOOST_ASSERT(GL_LIGHT0 <= i_light && i_light <= GL_LIGHT7);
        glLightiv(i_light, pname, params);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_position<GLfloat>(
        GLenum i_light,
        GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        GLfloat const position[] = {x, y, z, w};
        light(i_light, GL_POSITION, position);
    }

    template<>
    inline void light_position<GLint>(
        GLenum i_light,
        GLint x, GLint y, GLint z, GLint w)
    {
        GLint const position[] = {x, y, z, w};
        light(i_light, GL_POSITION, position);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_constant_attenuation<GLfloat>(GLenum i_light, GLfloat value)
    {
        light(i_light, GL_CONSTANT_ATTENUATION, value);
    }

    template<>
    inline void light_constant_attenuation<GLint>(GLenum i_light, GLint value)
    {
        light(i_light, GL_CONSTANT_ATTENUATION, value);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_linear_attenuation<GLfloat>(GLenum i_light, GLfloat value)
    {
        light(i_light, GL_LINEAR_ATTENUATION, value);
    }

    template<>
    inline void light_linear_attenuation<GLint>(GLenum i_light, GLint value)
    {
        light(i_light, GL_LINEAR_ATTENUATION, value);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_quadratic_attenuation<GLfloat>(GLenum i_light, GLfloat value)
    {
        light(i_light, GL_QUADRATIC_ATTENUATION, value);
    }

    template<>
    inline void light_quadratic_attenuation<GLint>(GLenum i_light, GLint value)
    {
        light(i_light, GL_QUADRATIC_ATTENUATION, value);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_spot_cutoff<GLfloat>(GLenum i_light, GLfloat value)
    {
        light(i_light, GL_SPOT_CUTOFF, value);
    }

    template<>
    inline void light_spot_cutoff<GLint>(GLenum i_light, GLint value)
    {
        light(i_light, GL_SPOT_CUTOFF, value);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_spot_exponent<GLfloat>(GLenum i_light, GLfloat value)
    {
        light(i_light, GL_SPOT_EXPONENT, value);
    }

    template<>
    inline void light_spot_exponent<GLint>(GLenum i_light, GLint value)
    {
        light(i_light, GL_SPOT_EXPONENT, value);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_spot_direction<GLfloat>(GLenum i_light, GLfloat x, GLfloat y, GLfloat z)
    {
        GLfloat const direction[] = {x, y, z};
        light(i_light, GL_SPOT_DIRECTION, direction);
    }

    template<>
    inline void light_spot_direction<GLint>(GLenum i_light, GLint x, GLint y, GLint z)
    {
        GLint const direction[] = {x, y, z};
        light(i_light, GL_SPOT_DIRECTION, direction);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_specular<GLfloat>(GLenum i_light,
        GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        GLfloat const specular_color[] = {r, g, b, a};
        light(i_light, GL_SPECULAR, specular_color);
    }

    template<>
    inline void light_specular<GLint>(GLenum i_light,
        GLint r, GLint g, GLint b, GLint a)
    {
        GLint const specular_color[] = {r, g, b, a};
        light(i_light, GL_SPECULAR, specular_color);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_diffuse<GLfloat>(GLenum i_light,
        GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        GLfloat const diffuse_color[] = {r, g, b, a};
        light(i_light, GL_DIFFUSE, diffuse_color);
    }

    template<>
    inline void light_diffuse<GLint>(GLenum i_light,
        GLint r, GLint g, GLint b, GLint a)
    {
        GLint const diffuse_color[] = {r, g, b, a};
        light(i_light, GL_DIFFUSE, diffuse_color);
    }

    //////////////////////////////////////////////////////////////////////////
    template<>
    inline void light_ambient<GLfloat>(GLenum i_light,
        GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        GLfloat const ambient_color[] = {r, g, b, a};
        light(i_light, GL_AMBIENT, ambient_color);
    }

    template<>
    inline void light_ambient<GLint>(GLenum i_light,
        GLint r, GLint g, GLint b, GLint a)
    {
        GLint const ambient_color[] = {r, g, b, a};
        light(i_light, GL_AMBIENT, ambient_color);
    }

    //////////////////////////////////////////////////////////////////////////
    template<class T>
    inline light_setup const& light_setup::position(T x, T y, T z, T w) const
    {
        light_position(m_light, x, y, z, w);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::constant_attenuation(T value) const
    {
        light_constant_attenuation(m_light, value);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::linear_attenuation(T value) const
    {
        light_linear_attenuation(m_light, value);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::quadratic_attenuation(T value) const
    {
        light_quadratic_attenuation(m_light, value);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::spot_cutoff(T value) const
    {
        light_spot_cutoff(m_light, value);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::spot_exponent(T value) const
    {
        light_spot_exponent(m_light, value);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::spot_direction(T x, T y, T z) const
    {
        light_spot_direction(m_light, x, y, z);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::specular(T r, T g, T b, T a) const
    {
        light_specular(m_light, r, g, b, a);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::diffuse(T r, T g, T b, T a) const
    {
        light_diffuse(m_light, r, g, b, a);
        return *this;
    }

    template<class T>
    inline light_setup const& light_setup::ambient(T r, T g, T b, T a) const
    {
        light_ambient(m_light, r, g, b, a);
        return *this;
    }

    inline light_setup light(GLenum i_light)
    {
        glEnable(i_light);
        return light_setup(i_light);
    }

}}}

#endif // BOOST__GUIGL__GL__LIGHT_HPP
