#include <idc.idc>

static write_result(name, num_decompiled, num_functions) {
  auto ratio, pct, pct_fraction;

  ratio = 100 * 100 * num_decompiled / num_functions;
  pct = ratio / 100;
  pct_fraction = ratio % 100;

  msg("%s: %d / %d (%d.%02d%%)\n", name, num_decompiled, num_functions, pct, pct_fraction);
}

static main() {
  auto ea,x,num_functions,num_decompiled,c,segname;

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
  write_result("RESULTS", num_decompiled, num_functions);


  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {

    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (strstr(segname, "gluBN") != -1) continue;
    if (strstr(segname, "net_bnet") != -1) continue;
    if (strstr(segname, "Modem") != -1) continue;
    if (strstr(segname, "statwrite") != -1) continue;
    if (strstr(segname, "codec") != -1) continue;
    if (strstr(segname, "League") != -1) continue;

    num_functions = num_functions + 1;

    c = get_color(ea, CIC_FUNC);
    if (c != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("EXCLUDING BNET", num_decompiled, num_functions);


  num_functions = 0;
  num_decompiled = 0;
  for ( ea=get_next_func(0); ea != BADADDR; ea=get_next_func(ea) ) {

    x = get_func_flags(ea);
    if ( x & FUNC_LIB ) continue;

    segname = get_segm_name(ea, 1);
    if (strstr(segname, "gluBN") != -1) continue;
    if (strstr(segname, "net_bnet") != -1) continue;
    if (strstr(segname, "Modem") != -1) continue;
    if (strstr(segname, "statwrite") != -1) continue;
    if (strstr(segname, "codec") != -1) continue;
    if (strstr(segname, "League") != -1) continue;

    if (strstr(segname, "gluChat") != -1) continue;
    if (strstr(segname, "gluCreat") != -1) continue;
    if (strstr(segname, "gluJoin") != -1) continue;
    if (strstr(segname, "gluMap") != -1) continue;
    if (strstr(segname, "gluScore") != -1) continue;
    if (strstr(segname, "net_chat") != -1) continue;
    if (strstr(segname, "net_record") != -1) continue;
    if (strstr(segname, "replay") != -1) continue;
    if (strstr(segname, "uiMulti") != -1) continue;

    num_functions = num_functions + 1;

    c = get_color(ea, CIC_FUNC);
    if (c != DEFCOLOR) {
      num_decompiled = num_decompiled + 1;
    }
  }
  write_result("EXCLUDING MULTIPLAYER AND REPLAYS", num_decompiled, num_functions);
}
