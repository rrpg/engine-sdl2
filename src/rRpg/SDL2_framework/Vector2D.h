#ifndef __Vector2D__
#define __Vector2D__

enum Vector2DCoord {VECTOR_X, VECTOR_Y};

/**
 * Class to handle vectors. a vector is a distance between two points. It is
 * composed of a x and a y values.
 */
class Vector2D {
	protected:
	float m_iX = 0.0;
	float m_iY = 0.0;

	public:
	/**
	 * Default construct
	 */
	Vector2D();

	/**
	 * Construct providing the vector information.
	 */
	Vector2D(const float x, const float y);

	/**
	 * Different getters for the vector.
	 */
	float getLength();
	float getX();
	float getY();

	/**
	 * Coord can be either VECTOR_X or VECTOR_Y, depending it, the coordinate x or
	 * y of the vector with be set with value
	 */
	void set(Vector2DCoord coord, const float value);
	void setX(const float x);
	void setY(const float y);

	/**
	 * Extands or reduce the x and y of the vector so its length is equal to 1.
	 */
	void normalize();

	// Vector operations
	Vector2D operator+(const Vector2D& v2) const;
	Vector2D operator-(const Vector2D& v2) const;
	Vector2D operator*(float scalar);
	Vector2D operator/(float scalar);

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*=(Vector2D& v, float scalar);
	friend Vector2D& operator/=(Vector2D& v, float scalar);
};

#endif
