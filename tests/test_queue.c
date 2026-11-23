#include "unity.h"
#include "queue.h"

#define CAP 4   // usable depth is 3, one slot is always left empty

static queue_t q;
static uint32_t storage[CAP];

void setUp(void)    { q_init(&q, storage, sizeof(uint32_t), CAP); }
void tearDown(void) { }

void test_init_rejects_non_power_of_two(void) {
    queue_t bad;
    uint32_t buf[3];
    TEST_ASSERT_EQUAL_INT(0, q_init(&bad, buf, sizeof(uint32_t), 3));
}

void test_starts_empty(void) {
    uint32_t out;
    TEST_ASSERT_EQUAL_UINT32(0, q_count(&q));
    TEST_ASSERT_EQUAL_INT(0, q_get(&q, &out));
}

void test_put_then_get_returns_same_value(void) {
    uint32_t in = 0xDEADBEEF, out = 0;
    TEST_ASSERT_EQUAL_INT(1, q_put(&q, &in));
    TEST_ASSERT_EQUAL_UINT32(1, q_count(&q));
    TEST_ASSERT_EQUAL_INT(1, q_get(&q, &out));
    TEST_ASSERT_EQUAL_UINT32(0xDEADBEEF, out);
    TEST_ASSERT_EQUAL_UINT32(0, q_count(&q));
}

void test_fills_to_capacity_minus_one(void) {
    uint32_t v;
    for (uint32_t i = 0; i < CAP - 1; i++) {
        v = i;
        TEST_ASSERT_EQUAL_INT(1, q_put(&q, &v));
    }
    TEST_ASSERT_EQUAL_UINT32(CAP - 1, q_count(&q));
}

void test_put_on_full_is_refused_and_does_not_overwrite(void) {
    uint32_t v, out;
    for (uint32_t i = 0; i < CAP - 1; i++) { v = i; q_put(&q, &v); }

    v = 0xFFFFFFFF;
    TEST_ASSERT_EQUAL_INT(0, q_put(&q, &v));
    TEST_ASSERT_EQUAL_UINT32(CAP - 1, q_count(&q));

    for (uint32_t i = 0; i < CAP - 1; i++) {
        TEST_ASSERT_EQUAL_INT(1, q_get(&q, &out));
        TEST_ASSERT_EQUAL_UINT32(i, out);
    }
}

void test_fill_drain_fill_wraps_correctly(void) {
    uint32_t v, out;

    for (uint32_t i = 0; i < CAP - 1; i++) { v = i; q_put(&q, &v); }
    for (uint32_t i = 0; i < CAP - 1; i++) { q_get(&q, &out); }
    TEST_ASSERT_EQUAL_UINT32(0, q_count(&q));

    // head and tail now sit mid buffer, so this pass crosses the wrap
    for (uint32_t i = 0; i < CAP - 1; i++) {
        v = 100 + i;
        TEST_ASSERT_EQUAL_INT(1, q_put(&q, &v));
    }
    for (uint32_t i = 0; i < CAP - 1; i++) {
        TEST_ASSERT_EQUAL_INT(1, q_get(&q, &out));
        TEST_ASSERT_EQUAL_UINT32(100 + i, out);
    }
}

void test_holds_structs_not_just_scalars(void) {
    typedef struct { uint32_t a; int16_t b, c; } item_t;
    queue_t sq;
    item_t sbuf[CAP];
    item_t in = { 7, -3, 9 }, out = { 0, 0, 0 };

    q_init(&sq, sbuf, sizeof(item_t), CAP);
    TEST_ASSERT_EQUAL_INT(1, q_put(&sq, &in));
    TEST_ASSERT_EQUAL_INT(1, q_get(&sq, &out));
    TEST_ASSERT_EQUAL_UINT32(7, out.a);
    TEST_ASSERT_EQUAL_INT16(-3, out.b);
    TEST_ASSERT_EQUAL_INT16(9, out.c);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_rejects_non_power_of_two);
    RUN_TEST(test_starts_empty);
    RUN_TEST(test_put_then_get_returns_same_value);
    RUN_TEST(test_fills_to_capacity_minus_one);
    RUN_TEST(test_put_on_full_is_refused_and_does_not_overwrite);
    RUN_TEST(test_fill_drain_fill_wraps_correctly);
    RUN_TEST(test_holds_structs_not_just_scalars);
    return UNITY_END();
}