#version 330 //#version 330 core

in vec3 outColor;
//<<<<<<< HEAD
in vec2 TexCoord;
//=======
in vec3 Normal;
in vec3 FragPos;
//>>>>>>> lightNew

out vec4 color;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform sampler2D Texture0;

//<<<<<<< HEAD
void main(){
	color = vec4(outColor, 1.0);
	color = color + texture(Texture0, TexCoord);
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = ambient * outColor;
}
//=======
void main()
{
    // ambient
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (diffuse+ambient) * outColor;
    color = vec4(result, 1.0);
} 
//>>>>>>> lightNew
