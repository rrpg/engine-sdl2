#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() {
	m_iX = 0;
	m_iY = 0;
}

Vector2D::Vector2D(const float x, const float y) {
	m_iX = x;
	m_iY = y;
}

float Vector2D::getLength() {
	return sqrtf(powf(m_iX, 2.0) + powf(m_iY, 2.0));
}

float Vector2D::getX() {
	return m_iX;
}
float Vector2D::getY() {
	return m_iY;
}

void Vector2D::setX(const float x) {
	m_iX = x;
}

void Vector2D::setY(const float y) {
	m_iY = y;
}

void Vector2D::set(Vector2DCoord coord, const float value) {
	if (coord == VECTOR_X) {
		setX(value);
	}
	else {
		setY(value);
	}
}

void Vector2D::normalize() {
	float l = getLength();
	if (l > 0) { // we never want to attempt to divide by 0
		(*this) *= 1 / l;
	}
}

// Vector operations

Vector2D Vector2D::operator+(const Vector2D& v2) const {
	return Vector2D(m_iX + v2.m_iX, m_iY + v2.m_iY);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const {
	return Vector2D(m_iX - v2.m_iX, m_iY - v2.m_iY);
}

Vector2D Vector2D::operator*(float scalar) {
	return Vector2D(m_iX * scalar, m_iY * scalar);
}

Vector2D Vector2D::operator/(float scalar) {
	return Vector2D(m_iX / scalar, m_iY / scalar);
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
	v1.m_iX += v2.m_iX;
	v1.m_iY += v2.m_iY;
	return v1;
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
	v1.m_iX -= v2.m_iX;
	v1.m_iY -= v2.m_iY;
	return v1;
}

Vector2D& operator*=(Vector2D& v1, float scalar) {
	v1.m_iX *= scalar;
	v1.m_iY *= scalar;
	return v1;
}

Vector2D& operator/=(Vector2D& v1, float scalar) {
	v1.m_iX /= scalar;
	v1.m_iY /= scalar;
	return v1;
}
