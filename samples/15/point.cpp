class Point {
private:
    int x, y;
public:

    Point(int x, int y) : x(x), y(y) {}
    int getX() const { return x; }
    int getY() const { return y; }  
};

class Vector2D {
private:
    int x, y;

public:
    Vector2D() = default;
    Vector2D(int x, int y) : x(x), y(y) {}
    Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}
    Vector2D(const Point& p1, const Point& p2) {
        x = p2.getX() - p1.getX();
        y = p2.getY() - p1.getY();
    }
    int getX() const { return x; }
    int getY() const { return y; }

    Vector2D& operator+= (const Vector2D& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2D& operator-= (const Vector2D& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2D& operator= (const Vector2D& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
};

Vector2D operator+ (const Vector2D& v1, const Vector2D& v2) {
    Vector2D tmp(v1);
    tmp += v2;
    return tmp;
}
Vector2D operator- (const Vector2D& v1, const Vector2D& v2) {
    Vector2D tmp(v1);
    tmp -= v2;
    return tmp;
}

int operator* (const Vector2D& v1, const Vector2D& v2) {
    return v1.getX()*v2.getX() + v1.getY()*v2.getY();
}

bool operator== (const Vector2D& v1, const Vector2D& v2) {
    return v1.getX() == v2.getX() && v1.getY() == v2.getY();
}

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Vector2D v1(p1, p2);
    Vector2D v2(2, 3);
    Vector2D v3;
    v3 = v1+v2; // v3 = operator+(v1, v2);
    v2 += v1; // v2.operator+=(v1);
    return 0;
}
