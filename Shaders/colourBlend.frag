precision mediump float;

varying vec4 fColor;
varying vec2 fTexCoord;

uniform sampler2D sampler2d;

uniform float r;
uniform float g;
uniform float b;
uniform float a;

void main() {

	gl_FragColor = texture2D(sampler2d, fTexCoord) * vec4(r, g, b, a);
	 
}
