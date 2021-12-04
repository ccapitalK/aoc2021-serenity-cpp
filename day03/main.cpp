#include <AK/Format.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

u64 calc(Vector<String> input, bool param) {
    for (size_t col = 0; col < input[0].length(); ++col) {
        size_t numOnes = 0;
        for (auto line: input) {
            numOnes += line[col] - '0';
        }
        auto digitValue = '0';
        if (param) {
            // Looking for most common
            digitValue += 2 * numOnes >= input.size();
        } else {
            // Looking for least common
            digitValue += 2 * numOnes < input.size();
        }
        input.remove_all_matching([col, digitValue](String &line) {
            return line[col] != digitValue;
        });
        if (input.size() == 1) break    ;
    }
    return strtoul(input[0].characters(), nullptr, 2);
}

ErrorOr<int> serenity_main(Main::Arguments)
{
    Vector<String> input;
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    int n = 0;
    Vector<size_t> setBitCount;
    while (file->can_read_line()) {
        auto line = file->read_line();
        input.append(line);
        if (line.length() > setBitCount.size()) setBitCount.resize(line.length());
        for (auto i = 0; i < setBitCount.size() ; ++i) {
            setBitCount[i] += line[i] - '0';
        }
        ++n;
    }
    u64 gamma = 0;
    for (auto v: setBitCount) {
        auto currentBit = 0;
        if (v >= n/2) {
            currentBit = 1;
        }
        gamma = (gamma << 1) | currentBit;
    }
    u64 mask = (1 << setBitCount.size()) - 1;
    outln("Part 1: {}", gamma * (mask & ~gamma));
    auto oxygen = calc(input, true);
    auto co2 = calc(input, false);
    outln("Part 2: {}", oxygen * co2);
    return 0;
}
