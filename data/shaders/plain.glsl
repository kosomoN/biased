#version 330

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 uv;

uniform mat4 mvp;
out vec2 v_uv;

void main(){
    gl_Position = mvp * vertex;
    v_uv = uv;
}

@

#version 330

uniform sampler2D u_textureSampler;

out vec4 color;
in vec2 v_uv;

void main(){
    color = texture(u_textureSampler,v_uv);
}
