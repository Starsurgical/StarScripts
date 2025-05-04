#include <idc.idc>

static main() {
  auto ea,x,num_functions,num_decompiled,c;

  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {

    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    num_functions = num_functions + 1;

    c = get_color(ea, CIC_FUNC);
    if (c != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  msg("RESULTS: %d / %d\n", num_decompiled, num_functions);
}
