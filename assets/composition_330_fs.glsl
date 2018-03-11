#version 330

// attributs uniformes
uniform sampler2D image;
uniform sampler2D mask;

// attribut en entrée
in vec2 varyingTexcoord;

// attribut en sortie
out vec4 fragmentColor;

void main()
{
  // échantillonner la texture
  vec4 textureSample = texture(image, varyingTexcoord);

  vec4 textureMask = texture(mask, varyingTexcoord);

  // couleur finale du fragment
  fragmentColor =  mix(textureSample, textureMask, 0.5);
}
