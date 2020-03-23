// ==========================================================================
// Fragment program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410
// interpolated colour received from vertex stage
in vec4 Colour;
in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2D tex;
uniform uint diffuse;
uniform uint clouds;
uniform float distance;

void main(void)
{
    // write colour output without modification
    if (diffuse == 1) {
        // TODO brighter is further away?
        FragmentColour = texture(tex, TextureCoord.xy)
                                * (dot(Normal, -FragPos))
                                * 0.1
                                * distance;
    } else if (diffuse == 0) {
        FragmentColour = texture(tex, TextureCoord.xy);
    }

    if (clouds == 1) {
        FragmentColour.a = 0.4; // translucent clouds
    } else if (clouds == 0) {
        FragmentColour.a = 1;  // opaque clouds????
    }
}
