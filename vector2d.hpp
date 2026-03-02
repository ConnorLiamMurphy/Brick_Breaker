#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

class Vector2d {
	private:
		
	public:
		float X;
		float Y;
		Vector2d(float x, float y) : X(x) Y(y) {};

		Vector2d operator+(const Vector2d& other) const {
			return Vector2d(X + other.X, Y + other.Y);
		}

		Vector2d operator-(const Vector2d& other) const {
			return Vector2d(X - other.X, Y - other.Y);
		}

		Vector2d operator*(float mult) const {
			return Vector2d(X * mult, Y * mult);
		}
};





#endif
