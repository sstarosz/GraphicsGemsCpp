/**** BallMath.c - Essential routines for ArcBall.  ****/
#include <math.h>
#include "BallMath.hpp"
#include "BallAux.hpp"

/* Convert window coordinates to sphere coordinates. */
HVect MouseOnSphere(HVect mouse, HVect ballCenter, float ballRadius)
{
    HVect ballMouse;
    float mag;
    ballMouse.x = (mouse.x - ballCenter.x) / ballRadius;
    ballMouse.y = (mouse.y - ballCenter.y) / ballRadius;
    mag = ballMouse.x*ballMouse.x + ballMouse.y*ballMouse.y;
    if (mag > 1.f) {
	float scale = 1.f/sqrtf(mag);
	ballMouse.x *= scale; ballMouse.y *= scale;
	ballMouse.z = 0.f;
    } else {
	ballMouse.z = sqrtf(1 - mag);
    }
    ballMouse.w = 0.f;
    return (ballMouse);
}

/* Construct a unit quaternion from two points on unit sphere */
Quat Qt_FromBallPoints(HVect from, HVect to)
{
    Quat qu;
    qu.x = from.y*to.z - from.z*to.y;
    qu.y = from.z*to.x - from.x*to.z;
    qu.z = from.x*to.y - from.y*to.x;
    qu.w = from.x*to.x + from.y*to.y + from.z*to.z;
    return (qu);
}

/* Convert a unit quaternion to two points on unit sphere */
void Qt_ToBallPoints(Quat q, HVect *arcFrom, HVect *arcTo)
{
    float s;
    s = sqrtf(q.x*q.x + q.y*q.y);
    if (s == 0.f) {
	*arcFrom = V3_(0.f, 1.f, 0.f);
    } else {
	*arcFrom = V3_(-q.y/s, q.x/s, 0.f);
    }
    arcTo->x = q.w*arcFrom->x - q.z*arcFrom->y;
    arcTo->y = q.w*arcFrom->y + q.z*arcFrom->x;
    arcTo->z = q.x*arcFrom->y - q.y*arcFrom->x;
    if (q.w < 0.f) *arcFrom = V3_(-arcFrom->x, -arcFrom->y, 0.f);
}

/* Force sphere point to be perpendicular to axis. */
HVect ConstrainToAxis(HVect loose, HVect axis)
{
    HVect onPlane;
    float norm;
    onPlane = V3_Sub(loose, V3_Scale(axis, V3_Dot(axis, loose)));
    norm = V3_Norm(onPlane);
    if (norm > 0.f) {
	if (onPlane.z < 0.f) onPlane = V3_Negate(onPlane);
	return ( V3_Scale(onPlane, 1/sqrtf(norm)) );
    } /* else drop through */
    if (axis.z == 1) {
	onPlane = V3_(1.f, 0.f, 0.f);
    } else {
	onPlane = V3_Unit(V3_(-axis.y, axis.x, 0.f));
    }
    return (onPlane);
}

/* Find the index of nearest arc of axis set. */
int NearestConstraintAxis(HVect loose, HVect *axes, int nAxes)
{
    HVect onPlane;
    float max, dot;
    int i, nearest;
    max = -1; nearest = 0;
    for (i=0; i<nAxes; i++) {
	onPlane = ConstrainToAxis(loose, axes[i]);
	dot = V3_Dot(onPlane, loose);
	if (dot>max) {
	    max = dot; nearest = i;
	}
    }
    return (nearest);
}
