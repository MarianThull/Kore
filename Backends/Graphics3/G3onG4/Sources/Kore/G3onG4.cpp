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
	Graphics4::setVertexBuffer(vertexBuffer);
	// TODO test	
}

void Graphics3::setVertexBuffers(VertexBuffer** vertexBuffers, int count) {
	Graphics4::setVertexBuffers(vertexBuffer);
	// TODO test	
}

void Graphics3::setIndexBuffer(IndexBuffer& indexBuffer) {
	Graphics4::setIndexBuffer(indexBuffer);
	// TODO test
}

void Graphics3::setTexture(TextureUnit unit, Texture* texture) {
	Graphics4::setTexture(unit, texture);
	// TODO test
}

void Graphics3::drawIndexedVertices() {
	Graphics4::drawIndexedVertices();
	//TODO test
}

void Graphics3::drawIndexedVertices(int start, int count) {
	Graphics4::drawIndexedVertices(start, count);
	//TODO test
}

// OpenGL 1.X does not support hardware instancing
/*void drawIndexedVerticesInstanced(int instanceCount);
void drawIndexedVerticesInstanced(int instanceCount, int start, int count);*/

void Graphics3::changeResolution(int width, int height) {
	// TODO implement
	// -> Graphics4::_resize(window, width, height)
}

bool Graphics3::hasWindow() {
	// TODO implement
}

void Graphics3::setWindow(bool) {
	// TODO implement
}
	
int Graphics3::antialiasingSamples() {
	Graphics4::antialiasingSamples();
	//TODO test
}
	
void Graphics3::setAntialiasingSamples(int samples) {
	Graphics4::antialiasingSamples(samples);
	//TODO test
}
	

bool Graphics3::renderTargetsInvertedY() {
	Graphics4::renderTargetsInvertedY();
	//TODO test
}
	
void Graphics3::setRenderTarget(RenderTarget* texture, int num = 0, int additionalTargets = 0) {
	//Graphics4::setRenderTarget(RenderTarget* target);
	//Graphics4::setRenderTargets(RenderTarget** targets, int count);
	
	//TODO implement
}
	
void Graphics3::restoreRenderTarget() {
	Graphics4::restoreRenderTarget();
}
	

// TODO (DK) windowId should be renamed contextId?
void Graphics3::setup() {
	// TODO
}

void Graphics3::swapBuffers(int windowId = 0) {
	//TODO implement
	//windowId ??
	Graphics4::swapBuffers();
}

void Graphics3::begin(int windowId = 0) {
	Graphics4::begin(windowId);
	//TODO test
}

void Graphics3::end(int windowId = 0) {
	Graphics4::end(windowId);
	//TODO test
}

void Graphics3::makeCurrent(int windowId) {
	//TODO implement
}

void Graphics3::clearCurrent() {
	//TODO implement
}


void Graphics3::viewport(int x, int y, int width, int height) {
	Graphics4::viewport(x, y, width, height);
	//TODO test
}

void Graphics3::scissor(int x, int y, int width, int height) {
	Graphics4::scissor(x, y, width, height);
	//TODO test
}

void Graphics3::disableScissor() {
	Graphics4::disableScissor();
	//TODO test
}

void Graphics3::setStencilParameters(ZCompareMode compareMode, StencilAction bothPass, StencilAction depthFail, StencilAction stencilFail, int referenceValue,
						  int readMask = 0, int writeMask = 0) {
	// TODO implement						
}


// NEW: material states

// Fixed-function material states (OpenGL 1.X) {

void Graphics3::setMaterialState(MaterialState state, const vec4& value) {
	// TODO implement						
	
}

void Graphics3::setMaterialState(MaterialState state, float value) {
	// TODO implement						
	
}

void Graphics3::setTextureMapping(TextureUnit texunit, TextureMapping mapping, bool on) {
	// TODO implement						
	
}

void Graphics3::setTexCoordGeneration(TextureUnit texunit, TextureCoordinate texcoord, TexCoordGeneration generation) {
	// TODO implement						
	
}


// } /Fixed-function material states

void Graphics3::setRenderState(RenderState state, bool on) {
	// TODO implement						
	
}

void Graphics3::setRenderState(RenderState state, int v) {
	// TODO implement						
	
}

void Graphics3::setRenderState(RenderState state, float value) {
	// TODO implement						
	
}

void Graphics3::setTextureAddressing(TextureUnit unit, TexDir dir, TextureAddressing addressing) {
	Graphics4::setTextureAddressing(unit, dir, addressing);
	//TODO test
}

void Graphics3::setTextureMagnificationFilter(TextureUnit texunit, TextureFilter filter) {
	Graphics4::setTextureMagnificationFilter(texunit, filter);
	//TODO test
}

void Graphics3::setTextureMinificationFilter(TextureUnit texunit, TextureFilter filter) {
	Graphics4::setTextureMinificationFilter(texunit, filter);
	//TODO test
}

void Graphics3::setTextureMipmapFilter(TextureUnit texunit, MipmapFilter filter) {
	Graphics4::setTextureMipmapFilter(texunit, filter);
	//TODO test
}

void Graphics3::setBlendingMode(BlendingOperation source, BlendingOperation destination) {
	// TODO implement						
	
}

void Graphics3::setTextureOperation(TextureOperation operation, TextureArgument arg1, TextureArgument arg2) {
	Graphics4::setTextureOperation(operation, arg1, arg2);
	//TODO test
}

void Graphics3::setColorMask(bool red, bool green, bool blue, bool alpha) {
	// TODO implement						
}


bool Graphics3::vsynced() {
	// TODO implement						
}

unsigned Graphics3::refreshRate() {
	// TODO implement						
}

bool Graphics3::nonPow2TexturesSupported() {
	Graphics4::nonPow2TexturesSupported();
	// TODO test						
}


void Graphics3::clear(uint flags, uint color = 0, float depth = 1.0f, int stencil = 0) {
	Graphics4::clear(flags, color, depth, stencil);	
	// TODO test						
}


void Graphics3::init(int windowId, int depthBufferBits, int stencilBufferBits, bool vsync) {
	Graphics4::init(windowId, depthBufferBits, stencilBufferBits, vsync);
	
	// TODO Initialize pipelines to simulate OGL1 fixed functions with shaders
}

void Graphics3::destroy(int windowId) {
	Graphics4::destroy(windowId);
	// TODO test						
}


void Graphics3::flush() {
	Graphics4::flush();
	// TODO test						
}