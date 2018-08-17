#include "pch.h"

#include "G3onG4.h"

#include <Kore/Math/Core.h>
#include <Kore/System.h>

using namespace Kore;


// Shader constants not supported in OpenGL 1.X
/*void setBool(ConstantLocation location, bool value);
void setInt(ConstantLocation location, int value);
void setFloat(ConstantLocation location, float value);
void setFloat2(ConstantLocation location, float value1, float value2);
void setFloat2(ConstantLocation location, vec2 value);
void setFloat3(ConstantLocation location, float value1, float value2, float value3);
void setFloat3(ConstantLocation location, vec3 value);
void setFloat4(ConstantLocation location, float value1, float value2, float value3, float value4);
void setFloat4(ConstantLocation location, vec4 value);
void setFloats(ConstantLocation location, float* values, int count);
void setMatrix(ConstantLocation location, const mat3& value);
void setMatrix(ConstantLocation location, const mat4& value);*/

// Fixed-function features (OpenGL 1.X) {

void Graphics3::setLight(Light* light, int num = 0) {
	// TODO
}

void Graphics3::setFogColor(const Graphics1::Color& color) {
	// TODO
}

void Graphics3::setViewMatrix(const mat4& value) {
	// TODO
}

void Graphics3::setWorldMatrix(const mat4& value) {
	// TODO
}

void Graphics3::setProjectionMatrix(const mat4& value) {
	// TODO
}

// } /Fixed-function features

void Graphics3::setVertexBuffer(VertexBuffer& vertexBuffer) {
	// TODO
}

void Graphics3::setVertexBuffers(VertexBuffer** vertexBuffers, int count) {
	// TODO
}

void Graphics3::setIndexBuffer(IndexBuffer& indexBuffer) {
	// TODO
}

void Graphics3::setTexture(TextureUnit unit, Texture* texture) {
	// TODO
}

void Graphics3::drawIndexedVertices() {

}

void Graphics3::drawIndexedVertices(int start, int count) {

}

// OpenGL 1.X does not support hardware instancing
/*void drawIndexedVerticesInstanced(int instanceCount);
void drawIndexedVerticesInstanced(int instanceCount, int start, int count);*/

void Graphics3::changeResolution(int width, int height) {

}

bool Graphics3::hasWindow() {

}

void Graphics3::setWindow(bool) {
	
}
	
int Graphics3::antialiasingSamples() {
	
}
	
void Graphics3::setAntialiasingSamples(int samples) {
	
}
	

bool Graphics3::renderTargetsInvertedY() {
	
}
	
void Graphics3::setRenderTarget(RenderTarget* texture, int num = 0, int additionalTargets = 0) {
	
}
	
void Graphics3::restoreRenderTarget() {
	
}
	

// TODO (DK) windowId should be renamed contextId?
void Graphics3::setup() {
	
}

void Graphics3::swapBuffers(int windowId = 0) {
	
}

void Graphics3::begin(int windowId = 0) {
	
}

void Graphics3::end(int windowId = 0) {
	
}

void Graphics3::makeCurrent(int windowId) {
	
}

void Graphics3::clearCurrent() {
	
}


void Graphics3::viewport(int x, int y, int width, int height) {
	
}

void Graphics3::scissor(int x, int y, int width, int height) {
	
}

void Graphics3::disableScissor() {
	
}

void Graphics3::setStencilParameters(ZCompareMode compareMode, StencilAction bothPass, StencilAction depthFail, StencilAction stencilFail, int referenceValue,
						  int readMask = 0, int writeMask = 0) {
							
}


// NEW: material states

// Fixed-function material states (OpenGL 1.X) {

void Graphics3::setMaterialState(MaterialState state, const vec4& value) {
	
}

void Graphics3::setMaterialState(MaterialState state, float value) {
	
}

void Graphics3::setTextureMapping(TextureUnit texunit, TextureMapping mapping, bool on) {
	
}

void Graphics3::setTexCoordGeneration(TextureUnit texunit, TextureCoordinate texcoord, TexCoordGeneration generation) {
	
}


// } /Fixed-function material states

void Graphics3::setRenderState(RenderState state, bool on) {
	
}

void Graphics3::setRenderState(RenderState state, int v) {
	
}

void Graphics3::setRenderState(RenderState state, float value) {
	
}

void Graphics3::setTextureAddressing(TextureUnit unit, TexDir dir, TextureAddressing addressing) {
	
}

void Graphics3::setTextureMagnificationFilter(TextureUnit texunit, TextureFilter filter) {
	
}

void Graphics3::setTextureMinificationFilter(TextureUnit texunit, TextureFilter filter) {
	
}

void Graphics3::setTextureMipmapFilter(TextureUnit texunit, MipmapFilter filter) {
	
}

void Graphics3::setBlendingMode(BlendingOperation source, BlendingOperation destination) {
	
}

void Graphics3::setTextureOperation(TextureOperation operation, TextureArgument arg1, TextureArgument arg2) {
	Graphics4::setTextureOperation(operation, arg1, arg2);
}

void Graphics3::setColorMask(bool red, bool green, bool blue, bool alpha) {
	//TODO
}


bool Graphics3::vsynced() {
	//TODO
}

unsigned Graphics3::refreshRate() {
	//TODO
}

bool Graphics3::nonPow2TexturesSupported() {
	Graphics4::nonPow2TexturesSupported();
}


void Graphics3::clear(uint flags, uint color = 0, float depth = 1.0f, int stencil = 0) {
	Graphics4::clear(flags, color, depth, stencil);	
}


void Graphics3::init(int windowId, int depthBufferBits, int stencilBufferBits, bool vsync) {
	Graphics4::init(windowId, depthBufferBits, stencilBufferBits, vsync);
	
	// TODO Initialize pipelines to simulate OGL1 fixed functions with shaders
}

void Graphics3::destroy(int windowId) {
	Graphics4::destroy(windowId);
}


void Graphics3::flush() {
	Graphics4::flush();
}