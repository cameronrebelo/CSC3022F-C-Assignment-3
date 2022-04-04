#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"

TEST_CASE("Accessor Checks for PGMimageProcessor") {
	RBLCAM001::PGMimageProcessor p ("test.pgm"); 	
	SECTION("RETURN VALUE") {
		const auto count = p.getComponentCount();
		REQUIRE(is_close(count, 0));
        REQUIRE(is_close(p.getLargestSize, 0));
        REQUIRE(is_close(p.getSmallestSize, 0));
	}

}
TEST_CASE("Accessor Checks for ConnectedComponent") {
	RBLCAM001::ConnectedComponent c (3); 	
	SECTION("RETURN VALUE") {
		const auto ID = c.getID();
        const auto pNum = c.getPixelNum();
        const auto px = c.getPixels();
		REQUIRE(is_close(ID, 3));
        REQUIRE(is_close(pNum, 0));
        REQUIRE(is_close(px, nullptr));
	}
}
