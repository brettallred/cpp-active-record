#include "test_helper.h"
#include <active_record/field.h>

class FieldTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST_F( FieldTest, ReturnsProperties ) {
  Field field( "foo", ActiveRecord::integer );

  ASSERT_STREQ( "foo", field.name().c_str() );
  ASSERT_EQ( ActiveRecord::integer, field.type() );
}

TEST_F( FieldTest, SubtractsAccordingToName ) {
  Field a( "a", ActiveRecord::integer );
  Field b( "b", ActiveRecord::integer );
  Field c( "c", ActiveRecord::integer );
  Field d( "d", ActiveRecord::integer );

  Fields abc;
  abc.push_back( a );
  abc.push_back( b );
  abc.push_back( c );

  Fields cd;
  cd.push_back( c );
  cd.push_back( d );

  Fields ab = abc - cd;

  ASSERT_EQ( 2, ab.size() );
  ASSERT_STREQ( "a", ab[ 0 ].name().c_str() );
  ASSERT_STREQ( "b", ab[ 1 ].name().c_str() );
}
/*
TEST_F( FieldTest, Ostream ) {
  stringstream field_out;
  Field a( "a", ActiveRecord::integer );

  field_out << a;

  assert_string( "", field_out.str() );
}
*/
class FieldsTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST_F( FieldsTest, DoesNotSubtractAccordingToType ) {
  Field i( "a", ActiveRecord::integer );
  Field t( "a", ActiveRecord::text );
  Field f( "a", ActiveRecord::floating_point );

  Fields it;
  it.push_back( i );
  it.push_back( t );

  Fields tf;
  tf.push_back( t );
  tf.push_back( f );

  Fields result = it - tf;

  ASSERT_EQ( 0, result.size() );
}

TEST_F( FieldsTest, FieldsMethodInCtor ) {
  Fields abc( fields
              ( "a", ActiveRecord::integer )
              ( "b", ActiveRecord::text )
              ( "c", ActiveRecord::floating_point )
              ( "d", ActiveRecord::date ) );

  ASSERT_EQ( 4, abc.size() );
}

TEST_F( FieldsTest, FieldsMethodInAssignment ) {
  Fields abc = fields
               ( "a", ActiveRecord::integer )
               ( "b", ActiveRecord::text )
               ( "c", ActiveRecord::floating_point )
               ( "d", ActiveRecord::date );

  ASSERT_EQ( 4, abc.size() );
}
