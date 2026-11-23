#include "unity.h"
#include "ringbuffer.h"

static ringbuf_t rb;

void setUp(void)    { rb.head = 0; rb.tail = 0; }
void tearDown(void) { }

void test_starts_empty(void) {
    char c;
    TEST_ASSERT_EQUAL_INT(0, rb_get(&rb, &c));
}

void test_put_then_get_returns_same_byte(void) {
    char c = 0;
    rb_put(&rb, 'A');
    TEST_ASSERT_EQUAL_INT(1, rb_get(&rb, &c));
    TEST_ASSERT_EQUAL_CHAR('A', c);
}

void test_fifo_order(void) {
    char c;
    rb_put(&rb, 'a'); rb_put(&rb, 'b'); rb_put(&rb, 'c');
    rb_get(&rb, &c); TEST_ASSERT_EQUAL_CHAR('a', c);
    rb_get(&rb, &c); TEST_ASSERT_EQUAL_CHAR('b', c);
    rb_get(&rb, &c); TEST_ASSERT_EQUAL_CHAR('c', c);
    TEST_ASSERT_EQUAL_INT(0, rb_get(&rb, &c));
}

// pins the current behaviour: rb_put drops silently when full
void test_overflow_drops_silently_without_corrupting(void) {
    char c;
    for (int i = 0; i < RB_MAXSIZE - 1; i++) {
        rb_put(&rb, (char)('0' + (i % 10)));
    }
    rb_put(&rb, 'Z');

    for (int i = 0; i < RB_MAXSIZE - 1; i++) {
        TEST_ASSERT_EQUAL_INT(1, rb_get(&rb, &c));
        TEST_ASSERT_EQUAL_CHAR((char)('0' + (i % 10)), c);
    }
    TEST_ASSERT_EQUAL_INT(0, rb_get(&rb, &c)); // Z never made it in
}

void test_wraps_after_drain(void) {
    char c;
    for (int i = 0; i < RB_MAXSIZE - 1; i++) rb_put(&rb, 'x');
    for (int i = 0; i < RB_MAXSIZE - 1; i++) rb_get(&rb, &c);

    rb_put(&rb, 'w');
    TEST_ASSERT_EQUAL_INT(1, rb_get(&rb, &c));
    TEST_ASSERT_EQUAL_CHAR('w', c);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_starts_empty);
    RUN_TEST(test_put_then_get_returns_same_byte);
    RUN_TEST(test_fifo_order);
    RUN_TEST(test_overflow_drops_silently_without_corrupting);
    RUN_TEST(test_wraps_after_drain);
    return UNITY_END();
}