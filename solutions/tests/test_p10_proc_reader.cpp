
#include <gtest/gtest.h>
extern "C" {
#include "p10_proc_reader.h"
}
static const char *meminfo =
    "MemTotal:      16384000 kB\nMemFree:       8192000 kB\nVmRSS:         1024 kB\n";
TEST(ProcReader, GetField) { EXPECT_EQ(proc_get_field_kb(meminfo, "MemFree"), 8192000); }
TEST(ProcReader, GetBytes) { EXPECT_EQ(proc_get_field_bytes(meminfo, "VmRSS"), 1024*1024); }
TEST(ProcReader, Missing) { EXPECT_EQ(proc_get_field_kb(meminfo, "Nonexistent"), -1); }
TEST(ProcReader, CountFields) { EXPECT_EQ(proc_count_fields(meminfo), 3); }
