#include "../inc/helpers/Vector2D.h"

#define EPSILON 0.0001
#define PI 3.1415926535897932384626433832795

// ---------------------------------------------------------------------------
// sets pResult to vector2D(0,0)
void Vector2DZero(Vector2D* pResult)
{
	pResult->x = pResult->y = 0;
}

// ---------------------------------------------------------------------------
// sets pResult to vector2D(x,y)
void Vector2DSet(Vector2D* pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = -pVec0
void Vector2DNeg(Vector2D* pResult, Vector2D* pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = pVec0 + pVec1
void Vector2DAdd(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1)
{
	Vector2D temp;
	temp.x = pVec0->x + pVec1->x;
	temp.y = pVec0->y + pVec1->y;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = pVec0 - pVec1
void Vector2DSub(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1)
{
	Vector2D temp;
	temp.x = pVec0->x - pVec1->x;
	temp.y = pVec0->y - pVec1->y;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = normalize(pVec0)
void Vector2DNormalize(Vector2D* pResult, Vector2D* pVec0)
{
	Vector2D temp;
	double magnitude = sqrt((double)pVec0->x * pVec0->x + (double)pVec0->y * pVec0->y);
	temp.x = pVec0->x / magnitude;
	temp.y = pVec0->y / magnitude;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = pVec0*C
void Vector2DScale(Vector2D* pResult, Vector2D* pVec0, float c)
{
	Vector2D temp;
	temp.x = pVec0->x * c;
	temp.y = pVec0->y * c;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = pVec0*C + pVec1
void Vector2DScaleAdd(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1, float c)
{
	Vector2D temp;
	// scale 
	temp.x = pVec0->x * c;
	temp.y = pVec0->y * c;
	// add
	temp.x = temp.x + pVec1->x;
	temp.y = temp.y + pVec1->y;
	// res
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Evaluates pResult = pVec0*C - pVec1
void Vector2DScaleSub(Vector2D* pResult, Vector2D* pVec0, Vector2D* pVec1, float c)
{
	Vector2D temp;
	// scale 
	temp.x = pVec0->x * c;
	temp.y = pVec0->y * c;
	// sub
	temp.x = temp.x - pVec1->x;
	temp.y = temp.y - pVec1->y;
	// res
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Returns  Magnitude of pVec0
float Vector2DLength(Vector2D* pVec0)
{
	return(sqrt((double)pVec0->x * pVec0->x + (double)pVec0->y * pVec0->y));
}

// ---------------------------------------------------------------------------
// Returns Squared Magnitude of pVec0
float Vector2DSquareLength(Vector2D* pVec0)
{
	return((double)pVec0->x * pVec0->x + (double)pVec0->y * pVec0->y);
}

// ---------------------------------------------------------------------------
// Returns distance between pVec0 and pVec1
float Vector2DDistance(Vector2D* pVec0, Vector2D* pVec1)
{
	return(sqrt(((double)pVec0->x - pVec1->x) * ((double)pVec0->x - pVec1->x) + ((double)pVec0->y - pVec1->y) * ((double)pVec0->y - pVec1->y)));
}

// ---------------------------------------------------------------------------
// Returns Squared distance between pVec0 and pVec1
float Vector2DSquareDistance(Vector2D* pVec0, Vector2D* pVec1)
{
	return(((double)pVec0->x - pVec1->x) * ((double)pVec0->x - pVec1->x) + ((double)pVec0->y - pVec1->y) * ((double)pVec0->y - pVec1->y));
}

// ---------------------------------------------------------------------------
// Returns pVec0 [dot] pVec1
float Vector2DDotProduct(Vector2D* pVec0, Vector2D* pVec1)
{
	return((float)pVec0->x * pVec1->x + (float)pVec0->y * pVec1->y);
}

// ---------------------------------------------------------------------------
// Returns Vector2D from Angle(Deg)
void Vector2DFromAngleDeg(Vector2D* pResult, float angle)
{
	Vector2D temp;
	temp.x = cos(180 / PI * angle);
	temp.y = sin(180 / PI * angle);
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Returns Vector2D from Angle(Radians)
void Vector2DFromAngleRad(Vector2D* pResult, float angle)
{
	Vector2D temp;
	temp.x = cos(angle);
	temp.y = sin(angle);
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
// Returns the angle that the vector makes wrt to positive x axis
float Vector2DAngleFromVec2(Vector2D* vec) {
	return(atan2(vec->y, vec->x));
}
