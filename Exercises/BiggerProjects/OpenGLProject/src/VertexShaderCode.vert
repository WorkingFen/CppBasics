#version 330 //#version 330 core

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;
//<<<<<<< HEAD
//in layout (location = 2) vec3 Normals;
/*in layout (location = 2) vec2 texCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 fullTransformMatrix;

void main(){
	vec4 v = vec4(position, 1.0f);
	gl_Position = fullTransformMatrix * v;
	outColor = vertexColor;
	TexCoord = texCoord;
}
=======
in layout(location=2) vec3 aNormal;

out vec3 outColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    FragPos = vec3(model * vec4(position, 1.0));
	Normal=aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
	
	outColor = vertexColor;
}

>>>>>>> lightNew*/
