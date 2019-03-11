#include <iostream>
// class taken from: https://r3dux.org/2012/12/vec3-a-simple-vector-class-in-c/
template <class T> class vec3
{
public:
	// A vec3 simply has three properties called x, y and z
	T x, y, z;
	// ------------ Constructors ------------

	// Default constructor
	vec3() { x = y = z = 0; };

	// Three parameter constructor
	vec3(T xValue, T yValue, T zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	};
	vec3(T xValue)
	{
		x = xValue;
		y = xValue;
		z = xValue;
	};
	// ------------ Getters and setters ------------

	void set(const T &xValue, const T &yValue, const T &zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }

	void setX(const T &xValue) { x = xValue; }
	void setY(const T &yValue) { y = yValue; }
	void setZ(const T &zValue) { z = zValue; }

	// ------------ Helper methods ------------

	// Method to reset a vector to zero
	void zero()
	{
		x = y = z = 0;
	}

	// Method to normalise a vector
	void normalise()
	{
		// Calculate the magnitude of our vector
		T magnitude = sqrt((x * x) + (y * y) + (z * z));

		// As long as the magnitude isn't zero, divide each element by the magnitude
		// to get the normalised value between -1 and +1
		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}

	// Static method to calculate and return the scalar dot product of two vectors
	//
	// Note: The dot product of two vectors tell us things about the angle between
	// the vectors. That is, it tells us if they are pointing in the same direction
	// (i.e. are they parallel? If so, the dot product will be 1), or if they're
	// perpendicular (i.e. at 90 degrees to each other) the dot product will be 0,
	// or if they're pointing in opposite directions then the dot product will be -1.
	//
	// Usage example: double foo = vec3<double>::dotProduct(vectorA, vectorB);
	static T dotProduct(const vec3 &vec1, const vec3 &vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	// Non-static method to calculate and return the scalar dot product of this vector and another vector
	//
	// Usage example: double foo = vectorA.dotProduct(vectorB);
	T dotProduct(const vec3 &vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	// Static method to calculate and return a vector which is the cross product of two vectors
	//
	// Note: The cross product is simply a vector which is perpendicular to the plane formed by
	// the first two vectors. Think of a desk like the one your laptop or keyboard is sitting on.
	// If you put one pencil pointing directly away from you, and then another pencil pointing to the
	// right so they form a "L" shape, the vector perpendicular to the plane made by these two pencils
	// points directly upwards.
	//
	// Whether the vector is perpendicularly pointing "up" or "down" depends on the "handedness" of the
	// coordinate system that you're using.
	//
	// Further reading: http://en.wikipedia.org/wiki/Cross_product
	//
	// Usage example: vec3<double> crossVect = vec3<double>::crossProduct(vectorA, vectorB);
	static vec3 crossProduct(const vec3 &vec1, const vec3 &vec2)
	{
		return vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
	}

	// Easy adders
	void addX(T value) { x += value; }
	void addY(T value) { y += value; }
	void addZ(T value) { z += value; }

	// Method to return the distance between two vectors in 3D space
	//
	// Note: This is accurate, but not especially fast - depending on your needs you might
	// like to use the Manhattan Distance instead: http://en.wikipedia.org/wiki/Taxicab_geometry
	// There's a good discussion of it here: http://stackoverflow.com/questions/3693514/very-fast-3d-distance-check
	// The gist is, to find if we're within a given distance between two vectors you can use:
	//
	// bool within3DManhattanDistance(vec3 c1, vec3 c2, float distance)
	// {
	//      float dx = abs(c2.x - c1.x);
	//      if (dx > distance) return false; // too far in x direction
	//
	//      float dy = abs(c2.y - c1.y);
	//      if (dy > distance) return false; // too far in y direction
	//
	//      float dz = abs(c2.z - c1.z);
	//      if (dz > distance) return false; // too far in z direction
	//
	//      return true; // we're within the cube
	// }
	//
	// Or to just calculate the straight Manhattan distance you could use:
	//
	// float getManhattanDistance(vec3 c1, vec3 c2)
	// {
	//      float dx = abs(c2.x - c1.x);
	//      float dy = abs(c2.y - c1.y);
	//      float dz = abs(c2.z - c1.z);
	//      return dx+dy+dz;
	// }
	//
	static T getDistance(const vec3 &v1, const vec3 &v2)
	{
		T dx = v2.x - v1.x;
		T dy = v2.y - v1.y;
		T dz = v2.z - v1.z;

		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	// Method to display the vector so you can easily check the values
	void display()
	{
		std::cout << "X: " << x << "\t Y: " << y << "\t Z: " << z << std::endl;
	}

	// ------------ Overloaded operators ------------

	// Overloaded addition operator to add vec3s together
	vec3 operator+(const vec3 &vector) const
	{
		return vec3<T>(x + vector.x, y + vector.y, z + vector.z);
	}

	// Overloaded add and asssign operator to add vec3s together
	void operator+=(const vec3 &vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
	}

	// Overloaded subtraction operator to subtract a vec3 from another vec3
	vec3 operator-(const vec3 &vector) const
	{
		return vec3<T>(x - vector.x, y - vector.y, z - vector.z);
	}

	// Overloaded subtract and asssign operator to subtract a vec3 from another vec3
	void operator-=(const vec3 &vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
	}

	// Overloaded multiplication operator to multiply two vec3s together
	vec3 operator*(const vec3 &vector) const
	{
		return vec3<T>(x * vector.x, y * vector.y, z * vector.z);
	}


	// Overloaded multiply and assign operator to multiply a vector by a scalar
	void operator*=(const T &value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	// Overloaded multiply operator to multiply a vector by a scalar
	vec3 operator/(const T &value) const
	{
		return vec3<T>(x / value, y / value, z / value);
	}

	// Overloaded multiply and assign operator to multiply a vector by a scalar
	void operator/=(const T &value)
	{
		x /= value;
		y /= value;
		z /= value;
	}
};
template <class T>
T length(const vec3<T> &v1)
{
	return sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

template <class T>
vec3<T> absol(const vec3<T> &v1)
{
	return vec3<T>(abs(v1.x), abs(v1.y), abs(v1.z));
}

// Overloaded subtraction operator to subtract a vec3 from float
template <class T>
vec3<T> operator-(T value, const vec3<T> &vector)
{
	return vec3<T>(value -vector.x, value - vector.y, value - vector.z);
}


// Overloaded multiply operator to multiply a vector by a scalar
template <class T>
vec3<T> operator*( T value, vec3<T>& xyz)
{
	return vec3<T>(xyz.x * value, xyz.y * value, xyz.z * value);
}

// Overloaded multiply operator to multiply a vector by a scalar
template <class T>
vec3<T> operator/(T value, vec3<T>& xyz)
{
	return vec3<T>(xyz.x / value, xyz.y / value, xyz.z / value);
}

// Method to normalise a vector
template <class T>
vec3<T> normalize(vec3<T> rawVec)
{
	// Calculate the magnitude of our vector
	T magnitude = sqrt((rawVec.x * rawVec.x) + (rawVec.y * rawVec.y) + (rawVec.z * rawVec.z));

	// As long as the magnitude isn't zero, divide each element by the magnitude
	// to get the normalised value between -1 and +1
	if (magnitude != 0)
	{
		rawVec.x /= magnitude;
		rawVec.y /= magnitude;
		rawVec.z /= magnitude;
	}

	return rawVec;
}

////////////////////////////////////////////////////////////


// Vec2

///////////////////////////////////////////////////////////

template <class T> class vec2
{
public:
	// A vec2 simply has three properties called x, y and z
	T x, y;
	// ------------ Constructors ------------

	// Default constructor
	vec2() { x = y = 0; };

	// Three parameter constructor
	vec2(T xValue, T yValue)
	{
		x = xValue;
		y = yValue;
	};
	vec2(T xValue)
	{
		x = xValue;
		y = xValue;
	};
	// ------------ Getters and setters ------------

	void set(const T &xValue, const T &yValue)
	{
		x = xValue;
		y = yValue;
	}

	T getX() const { return x; }
	T getY() const { return y; }

	void setX(const T &xValue) { x = xValue; }
	void setY(const T &yValue) { y = yValue; }

	// ------------ Helper methods ------------

	// Method to reset a vector to zero
	void zero()
	{
		x = y = 0;
	}

	void normalise()
	{
		T magnitude = sqrt((x * x) + (y * y));
		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
		}
	}

	// Easy adders
	void addX(T value) { x += value; }
	void addY(T value) { y += value; }
	
	static T getDistance(const vec2 &v1, const vec2 &v2)
	{
		T dx = v2.x - v1.x;
		T dy = v2.y - v1.y;
		return sqrt(dx * dx + dy * dy);
	}

	// Method to display the vector so you can easily check the values
	void display()
	{
		std::cout << "X: " << x << "\t Y: " << y << std::endl;
	}

	// ------------ Overloaded operators ------------

	// Overloaded addition operator to add vec2s together
	vec2 operator+(const vec2 &vector) const
	{
		return vec2<T>(x + vector.x, y + vector.y);
	}

	// Overloaded add and asssign operator to add vec2s together
	void operator+=(const vec2 &vector)
	{
		x += vector.x;
		y += vector.y;
	}

	// Overloaded subtraction operator to subtract a vec2 from another vec2
	vec2 operator-(const vec2 &vector) const
	{
		return vec2<T>(x - vector.x, y - vector.y);
	}

	// Overloaded subtract and asssign operator to subtract a vec2 from another vec2
	void operator-=(const vec2 &vector)
	{
		x -= vector.x;
		y -= vector.y;
	}

	// Overloaded multiplication operator to multiply two vec2s together
	vec2 operator*(const vec2 &vector) const
	{
		return vec2<T>(x * vector.x, y * vector.y);
	}


	// Overloaded multiply and assign operator to multiply a vector by a scalar
	void operator*=(const T &value)
	{
		x *= value;
		y *= value;
	}

	// Overloaded multiply operator to multiply a vector by a scalar
	vec2 operator/(const T &value) const
	{
		return vec2<T>(x / value, y / value);
	}

	// Overloaded multiply and assign operator to multiply a vector by a scalar
	void operator/=(const T &value)
	{
		x /= value;
		y /= value;
	}
};
// Overloaded multiply operator to multiply a vector by a scalar
template <class T>
vec2<T> operator*(T value, vec2<T>& xy)
{
	return vec2<T>(xy.x * value, xy.y * value);
}

// Overloaded multiply operator to multiply a vector by a scalar
template <class T>
vec2<T> operator/(T value, vec2<T>& xy)
{
	return vec2<T>(xy.x / value, xy.y / value);
}



////////////////////////////////////////////////////////////


// Vec4

///////////////////////////////////////////////////////////



template <class T> class vec4
{
public:
	// A vec4 simply has three properties called x, y and z
	T x, y, z, a;
	// ------------ Constructors ------------

	// Default constructor
	vec4() { x = y = z = a = 0; };

	// Three parameter constructor
	vec4(T xValue, T yValue, T zValue, T aValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
		a = aValue;
	};
	vec4(T xValue)
	{
		x = xValue;
		y = xValue;
		z = xValue;
		a = xValue;
	};
	// ------------ Getters and setters ------------

	void set(const T &xValue, const T &yValue, const T &zValue, const T &aValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
		a = aValue;
	}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }

	void setX(const T &xValue) { x = xValue; }
	void setY(const T &yValue) { y = yValue; }
	void setZ(const T &zValue) { z = zValue; }
	void setA(const T &aValue) { a = aValue; }

	// ------------ Helper methods ------------

	// Method to reset a vector to zero
	void zero()
	{
		x = y = z = a = 0;
	}

	// Method to normalise a vector
	void normalise()
	{
		// Calculate the magnitude of our vector
		T magnitude = sqrt((x * x) + (y * y) + (z * z));

		// As long as the magnitude isn't zero, divide each element by the magnitude
		// to get the normalised value between -1 and +1
		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}
	static T dotProduct(const vec4 &vec1, const vec4 &vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}
	T dotProduct(const vec4 &vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}
	static vec4 crossProduct(const vec4 &vec1, const vec4 &vec2)
	{
		return vec4(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
	}

	// Easy adders
	void addX(T value) { x += value; }
	void addY(T value) { y += value; }
	void addZ(T value) { z += value; }
	void addA(T value) { a += value; }
static T getDistance(const vec4 &v1, const vec4 &v2)
	{
		T dx = v2.x - v1.x;
		T dy = v2.y - v1.y;
		T dz = v2.z - v1.z;

		return sqrt(dx * dx + dy * dy + dz * dz);
	}
	void display()
	{
		std::cout << "X: " << x << "\t Y: " << y << "\t Z: " << z <<  "\t A: " << a << std::endl;
	}

	// ------------ Overloaded operators ------------

	// Overloaded addition operator to add vec4s together
	vec4 operator+(const vec4 &vector) const
	{
		return vec4<T>(x + vector.x, y + vector.y, z + vector.z, a + vector.a);
	}

	// Overloaded add and asssign operator to add vec4s together
	void operator+=(const vec4 &vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		a += vector.a;
	}

	// Overloaded subtraction operator to subtract a vec4 from another vec4
	vec4 operator-(const vec4 &vector) const
	{
		return vec4<T>(x - vector.x, y - vector.y, z - vector.z, a - vector.a);
	}

	// Overloaded subtract and asssign operator to subtract a vec4 from another vec4
	void operator-=(const vec4 &vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		a -= vector.a;
	}

	// Overloaded multiplication operator to multiply two vec4s together
	vec4 operator*(const vec4 &vector) const
	{
		return vec4<T>(x * vector.x, y * vector.y, z * vector.z, a * vector.a);
	}


	// Overloaded multiply and assign operator to multiply a vector by a scalar
	void operator*=(const T &value)
	{
		x *= value;
		y *= value;
		z *= value;
		a *= value;
	}

	// Overloaded multiply operator to multiply a vector by a scalar
	vec4 operator/(const T &value) const
	{
		return vec4<T>(x / value, y / value, z / value, a / value);
	}

	// Overloaded multiply and assign operator to multiply a vector by a scalar
	void operator/=(const T &value)
	{
		x /= value;
		y /= value;
		z /= value;
		a /= value;
	}
};



// Overloaded multiply operator to multiply a vector by a scalar
template <class T>
vec4<T> operator*(T value, vec4<T>& xyza)
{
	return vec4<T>(xyza.x * value, xyza.y * value, xyza.z * value, xyza.a * value);
}

// Overloaded multiply operator to multiply a vector by a scalar
template <class T>
vec4<T> operator/(T value, vec4<T>& xyza)
{
	return vec4<T>(xyza.x / value, xyza.y / value, xyza.z / value, xyza.a / value);
}
