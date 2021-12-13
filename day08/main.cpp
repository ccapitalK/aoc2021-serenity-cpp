#include <AK/Format.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

u64 countBits(u64 v) {
    return __builtin_popcount(v);
}

constexpr u64 conv(StringView enabled) {
    u64 rv{};
    for (auto c: enabled) {
        if (c < 'a' || c > 'z') continue;
        rv |= 1ull << (c - 'a');
    }
    return rv;
}

HashMap<u64, u64> solve(const Vector<StringView> &table) {
    HashTable<u64> unsolved{};
    u64 bit_lut[10], digit_lut[10];
    HashMap<u64, u64> map{};

    VERIFY(table.size() == 10);
    auto registerSolve = [&](u64 bits, u64 digit) {
        map.set(bits, digit);
        digit_lut[digit] = bits;
    };
    for (auto i = 0; i < 10; ++i) {
        bit_lut[i] = conv(table[i]);
        switch (table[i].length()) {
        case 2: registerSolve(bit_lut[i], 1); break;
        case 3: registerSolve(bit_lut[i], 7); break;
        case 4: registerSolve(bit_lut[i], 4); break;
        case 7: registerSolve(bit_lut[i], 8); break;
        default: unsolved.set(bit_lut[i]); break;
        }
    }

    for (auto v: unsolved) {
        if (countBits(v) == 5) {
            if ((v & digit_lut[1]) == digit_lut[1]) {
                registerSolve(v, 3);
            } else if (countBits(v ^ digit_lut[4]) == 3) {
                registerSolve(v, 5);
            } else {
                registerSolve(v, 2);
            }
        } else {
            if ((v & digit_lut[1]) != digit_lut[1]) {
                registerSolve(v, 6);
            } else if ((v & digit_lut[4]) == digit_lut[4]) {
                registerSolve(v, 9);
            } else {
                registerSolve(v, 0);
            }
        }
    }

    VERIFY(map.size() == 10);
    return map;
}

bool is1478(StringView label) {
    switch (label.length()) {
    case 2: case 3: case 4: case 7:
        return true;
    default:
        return false;
    }
}

ErrorOr<int> serenity_main(Main::Arguments)
{
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    u64 ans1{}, ans2{};
    for (auto line: file->lines()) {
        auto parts = line.split_view("|");
        auto map = solve(parts[0].split_view(" "));
        u64 decoded{};
        for (auto v: parts[1].split_view(" ")) {
            ans1 += is1478(v);
            decoded = 10 * decoded + map.find(conv(v))->value;
        }
        ans2 += decoded;
    }
    outln("Part 1: {}", ans1);
    outln("Part 2: {}", ans2);
    return 0;
}
