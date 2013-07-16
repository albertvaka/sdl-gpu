#include "SDL_gpu.h"
#include <string.h>

#include "OpenGL_common/SDL_gpu_OpenGL_internal.h"

static GPU_ShapeRenderer* shapeRenderer = NULL;

static void (*freeShapeRendererFn)(GPU_ShapeRenderer* renderer) = NULL;

GPU_ShapeRenderer* GPU_GetCurrentShapeRenderer(void)
{
    return shapeRenderer;
}

void GPU_LoadShapeRenderer(void)
{
	// Free the old one
	if(shapeRenderer != NULL)
	{
		if(freeShapeRendererFn != NULL)
			freeShapeRendererFn(shapeRenderer);
		shapeRenderer = NULL;
		freeShapeRendererFn = NULL;
	}
	
	const char* rendererID = GPU_GetCurrentRendererID();
	GPU_Renderer* renderer = GPU_GetRendererByID(rendererID);
	if(renderer == NULL)
		return;
	
    #ifndef SDL_GPU_USE_OPENGLES_1
	if(strcmp(rendererID, "OpenGL") == 0)
	{
		GPU_ShapeRenderer* sr = GPU_CreateShapeRenderer_OpenGL();
		if(sr == NULL)
			return;
		sr->renderer = renderer;
		shapeRenderer = sr;
		freeShapeRendererFn = &GPU_FreeShapeRenderer_OpenGL;
	}
	#else
	
	if(strcmp(rendererID, "OpenGLES_1") == 0)
	{
		GPU_ShapeRenderer* sr = GPU_CreateShapeRenderer_OpenGLES_1();
		if(sr == NULL)
			return;
		sr->renderer = renderer;
		shapeRenderer = sr;
		freeShapeRendererFn = &GPU_FreeShapeRenderer_OpenGLES_1;
	}
	#endif
	

}

#define CHECK_RENDERER(ret) \
if(shapeRenderer == NULL) \
{ \
	GPU_LoadShapeRenderer(); \
	if(shapeRenderer == NULL) \
		return ret; \
}


float GPU_SetThickness(float thickness)
{
	CHECK_RENDERER(1.0f);
	if(shapeRenderer->SetThickness == NULL)
		return 1.0f;
	
	return shapeRenderer->SetThickness(shapeRenderer, thickness);
}

float GPU_GetThickness(void)
{
	CHECK_RENDERER(1.0f);
	if(shapeRenderer->GetThickness == NULL)
		return 1.0f;
	
	return shapeRenderer->GetThickness(shapeRenderer);
}

void GPU_Pixel(GPU_Target* target, float x, float y, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Pixel == NULL)
		return;
	
	shapeRenderer->Pixel(shapeRenderer, target, x, y, color);
}

void GPU_Line(GPU_Target* target, float x1, float y1, float x2, float y2, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Line == NULL)
		return;
	
	shapeRenderer->Line(shapeRenderer, target, x1, y1, x2, y2, color);
}


void GPU_Arc(GPU_Target* target, float x, float y, float radius, float startAngle, float endAngle, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Arc == NULL)
		return;
	
	shapeRenderer->Arc(shapeRenderer, target, x, y, radius, startAngle, endAngle, color);
}


void GPU_ArcFilled(GPU_Target* target, float x, float y, float radius, float startAngle, float endAngle, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->ArcFilled == NULL)
		return;
	
	shapeRenderer->ArcFilled(shapeRenderer, target, x, y, radius, startAngle, endAngle, color);
}

void GPU_Circle(GPU_Target* target, float x, float y, float radius, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Circle == NULL)
		return;
	
	shapeRenderer->Circle(shapeRenderer, target, x, y, radius, color);
}

void GPU_CircleFilled(GPU_Target* target, float x, float y, float radius, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->CircleFilled == NULL)
		return;
	
	shapeRenderer->CircleFilled(shapeRenderer, target, x, y, radius, color);
}

void GPU_Tri(GPU_Target* target, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Tri == NULL)
		return;
	
	shapeRenderer->Tri(shapeRenderer, target, x1, y1, x2, y2, x3, y3, color);
}

void GPU_TriFilled(GPU_Target* target, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->TriFilled == NULL)
		return;
	
	shapeRenderer->TriFilled(shapeRenderer, target, x1, y1, x2, y2, x3, y3, color);
}

void GPU_Rectangle(GPU_Target* target, float x1, float y1, float x2, float y2, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Rectangle == NULL)
		return;
	
	shapeRenderer->Rectangle(shapeRenderer, target, x1, y1, x2, y2, color);
}

void GPU_RectangleFilled(GPU_Target* target, float x1, float y1, float x2, float y2, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->RectangleFilled == NULL)
		return;
	
	shapeRenderer->RectangleFilled(shapeRenderer, target, x1, y1, x2, y2, color);
}

void GPU_RectangleRound(GPU_Target* target, float x1, float y1, float x2, float y2, float radius, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->RectangleRound == NULL)
		return;
	
	shapeRenderer->RectangleRound(shapeRenderer, target, x1, y1, x2, y2, radius, color);
}

void GPU_RectangleRoundFilled(GPU_Target* target, float x1, float y1, float x2, float y2, float radius, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->RectangleRoundFilled == NULL)
		return;
	
	shapeRenderer->RectangleRoundFilled(shapeRenderer, target, x1, y1, x2, y2, radius, color);
}

void GPU_Polygon(GPU_Target* target, Uint16 n, float* vertices, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->Polygon == NULL)
		return;
	
	shapeRenderer->Polygon(shapeRenderer, target, n, vertices, color);
}

void GPU_PolygonFilled(GPU_Target* target, Uint16 n, float* vertices, SDL_Color color)
{
	CHECK_RENDERER();
	if(shapeRenderer->PolygonFilled == NULL)
		return;
	
	shapeRenderer->PolygonFilled(shapeRenderer, target, n, vertices, color);
}


void GPU_PolygonBlit(GPU_Image* src, GPU_Rect* srcrect, GPU_Target* target, Uint16 n, float* vertices, float textureX, float textureY, float angle, float scaleX, float scaleY)
{
	CHECK_RENDERER();
	if(shapeRenderer->PolygonBlit == NULL)
		return;
	
	shapeRenderer->PolygonBlit(shapeRenderer, src, srcrect, target, n, vertices, textureX, textureY, angle, scaleX, scaleY);
}
