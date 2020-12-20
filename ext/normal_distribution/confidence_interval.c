#include "confidence_interval.h"

static VALUE t_init( VALUE self, VALUE lower_bound, VALUE upper_bound ) {
	double lower = NUM2DBL( lower_bound );
	double upper = NUM2DBL( upper_bound );

	if ( lower > upper ) {
		rb_raise( rb_eArgError, "lower bound must not be greater then upper bound" );
	}

	rb_iv_set( self, "@lower_bound", lower_bound );
	rb_iv_set( self, "@upper_bound", upper_bound );

	return self;
}

static VALUE t_attr_get_upper_bound( VALUE self ) {
	return rb_iv_get( self, "@upper_bound" );
}

static VALUE t_attr_get_lower_bound( VALUE self ) {
	return rb_iv_get( self, "@lower_bound" );
}

void Init_confidence_interval( void ) {
	VALUE rb_mNormalDistribution = rb_define_module( "NormalDistribution" );
	VALUE rb_cConfidenceInterval = rb_define_class_under( rb_mNormalDistribution, "ConfidenceInterval", rb_cObject );

	rb_define_method( rb_cConfidenceInterval, "initialize", t_init, 2 );
	rb_define_method( rb_cConfidenceInterval, "lower_bound", t_attr_get_lower_bound, 0 );
	rb_define_method( rb_cConfidenceInterval, "upper_bound", t_attr_get_upper_bound, 0 );
}
