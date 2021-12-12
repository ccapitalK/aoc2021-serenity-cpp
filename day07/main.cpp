#include <AK/Format.h>
#include <AK/QuickSort.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

i64 sdist(auto v) {
    return (v * (v + 1))/2;
}

ErrorOr<int> serenity_main(Main::Arguments)
{
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    auto line = file->read_line();
    Vector<i64> values;
    for (auto part: line.split_view(','))
        values.append(part.to_int().value());
    AK::quick_sort(values.begin(), values.end());
    auto pos = values[values.size()/2];
    i64 fuel_used1{}, fuel_used2 = NumericLimits<i64>::max();
    for (auto v: values) {
        fuel_used1 += abs(v - pos);
    }
    outln("Part 1: {}", fuel_used1);
    for (i64 pos = values[0]; pos < values.last(); ++pos) {
        i64 current_run = 0;
        for (auto v: values) {
            current_run += sdist(abs(v - pos));
        }
        fuel_used2 = min(fuel_used2, current_run);
    }
    outln("Part 2: {}", fuel_used2);
    return 0;
}
