#include "model.h"

static double t_parse_percentage( VALUE percentage ) {
	double perc = NUM2DBL( percentage );

	if ( perc > 100 || perc < 0 ) {
		rb_raise( rb_eArgError, "percentage must be between 0 and 100" );
	}

	return perc;
}

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
	double * squared_diff = ALLOC_N( double, size );

	for ( long i = 0 ; i < size ; ++ i ) {
		squared_diff[i] = pow( mean - data[i], 2 );
	}

	double variance = t_mean( squared_diff, size );
	free( squared_diff );

	return variance;
}

static double t_stddev( double * data, long size, double mean ) {
	return sqrt( t_variance( data, size, mean ) );
}

static double * t_parse_dbl_ary( VALUE ary, long * size ) {
	Check_Type( ary, T_ARRAY );
	long len = RARRAY_LEN( ary );

	if ( len == 0 ) {
		rb_raise( rb_eArgError, "data must not be empty" );
	}

	VALUE * values = RARRAY_PTR( ary );
	double * d_data = ALLOC_N( double, len );

	for ( int i = 0 ; i < len ; ++ i ) {
		d_data[i] = NUM2DBL( values[i] );
	}

	*size = len;

	return d_data;
}

static VALUE t_init( VALUE self, VALUE values ) {
	long size;
	double * data = t_parse_dbl_ary( values, &size );
	double mean = t_mean( data, size );
	double stddev = t_stddev( data, size, mean );

	rb_iv_set( self, "@mean", rb_float_new( mean ) );
	rb_iv_set( self, "@standard_deviation", rb_float_new( stddev ) );
	xfree( data );

	return self;
}

static VALUE t_confidence_interval( VALUE self, VALUE percentage ) {
	double perc = t_parse_percentage( percentage );
	double z = t_z_score( perc );
	double stddev = NUM2DBL( rb_iv_get( self, "@standard_deviation" ) );
	double mean = NUM2DBL( rb_iv_get( self, "@mean" ) );
	double lower_bound = - z * stddev + mean;
	double upper_bound = z * stddev + mean;

	VALUE rb_cConfidenceInterval = rb_path2class( "NormalDistribution::ConfidenceInterval" );
	VALUE interval = rb_funcall(
			rb_cConfidenceInterval, rb_intern( "new" ), 2,
			rb_float_new( lower_bound ),
			rb_float_new( upper_bound )
	);

	return interval;
}

static VALUE t_attr_mean( VALUE self ) {
	return rb_iv_get( self, "@mean" );
}

static VALUE t_attr_stddev( VALUE self ) {
	return rb_iv_get( self, "@standard_deviation" );
}

void Init_model( void ) {
	VALUE rb_mNormalDistribution = rb_path2class( "NormalDistribution" );
	VALUE rb_cModel = rb_define_class_under( rb_mNormalDistribution, "Model", rb_cObject );

	rb_define_method( rb_cModel, "initialize", t_init, 1 );
	rb_define_method( rb_cModel, "confidence_interval", t_confidence_interval, 1 );
	rb_define_method( rb_cModel, "mean", t_attr_mean, 0 );
	rb_define_method( rb_cModel, "standard_deviation", t_attr_stddev, 0 );
}
