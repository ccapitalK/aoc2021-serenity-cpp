#include <AK/Format.h>
#include <LibCore/System.h>
#include <LibCore/File.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments)
{
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    u64 x = 0, y = 0;
    u64 aim = 0;
    u64 p2y = 0;
    while (file->can_read_line()) {
        auto line = file->read_line();
        auto parts = line.split_view(' ');
        if (parts[0] == "down") {
            u64 val = parts[1].to_uint().value();
            y += val;
            aim += val;
        } else if (parts[0] == "forward") {
            u64 val = parts[1].to_uint().value();
            x += val;
            p2y += aim * val;
        } else {
            u64 val = parts[1].to_uint().value();
            y -= val;
            aim -= val;
        }
    }
    outln("Part 1: {}", x * y);
    outln("Part 2: {}", x * p2y);
    return 0;
}
