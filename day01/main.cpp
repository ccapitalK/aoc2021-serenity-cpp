#include <AK/Format.h>
#include <AK/StringUtils.h>
#include <AK/Vector.h>
#include <LibCore/System.h>
#include <LibCore/File.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments)
{
    Vector<int> values;
    int p1ans = 0, p2ans = 0;
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    while (file->can_read_line()) {
        auto line = file->read_line();
        auto value = AK::StringUtils::convert_to_uint(line);
        if (!value.has_value()) break;
        values.append(*value);
    }
    for (int i = 1; i < values.size(); ++i) {
        if (values[i] > values[i-1]) ++p1ans;
        if (i >= 3 && values[i] > values[i-3]) ++p2ans;
    }
    outln("Part 1: {}", p1ans);
    outln("Part 2: {}", p2ans);
    return 0;
}
