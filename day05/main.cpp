#include <AK/Format.h>
#include <AK/HashTable.h>
#include <AK/Tuple.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

i64 gcd(i64 a, i64 b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    return gcd(b % a, a);
}

struct Point {
    i64 x;
    i64 y;
};

struct PointTraits {
    static constexpr bool equals(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
    static constexpr u32 hash(const Point& p) {
        return ((p.x ^ p.y) + p.x) * p.y;
    }
};

Point parsePoint(StringView s) {
    auto parts = s.split_view(",");
    VERIFY(parts.size() == 2);
    return {parts[0].to_int().value(), parts[1].to_int().value()};
}

ErrorOr<int> serenity_main(Main::Arguments)
{
    HashMap<Point, size_t, PointTraits> counts1, counts2;
    auto incPos = [](decltype(counts1) &counts, Point p) {
        auto it = counts.find(p);
        if (it == counts.end()) {
            counts.set(p, 1);
        } else {
            auto prevCount = it->value;
            counts.remove(it);
            counts.set(p, prevCount + 1);
        }
    };
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    for (auto line: file->lines()) {
        auto parts = line.split_view(" ");
        auto p1 = parsePoint(parts[0]), p2 = parsePoint(parts[2]);
        if (p1.x == p2.x) {
            auto x = p1.x, y1 = min(p1.y, p2.y), y2 = max(p1.y, p2.y);
            for (auto y = y1; y <= y2; ++y) {
                incPos(counts1, {x, y});
                incPos(counts2, {x, y});
            }
        } else if (p1.y == p2.y) {
            auto x1 = min(p1.x, p2.x), x2 = max(p1.x, p2.x), y = p1.y;
            for (auto x = x1; x <= x2; ++x) {
                incPos(counts1, {x, y});
                incPos(counts2, {x, y});
            }
        } else {
            auto dx = p2.x - p1.x, dy = p2.y - p1.y;
            auto numSteps = gcd(abs(dx), abs(dy));
            auto xStep = dx / numSteps;
            auto yStep = dy / numSteps;
            for (size_t i = 0; i <= numSteps; ++i) {
                incPos(counts2, {p1.x+i*xStep, p1.y+i*yStep});
            }
        }
    }
    size_t numIntersections1 = 0, numIntersections2 = 0;
    for (auto [p, c]: counts1) if (c > 1) ++numIntersections1;
    for (auto [p, c]: counts2) if (c > 1) ++numIntersections2;
    outln("Part 1: {}", numIntersections1);
    outln("Part 2: {}", numIntersections2);
    return 0;
}
