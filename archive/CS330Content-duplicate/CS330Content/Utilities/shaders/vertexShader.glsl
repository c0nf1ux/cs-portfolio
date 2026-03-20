#version 330 core
layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inVertexNormal;
layout (location = 2) in vec2 inTextureCoordinate;

out vec3 fragmentPosition;
out vec3 fragmentVertexNormal;
out vec2 fragmentTextureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   fragmentPosition = vec3(model * vec4(inVertexPosition, 1.0));
   gl_Position = projection * view * model * vec4(inVertexPosition, 1.0f);

   // Transform normals to world space using the normal matrix
   // Normal matrix is transpose of inverse of model matrix to handle non-uniform scaling
   mat3 normalMatrix = mat3(transpose(inverse(model)));
   fragmentVertexNormal = normalize(normalMatrix * inVertexNormal);

   fragmentTextureCoordinate = inTextureCoordinate;
}