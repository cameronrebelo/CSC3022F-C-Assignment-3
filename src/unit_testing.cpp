#include "catch.hpp"
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"

TEST_CASE("Postfix Increment", "[PostfixIncrement]") {
	nd_vector_t a = { 1.0, 2.0, 3.0 }; //1A constructor.	
	const auto b = a++;
	SECTION("RETURN VALUE") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	}
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 2.0));
		REQUIRE(is_close(buf[1], 3.0));
		REQUIRE(is_close(buf[2], 4.0));
	}
}