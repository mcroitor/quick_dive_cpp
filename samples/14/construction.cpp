struct point
{
    int x, y, z;

    point()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    point(const point& pt) {
        x = pt.x;
        y = pt.y;
        z = pt.z;
    }

    point(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    static point createOxPoint(int x)
    {
        point pt;
        pt.x = x;
        return pt;
    }

    static point createOyPoint(int y)
    {
        return point(0, y, 0);
    }

    static point createOzPoint(int z)
    {
        return point(0, 0, z);
    }
};

point pt { point::createOyPoint(5) };
point pt2 { pt };

int main() {
    point p;
    point pt {};
    // point pt1(1); // bad guy
    // point pt2 = point(1); // bad guy
    point pt3 = point();
    // point pt4();
    point pt5(pt);
    point pt6 {1, 2, 3};

    point sample = point::createOxPoint(5);
    point sample2 = pt3.createOyPoint(2);
    return 0;
}