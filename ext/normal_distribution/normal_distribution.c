#include "normal_distribution.h"

VALUE rb_mNormalDistribution;

void
Init_normal_distribution(void)
{
  rb_mNormalDistribution = rb_define_module("NormalDistribution");
}
