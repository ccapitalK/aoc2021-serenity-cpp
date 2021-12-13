#include <AK/Format.h>
#include <AK/QuickSort.h>
#include <AK/Tuple.h>
#include <AK/Queue.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

Vector<Vector<int>> heights;

struct Point {
    int x;
    int y;
};

struct PointTraits {
    static bool equals(Point a, Point b) { return a.x == b.x && a.y == b.y; }
    static unsigned hash(Point p) {
        return (p.x * p.y) ^ (p.x + p.y);
    }
};


size_t basinSize(int sx, int sy) {
    HashTable<Point, PointTraits> seen;
    Queue<Point> q;
    q.enqueue({sx, sy});
    while (!q.is_empty()) {
        auto [x, y] = q.dequeue();
        if (seen.contains({x, y})) continue;
        seen.set({x, y});
        for(int cx = x - 1; cx < x + 2; ++cx) {
            for(int cy = y - 1; cy < y + 2; ++cy) {
                if ((x != cx) == (y != cy)) continue;
                if (cx < 0 || cx >= heights[0].size()) continue;
                if (cy < 0 || cy >= heights.size()) continue;
                if (heights[cy][cx] != 9) q.enqueue({cx, cy});
            }
        }
    }
    return seen.size();
}

ErrorOr<int> serenity_main(Main::Arguments)
{
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    for (auto line: file->lines()) {
        Vector<int> heightLine;
        for (auto c: line) heightLine.append(c - '0');
        if (heights.size()) VERIFY(heightLine.size() == heights[0].size());
        heights.append(move(heightLine));
    }
    VERIFY(heights.size() > 0 && heights[0].size() > 0);
    int p1ans{}, p2ans = 1;
    Vector<u64> basinSizes;
    for (int y = 0; y < heights.size(); ++y) {
        for (int x = 0; x < heights[0].size(); ++x) {
            bool isLow{true};
            for(int cx = x - 1; cx < x + 2; ++cx) {
                for(int cy = y - 1; cy < y + 2; ++cy) {
                    if ((x != cx) == (y != cy)) continue;
                    if (cx < 0 || cx >= heights[0].size()) continue;
                    if (cy < 0 || cy >= heights.size()) continue;
                    if (heights[cy][cx] <= heights[y][x]) isLow = false;
                }
            }
            if (isLow) {
                p1ans += 1 + heights[y][x];
                basinSizes.append(basinSize(x, y));
            }
        }
    }
    quick_sort(basinSizes.begin(), basinSizes.end());
    VERIFY(basinSizes.size() >= 3);
    for (int i = 0; i < 3; ++i) p2ans *= basinSizes[basinSizes.size()-i-1];
    outln("Part 1: {}", p1ans);
    outln("Part 2: {}", p2ans);
    return 0;
}
