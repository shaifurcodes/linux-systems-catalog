
#include <gtest/gtest.h>
extern "C" {
#include "p06_device_registry.h"
}
static int probe_called = 0;
static void my_probe(uint32_t d) { probe_called++; }
static void my_remove(uint32_t d) {}
TEST(DevReg, RegisterLookup) {
    DeviceRegistry r; dr_init(&r); probe_called=0;
    ASSERT_EQ(dr_register(&r, 1, 42, "eth0", my_probe, my_remove), 0);
    EXPECT_EQ(probe_called, 1);
    auto *e = dr_lookup(&r, 1, 42);
    ASSERT_NE(e, nullptr);
    EXPECT_STREQ(e->name, "eth0");
}
TEST(DevReg, RemoveCallback) {
    DeviceRegistry r; dr_init(&r);
    dr_register(&r, 0, 1, "usb0", my_probe, my_remove);
    EXPECT_EQ(dr_remove(&r, 0, 1), 0);
    EXPECT_EQ(dr_lookup(&r, 0, 1), nullptr);
    EXPECT_EQ(dr_count_active(&r), 0);
}
