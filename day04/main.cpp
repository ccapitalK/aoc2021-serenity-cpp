#include <AK/Format.h>
#include <LibCore/File.h>
#include <LibCore/System.h>
#include <LibMain/Main.h>

Vector<String> order;

i64 calcAnswer(Vector<StringView> const &squares, Array<Array<bool, 5>, 5> const &seen, StringView lastCall) {
    i64 ans = 0;
    for (size_t x = 0; x < 5; ++x) {
        for (size_t y = 0; y < 5; ++y) {
            if (!seen[x][y]) ans += squares[x + 5 * y].to_int().value();
        }
    }
    return ans * lastCall.to_int().value();
}

size_t solveBingo(Vector<StringView> const &squares, i64 &outAnswer) {
    // I can't be bothered optimizing this, the code you see is the code you get
    VERIFY(squares.size() == 25);
    Array<Array<bool, 5>, 5> seen{};
    for (size_t i = 0; i < order.size(); ++i) {
        // Mark as seen
        for (auto j = 0; j < squares.size(); ++j) {
            if (squares[j] == order[i]) seen[j%5][j/5] = true;
        }
        // Check for bingo (rows and cols)
        for (auto v1 = 0; v1 < 5; ++v1) {
            bool fullRow = true, fullCol = true;
            for (auto v2 = 0; v2 < 5; ++v2) {
                fullRow &= seen[v1][v2];
                fullCol &= seen[v2][v1];
            }
            if (fullRow || fullCol) {
                outAnswer = calcAnswer(squares, seen, order[i]);
                return i;
            }
        }
        bool fullMajor = true, fullMinor = true;
        for (auto v = 0; v < 5; ++v) {
            fullMajor &= seen[v][v];
            fullMinor &= seen[v][4-v];
        }
        if (fullMinor || fullMajor) {
            outAnswer = calcAnswer(squares, seen, order[i]);
            return i;
        }
    }
    return 99999999;
}

ErrorOr<int> serenity_main(Main::Arguments)
{
    size_t fastestSolve = 9999999;
    size_t slowestSolve = 0;
    i64 p1ans = 0, p2ans = 0;
    // Parse input
    auto file = TRY(Core::File::open("input", Core::OpenMode::ReadOnly));
    order = file->read_line().split(',');
    Vector<i64> order;
    // HACK democratically vot  ed on by SOME members of SerenityOS staff
    auto rest_of_file = String::copy(file->read_all())
        .replace("\n\n", "X", true)
        .replace("\n", " ", true);
    auto boards = rest_of_file.view().split_view("X");
    // Find solution to part 1
    for (auto board: boards) {
        i64 answer;
        outln("Board: {}", board);
        auto numSteps = solveBingo(board.split_view(' '), answer);
        if (numSteps < fastestSolve) {
            fastestSolve = numSteps;
            p1ans = answer;
        }
        if (numSteps > slowestSolve) {
            slowestSolve = numSteps;
            p2ans = answer;
        }
    }
    outln("Part 1: {}", p1ans);
    outln("Part 2: {}", p2ans);
    return 0;
}
