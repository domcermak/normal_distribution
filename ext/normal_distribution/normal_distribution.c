#include "normal_distribution.h"

void Init_normal_distribution( void ) {
	rb_define_module( "NormalDistribution" );

	Init_model();
}
