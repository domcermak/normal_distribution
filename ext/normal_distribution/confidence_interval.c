#include "confidence_interval.h"

static VALUE t_init( VALUE self, VALUE lower_bound, VALUE upper_bound ) {
	Check_Type( lower_bound, NUMERIC );
	Check_Type( upper_bound, NUMERIC );

	rb_iv_set( self, "@lower_bound", lower_bound );
	rb_iv_set( self, "@upper_bound", upper_bound );

	return self;
}

void Init_confidence_interval( void ) {
	VALUE rb_mNormalDistribution = rb_define_module( "NormalDistribution" );
	VALUE rb_cConfidenceInterval = rb_define_class_under( rb_mNormalDistribution, "ConfidenceInterval", rb_cObject );

	rb_define_method( rb_cConfidenceInterval, "initialize", t_init, 2 );
}
