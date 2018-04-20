
#include <catch/catch.hpp>

#define CPPMAT_NOCONVERT
#include <cppmat/cppmat.h>

#include <Eigen/Eigen>

#include <GooseFEM/GooseFEM.h>

#define EQ(a,b) REQUIRE_THAT( (a), Catch::WithinAbs((b), 1.e-12) );

// =================================================================================================

TEST_CASE("GooseFEM::Iterate", "Iterate.h")
{

// =================================================================================================

SECTION( "StopList" )
{
  GooseFEM::Iterate::StopList stop(1.e-3, 5);

  REQUIRE( stop.stop(5.e+0) == false );
  REQUIRE( stop.stop(5.e+1) == false );
  REQUIRE( stop.stop(5.e-1) == false );
  REQUIRE( stop.stop(5.e-2) == false );
  REQUIRE( stop.stop(5.e-3) == false );
  REQUIRE( stop.stop(5.e-4) == false );
  REQUIRE( stop.stop(5.e-4) == false );
  REQUIRE( stop.stop(5.e-4) == false );
  REQUIRE( stop.stop(5.e-4) == false );
  REQUIRE( stop.stop(5.e-4) == true  );
}

// =================================================================================================

}
