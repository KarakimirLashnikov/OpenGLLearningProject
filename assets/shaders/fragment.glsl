#version 460 core
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 visitorPos;

void main()
{
    float specularStrength = 0.5;
    float ambientStrength = 0.1;
    // ambience
    vec3 ambient = ambientStrength * lightColor;
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular 
    vec3 visitorDir = normalize(visitorPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(visitorDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    // final color
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}