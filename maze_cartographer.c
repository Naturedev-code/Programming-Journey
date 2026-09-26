/* Maze Cartographer: iterative maze carving and breadth-first treasure search. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

#define MAX_SIDE 30
#define MAX_CELLS (MAX_SIDE * MAX_SIDE)
#define CANVAS (2 * MAX_SIDE + 1)

static const int dx[4] = {0, 1, 0, -1};
static const int dy[4] = {-1, 0, 1, 0};
static char map[CANVAS][CANVAS];

/* Explicit 32-bit arithmetic makes a seed reproducible across platforms. */
static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static int parse_number(const char *text, uint32_t limit, uint32_t *value)
{
    uint32_t number = 0;
    if (*text == '\0') return 0;
    for (; *text; ++text) {
        uint32_t digit;
        if (*text < '0' || *text > '9') return 0;
        digit = (uint32_t)(*text - '0');
        if (number > limit / 10 ||
            (number == limit / 10 && digit > limit % 10)) return 0;
        number = number * 10 + digit;
    }
    *value = number;
    return 1;
}

static void carve(int width, int height, uint32_t seed)
{
    int seen[MAX_CELLS] = {0};
    int stack[MAX_CELLS];
    int depth = 1;
    memset(map, '#', sizeof(map));
    stack[0] = 0;
    seen[0] = 1;
    map[1][1] = ' ';

    /* The explicit stack avoids recursive call-stack limits. */
    while (depth > 0) {
        int current = stack[depth - 1];
        int x = current % width, y = current / width;
        int choices[4], count = 0;
        for (int direction = 0; direction < 4; ++direction) {
            int nx = x + dx[direction], ny = y + dy[direction];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                !seen[ny * width + nx]) choices[count++] = direction;
        }
        if (count == 0) {
            --depth;
        } else {
            int direction = choices[(next_random(&seed) >> 16) % (uint32_t)count];
            int nx = x + dx[direction], ny = y + dy[direction];
            int next = ny * width + nx;
            map[2 * y + 1 + dy[direction]][2 * x + 1 + dx[direction]] = ' ';
            map[2 * ny + 1][2 * nx + 1] = ' ';
            seen[next] = 1;
            stack[depth++] = next;
        }
    }
}

/* Return the farthest room; parents also encode its shortest route. */
static int find_treasure(int width, int height, int *parents, int *distance)
{
    int queue[MAX_CELLS], head = 0, tail = 1;
    for (int i = 0; i < width * height; ++i) parents[i] = -1;
    queue[0] = 0;
    parents[0] = 0;
    distance[0] = 0;
    while (head < tail) {
        int current = queue[head++];
        int x = current % width, y = current / width;
        for (int direction = 0; direction < 4; ++direction) {
            int nx = x + dx[direction], ny = y + dy[direction];
            int next;
            if (nx < 0 || nx >= width || ny < 0 || ny >= height) continue;
            next = ny * width + nx;
            if (parents[next] != -1 ||
                map[2 * y + 1 + dy[direction]][2 * x + 1 + dx[direction]] == '#')
                continue;
            parents[next] = current;
            distance[next] = distance[current] + 1;
            queue[tail++] = next;
        }
    }
    return queue[tail - 1];
}

int main(int argc, char **argv)
{
    uint32_t width = 12, height = 8, seed = (uint32_t)time(NULL);
    int solve = 0;
    int parents[MAX_CELLS], distance[MAX_CELLS];
    int treasure;
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s [width height seed [--solve]]\n", argv[0]);
        puts("Width and height: 2..30. Seed: 0..4294967295. Defaults: 12 x 8, current time.");
        return 0;
    }
    if (argc != 1) {
        if ((argc != 4 && argc != 5) ||
            !parse_number(argv[1], MAX_SIDE, &width) || width < 2 ||
            !parse_number(argv[2], MAX_SIDE, &height) || height < 2 ||
            !parse_number(argv[3], UINT32_MAX, &seed) ||
            (argc == 5 && strcmp(argv[4], "--solve") != 0)) {
            fprintf(stderr, "Usage: %s [width height seed [--solve]]\n"
                    "Dimensions must be 2..30; seed must be 0..4294967295.\n", argv[0]);
            return 1;
        }
        solve = argc == 5;
    }
    carve((int)width, (int)height, seed);
    treasure = find_treasure((int)width, (int)height, parents, distance);
    if (solve) {
        for (int current = treasure; current != 0; current = parents[current]) {
            int previous = parents[current];
            int x = current % (int)width, y = current / (int)width;
            int px = previous % (int)width, py = previous / (int)width;
            map[2 * y + 1][2 * x + 1] = '.';
            map[y + py + 1][x + px + 1] = '.';
        }
    }
    map[1][1] = 'S';
    map[2 * (treasure / (int)width) + 1][2 * (treasure % (int)width) + 1] = 'T';
    printf("Maze Cartographer | %" PRIu32 " x %" PRIu32 " | seed %" PRIu32 "\n",
           width, height, seed);
    puts("S = start, T = treasure, # = wall, . = solution");
    for (int y = 0; y < 2 * (int)height + 1; ++y) {
        for (int x = 0; x < 2 * (int)width + 1; ++x) putchar(map[y][x]);
        putchar('\n');
    }
    printf("Treasure is %d room steps away (the farthest room from S).\n", distance[treasure]);
    if (!solve) puts("Replay with the same dimensions and seed plus --solve to reveal the route.");
    return 0;
}
