#include "normal_distribution.h"

static double t_mean( double * data, long size ) {
	double sum = .0;

	for ( long i = 0 ; i < size ; ++ i ) {
		sum += data[i];
	}

	return sum / size;
}

static double t_z_score( double percentage ) {
	return sqrt( 2 ) * t_erf_inv( percentage / 100 );
}

static double t_variance( double * data, long size, double mean ) {
	double * squared_diff, variance;

	squared_diff = ALLOC_N(
	double, size);
	for ( long i = 0 ; i < size ; ++ i ) {
		squared_diff[i] = pow( mean - data[i], 2 );
	}

	variance = t_mean( squared_diff, size );
	free( squared_diff );

	return variance;
}

static double t_stddev( double * data, long size, double mean ) {
	return sqrt( t_variance( data, size, mean ) );
}

static double * t_ary_to_double( VALUE ary, long * size ) {
	long len = RARRAY_LEN(ary);
	VALUE * values = RARRAY_PTR(ary);
	double * d_data = ALLOC_N(double,len );

	for ( int i = 0 ; i < len ; ++ i ) {
		d_data[i] = NUM2DBL( values[i] );
	}

	*size = len;

	return d_data;
}

static VALUE t_init( VALUE self, VALUE values ) {
	long size;
	double * data = t_ary_to_double( values, &size );
	double mean = t_mean( data, size );
	double stddev = t_stddev( data, size, mean );

	rb_iv_set( self, "@data_size", INT2NUM( size ) );
	rb_iv_set( self, "@mean", rb_float_new( mean ) );
	rb_iv_set( self, "@standard_deviation", rb_float_new( stddev ) );
	free( data );

	return self;
}

static VALUE t_confidence_interval( VALUE self, VALUE percentage ) {
	double z = t_z_score( NUM2DBL( percentage ) );
	double stddev = NUM2DBL( rb_iv_get( self, "@standard_deviation" ) );
	int size = NUM2INT( rb_iv_get( self, "@data_size" ) );
	double delta = z * stddev / sqrt( size );
	double mean = NUM2DBL( rb_iv_get( self, "@mean" ) );
	VALUE pair = rb_ary_new();

	rb_ary_push( pair, rb_float_new( mean - delta ) );
	rb_ary_push( pair, rb_float_new( mean + delta ) );

	return pair;
}

static VALUE t_attr_mean( VALUE self ) {
	return rb_iv_get( self, "@mean" );
}

static VALUE t_attr_stddev( VALUE self ) {
	return rb_iv_get( self, "@standard_deviation" );
}

void Init_normal_distribution( void ) {
	VALUE module = rb_define_module( "NormalDistribution" );
	VALUE model = rb_define_class_under( module, "Model", rb_cObject );

	rb_define_method( model, "initialize", t_init, 1 );
	rb_define_method( model, "confidence_interval", t_confidence_interval, 1 );
	rb_define_method( model, "mean", t_attr_mean, 0 );
	rb_define_method( model, "standard_deviation", t_attr_stddev, 0 );
}
