#version 330 core
out vec4 FragColor;


uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 specularExponent;
uniform vec3 opticalDensity;
uniform vec3 dissolve;
uniform vec3 illumination;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D ambient;
uniform sampler2D diffuse;
uniform sampler2D specular;


void main() {
	FragColor = texture(ambient, TexCoords);
}
