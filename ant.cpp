#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point {
public:
	int id = -1;
	int x = INT_MAX;
	int y = INT_MAX;

	Point(){}
	Point(int x, int y) : x(x), y(y) {};
	Point(int x, int y, int id) : x(x), y(y), id(id) {};

	Point operator -(const Point& p) {
		return Point(x - p.x, y - p.y);
	}

	Point& operator -=(const Point& p) {
		x -= p.x;
		y -= p.y;

		return *this;
	}

	friend ostream& operator<<(ostream& o, const Point& p) {
		o << "(" << p.x << ", " << p.y << ")";

		return o;
	}
};

int crossProduct(Point p, Point q) {
	return p.x * q.y - p.y * q.x;
}

int distance(Point p, Point q) {
	return pow(p.x + q.x, 2) + pow(p.y + q.y, 2);
}

Point* vertices;
Point* antennas;
pair<int, int>* queries;
int w, m, q;
int x, y;

void load() {
	cin >> w;
	vertices = new Point[w];

	for (int i = 0; i < w; i++) {
		cin >> x >> y;
		vertices[i] = Point(x, y);
	}

	cin >> m;
	antennas = new Point[m];

	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		antennas[i] = Point(x, y);
	}

	cin >> q;
	queries = new pair<int, int>[q];

	for (int i = 0; i < q; i++) {
		cin >> x >> y;
		queries[i] = make_pair(x, y);
	}
}

void reset() {
	w = 0, m = 0, q = 0;
	x = 0, y = 0;

	delete[] vertices, antennas, queries;
}

vector<Point> getPointsBelowSegment(Point A, Point B) {
	vector<Point> result;
	Point vector = A - B;

	for (int i = 0; i < m; i++) {
		if (crossProduct(vector, antennas[i] - B) > 0) {
			result.push_back(antennas[i]);
			result.back().id = result.size() - 1;
		}
	}

	return result;
}

vector<Point> sortPointsByAngle(vector<Point> points, Point A) {
	sort(points.begin(), points.end(), [&](Point p, Point q) {
		int cross_product = crossProduct(p - A, q - A);

		if (cross_product > 0) {
			return true;
		}
		else if (cross_product < 0) {
			return false;
		}
		else {
			return distance(p, A) < distance(q, A);
		}
	});

	return points;
}

vector<int> convertToPointsIdList(vector<Point> points) {
	vector<int> result(points.size());

	for (int i = 0; i < points.size(); i++) {
		result[i] = points[i].id;
	}

	return result;
}

int merge(vector<int>& arr, int left, int mid, int right) {
	int inversions = 0;

	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		}
		else {
			arr[k++] = R[j++];
			inversions += (mid - i - left + 1);
		}
	}

	while (i < n1) {
		arr[k++] = L[i++];
	}

	while (j < n2) {
		arr[k++] = R[j++];
	}

	return inversions;
}

int mergeSort(vector<int>& arr, int left, int right) {
	int inversions = 0;

	if (left < right) {
		int mid = left + (right - left) / 2;

		inversions += mergeSort(arr, left, mid);
		inversions += mergeSort(arr, mid + 1, right);
		inversions += merge(arr, left, mid, right);
	}

	return inversions;
}

int countInversions(vector<int> l1, vector<int> l2, int n) {
	vector<int> p(n);
	vector<int> t(n);

	for (int i = 0; i < n; i++) {
		p[l1[i]] = i;
	}

	for (int i = 0; i < n; i++) {
		t[i] = p[l2[i]];
	}

	return n * (n - 1) / 2 - mergeSort(t, 0, n - 1);
}

int countHalfLineIntersectionWithSegment(Point A, Point B) {
	vector<Point> points = getPointsBelowSegment(A, B);

	vector<Point> o1 = sortPointsByAngle(points, A);
	vector<Point> o2 = sortPointsByAngle(points, B);

	vector<int> l1 = convertToPointsIdList(o1);
	vector<int> l2 = convertToPointsIdList(o2);

	return countInversions(l1, l2, points.size());
}

void init() {
	int a, b;
	int next_a, next_b;
	int result;

	for (int i = 0; i < q; i++) {
		result = 0;
		a = queries[i].first;
		b = queries[i].second;
		next_a = a + 1;
		next_b = (b + 1) % w;

		if (a + 1 == b) {
			result -= countHalfLineIntersectionWithSegment(vertices[a], vertices[b]);
			result -= countHalfLineIntersectionWithSegment(vertices[b], vertices[next_b]);
			result += countHalfLineIntersectionWithSegment(vertices[a], vertices[next_b]);
			result +=  m * (m - 1) / 2;
		}
		else {
			result += countHalfLineIntersectionWithSegment(vertices[next_a], vertices[b]);
			result -= countHalfLineIntersectionWithSegment(vertices[a], vertices[b]);
			result -= countHalfLineIntersectionWithSegment(vertices[next_a], vertices[next_b]);
			result += countHalfLineIntersectionWithSegment(vertices[a], vertices[next_b]);
		}


		cout << result << " ";
	}

	cout << endl;
}

void test() {
	load();
	init();
	reset();
}

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		test();
	}

	return 0;
}