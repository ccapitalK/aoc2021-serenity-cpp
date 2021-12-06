#include <AK/Format.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments)
{
    Array<u64, 9> byTimeLeft{};
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    auto line = file->read_line().split(',');
    for (auto fish: line) {
        auto daysLeft = fish.to_uint().value();
        ++byTimeLeft[daysLeft % 8];
    }
    u64 p1ans = 0, p2ans = 0;
    for (auto i = 0; i < 256; ++i) {
        if (i == 80) for (auto v: byTimeLeft) p1ans += v;
        auto numSpawning = byTimeLeft[0];
        for (auto j = 0; j < 8; ++j) {
            byTimeLeft[j] = byTimeLeft[j + 1];
        }
        byTimeLeft[8] = numSpawning;
        byTimeLeft[6] += numSpawning;
    }
    for (auto v: byTimeLeft) p2ans += v;
    outln("Part 1: {}", p1ans);
    outln("Part 2: {}", p2ans);
    return 0;
}
