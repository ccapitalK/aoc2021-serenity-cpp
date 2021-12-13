#include <AK/Format.h>
#include <AK/QuickSort.h>
#include <AK/Vector.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments)
{
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    Vector<u64> p2scores;
    u64 p1ans{};
    for (auto line: file->lines()) {
        Vector<char> s;
        bool corrupt = false;
        for (auto c: line) {
            auto check_match = [&](char expected, u64 score) {
                if (!s.size() || s.take_last() != expected) {
                    outln("{} {}", expected, score);
                    corrupt = true;
                    p1ans += score;
                }
            };
            switch (c) {
            case '{': case '<': case '[': case '(': s.append(c); break;
            case ')': check_match('(', 3); break;
            case ']': check_match('[', 57); break;
            case '}': check_match('{', 1197); break;
            case '>': check_match('<', 25137); break;
            default: VERIFY(0); break;
            }
            if (corrupt) break;
        }
        if (!corrupt) {
            u64 score = 0;
            for (int i = s.size() - 1; i >= 0; --i) {
                score *= 5;
                switch (s[i]) {
                case '(': score += 1; break;
                case '[': score += 2; break;
                case '{': score += 3; break;
                case '<': score += 4; break;
                default: VERIFY(0); break;
                }
            }
            p2scores.append(score);
        }
    }
    quick_sort(p2scores.begin(), p2scores.end());
    outln("Part 1: {}", p1ans);
    outln("Part 2: {}", p2scores[p2scores.size()/2]);
    return 0;
}
