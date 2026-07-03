#include <gtest/gtest.h>
extern "C" {
#include "p14_uevent_filter.h"
}

TEST(p14_uevent_filter, Match) { UeventFilter f; uf_init(&f); uf_add_rule(&f,"SUBSYSTEM","block"); const char *ev="SUBSYSTEM=block\0ACTION=add\0"; EXPECT_TRUE(uf_matches(&f,ev,32)); }

TEST(p14_uevent_filter, NoMatch) { UeventFilter f; uf_init(&f); uf_add_rule(&f,"SUBSYSTEM","net"); const char *ev="SUBSYSTEM=block\0"; EXPECT_FALSE(uf_matches(&f,ev,16)); }
