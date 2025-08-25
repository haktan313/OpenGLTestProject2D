#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoordRef;

uniform mat4 MVPref;

void main()
{
   gl_Position = MVPref * position;
   TexCoordRef = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 TexCoordRef;

uniform vec4 colorRef;
uniform sampler2D textureBase;
uniform bool useTexture;

void main()
{
    if (useTexture)
        color = texture(textureBase, TexCoordRef);
    else
        color = colorRef;
};