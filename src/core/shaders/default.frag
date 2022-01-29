#version 330 core
out vec3 color;
in vec3 fragmentColor;
void main(){
    
    
    color = fragmentColor;
}
/*#version 330 core
out vec3 color;
in vec3 fragmentColor;
void main(){
    
    
    color = fragmentColor;
}*/

/*
#version 330 core
in vec3 UV;
out vec3 color;
uniform sampler2D myTextureSampler;
void main(){
    color = texture(myTextureSampler, UV).rgb;
}
*/