
#include <limits.h>
#include <string.h>
#include "file2passwd.hpp"
#include "gtest/gtest.h"

namespace {

TEST(TEST_get_md5_hash_from_file, Trivial) {
	file2passwd fpo("LICENSE");
	const std::string expected_string = "5cbe034c343ead03a139a598a5d27d55";
	const std::string Test_string = fpo.get_md5_hash_from_file();
	EXPECT_EQ(expected_string, Test_string);
}

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
