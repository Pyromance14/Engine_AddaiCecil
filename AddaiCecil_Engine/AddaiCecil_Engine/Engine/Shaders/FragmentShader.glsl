#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;


out vec4 fColour;

 struct Light
 {
   vec3 lightPos;
   float ambVal;
   float diffVal;
   float specVal;
   vec3 lightColour;
 };

struct Material 
{

		sampler2D diffuseMap; // newmtl

		float shininess; // Ns
		float transparency; //d

		vec3 ambient; // Ka
		vec3 diffuse; // Kd
		vec3 specular; // Ks	
};

 uniform vec3 camPos;
 uniform Light light;
 uniform Material material;

void main(){
 
 // Ambient
 vec3 ambient = light.ambVal * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
 
 // Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.lightPos - FragPos);
  float diffVal = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = (diffVal * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb *
  light.lightColour;
 
 // Specular
  vec3 viewDir = normalize(camPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float specVal = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = (specVal * material.specular) * light.lightColour;
 
  vec3 result = ambient + diffuse + specular;
 
  fColour = vec4(result, material.transparency);
  
}