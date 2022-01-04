namespace Geometry {
	double PI = std::atan(1) * 4;
	class BaseGeometryClass {
	public:
		double x = 0, y = 0;
		BaseGeometryClass(double x, double y) : x(x), y(y) {};
		//virtual std::ostream& operator<<(std::ostream& stream) = 0;
	};

	class Point2D : public BaseGeometryClass{
	public:
		Point2D() : BaseGeometryClass(0, 0) {};
		Point2D(double x, double y) : BaseGeometryClass(x, y) {};
		Point2D(const Point2D& point) = default;

		bool operator==(const Point2D& point) const {
			return x == point.x && y == point.y;
		}
		double distance(const Point2D& point) const {
			return std::sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
		}

		friend std::istream& operator>>(std::istream& stream, Point2D& point) {
			//so far I interpret input as simply two doubles separated by a space symbol
			stream >> point.x >> point.y;
			return stream;
		}
	};

	std::ostream& operator<<(std::ostream& stream, const Point2D& point) {
		return (stream << "(" << point.x << ", " << point.y << ")");
	}

	class Vector2D : public BaseGeometryClass {
	public:
		bool zero;
		Vector2D() : BaseGeometryClass(0, 0), zero(true) {};
		Vector2D(double x, double y) : BaseGeometryClass(x, y), zero(x == 0 && y == 0) {};
		Vector2D(const Point2D& start, const Point2D& end) : BaseGeometryClass(end.x - start.x, end.y - start.y), zero(x == 0 && y == 0) {};

		bool operator==(const Vector2D& vector) {
			return x == vector.x && y == vector.y;
		}

		double dot(const Vector2D& vector) const {
			return x * vector.x + y * vector.y;
		}
		double cross(const Vector2D& vector) const {
			return x * vector.y - y * vector.x;
		}

		Vector2D& operator+=(const Vector2D& vector) {
			x += vector.x;
			y += vector.y;
			return *this;
		}
		Vector2D& operator-=(const Vector2D& vector) {
			x -= vector.x;
			y -= vector.y;
			return *this;
		}
		Vector2D& operator*=(double k) {
			x *= k;
			y *= k;
			zero = (k == 0);
			return *this;
		}
		Vector2D operator-() const {
			return Vector2D(-x, -y);
		}

		double length() const {
			return std::sqrt(x * x + y * y);
		}
		double oriented_angle(const Vector2D& vector) const {
			if (zero || vector.zero) {
				//throw std::invalid_argument("One of the vectors is zero-vector => the result is undefined");
				return 0;
			}
			return std::asin(cross(vector) / (length() * vector.length()));
		}
		double angle(const Vector2D& vector) const {
			if (zero || vector.zero) {
				//throw std::invalid_argument("One of the vectors is zero-vector => the result is undefined");
				return 0;
			}
			return std::acos(dot(vector) / (length() * vector.length()));
		}

		bool are_collinear(const Vector2D& vector) const {
			if (zero || vector.zero) {
				return true;
			}
			return cross(vector) == 0;
		}
		bool are_orthogonal(const Vector2D& vector) const {
			if (zero || vector.zero) {
				return true;
			}
			return dot(vector) == 0;
		}
		bool are_co_directional(const Vector2D& vector) const {
			if (!are_collinear(vector)) {
				return false;
			}
			return dot(vector) >= 0;
		}
		
		void normalize() {
			*this *= (1 / length());
		}
		Vector2D normalized() const {
			Vector2D temp(*this);
			temp.normalize();
			return temp;
		}
		Vector2D get_orthogonal() const {
			return Vector2D(-y, x);
		}
	};

	std::ostream& operator<<(std::ostream& stream, const Vector2D& vector) {
		return (stream << "{" << vector.x << ", " << vector.y << "}");
	}
	Vector2D operator*(const Vector2D& vector, double k) {
		Vector2D temp(vector);
		temp *= k;
		return temp;
	}
	Vector2D operator*(double k, const Vector2D& vector) {
		Vector2D temp(vector);
		temp *= k;
		return temp;
	}
	Vector2D operator+(const Vector2D& vector1, const Vector2D& vector2) {
		Vector2D temp(vector1);
		temp += vector2;
		return temp;
	}
	Vector2D operator-(const Vector2D& vector1, const Vector2D& vector2) {
		Vector2D temp(vector1);
		temp -= vector2;
		return temp;
	}

	Point2D add_vector_to_point(const Point2D& point, const Vector2D& vector) {
		Point2D temp(point);
		temp.x += vector.x;
		temp.y += vector.y;
		return temp;
	}

	int orientation_of_triplet(const Point2D& A, const Point2D& B, const Point2D& C) {
		Vector2D AB(A, B), BC(B, C);
		double product = AB.cross(BC);
		if (product == 0) {
			return 0;
		}
		if (product > 0) {
			return 1;
		}
		return -1;
	}
	bool are_points_collinear(const Point2D& point1, const Point2D& point2, const Point2D& point3) {
		return Vector2D(point1, point2).are_collinear(Vector2D(point1, point3));
	}

	class Segment2D {
	public:
		Point2D start, end;
		Vector2D vector;
		double a, b, c;

		Segment2D() : start(0, 0), end(0, 1), vector(0, 1), a(1), b(0), c(0) {};
		Segment2D(const Point2D& point1, const Point2D& point2) : start(point1), end(point2), vector(point1, point2) {
			a = vector.y;
			b = -vector.x;
			c = vector.x * start.y - vector.y * start.x;
		}

		bool operator==(const Segment2D& segment) const {
			return (start == segment.start && end == segment.end) || (start == segment.end && end == segment.start);
		}
		double length() const {
			return vector.length();
		}
		bool are_collinear(const Segment2D& segment) const {
			return vector.are_collinear(segment.vector);
		}
		bool does_lie_on(const Point2D& point) const {
			Vector2D temp(start, point);
			if (!vector.are_collinear(temp)) {
				return false;
			}
			//double product = vector.dot(temp);
			//return (product == 0) || ((product > 0) && (product <= vector.x * vector.x + vector.y * vector.y));
			return (point.x <= std::max(start.x, end.x)) && (point.x >= std::min(start.x, end.x)) && (point.y <= std::max(start.y, end.y)) && (point.y >= std::min(start.y, end.y));
		}
		double distance(const Point2D& point) const {
			Vector2D start_to_point(start, point);
			if (vector.dot(start_to_point) < 0) {
				return start_to_point.length();
			}
			Vector2D end_to_point(end, point);
			if (vector.dot(end_to_point) > 0) {
				return end_to_point.length();
			}
			return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
		}

		Point2D divides_in_relation(double lambda) const {
			if (lambda == -1) {
				throw std::invalid_argument("Lambda is never -1");
			}
			return add_vector_to_point(start, (lambda / (1 + lambda)) * vector);
		}
		Point2D midpoint() const {
			return divides_in_relation(1);
		}

		bool do_intersect(const Segment2D& segment) const {
			int orientation1, orientation2, orientation3, orientation4;
			orientation1 = orientation_of_triplet(start, end, segment.start);
			orientation2 = orientation_of_triplet(start, end, segment.end);
			orientation3 = orientation_of_triplet(segment.start, segment.end, start);
			orientation4 = orientation_of_triplet(segment.start, segment.end, end);
			if (orientation1 != orientation2 && orientation3 != orientation4) {
				return true;
			}
			if (does_lie_on(segment.start) || does_lie_on(segment.end)) {
				return true;
			}
			if (segment.does_lie_on(start) || segment.does_lie_on(end)) {
				return true;
			}
			return false;
		}

		Segment2D segment_intersection(const Segment2D& segment) const {
			if (does_lie_on(segment.start) && does_lie_on(segment.end)) {
				return segment;
			}
			if (does_lie_on(segment.start)) {
				return Segment2D(segment.start, end);
			}
			if (does_lie_on(segment.end)) {
				return Segment2D(segment.end, end);
			}
			return *this;
		}
		Point2D point_intersection(const Segment2D& segment) const {
			if (!do_intersect(segment)) {
				throw std::invalid_argument("Segments do not intersect");
			}
			double den = segment.a * b - a * segment.b;
			if (den == 0) {
				if (start == segment.start) {
					if (!vector.are_co_directional(segment.vector)) {
						return start;
					}
					else {
						throw std::invalid_argument("Segments intersect by a segment");
					}
				}
				if (start == segment.end) {
					if (!vector.are_co_directional(-segment.vector)) {
						return start;
					}
					else {
						throw std::invalid_argument("Segments intersect by a segment");
					}

				}
				if (segment.start == end) {
					if (segment.vector.are_co_directional(-vector)) {
						return end;
					}
					else {
						throw std::invalid_argument("Segments intersect by a segment");
					}
				}
				if (segment.end == end) {
					if ((-segment.vector).are_co_directional(-vector)) {
						return end;
					}
					else {
						throw std::invalid_argument("Segments intersect by a segment");
					}
				}
				throw std::invalid_argument("Segments intersect by a segment");
			}
			double x = (segment.b * c - b * segment.c) / den;
			double y = (segment.c * a - c * segment.a) / den;
			return Point2D(x, y);
		}
	};

	std::ostream& operator<<(std::ostream& stream, const Segment2D& segment) {
		return (stream << "[" << segment.start << "; " << segment.end << "]");
	}

	class Line2D {
	public:
		Point2D point;
		Vector2D vector;
		double a, b, c;

		Line2D() : point(), vector(0, 1), a(1), b(0), c(0) {};
		Line2D(const Point2D& point1, const Point2D& point2) : point(point1), vector(point1, point2) {
			a = point2.y - point1.y;
			b = point1.x - point2.x;
			c = point2.x * point1.y - point1.x * point2.y;
		}
		Line2D(const Point2D& point, const Vector2D& vector) : point(point), vector(vector) {
			a = vector.y;
			b = -vector.x;
			c = vector.x * point.y - vector.y * point.x;
		}
		Line2D(const Segment2D& segment) : Line2D(segment.start, segment.end) {};
		Line2D(double a, double b, double c) {
			(*this).a = a;
			(*this).b = b;
			(*this).c = c;
			if (a == 0) {
				point.x = 0;
				point.y = -c / b;
			}
			else {
				point.y = 0;
				point.x = -c / a;
			}
			vector.x = -b;
			vector.y = a;
		}

		bool operator==(const Line2D& line) const {
			if (!vector.are_collinear(line.vector)) {
				return false;
			}
			return vector.are_collinear(Vector2D(point, line.point));
		}
		bool are_collinear(const Line2D& line) const {
			return vector.are_collinear(line.vector);
		}
		bool are_parallel(const Line2D& line) const {
			if (!vector.are_collinear(line.vector)) {
				return false;
			}
			return !vector.are_collinear(Vector2D(point, line.point));
		}
		bool are_perpendicular(const Line2D& line) const {
			return vector.are_orthogonal(line.vector);
		}

		double angle(const Line2D& line) const {
			double res = vector.angle(line.vector);
			return (res - PI / 2 < 0) ? res : PI - res;
		}
		Point2D intersection(const Line2D& line) const {
			if (vector.are_collinear(line.vector)) {
				throw std::invalid_argument("Intersection is undefined: lines are collinear");
			}
			/*Point2D A = add_vector_to_point(point, vector), B = add_vector_to_point(line.point, line.vector);
			double den = (point.x - A.x) * (line.point.y - B.y) - (point.y - A.y) * (line.point.x - B.x);
			double var1 = point.x * A.y - point.y * A.x;
			double var2 = line.point.x * B.y - line.point.y * B.x;
			double x = (var1 * (line.point.x - B.x) - var2 * (point.x - A.x)) / den;
			double y = (var1 * (line.point.y - B.y) - var2 * (point.y - A.y)) / den;
			return Point2D(x, y);*/
			double den = line.a * b - a * line.b;
			double x = (line.b * c - b * line.c) / den;
			double y = (line.c * a - c * line.a) / den;
			return Point2D(x, y);
		}

		bool do_intersect(const Segment2D& segment) const {
			if (vector.are_collinear(segment.vector)) {
				return are_points_collinear(point, segment.start, segment.end);
			}
			return segment.does_lie_on(intersection(Line2D(segment)));
		}
		Point2D intersection(const Segment2D& segment) const {
			if (vector.are_collinear(segment.vector)) {
				if (are_points_collinear(point, segment.start, segment.end)) {
					throw std::invalid_argument("Intersection is a segment");
				}
				throw std::invalid_argument("Line is parallel to segment");
			}
			
			Point2D intersect = intersection(Line2D(segment));
			if (!segment.does_lie_on(intersect)) {
				throw std::invalid_argument("Line and segment don't intersect");
			}
			return intersect;
		}

		double distance(const Point2D& point) const {
			return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
		}
		double distance(const Line2D& line) const {
			if (!are_collinear(line)) {
				throw std::invalid_argument("Distance is undefined");
			}
			return line.distance(point);
		}
		double distance(const Segment2D& segment) const {
			if (do_intersect(segment)) {
				throw std::invalid_argument("Line and segment intersect - distance is undefined");
			}
			return std::min(distance(segment.start), distance(segment.end));
		}
		Vector2D normal_vector() const {
			return Vector2D(a, b);
		}

		bool does_lie_on(const Point2D& point) const {
			return a * point.x + b * point.y + c == 0;
		}
	};

	Point2D project_on_line(const Point2D& point, const Line2D& line) {
		return line.intersection(Line2D(point, line.normal_vector()));
	}
	Vector2D project_on_line(const Vector2D& vector, const Line2D& line) {
		return (line.vector.normalized()) * (vector.dot(line.vector) / line.vector.length());
	}

	class Ray2D {
	public:
		Point2D start;
		Vector2D vector;
		double a, b, c;

		Ray2D() : start(), vector(0, 1), a(1), b(0), c(0) {};
		Ray2D(const Point2D& start, const Vector2D& vector) : start(start), vector(vector) {
			a = vector.y;
			b = -vector.x;
			c = vector.x * start.y - vector.y * start.x;
		}
		Ray2D(const Point2D& start, const Point2D& point) : start(start), vector(start, point) {
			a = point.y - start.y;
			b = start.x - point.x;
			c = point.x * start.y - start.x * point.y;
		}

		bool operator==(const Ray2D& ray) const {
			return start == ray.start && vector.are_co_directional(ray.vector);
		}
		bool are_collinear(const Ray2D& ray) const {
			return vector.are_collinear(ray.vector);
		}
		bool are_perpendicular(const Ray2D& ray) const {
			return vector.are_orthogonal(ray.vector);
		}

		double angle(const Ray2D& ray) const {
			return vector.angle(ray.vector);
		}
		double oriented_angle(const Ray2D& ray) const {
			return vector.oriented_angle(ray.vector);
		}

		bool does_lie_on(const Point2D& point) const {
			return vector.are_co_directional(Vector2D(start, point));
		}

		double distance(const Point2D& point) const {
			Vector2D start_to_point(start, point);
			if (vector.dot(start_to_point) < 0) {
				return start_to_point.length();
			}
			return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
		}
		double distance(const Ray2D& ray) const {
			if (vector.are_co_directional(ray.vector)) {
				if (vector.are_collinear(Vector2D(start, ray.start))) {
					throw std::invalid_argument("Rays intersect: distance is undefined");
				}
				return std::abs(a * ray.start.x + b * ray.start.y + c) / std::sqrt(a * a + b * b);
			}
			if (vector.are_collinear(ray.vector)) { // anti_directional
				Vector2D start_to_start(start, ray.start);
				if (vector.dot(start_to_start) < 0) {
					return start_to_start.length();
				}
				if (does_lie_on(ray.start)) {
					throw std::invalid_argument("Rays intersect : distance is undefined");
				}
				return std::abs(a * ray.start.x + b * ray.start.y + c) / std::sqrt(a * a + b * b);
			}
			Point2D intersect = Line2D(start, vector).intersection(Line2D(ray.start, ray.vector));
			if (does_lie_on(intersect) && ray.does_lie_on(intersect)) {
				throw std::invalid_argument("Rays intersect: distance is undefined");
			}

			Vector2D start_to_start(start, ray.start);
			if (vector.dot(start_to_start) < 0) {
				if (ray.vector.dot(-start_to_start) < 0) {
					return start_to_start.length();
				}
				return std::abs(a * ray.start.x + b * ray.start.y + c) / std::sqrt(a * a + b * b);
			}
			if (ray.vector.dot(-start_to_start) < 0) {
				return std::abs(ray.a * start.x + ray.b * start.y + ray.c) / std::sqrt(ray.a * ray.a + ray.b * ray.b);
			}
			return std::min(std::abs(ray.a * start.x + ray.b * start.y + ray.c) / std::sqrt(ray.a * ray.a + ray.b * ray.b),
				std::abs(a * ray.start.x + b * ray.start.y + c) / std::sqrt(a * a + b * b));

		}
		double distance(const Segment2D& segment) const {
			if (vector.are_co_directional(segment.vector)) {
				Vector2D end_to_start(segment.end, start);
				if (segment.vector.dot(end_to_start) > 0) {
					return end_to_start.length();
				}
				return std::abs(a * segment.start.x + b * segment.start.y + c) / std::sqrt(a * a + b * b);
			}
			if (vector.are_collinear(segment.vector)) { // anti-directional
				Vector2D start_to_start(segment.start, start);
				if (segment.vector.dot(start_to_start) < 0) {
					return start_to_start.length();
				}
				return std::abs(a * segment.start.x + b * segment.start.y + c) / std::sqrt(a * a + b * b);
			}

		}
		bool do_intersect(const Ray2D& ray) const {
			if (vector.are_co_directional(ray.vector)) {
				return vector.are_collinear(Vector2D(start, ray.start));
			}
			if (vector.are_collinear(ray.vector)) { // anti_directional
				if (!vector.are_collinear(Vector2D(start, ray.start))) {
					return false;
				}
				return does_lie_on(ray.start);
			}

			Point2D intersect = Line2D(start, vector).intersection(Line2D(ray.start, ray.vector));
			return does_lie_on(intersect) && ray.does_lie_on(intersect);
		}
		bool do_intersect(const Segment2D& segment) const {

		}

		Point2D intersection(const Line2D& line) const {

		}
		Point2D point_intersection(const Ray2D& ray) const {

		}
		Segment2D segment_intersection(const Ray2D& ray) const {

		}
		Point2D point_intersection(const Segment2D& segment) const {

		}
		Segment2D segment_intersection(const Segment2D& segment) const {

		}
	};

	class Shape {
		virtual double perimeter() const = 0;
		virtual double area() const = 0;
		virtual bool operator==(const Shape& shape) const = 0;
		virtual bool isCongruentTo(const Shape& shape) const = 0;
		virtual bool isSimilarTo(const Shape& shape) const = 0;
		virtual bool containsPoint(const Shape& shape) const = 0;
		virtual void rotate(const Point2D& point, double angle) const = 0;
		virtual void reflect(const Point2D& point) const = 0;
		virtual void reflect(const Line2D& line) const = 0;
		virtual void scale(const Point2D& point, double coefficient) const = 0;
	};

	class Polygon : public Shape {
	private:
		std::vector <Point2D> vertices;

		Polygon(const Point2D& point1, const Point2D& point2, const Point2D& point3, std::initializer_list <Point2D> points_list) {
			vertices.push_back(point1);
			vertices.push_back(point2);
			vertices.insert(vertices.end(), points_list);
		}
		/*template <typename... Points>
		Polygon(Points... points) {

		}*/
	public:
		Polygon(const std::vector <Point2D>& vertices) : vertices(vertices) {};
		//Polygon(std::initializer_list <Point2D> point_list) : vertices(point_list) {};

		template <typename... Points>
		Polygon(const Point2D& point1, const Point2D& point2, const Point2D& point3, Points... points) {

		}
		Polygon(std::initializer_list <Point2D> points_list) {
			vertices = points_list;
		}

		std::vector <Point2D> getVertices() const {
			return vertices;
		}

		int verticesCount() const {
			return vertices.size();
		}

		bool isConvex() const {
			if (vertices.size() == 3) {
				return true;
			}
			Vector2D first(vertices[0], vertices[1]);
			Vector2D second(vertices[1], vertices[2]);
			bool right = (first.cross(second)) > 0;
			first = second;
			for (int i = 3; i < vertices.size(); i++) {
				second = Vector2D(vertices[i - 1], vertices[i]);
				if (right != (first.cross(second) > 0)) {
					return false;
				}
				first = second;
			}
			second = Vector2D(vertices[vertices.size() - 1], vertices[0]);
			if (right != (first.cross(second) > 0)) {
				return false;
			}
			first = second;

			second = Vector2D(vertices[0], vertices[1]);
			if (right != (first.cross(second) > 0)) {
				return false;
			}
			return true;
		}

		virtual double perimeter() const override {
			double res = vertices[vertices.size() - 1].distance(vertices[0]);
			for (int i = 1; i < vertices.size(); i++) {
				res += vertices[i - 1].distance(vertices[i]);
			}
			return res;
		}

		virtual double area() const override {
			return 0;
		}

		virtual bool operator==(const Shape& shape) const override {
			return 0;
		}

		virtual bool containsPoint(const Shape& shape) const override {
			return 0;
		}

		virtual bool isCongruentTo(const Shape& shape) const override {
			return 0;
		}

		virtual bool isSimilarTo(const Shape& shape) const override {
			return 0;
		}

		virtual void rotate(const Point2D& point, double angle) const override {

		}

		virtual void reflect(const Point2D& point) const override {

		}

		virtual void reflect(const Line2D& line) const override {

		}

		virtual void scale(const Point2D& point, double coefficient) const override {

		}
	};

	class Rectangle : public Polygon {

	};

	class Square : public Rectangle {

	};

	class Ellipse : public Shape {

	};

	class Circle : public Ellipse {

	};

	class Triangle : public Polygon {

	};
}
